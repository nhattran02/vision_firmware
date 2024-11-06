#include "face_recog.hpp"
#include <list>
#include "esp_log.h"
#include "esp_camera.h"
#include "dl_image.hpp"
#include "fb_gfx.h"
#include "who_ai_utils.hpp"
#include "lcd.hpp"

static const char TAG[] = "face recognition";

#define RGB565_MASK_RED 0xF800
#define RGB565_MASK_GREEN 0x07E0
#define RGB565_MASK_BLUE 0x001F

#define FRAME_DELAY_NUM 16

static void rgb_print(camera_fb_t *fb, uint32_t color, const char *str)
{
    fb_gfx_print(fb, (fb->width - (strlen(str) * 14)) / 2, 10, color, str);
}

static int rgb_printf(camera_fb_t *fb, uint32_t color, const char *format, ...)
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
    rgb_print(fb, color, temp);
    if (len > 64)
    {
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
        if (lcd_switch_on == true)
        {
            if (this->key->pressed == BUTTON_MENU)
            {
                this->state = FACE_IDLE;
                if (this->switch_on == true)
                    this->switch_on = false;
                else
                    this->switch_on = true;
                ESP_LOGD(TAG, "%s", this->switch_on ? "ON" : "OFF");
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
            if (self->switch_on)
            {
                std::list<dl::detect::result_t> &detect_candidates = self->detector.infer((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3});
                std::list<dl::detect::result_t> &detect_results = self->detector2.infer((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3}, detect_candidates);
    
                if (detect_results.size())
                {
                    // print_detection_result(detect_results);
                    draw_detection_result((uint16_t *)frame->buf, frame->height, frame->width, detect_results);
                }
                
                if (self->state)
                {
                    if (detect_results.size() == 1)
                    {
                        if (self->state == FACE_ENROLL)
                        {
                            self->recognizer->enroll_id((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3}, detect_results.front().keypoint, "", true);
                            ESP_LOGI(TAG, "Enroll ID %d", self->recognizer->get_enrolled_ids().back().id);
                        }
                        else if (self->state == FACE_RECOGNIZE)
                        {
                            self->recognize_result = self->recognizer->recognize((uint16_t *)frame->buf, {(int)frame->height, (int)frame->width, 3}, detect_results.front().keypoint);
                            // print_detection_result(detect_results);
                            ESP_LOGI(TAG, "Similarity: %f", self->recognize_result.similarity);
                            if (self->recognize_result.id > 0)
                                ESP_LOGI(TAG, "Match ID: %d", self->recognize_result.id);
                            else
                                ESP_LOGI(TAG, "Match ID: %d", self->recognize_result.id);
                        }
                    }

                    if (self->state == FACE_DELETE)
                    {
                        vTaskDelay(10);
                        self->recognizer->delete_id(true);
                        ESP_LOGI(TAG, "%d IDs left", self->recognizer->get_enrolled_id_num());
                    }

                    self->state_previous = self->state;
                    self->state = FACE_IDLE;
                    self->frame_count = FRAME_DELAY_NUM;
                }

                // Write result on several frames of image
                if (self->frame_count)
                {
                    switch (self->state_previous)
                    {
                    case FACE_DELETE:
                        rgb_printf(frame, RGB565_MASK_RED, "%d IDs left", self->recognizer->get_enrolled_id_num());
                        break;

                    case FACE_RECOGNIZE:
                        if (self->recognize_result.id > 0)
                            rgb_printf(frame, RGB565_MASK_GREEN, "ID %d", self->recognize_result.id);
                        else
                            rgb_print(frame, RGB565_MASK_RED, "UNKNOWN");
                        break;

                    case FACE_ENROLL:
                        rgb_printf(frame, RGB565_MASK_BLUE, "Enroll: ID %d", self->recognizer->get_enrolled_ids().back().id);
                        break;

                    default:
                        break;
                    }

                    self->frame_count--;
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