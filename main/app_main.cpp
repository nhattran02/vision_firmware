#include "smartconfig_wifi.hpp"
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
#include "mqtt_client.hpp"
#include "ntp_time.hpp"

static const char *TAG = "main";

#define TEST_R307 0

static QueueHandle_t xQueueHttpFrame = NULL;
Face *face = NULL;

extern "C" void app_main()
{
    AppSDCard *sd_card = new AppSDCard();
    // AppUSBMSC *usb_msc = new AppUSBMSC();

    vTaskDelay(1000 / portTICK_PERIOD_MS);
    // initialise_wifi();

    // aws_iot_run();

    // vTaskDelay(2000 / portTICK_PERIOD_MS);

    QueueHandle_t xQueueFrame1 = xQueueCreate(2, sizeof(camera_fb_t *));
    QueueHandle_t xQueueFrame2 = xQueueCreate(2, sizeof(camera_fb_t *));

    Button *matrix_button = new Button();
    Camera *camera = new Camera(PIXFORMAT_RGB565, FRAMESIZE_QVGA, 2, xQueueFrame1);
    face = new Face(matrix_button, xQueueFrame1, xQueueFrame2);
    // face->face_delete_all();
    LCD *lcd = new LCD(matrix_button, xQueueFrame2);
    GUIHandler *gui_handler = new GUIHandler(matrix_button);
    Fingerprint *fingerprint = new Fingerprint(matrix_button);
    // finger_delete_all();
    // test();
    SQLiteDB *sqlite_db = new SQLiteDB(matrix_button);

    matrix_button->attach(face);    
    matrix_button->attach(lcd);
    matrix_button->attach(gui_handler);
    matrix_button->attach(fingerprint);

    lcd->run();
    face->run();
    camera->run();
    matrix_button->run();
    fingerprint->fingerprint_detect_run(); 


    // sntp_task_run();

}
