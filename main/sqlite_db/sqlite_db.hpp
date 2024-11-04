#pragma once

#include "esp_log.h"
#include "button.hpp"
#include "sdmmc_cmd.h"
#include "__base__.hpp"
#include "driver/sdmmc_host.h"
#include "camera.hpp"
#include "sqlite3.h"


class SQLiteDB : public Observer, public Frame
{
private:
    Button *key;
public:
    SQLiteDB(Button *key,
             QueueHandle_t queue_i = nullptr,
             QueueHandle_t queue_o = nullptr,
             void (*callback)(camera_fb_t *) = esp_camera_fb_return);
    ~SQLiteDB();
    void update();
    void run();
};
