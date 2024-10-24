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
extern ui_state_t current_state;


void push_screen_to_history(ui_state_t state);
ui_state_t pop_screen_from_history();
ui_state_t peek_current_screen();
