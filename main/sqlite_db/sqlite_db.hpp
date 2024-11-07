#pragma once

#include "esp_log.h"
#include "button.hpp"
#include "sdmmc_cmd.h"
#include "__base__.hpp"
#include "driver/sdmmc_host.h"
#include "camera.hpp"
#include "sqlite3.h"
extern "C"
{
    #include "gui_logic_utils.h"
}

void load_data_from_database_to_users(void);
void print_users(void);


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
    void create_csv_template();
    void import_csv_to_db(const char* csv_filename);
    void delete_db();
    void print_db();
    void update();
    void run();
};
