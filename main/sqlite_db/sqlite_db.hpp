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

#define TEMPLATE_CSV "/sdcard/template.csv"

void load_data_from_database_to_users(void);
void update_finger_print_to_db(int id, int value);
void update_faceid_to_db(int id, int value);
void update_role_to_db(int id, int value);
bool check_admin_exist();
void update_password_to_db(int id, const char *password_hash);
void print_users(void);
void create_csv_template(const char *csv_filename);
void import_csv_to_db(const char* csv_filename);

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
    
    void delete_db();
    void print_employee_db();
    void print_attendance_db();
    void update();
    void run();
};
