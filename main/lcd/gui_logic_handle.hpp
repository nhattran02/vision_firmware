#pragma once

#include "gui_guider.h"
#include "__base__.hpp"
#include "camera.hpp"
#include "button.hpp"
#include "lcd.hpp"


class GUIHandler : public Observer, public Frame
{
private:
    Button *key;

public:
    GUIHandler(Button *key,
               QueueHandle_t xQueueFrameI = nullptr,
               QueueHandle_t xQueueFrameO = nullptr,
               void (*callback)(camera_fb_t *) = esp_camera_fb_return);

    void update();
};

