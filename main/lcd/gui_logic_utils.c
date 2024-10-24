#include "gui_logic_utils.h"
#include "lvgl.h"
#include "wifi.h"
#include "esp_log.h"
#include "gui_guider.h"


#define MAX_SCREEN_HISTORY 10


// Navigation variables
ui_state_t screen_history[MAX_SCREEN_HISTORY];
uint8_t screen_history_index = 0;
ui_state_t current_state = STATE_MAIN_SCREEN;
uint8_t menu_selected_item = 0;

void push_screen_to_history(ui_state_t state)
{
    if (screen_history_index < MAX_SCREEN_HISTORY)
    {
        screen_history[screen_history_index] = state;
        screen_history_index++;
    }
}

ui_state_t pop_screen_from_history()
{
    if (screen_history_index > 0)
    {
        screen_history_index--;
        return screen_history[screen_history_index];
    }
    return STATE_MAIN_SCREEN;
}

ui_state_t peek_current_screen()
{
    if (screen_history_index > 0)
    {
        return screen_history[screen_history_index - 1]; // Lấy màn hình hiện tại từ stack
    }
    return STATE_MAIN_SCREEN; // Trả về màn hình mặc định nếu stack trống
}

