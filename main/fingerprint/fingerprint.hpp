#pragma once

#include "gui_guider.h"
#include "__base__.hpp"
#include "button.hpp"

class Fingerprint : public Observer, public Frame
{
private:
    Button *key;

public:
    Fingerprint(Button *key,
                QueueHandle_t xQueueFrameI = nullptr,
                QueueHandle_t xQueueFrameO = nullptr,
                void (*callback)(camera_fb_t *) = esp_camera_fb_return);
    
    void update();
    void fingerprint_enroll_run();
    void fingerprint_detect_run();
};
