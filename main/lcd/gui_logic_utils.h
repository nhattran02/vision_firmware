#pragma once

#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <mbedtls/sha256.h>
#include "esp_system.h"
#include "esp_sleep.h"

#define MAX_USERS 500
#define MAX_ATTENDANCE 1000

typedef struct 
{
    int id;
    char name[50];
    char employeeId[20];
    int role;
    int fingerprint;
    int faceid;
    char password_hash[65];
} user_data_t;

typedef struct
{
    char id[5];
    char name[50];
    char date[11];
    char check1[9];
    char check2[9];
    char check3[9];
    char check4[9];
    char check5[9];
    char check6[9];
} attendance_data_t;

extern attendance_data_t attendance_data[MAX_ATTENDANCE];
extern user_data_t users[MAX_USERS];
extern uint16_t n_users;
extern uint16_t n_attendance;
extern TaskHandle_t FingerprintDetectTaskHandle;

extern char ntp_date[11];
extern char ntp_time[9];
extern char ntp_time_no_sec[6];
extern char ntp_day[10];

typedef enum
{
    STATE_MAIN_SCREEN,

    STATE_MENU_SCREEN,

    STATE_ATTENDANCE_SCREEN, 
    
    STATE_CAMERA_SCREEN, 

    STATE_CONNECTION_SCREEN,

    STATE_DATA_SCREEN, 

    STATE_FINISH_SCREEN,

    STATE_USER_DATA_SCREEN, 

    STATE_USER_INFO_SCREEN, 

    STATE_FINGERPRINT_ENROLL_SCREEN,
    
    STATE_PW_ENTER_SCREEN,

    STATE_FACEID_ENROLL_SCREEN, 

    STATE_SET_ROLE_SCREEN,

} ui_state_t;


extern uint8_t menu_selected_item;
extern uint8_t attendance_selected_item;
extern uint8_t data_selected_item;
extern uint8_t role_selected_item;
extern uint16_t usr_data_selected_item;
extern uint8_t usr_info_selected_item;


extern lv_obj_t **list_id_items;
extern lv_obj_t **list_name_items;
extern lv_obj_t **list_role_items;


extern ui_state_t current_state;

void _setup_scr_usrdata_screen(lv_ui *ui);
void _setup_scr_usrinfo_screen(lv_ui *ui);
void _setup_scr_finger_enroll_screen(lv_ui *ui);
void _setup_scr_pw_enter_screen(lv_ui *ui);
void _setup_scr_connect_screen(lv_ui *ui);
void _setup_scr_main_screen(lv_ui *ui);
void _setup_scr_role_screen(lv_ui *ui);

bool compare_passwords(const char *pw1, const char *pw2, size_t length);
void hash_password(const char *password, size_t length, char *output_hash_hex);
void generate_pwchar_string(char *str, int number_of_pwchar);
void update_data_gui(ui_state_t current_screen);
void update_time_to_gui(void);

void menu_screen_setting_default(void);
void menu_screen_data_default(void);
void menu_screen_connection_default(void);
void menu_screen_attendance_default(void);
void menu_screen_setting_check(void);
void menu_screen_data_check(void);
void menu_screen_connection_check(void);
void menu_screen_attendance_check(void);

void attendance_screen_checkout_check(void);
void attendance_screen_checkin_check(void);
void attendance_screen_checkout_default(void);
void attendance_screen_checkin_default(void);

void data_screen_dwnreport_default(void);
void data_screen_dwntemplate_default(void);
void data_screen_uptemplate_default(void);
void data_screen_usrdata_default(void);
void data_screen_dwnreport_check(void);
void data_screen_dwntemplate_check(void);
void data_screen_uptemplate_check(void);
void data_screen_usrdata_check(void);

void usrinfo_screen_finger_check(void);
void usrinfo_screen_password_check(void);
void usrinfo_screen_faceid_check(void);
void usrinfo_screen_role_check(void);
void usrinfo_screen_finger_default(void);
void usrinfo_screen_password_default(void);
void usrinfo_screen_faceid_default(void);
void usrinfo_screen_role_default(void);

void role_screen_cont_normal_user_default(void);
void role_screen_cont_admin_default(void);
void role_screen_cont_normal_user_check(void);
void role_screen_cont_admin_check(void);
