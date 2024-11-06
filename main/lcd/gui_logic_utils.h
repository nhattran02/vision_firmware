#pragma once

#include <stdio.h>

typedef enum
{
    STATE_MAIN_SCREEN,

    STATE_MENU_SCREEN,  //parent
    STATE_ATTENDANCE,  // child of parent
    STATE_WIRELESS_CONNECTION,
    STATE_DATA_MANAGEMENT,
    STATE_SETTINGS,

    STATE_ATTENDANCE_SCREEN, //parent
    STATE_CHECK_IN, //child of parent
    STATE_CHECK_OUT, 

    STATE_CONNECTION_SCREEN,

    STATE_DATA_SCREEN, //parent

    STATE_LOADER_SAVE_REPORT_SCREEN,
    STATE_LOADER_DOWNLOAD_TEMPLATE_SCREEN,
    STATE_LOADER_UPLOAD_TEMPLATE_SCREEN,
    STATE_LOADER_DELETE_DB_SCREEN,
    STATE_FINISH_SCREEN,

} ui_state_t;

extern uint8_t menu_selected_item;
extern uint8_t attendance_selected_item;
extern uint8_t data_selected_item;

extern ui_state_t current_state;

void update_data_gui(ui_state_t current_screen);

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
void data_screen_deletedb_default(void);
void data_screen_dwnreport_check(void);
void data_screen_dwntemplate_check(void);
void data_screen_uptemplate_check(void);
void data_screen_deletedb_check(void);


