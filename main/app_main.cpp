#include "wifi.h"
#include "httpd.hpp"
#include "camera.h"

static QueueHandle_t xQueueHttpFrame = NULL;

extern "C" void app_main()
{
    app_wifi_main();

    xQueueHttpFrame = xQueueCreate(2, sizeof(camera_fb_t *));

    register_camera(PIXFORMAT_RGB565, FRAMESIZE_240X240, 2, xQueueHttpFrame);
            
    register_httpd(xQueueHttpFrame, NULL, true);
}
