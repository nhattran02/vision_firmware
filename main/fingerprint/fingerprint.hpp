#pragma once

#include "gui_guider.h"
#include "__base__.hpp"
#include "button.hpp"

void r307_stop();
void r307_run();
void fingerprint_detect_task_run();
void finger_delete_all();
void test();

extern volatile bool finger_detected;
extern volatile bool is_finger_true;

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
