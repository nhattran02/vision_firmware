#include "button.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "esp_timer.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mcp23017.h"

#define PRESS_INTERVAL 500000

static const char *TAG = "button";

Button::Button() : key_configs({{BUTTON_0}, {BUTTON_1}, {BUTTON_2}, {BUTTON_3}, 
                                {BUTTON_4}, {BUTTON_5}, {BUTTON_6}, {BUTTON_7}, 
                                {BUTTON_8}, {BUTTON_9}, {BUTTON_STAR}, {BUTTON_OK}, 
                                {BUTTON_ESC}, {BUTTON_MENU}, {BUTTON_UP}, {BUTTON_DOWN}}),
                                pressed(BUTTON_IDLE), menu(0)
{


}

static void button_task(Button *self)
{
    int64_t backup_time = esp_timer_get_time();
    int64_t last_time = esp_timer_get_time();

    uint8_t menu_count = 0;

    while (true)
    {
        int voltage = 0;

        backup_time = esp_timer_get_time();
        for (auto key_config : self->key_configs)
        {
            if (1) // key is pressed
            {
                if (((backup_time - last_time) > PRESS_INTERVAL))
                {
                    self->pressed = key_config.key;
                    ESP_LOGI(TAG, "Button[%d] is clicked", self->pressed);

                    if (self->pressed == BUTTON_MENU)
                    {
                        self->menu++;
                        self->menu %= (MENU_MOTION_DETECTION + 1);
                    }

                    last_time = backup_time;
                    self->notify();

                    self->pressed = BUTTON_IDLE;
                    break;
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void Button::run()
{
    xTaskCreatePinnedToCore((TaskFunction_t)button_task, TAG, 3 * 1024, this, 5, NULL, 0);
}
