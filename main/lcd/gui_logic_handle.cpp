#include <stdio.h>
#include "lvgl.h"
#include "wifi.h"
#include "gui_logic_handle.hpp"
#include "esp_log.h"
#include "gui_guider.h"
extern "C"
{
    #include "gui_logic_utils.h"
}
#include "lcd.hpp"
#include "camera.hpp"


static const char TAG[] = "gui_logic_handle";


// Useful data variables
volatile bool is_attendance_check_in = true; // check out = ~check in state


GUIHandler::GUIHandler(Button *key,
                       QueueHandle_t queue_i,
                       QueueHandle_t queue_o,
                       void (*callback)(camera_fb_t *)) : Frame(queue_i, queue_o, callback),
                                                          key(key)
{
}

static void update_menu_selection(uint8_t _menu_selected_item)
{
    menu_screen_setting_default();
    menu_screen_data_default();
    menu_screen_connection_default();
    menu_screen_attendance_default();

    switch (_menu_selected_item)
    {
    case 0:
        menu_screen_attendance_check();
        break;
    case 1:
        menu_screen_connection_check();
        break;
    case 2:
        menu_screen_data_check();       
        break;
    case 3:
        menu_screen_setting_check();       
        break;
    default:
        break;
    }
}


static void update_attendance_selection(uint8_t _attendance_selected_item)
{
    attendance_screen_checkin_default();
    attendance_screen_checkout_default();

    switch (_attendance_selected_item)
    {
    case 0:
        attendance_screen_checkin_check();
        break;
    case 1:
        attendance_screen_checkout_check();
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
                setup_scr_menu_screen(&guider_ui);
                lv_scr_load_anim(guider_ui.menu_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 0, 0, true);
                update_data_gui(STATE_MENU_SCREEN);
            }
            break;
        }
        case STATE_MENU_SCREEN:
        {

            if (this->key->pressed == BUTTON_UP)
            {
                menu_selected_item = (menu_selected_item - 1 + 4) % 4;
                update_menu_selection(menu_selected_item);
            }
            else if (this->key->pressed == BUTTON_DOWN)
            {
                menu_selected_item = (menu_selected_item + 1) % 4;
                update_menu_selection(menu_selected_item);
            }
            else if (this->key->pressed == BUTTON_OK)
            {
                switch (menu_selected_item)
                {
                case 0: // Load STATE_ATTENDANCE_SCREEN
                {
                    current_state = STATE_ATTENDANCE_SCREEN;
                    setup_scr_attendance_screen(&guider_ui);
                    lv_scr_load_anim(guider_ui.attendance_screen, LV_SCR_LOAD_ANIM_MOVE_LEFT, 0, 0, true);
                    update_data_gui(STATE_ATTENDANCE_SCREEN);

                    break;
                }
                case 1:
                {
                    
                    break;
                }                
                case 2:
                {
                    
                    break;
                }
                case 3:
                {
                    
                    break;
                }                                
                default:
                    break;
                }
            }
            else if (this->key->pressed == BUTTON_ESC)
            {
                current_state = STATE_MAIN_SCREEN;
                // ui_load_scr_animation(&guider_ui, &guider_ui.main_screen, guider_ui.main_screen_del, &guider_ui.menu_screen_del, setup_scr_main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);

                setup_scr_main_screen(&guider_ui);
                lv_scr_load_anim(guider_ui.main_screen, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 0, 0, true);
                
                update_data_gui(STATE_MAIN_SCREEN);
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
            if (this->key->pressed == BUTTON_UP)
            {
                attendance_selected_item = (attendance_selected_item - 1 + 2) % 2;
                update_attendance_selection(attendance_selected_item);
            }
            else if (this->key->pressed == BUTTON_DOWN)
            {
                attendance_selected_item = (attendance_selected_item + 1) % 2;
                update_attendance_selection(attendance_selected_item);
            }
            else if (this->key->pressed == BUTTON_OK)
            {
                switch (attendance_selected_item)
                {
                case 0:
                {
                    is_attendance_check_in = true;
                    break;
                }
                case 1:
                {
                    is_attendance_check_in = false;
                    break;
                }
                default:
                    break;
                }
                disable_lvgl();
                lcd_switch_on = true;
            }
            else if (this->key->pressed == BUTTON_ESC)
            {

                
            }
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
