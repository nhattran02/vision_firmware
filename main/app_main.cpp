#include "wifi.h"
#include "httpd.hpp"
#include "http_client.hpp"
#include "websocket_client.hpp"
#include "camera.hpp"
#include "lcd.hpp"
#include "face_recog.hpp"

#define NEW_VERSION 1

static QueueHandle_t xQueueHttpFrame = NULL;

extern "C" void app_main()
{
#if NEW_VERSION
    QueueHandle_t xQueueFrame1 = xQueueCreate(2, sizeof(camera_fb_t *));
    QueueHandle_t xQueueFrame2 = xQueueCreate(2, sizeof(camera_fb_t *));
    QueueHandle_t xQueueFrame3 = xQueueCreate(2, sizeof(camera_fb_t *));

    Camera *camera = new Camera(PIXFORMAT_RGB565, FRAMESIZE_QVGA, 2, xQueueFrame1);
    Face *face = new Face(xQueueFrame1, xQueueFrame2);
    LCD *lcd = new LCD(xQueueFrame2);
            
    lcd->run();
    face->run();
    camera->run();


#else
    app_wifi_main();

    xQueueHttpFrame = xQueueCreate(2, sizeof(camera_fb_t *));

    register_camera(PIXFORMAT_RGB565, FRAMESIZE_QVGA, 2, xQueueHttpFrame);
                        
    register_httpd(xQueueHttpFrame, NULL, true);
    // register_http_client(xQueueHttpFrame, NULL, true);
    // register_websocket_client(xQueueHttpFrame, NULL, true);
#endif
}
