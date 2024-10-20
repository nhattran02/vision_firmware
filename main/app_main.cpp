#include "wifi.h"
#include "httpd.hpp"
#include "http_client.hpp"
#include "websocket_client.hpp"
#include "camera.hpp"
#include "lcd.hpp"
#include "face_recog.hpp"
#include "button.hpp"


static const char *TAG = "main";

#define NEW_VERSION 1

static QueueHandle_t xQueueHttpFrame = NULL;

extern "C" void app_main()
{
#if NEW_VERSION
    QueueHandle_t xQueueFrame1 = xQueueCreate(2, sizeof(camera_fb_t *));
    QueueHandle_t xQueueFrame2 = xQueueCreate(2, sizeof(camera_fb_t *));
    QueueHandle_t xQueueFrame3 = xQueueCreate(2, sizeof(camera_fb_t *));

    Button *matrix_button = new Button();
    Camera *camera = new Camera(PIXFORMAT_RGB565, FRAMESIZE_QVGA, 2, xQueueFrame1);
    Face *face = new Face(matrix_button, xQueueFrame1, xQueueFrame2);
    LCD *lcd = new LCD(matrix_button, xQueueFrame2);
    
    matrix_button->attach(face);
    matrix_button->attach(lcd);
    
    lcd->run();
    face->run();
    camera->run();
    matrix_button->run();

    
#else
    app_wifi_main();

    xQueueHttpFrame = xQueueCreate(2, sizeof(camera_fb_t *));

    register_camera(PIXFORMAT_RGB565, FRAMESIZE_QVGA, 2, xQueueHttpFrame);
                        
    register_httpd(xQueueHttpFrame, NULL, true);
    // register_http_client(xQueueHttpFrame, NULL, true);
    // register_websocket_client(xQueueHttpFrame, NULL, true);
#endif // NEW_VERSION
}
