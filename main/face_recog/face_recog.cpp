#include "face_recog.hpp"
#include <list>
#include "esp_log.h"
#include "esp_camera.h"
#include "dl_image.hpp" 
#include "fb_gfx.h"
#include "who_ai_utils.hpp"
#include "lcd.hpp"
#include "gui_logic_utils.h"
#include "utils.hpp"
#include "gui_logic_handle.hpp"
#include "r307.h"
#include "fingerprint.hpp"
#include "sqlite_db.hpp"

static const char TAG[] = "face recognition";

#define RGB565_MASK_RED 0xF800
#define RGB565_MASK_GREEN 0x05A0
#define RGB565_MASK_BLUE 0x001F
#define RGB565_MASK_WHITE 0xFFFF
#define RGB565_MASK_BLACK 0x0000
#define RGB565_MASK_YELLOW 0xFEE0

#define FRAME_DELAY_NUM 16

int stable_face_count = 0;
int stable_face_count_authen = 0;
int stable_face_count_attendance = 0;
int post_enroll_frame_count = 0;
int post_recog_frame_count = 0;
int post_attend_frame_count = 0;
int post_finger_frame_count = 0;

uint16_t *original_frame_buf = nullptr;
std::list<dl::detect::result_t> detect_results;
volatile bool is_face_enrolled = false;
volatile bool is_face_recognized = false;
volatile bool is_authen_success = false;
volatile bool is_attend_success = false;

static void draw_fixed_eye_box(uint16_t *image_ptr, int image_height, int image_width)
{
    dl::image::draw_hollow_rectangle(image_ptr, image_height, image_width, 110, 80, 210, 120, 0x0000FF);
}

static void draw_fixed_face_box(uint16_t *image_ptr, int image_height, int image_width)
{
    dl::image::draw_hollow_rectangle(image_ptr, image_height, image_width, 100, 20, 230, 200, 0x0000FF);
}

void draw_line(uint16_t *image_ptr, int image_height, int image_width, int x0, int y0, int x1, int y1, uint16_t color, int thickness = 1) 
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    for (int t = -thickness / 2; t <= thickness / 2; t++) {
        int x_offset = (dy > dx) ? t : 0; 
        int y_offset = (dx >= dy) ? t : 0;
        int x = x0, y = y0, e2;

        while (true) {
            dl::image::draw_point(image_ptr, image_height, image_width, x + x_offset, y + y_offset, 1, color);
            if (x == x1 && y == y1) break;
            e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x += sx;
            }
            if (e2 < dx) {
                err += dx;
                y += sy;
            }
        }
    }
}


void Face::face_delete_all()
{
    int total_ids = this->recognizer->get_enrolled_id_num();

    if (total_ids <= 0) {
        return;
    }

    for (int id = 0; id < total_ids; id++) 
    {
        this->recognizer->delete_id(true);
    }
    ESP_LOGI(TAG, "All face ids have been deleted.");
}

