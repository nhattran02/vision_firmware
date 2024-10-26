#pragma once

#include <stdio.h>

typedef enum
{
    STATE_MAIN_SCREEN,
    STATE_MENU_SCREEN,
    STATE_ATTENDANCE,
    STATE_WIRELESS_CONNECTION,
    STATE_DATA_MANAGEMENT,
    STATE_SETTINGS,
    STATE_ATTENDANCE_SCREEN,
    STATE_CHECK_IN,
    STATE_CHECK_OUT
} ui_state_t;

extern uint8_t menu_selected_item;
extern uint8_t attendance_selected_item;

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



