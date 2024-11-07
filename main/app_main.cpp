#include "wifi.h"
#include "httpd.hpp"
#include "http_client.hpp"
#include "websocket_client.hpp"
#include "camera.hpp"
#include "lcd.hpp"
#include "face_recog.hpp"
#include "button.hpp"
#include "gui_logic_handle.hpp"
#include "fingerprint.hpp"
#include "usb_msc.hpp"
#include "sdcard.hpp"
#include "sqlite_db.hpp"
#include "utils.hpp"

static const char *TAG = "main";

#define TEST_R307 0

static QueueHandle_t xQueueHttpFrame = NULL;


extern "C" void app_main()
{

    QueueHandle_t xQueueFrame1 = xQueueCreate(2, sizeof(camera_fb_t *));
    QueueHandle_t xQueueFrame2 = xQueueCreate(2, sizeof(camera_fb_t *));
    QueueHandle_t xQueueFrame3 = xQueueCreate(2, sizeof(camera_fb_t *));

    Button *matrix_button = new Button();
    Camera *camera = new Camera(PIXFORMAT_RGB565, FRAMESIZE_QVGA, 2, xQueueFrame1);
    Face *face = new Face(matrix_button, xQueueFrame1, xQueueFrame2);
    LCD *lcd = new LCD(matrix_button, xQueueFrame2);
    GUIHandler *gui_handler = new GUIHandler(matrix_button);
    // Fingerprint *fingerprint = new Fingerprint(matrix_button, xQueueFrame3);
    AppSDCard *sd_card = new AppSDCard(matrix_button);
    SQLiteDB *sqlite_db = new SQLiteDB(matrix_button);
    // AppUSBMSC *usb_msc = new AppUSBMSC();

    matrix_button->attach(face);
    matrix_button->attach(lcd);
    matrix_button->attach(gui_handler);
    // matrix_button->attach(fingerprint);
    // matrix_button->attach(sd_card);
    
    lcd->run();
    face->run();
    camera->run();
    matrix_button->run();
    // fingerprint->fingerprint_enroll_run();
    // sd_card->run();
    
}