void draw_detection(uint16_t *image_ptr, int image_height, int image_width, std::list<dl::detect::result_t> &results, int &left_eye_x, int &left_eye_y, int &right_eye_x, int &right_eye_y, int &left_mouth_x, int &left_mouth_y, int &right_mouth_x, int &right_mouth_y, int &nose_x, int &nose_y)
{
    int i = 0;
    for (std::list<dl::detect::result_t>::iterator prediction = results.begin(); prediction != results.end(); prediction++, i++)
    {
        int x_min = DL_MAX(prediction->box[0], 0);
        int y_min = DL_MAX(prediction->box[1], 0);
        int x_max = DL_MAX(prediction->box[2], 0);
        int y_max = DL_MAX(prediction->box[3], 0);        
        int corner_length  = 10;

        draw_line(image_ptr, image_height, image_width, x_min, y_min, x_min + corner_length, y_min, 0x0000FF, 1); 
        draw_line(image_ptr, image_height, image_width, x_min, y_min, x_min, y_min + corner_length, 0x0000FF, 1); 

        draw_line(image_ptr, image_height, image_width, x_max, y_min, x_max - corner_length, y_min, 0x0000FF, 1); 
        draw_line(image_ptr, image_height, image_width, x_max, y_min, x_max, y_min + corner_length, 0x0000FF, 1); 

        draw_line(image_ptr, image_height, image_width, x_min, y_max, x_min + corner_length, y_max, 0x0000FF, 1);
        draw_line(image_ptr, image_height, image_width, x_min, y_max, x_min, y_max - corner_length, 0x0000FF, 1); 

        draw_line(image_ptr, image_height, image_width, x_max, y_max, x_max - corner_length, y_max, 0x0000FF, 1);
        draw_line(image_ptr, image_height, image_width, x_max, y_max, x_max, y_max - corner_length, 0x0000FF, 1);

        if (prediction->keypoint.size() == 10)
        {
            left_eye_x = DL_MAX(prediction->keypoint[0], 0);
            left_eye_y = DL_MAX(prediction->keypoint[1], 0);
            dl::image::draw_point(image_ptr, image_height, image_width, left_eye_x, left_eye_y, 4, 0b0000000011111000); // left eye

            left_mouth_x = DL_MAX(prediction->keypoint[2], 0);
            left_mouth_y = DL_MAX(prediction->keypoint[3], 0);
            dl::image::draw_point(image_ptr, image_height, image_width, left_mouth_x, left_mouth_y, 4, 0b0000000011111000); // mouth left corner

            nose_x = DL_MAX(prediction->keypoint[4], 0);
            nose_y = DL_MAX(prediction->keypoint[5], 0);
            dl::image::draw_point(image_ptr, image_height, image_width, nose_x, nose_y, 4, 0b0000000011111000); // nose

            right_eye_x = DL_MAX(prediction->keypoint[6], 0);
            right_eye_y = DL_MAX(prediction->keypoint[7], 0);
            dl::image::draw_point(image_ptr, image_height, image_width, right_eye_x, right_eye_y, 4, 0b0000000011111000); // right eye

            right_mouth_x = DL_MAX(prediction->keypoint[8], 0);
            right_mouth_y = DL_MAX(prediction->keypoint[9], 0);
            dl::image::draw_point(image_ptr, image_height, image_width, right_mouth_x, right_mouth_y, 4, 0b0000000011111000); // mouth right corner
        }
    }
}

void draw_detection2(uint16_t *image_ptr, int image_height, int image_width, std::list<dl::detect::result_t> &results)
{
    int i = 0;
    for (std::list<dl::detect::result_t>::iterator prediction = results.begin(); prediction != results.end(); prediction++, i++)
    {
        int x_min = DL_MAX(prediction->box[0], 0);
        int y_min = DL_MAX(prediction->box[1], 0);
        int x_max = DL_MAX(prediction->box[2], 0);
        int y_max = DL_MAX(prediction->box[3], 0);        
        int corner_length  = 10;

        draw_line(image_ptr, image_height, image_width, x_min, y_min, x_min + corner_length, y_min, 0x0000FF, 1); 
        draw_line(image_ptr, image_height, image_width, x_min, y_min, x_min, y_min + corner_length, 0x0000FF, 1); 

        draw_line(image_ptr, image_height, image_width, x_max, y_min, x_max - corner_length, y_min, 0x0000FF, 1); 
        draw_line(image_ptr, image_height, image_width, x_max, y_min, x_max, y_min + corner_length, 0x0000FF, 1); 

        draw_line(image_ptr, image_height, image_width, x_min, y_max, x_min + corner_length, y_max, 0x0000FF, 1);
        draw_line(image_ptr, image_height, image_width, x_min, y_max, x_min, y_max - corner_length, 0x0000FF, 1); 
    
        draw_line(image_ptr, image_height, image_width, x_max, y_max, x_max - corner_length, y_max, 0x0000FF, 1);
        draw_line(image_ptr, image_height, image_width, x_max, y_max, x_max, y_max - corner_length, 0x0000FF, 1);
    }
}

bool check_eyes_in_box(int left_eye_x, int left_eye_y, int right_eye_x, int right_eye_y, int x_min, int y_min, int x_max, int y_max)
{
    if (left_eye_x > x_min && left_eye_x < x_max && left_eye_y > y_min && left_eye_y < y_max &&
        right_eye_x > x_min && right_eye_x < x_max && right_eye_y > y_min && right_eye_y < y_max)
    {
        return true;
    }
    return false;
}

