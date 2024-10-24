#include <stdio.h>
#include "lvgl.h"
#include "wifi.h"
#include "gui_logic_handle.hpp"
#include "esp_log.h"
#include "gui_guider.h"
#include "wifi.h"
extern "C"
{
    #include "gui_logic_utils.h"
}


static const char TAG[] = "gui_logic_handle";


// Useful data variables
volatile bool is_attendance_check_in = false; // check out = ~check in state


GUIHandler::GUIHandler(Button *key,
                       QueueHandle_t queue_i,
                       QueueHandle_t queue_o,
                       void (*callback)(camera_fb_t *)) : Frame(queue_i, queue_o, callback),
                                                          key(key)
{
}

static void update_menu_selection(uint8_t menu_selected_item)
{
    lv_obj_clear_state(guider_ui.menu_screen_menu_root_cont_1, LV_STATE_CHECKED);
    lv_obj_clear_state(guider_ui.menu_screen_menu_root_cont_2, LV_STATE_CHECKED);
    lv_obj_clear_state(guider_ui.menu_screen_menu_root_cont_3, LV_STATE_CHECKED);
    lv_obj_clear_state(guider_ui.menu_screen_menu_root_cont_4, LV_STATE_CHECKED);
    switch (menu_selected_item)
    {
    case 0:
        lv_obj_add_state(guider_ui.menu_screen_menu_root_cont_1, LV_STATE_CHECKED);
        break;
    case 1:
        lv_obj_add_state(guider_ui.menu_screen_menu_root_cont_2, LV_STATE_CHECKED);
        break;
    case 2:
        lv_obj_add_state(guider_ui.menu_screen_menu_root_cont_3, LV_STATE_CHECKED);
        break;
    case 3:
        lv_obj_add_state(guider_ui.menu_screen_menu_root_cont_4, LV_STATE_CHECKED);
        break;
    default:
        break;
    }
}

void GUIHandler::update()
{
    if (this->key->pressed == BUTTON_MENU || this->key->pressed == BUTTON_ESC || this->key->pressed == BUTTON_UP || this->key->pressed == BUTTON_DOWN || this->key->pressed == BUTTON_OK)
    {

        switch (current_state)
        {
        case STATE_MAIN_SCREEN:
        {
            if (this->key->pressed == BUTTON_MENU)
            {
                current_state = STATE_MENU_SCREEN;
                push_screen_to_history(STATE_MENU_SCREEN);
                ui_load_scr_animation(&guider_ui, &guider_ui.menu_screen, guider_ui.menu_screen_del, &guider_ui.main_screen_del, setup_scr_menu_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);
                update_wifi_status(wifi_connected);
            }
            break;
        }
        case STATE_MENU_SCREEN:
        {
            if (this->key->pressed == BUTTON_UP)
            {
                menu_selected_item = (menu_selected_item - 1 + 4) % 4;
                ESP_LOGI(TAG, "menu_selected_item: %d", menu_selected_item);
                update_menu_selection(menu_selected_item);
            }
            else if (this->key->pressed == BUTTON_DOWN)
            {
                menu_selected_item = (menu_selected_item + 1) % 4;
                ESP_LOGI(TAG, "menu_selected_item: %d", menu_selected_item);
                update_menu_selection(menu_selected_item);
            }
            break;
        }
        case STATE_ATTENDANCE:
        {

            break;
        }
        case STATE_WIRELESS_CONNECTION:
        {

            break;
        }
        case STATE_DATA_MANAGEMENT:
        {

            break;
        }
        case STATE_SETTINGS:
        {

            break;
        }
        case STATE_ATTENDANCE_SCREEN:
        {

            break;
        }
        case STATE_CHECK_IN:
        {

            break;
        }
        case STATE_CHECK_OUT:
        {

            break;
        }
        }
    }
}
