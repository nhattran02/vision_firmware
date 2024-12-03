#pragma once

#include "esp_log.h"
#include "button.hpp"
#include "sdmmc_cmd.h"
#include "__base__.hpp"
#include "driver/sdmmc_host.h"
#include "camera.hpp"

extern sdmmc_card_t *card;

typedef enum
{
    SDCARD_IDLE = 0,
    SDCARD_TAKE_PHOTO = 1,
    SDCARD_START_RECORD = 2,
    SDCARD_STOP_RECORD = 3,
} sdcard_action_t;

void save_fingerprint_to_sdcard(uint8_t *image_buf);


class AppSDCard : public Observer, public Frame
{
private:
    Button *key;

public:
    sdcard_action_t state;
    bool switch_on;

    AppSDCard(QueueHandle_t queue_i = nullptr,
              QueueHandle_t queue_o = nullptr,
              void (*callback)(camera_fb_t *) = esp_camera_fb_return);
    ~AppSDCard();
    void update();
    void run();
    esp_err_t write_file(const char *path, char *data);
    esp_err_t read_file(const char *path, char *data, size_t size);
};