bool check_face_in_box(int left_eye_x, int left_eye_y, 
                       int right_eye_x, int right_eye_y, 
                       int nose_x, int nose_y, 
                       int mouth_left_x, int mouth_left_y, 
                       int mouth_right_x, int mouth_right_y, 
                       int x_min, int y_min, int x_max, int y_max)
{
    if (left_eye_x > x_min && left_eye_x < x_max && left_eye_y > y_min && left_eye_y < y_max &&
        right_eye_x > x_min && right_eye_x < x_max && right_eye_y > y_min && right_eye_y < y_max &&
        nose_x > x_min && nose_x < x_max && nose_y > y_min && nose_y < y_max &&
        mouth_left_x > x_min && mouth_left_x < x_max && mouth_left_y > y_min && mouth_left_y < y_max &&
        mouth_right_x > x_min && mouth_right_x < x_max && mouth_right_y > y_min && mouth_right_y < y_max)
    {
        return true;
    }
    return false;
}


static void rgb_print(camera_fb_t *fb, int32_t x, int32_t y, uint32_t color, const char *str)
{
    fb_gfx_print(fb, x, y, color, str);
}

static int rgb_printf(camera_fb_t *fb, int32_t x, int32_t y, uint32_t color, const char *format, ...)
{
    char loc_buf[64];
    char *temp = loc_buf;
    int len;
    va_list arg;
    va_list copy;
    va_start(arg, format);
    va_copy(copy, arg);
    len = vsnprintf(loc_buf, sizeof(loc_buf), format, arg);
    va_end(copy);
    if (len >= sizeof(loc_buf))
    {
        temp = (char *)malloc(len + 1);
        if (temp == NULL)
        {
            return 0;
        }
    }
    vsnprintf(temp, len + 1, format, arg);
    va_end(arg);
    fb_gfx_print(fb, x, y, color, temp);
    if (len > 64)
    {
        free(temp);
    }
    return len;
}

static int frame_printf(camera_fb_t *fb, uint32_t color, int x, int y, const char *format, ...) 
{
    char loc_buf[64];
    char *temp = loc_buf;
    int len;
    va_list arg;
    va_list copy;
    va_start(arg, format);
    va_copy(copy, arg);
    len = vsnprintf(loc_buf, sizeof(loc_buf), format, arg);
    va_end(copy);

    if (len >= sizeof(loc_buf)) 
    {
        temp = (char *)malloc(len + 1);
        if (temp == NULL) 
        {
            return 0; 
        }
    }

    vsnprintf(temp, len + 1, format, arg);
    va_end(arg);
    fb_gfx_print(fb, x, y, color, temp);
    if (len > 64) {
        free(temp);
    }
    return len;
}


Face::Face(Button *key,
           QueueHandle_t queue_i,
           QueueHandle_t queue_o,
           void (*callback)(camera_fb_t *)) : Frame(queue_i, queue_o, callback),
                                              key(key),
                                              detector(0.3F, 0.3F, 10, 0.3F),
                                              detector2(0.4F, 0.3F, 10),
                                              state(FACE_IDLE), // I changed this from FACE_IDLE to FACE_RECOGNIZE
                                              switch_on(false)
{
#if CONFIG_MFN_V1
#if CONFIG_S8
    this->recognizer = new FaceRecognition112V1S8();
#elif CONFIG_S16
    this->recognizer = new FaceRecognition112V1S16();
#endif
#endif

    this->recognizer->set_partition(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "fr");
    this->recognizer->set_ids_from_flash();
}

Face::~Face()
{
    delete this->recognizer;
}

void Face::update()
{
#if 1
    // Parse key
    if (this->key->pressed > BUTTON_IDLE)
    {
        if (lcd_on == true)
        {
            if (this->key->pressed == BUTTON_MENU)
            {
                this->state = FACE_IDLE;
                if (this->switch_on == true)
                    this->switch_on = false;
                else
                    this->switch_on = true;
                ESP_LOGI(TAG, "%s", this->switch_on ? "ON" : "OFF");
            }
            else if (this->key->pressed == BUTTON_OK)
            {
                this->state = FACE_RECOGNIZE;
            }
            else if (this->key->pressed == BUTTON_UP)
            {
                this->state = FACE_ENROLL;
            }
            else if (this->key->pressed == BUTTON_DOWN)
            {
                this->state = FACE_DELETE;
            }
            ESP_LOGI(TAG, "Human face recognition state = %d", this->state);
        }else{
            this->switch_on = false;
        }
    }
#endif
}

