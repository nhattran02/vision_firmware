#pragma once

#include <stdio.h>
#include "lvgl.h"
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


#define MAX_USERS 500

typedef struct 
{
    int id;
    char name[40];
    char employeeId[20];
    int role;
    int check[6];  // CHECK1 to CHECK6
} user_data_t;

extern user_data_t users[MAX_USERS];
extern uint16_t n_users;

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

    STATE_FINISH_SCREEN,

} ui_state_t;


extern uint8_t menu_selected_item;
extern uint8_t attendance_selected_item;
extern uint8_t data_selected_item;

extern ui_state_t current_state;

void _setup_scr_usrdata_screen(lv_ui *ui);
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
void data_screen_usrdata_default(void);
void data_screen_dwnreport_check(void);
void data_screen_dwntemplate_check(void);
void data_screen_uptemplate_check(void);
void data_screen_usrdata_check(void);