static void face_task(Face *self)
{
    ESP_LOGD(TAG, "Start");
    camera_fb_t *frame = nullptr;

    while (true)
    {
        if (self->queue_i == nullptr)
            break;

        if (xQueueReceive(self->queue_i, &frame, portMAX_DELAY))
        {

            if (attendance_on)
            {
                int left_eye_x, left_eye_y, right_eye_x, right_eye_y, left_mouth_x, left_mouth_y, right_mouth_x, right_mouth_y, nose_x, nose_y;
                static int userid = -1;
                if (finger_detected == false)
                {
                    if (stable_face_count_attendance > 4)
                    {
                        if (is_face_recognized == false)
                        {
                            if (detect_results.size() == 1)
                            {
                                self->recognize_result = self->recognizer->recognize((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3}, detect_results.front().keypoint);

                                ESP_LOGI(TAG, "Similarity: %f", self->recognize_result.similarity);

                                const char *name_c_str = self->recognize_result.name.c_str();

                                if (name_c_str != nullptr && name_c_str[0] != '\0')
                                {
                                    userid = atoi(name_c_str);
                                }

                                ESP_LOGI(TAG, "Match ID: %d ", userid);
                                is_face_recognized = true;
                            }
                        }

                        if (userid > 0)
                        {
                            char text[60] = {0};
                            snprintf(text, sizeof(text), "ID-%d  %s", users[userid - 1].id, users[userid - 1].name);
                            dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 200, 340, 240, RGB565_MASK_RED);
                            rgb_printf(frame, 10, 224, RGB565_MASK_WHITE, text);
                            is_attend_success = true;
                            ESP_LOGI(TAG, "Attend success | Face");
                        }
                        else
                        {
                            dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 200, 340, 240, RGB565_MASK_GREEN);
                            rgb_printf(frame, 80, 224, RGB565_MASK_WHITE, "Attend failed");
                            is_attend_success = false;
                            ESP_LOGI(TAG, "Attend failed | Face");
                        }
                        post_attend_frame_count++;
                        if (post_attend_frame_count >= 15)
                        {
                            post_attend_frame_count = 0;
                            stable_face_count_attendance = 0;
                            is_face_recognized = false;
                            ESP_LOGI(TAG, "Attend completed.");
                            if (is_attend_success == true)
                            {
                                // write to database
                                ESP_LOGI(TAG, "Write to database");
                                update_attendance_to_db(users[userid - 1].id, (const char *)users[userid - 1].name, (const char *)ntp_date, (const char *)ntp_time);
                            }
                            userid = -1;
                        }
                    }
                    else
                    {
                        draw_fixed_face_box((uint16_t *)frame->buf, frame->height, frame->width);
                        dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 220, 340, 240, RGB565_MASK_WHITE);
                        rgb_printf(frame, 20, 234, RGB565_MASK_BLACK, "Keep your face in the box");

                        std::list<dl::detect::result_t> &detect_candidates = self->detector.infer((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3});
                        detect_results = self->detector2.infer((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3}, detect_candidates);

                        if (detect_results.size())
                        {
                            draw_detection((uint16_t *)frame->buf, frame->height, frame->width, detect_results, left_eye_x, left_eye_y, right_eye_x, right_eye_y, left_mouth_x, left_mouth_y, right_mouth_x, right_mouth_y, nose_x, nose_y);

                            if (check_face_in_box(left_eye_x, left_eye_y, right_eye_x, right_eye_y, nose_x, nose_y, left_mouth_x, left_mouth_y, right_mouth_x, right_mouth_y, 100, 20, 230, 200) == true)
                            {
                                stable_face_count_attendance++;
                                ESP_LOGI(TAG, "stable_face_count_attendance: %d", stable_face_count_attendance);
                            }
                        }
                    }
                }
                else // is finger detected
                {
                    if (is_finger_true == true && users[_page_id - 1].fingerprint == 1) // match
                    {
                        char text[60] = {0};
                        snprintf(text, sizeof(text), "ID-%d  %s", users[_page_id - 1].id, users[_page_id - 1].name);
                        dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 200, 340, 240, RGB565_MASK_RED);
                        rgb_printf(frame, 10, 224, RGB565_MASK_WHITE, text);
                        ESP_LOGI(TAG, "Attend success | Finger");
                    }
                    else // not match
                    {
                        dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 200, 340, 240, RGB565_MASK_GREEN);
                        rgb_printf(frame, 80, 224, RGB565_MASK_WHITE, "Attend failed");
                        ESP_LOGI(TAG, "Attend failed | Finger");
                    }
                    post_attend_frame_count++;
                    if (post_attend_frame_count >= 15)
                    {
                        post_attend_frame_count = 0;

                        ESP_LOGI(TAG, "Recognize by finger completed.");
                        finger_detected = false;
                        if (is_finger_true == true)
                        {
                            // write to database
                            ESP_LOGI(TAG, "Write to database");
                            update_attendance_to_db(users[_page_id - 1].id, (const char *)users[_page_id - 1].name, (const char *)ntp_date, (const char *)ntp_time);
                        }
                    }
                }
            }
            
            if (faceid_enroll_on == true)
            {

                int left_eye_x, left_eye_y, right_eye_x, right_eye_y, left_mouth_x, left_mouth_y, right_mouth_x, right_mouth_y, nose_x, nose_y;
                if (stable_face_count > 7)
                {
                    dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 220, 340, 240, RGB565_MASK_WHITE);
                    rgb_printf(frame, 80, 234, RGB565_MASK_GREEN, "Enroll success");
                    if (is_face_enrolled == false)
                    {
                        std::string text_id = std::to_string(users[usr_data_selected_item].id);
                        self->recognizer->enroll_id((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3}, detect_results.front().keypoint, text_id, true);
                        ESP_LOGI(TAG, "Enroll ID %d", self->recognizer->get_enrolled_ids().back().id);
                        is_face_enrolled = true;
                    }

                    post_enroll_frame_count++;
                    if (post_enroll_frame_count >= 10)
                    {
                        post_enroll_frame_count = 0;
                        stable_face_count = 0;
                        ESP_LOGI(TAG, "Enroll completed.");
                        esc_faceid_enroll();
                    }
                }
                else
                {
                    draw_fixed_eye_box((uint16_t *)frame->buf, frame->height, frame->width);
                    dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 220, 340, 240, RGB565_MASK_WHITE);
                    rgb_printf(frame, 20, 234, RGB565_MASK_BLACK, "Keep your eyes in the box");

                    std::list<dl::detect::result_t> &detect_candidates = self->detector.infer((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3});
                    detect_results = self->detector2.infer((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3}, detect_candidates);

                    if (detect_results.size())
                    {
                        draw_detection((uint16_t *)frame->buf, frame->height, frame->width, detect_results, left_eye_x, left_eye_y, right_eye_x, right_eye_y, left_mouth_x, left_mouth_y, right_mouth_x, right_mouth_y, nose_x, nose_y);
                        if (check_eyes_in_box(left_eye_x, left_eye_y, right_eye_x, right_eye_y, 110, 80, 210, 120))
                        {
                            stable_face_count++;
                            ESP_LOGI(TAG, "stable_face_count: %d", stable_face_count);
                        }
                    }
                }
            }
            if (authen_on == true)
            {
                int left_eye_x, left_eye_y, right_eye_x, right_eye_y, left_mouth_x, left_mouth_y, right_mouth_x, right_mouth_y, nose_x, nose_y;
                static int userid = -1;
                if (finger_detected == false)
                {
                    if (stable_face_count_authen > 4)
                    {
                        if (is_face_recognized == false)
                        {
                            if (detect_results.size() == 1)
                            {
                                self->recognize_result = self->recognizer->recognize((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3}, detect_results.front().keypoint);

                                ESP_LOGI(TAG, "Similarity: %f", self->recognize_result.similarity);

                                const char *name_c_str = self->recognize_result.name.c_str();

                                if (name_c_str != nullptr && name_c_str[0] != '\0')
                                {
                                    userid = atoi(name_c_str);
                                }

                                ESP_LOGI(TAG, "Match ID: %d ", userid);
                                is_face_recognized = true;
                            }
                        }

                        if (userid >= 0 && users[userid - 1].role == 1)
                        {
                            char text[60] = {0};
                            snprintf(text, sizeof(text), "ID-%d  %s", users[userid - 1].id, users[userid - 1].name);
                            dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 200, 340, 240, RGB565_MASK_RED);
                            rgb_printf(frame, 10, 224, RGB565_MASK_WHITE, text);
                            is_authen_success = true;
                            ESP_LOGI(TAG, "Authen success");
                        }
                        else
                        {
                            dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 200, 340, 240, RGB565_MASK_GREEN);
                            rgb_printf(frame, 80, 224, RGB565_MASK_WHITE, "Authen failed");
                            is_authen_success = false;
                            ESP_LOGI(TAG, "Authen failed");
                        }
                        post_recog_frame_count++;
                        if (post_recog_frame_count >= 15)
                        {
                            post_recog_frame_count = 0;
                            stable_face_count_authen = 0;
                            is_face_recognized = false;
                            userid = -1;
                            ESP_LOGI(TAG, "Recognize completed.");
                            if (is_authen_success == true)
                                enter_menu_after_face_recog();
                        }
                    }
                    else
                    {
                        draw_fixed_face_box((uint16_t *)frame->buf, frame->height, frame->width);
                        dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 220, 340, 240, RGB565_MASK_WHITE);
                        rgb_printf(frame, 20, 234, RGB565_MASK_BLACK, "Keep your face in the box");

                        std::list<dl::detect::result_t> &detect_candidates = self->detector.infer((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3});
                        detect_results = self->detector2.infer((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3}, detect_candidates);

                        if (detect_results.size())
                        {
                            draw_detection((uint16_t *)frame->buf, frame->height, frame->width, detect_results, left_eye_x, left_eye_y, right_eye_x, right_eye_y, left_mouth_x, left_mouth_y, right_mouth_x, right_mouth_y, nose_x, nose_y);

                            if (check_face_in_box(left_eye_x, left_eye_y, right_eye_x, right_eye_y, nose_x, nose_y, left_mouth_x, left_mouth_y, right_mouth_x, right_mouth_y, 100, 20, 230, 200) == true)
                            {
                                stable_face_count_authen++;
                                ESP_LOGI(TAG, "stable_face_count_authen: %d", stable_face_count_authen);
                            }
                        }
                    }
                }
                else // is finger detected
                {
                    if (is_finger_true == true && users[_page_id - 1].fingerprint == 1) // match
                    {
                        char text[60] = {0};
                        snprintf(text, sizeof(text), "ID-%d  %s", users[_page_id - 1].id, users[_page_id - 1].name);
                        dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 200, 340, 240, RGB565_MASK_RED);
                        rgb_printf(frame, 10, 224, RGB565_MASK_WHITE, text);
                        ESP_LOGI(TAG, "Authen success");
                    }
                    else // not match
                    {
                        dl::image::draw_filled_rectangle((uint16_t *)frame->buf, frame->height, frame->width, 0, 200, 340, 240, RGB565_MASK_GREEN);
                        rgb_printf(frame, 80, 224, RGB565_MASK_WHITE, "Authen failed");
                        ESP_LOGI(TAG, "Authen failed");
                    }
                    post_finger_frame_count++;
                    if (post_finger_frame_count >= 15)
                    {
                        post_finger_frame_count = 0;

                        ESP_LOGI(TAG, "Recognize by finger completed.");
                        finger_detected = false;
                        if (is_finger_true == true)
                            enter_menu_after_face_recog();
                    }
                }
            }

            if (self->queue_o)
                xQueueSend(self->queue_o, &frame, portMAX_DELAY);
            else
                self->callback(frame);
        }
    }
    ESP_LOGD(TAG, "Stop");
    vTaskDelete(NULL);
}


void Face::run()
{
    xTaskCreatePinnedToCore((TaskFunction_t)face_task, TAG, 4 * 1024, this, 5, NULL, 1);
}
