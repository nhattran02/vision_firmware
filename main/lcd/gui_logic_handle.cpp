#include <stdio.h>
#include "lvgl.h"
#include "gui_logic_handle.hpp"
#include "esp_log.h"
#include "gui_guider.h"
extern "C"
{
#include "gui_logic_utils.h"
}
#include "lcd.hpp"
#include "camera.hpp"
#include "sqlite_db.hpp"
#include "r307.h"
#include "fingerprint.hpp"
#include "utils.hpp"
#include "face_recog.hpp"
#include "smartconfig_wifi.hpp"

static const char TAG[] = "gui_logic_handle";

char _default_address[4] = {0xFF, 0xFF, 0xFF, 0xFF};
char _default_password[4] = {0x00, 0x00, 0x00, 0x00};
char _enroll_buffer_id_1[1] = {0x01};
char _enroll_buffer_id_2[1] = {0x02};

// Useful data variables
volatile bool is_attendance_check_in = true; // check out = ~check in state

GUIHandler::GUIHandler(Button *key,
                       QueueHandle_t queue_i,
                       QueueHandle_t queue_o,
                       void (*callback)(camera_fb_t *)) : Frame(queue_i, queue_o, callback),
                                                          key(key)
{
}

void delete_all_data(void)
{
    face->face_delete_all();
    finger_delete_all();
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

static void update_data_selection(uint8_t _data_selected_item)
{
    data_screen_dwnreport_default();
    data_screen_dwntemplate_default();
    data_screen_uptemplate_default();
    data_screen_usrdata_default();

    switch (_data_selected_item)
    {
    case 0:
        data_screen_dwnreport_check();
        break;
    case 1:
        data_screen_usrdata_check();
        break;
    case 2:
        data_screen_dwntemplate_check();
        break;
    case 3:
        data_screen_uptemplate_check();
        break;
    default:
        break;
    }
}


static void update_role_selection(uint8_t _role_selected_item)
{
    role_screen_cont_normal_user_default();
    role_screen_cont_admin_default();

    switch (_role_selected_item)
    {
    case 0:
        role_screen_cont_normal_user_check();
        break;
    case 1:
        role_screen_cont_admin_check();
        break;
    default:
        break;
    }
}

static void update_usr_data_selection(uint16_t _usr_data_selected_item)
{
    for (int i = 0; i < n_users; i++)
    {
        lv_obj_clear_state(list_id_items[i], LV_STATE_CHECKED);
        lv_obj_clear_state(list_name_items[i], LV_STATE_CHECKED);
        lv_obj_clear_state(list_role_items[i], LV_STATE_CHECKED);
    }

    lv_obj_add_state(list_id_items[_usr_data_selected_item], LV_STATE_CHECKED);
    lv_obj_add_state(list_name_items[_usr_data_selected_item], LV_STATE_CHECKED);
    lv_obj_add_state(list_role_items[_usr_data_selected_item], LV_STATE_CHECKED);

    lv_obj_scroll_to_view(list_id_items[_usr_data_selected_item], LV_ANIM_OFF);
    lv_obj_scroll_to_view(list_name_items[_usr_data_selected_item], LV_ANIM_OFF);
    lv_obj_scroll_to_view(list_role_items[_usr_data_selected_item], LV_ANIM_OFF);
}

static void update_usrinfo_selection(uint16_t _usrinfo_selected_item)
{
    usrinfo_screen_finger_default();
    usrinfo_screen_password_default();
    usrinfo_screen_faceid_default();
    usrinfo_screen_role_default();

    switch (_usrinfo_selected_item)
    {
    case 0:
        usrinfo_screen_finger_check();
        break;
    case 1:
        usrinfo_screen_password_check();
        break;
    case 2:
        usrinfo_screen_faceid_check();
        break;
    case 3:
        usrinfo_screen_role_check();
        break;
    default:
        break;
    }
}

void esc_faceid_enroll(void)
{
    update_faceid_to_db(users[usr_data_selected_item].id, 1);
    users[usr_data_selected_item].faceid = 1;
    lcd_on = false;
    faceid_enroll_on = false;
    vTaskDelay(pdMS_TO_TICKS(200));
    enable_lvgl();
    vTaskDelay(pdMS_TO_TICKS(500));

    current_state = STATE_USER_INFO_SCREEN;
    ui_load_scr_animation(&guider_ui, &guider_ui.usrinfo_screen, guider_ui.usrinfo_screen_del, &guider_ui.pw_enter_screen_del, _setup_scr_usrinfo_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
    update_usrinfo_selection(usr_info_selected_item);
    update_data_gui(STATE_USER_INFO_SCREEN);
}

void enter_menu_after_face_recog(void)
{
    lcd_on = false;
    faceid_enroll_on = false;
    authen_on = false;
    vTaskDelay(pdMS_TO_TICKS(200));
    enable_lvgl();
    vTaskDelay(pdMS_TO_TICKS(500));

    current_state = STATE_MENU_SCREEN;
    ui_load_scr_animation(&guider_ui, &guider_ui.menu_screen, guider_ui.menu_screen_del, &guider_ui.menu_screen_del, setup_scr_menu_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
    update_menu_selection(menu_selected_item);
    update_data_gui(STATE_MENU_SCREEN);
}

void GUIHandler::update()
{
    switch (current_state)
    {
    case STATE_MAIN_SCREEN:
    {
        if (this->key->pressed == BUTTON_MENU)
        {
            load_data_from_database_to_users();
            if (check_admin_exist() == false)
            {
                menu_selected_item = 0;
                current_state = STATE_MENU_SCREEN;
                ui_load_scr_animation(&guider_ui, &guider_ui.menu_screen, guider_ui.menu_screen_del, &guider_ui.main_screen_del, setup_scr_menu_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
                update_menu_selection(menu_selected_item);
                update_data_gui(STATE_MENU_SCREEN);
            }
            else  
            {
                disable_lvgl();
                lcd_on = true;
                faceid_enroll_on = false;
                authen_on = true;
                current_state = STATE_CAMERA_SCREEN;                
            }
        }
        else if (this->key->pressed == BUTTON_OK)
        {
            load_data_from_database_to_users();
            disable_lvgl();
            lcd_on = true;
            faceid_enroll_on = false;
            attendance_on = true;
            current_state = STATE_CAMERA_SCREEN;
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
                disable_lvgl();
                lcd_on = true;
                faceid_enroll_on = false;
                current_state = STATE_CAMERA_SCREEN;

                break;
            }
            case 1: // Load STATE_CONNECTION_SCREEN
            {
                current_state = STATE_CONNECTION_SCREEN;
                ui_load_scr_animation(&guider_ui, &guider_ui.connect_screen, guider_ui.connect_screen_del, &guider_ui.menu_screen_del, _setup_scr_connect_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
                update_data_gui(STATE_CONNECTION_SCREEN);
                if (is_wifi_connected == false)
                {
                    goto STATE_CONNECTION;
                }
                break;
            }
            case 2: // Load STATE_DATA_SCREEN
            {
                current_state = STATE_DATA_SCREEN;
                ui_load_scr_animation(&guider_ui, &guider_ui.data_screen, guider_ui.data_screen_del, &guider_ui.menu_screen_del, setup_scr_data_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
                update_data_selection(data_selected_item);
                update_data_gui(STATE_DATA_SCREEN);
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
            authen_on = false;
            lcd_on = false;
            faceid_enroll_on = false;
            current_state = STATE_MAIN_SCREEN;
            ui_load_scr_animation(&guider_ui, &guider_ui.main_screen, guider_ui.main_screen_del, &guider_ui.menu_screen_del, _setup_scr_main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            update_data_gui(STATE_MAIN_SCREEN);
        }
        break;
    }
    case STATE_ATTENDANCE_SCREEN:
    {
        
        break;
    }
    case STATE_CAMERA_SCREEN:
    {
        if (this->key->pressed == BUTTON_ESC)
        {
            lcd_on = false;
            faceid_enroll_on = false;
            authen_on = false;
            attendance_on = false;
            vTaskDelay(pdMS_TO_TICKS(200));
            enable_lvgl();
            vTaskDelay(pdMS_TO_TICKS(200));

            current_state = STATE_MAIN_SCREEN;
            ui_load_scr_animation(&guider_ui, &guider_ui.main_screen, guider_ui.main_screen_del, &guider_ui.main_screen_del, _setup_scr_main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            update_data_gui(STATE_MAIN_SCREEN);

            //current_state = STATE_ATTENDANCE_SCREEN;
            //ui_load_scr_animation(&guider_ui, &guider_ui.attendance_screen, guider_ui.attendance_screen_del, &guider_ui.attendance_screen_del, setup_scr_attendance_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            //update_data_gui(STATE_ATTENDANCE_SCREEN);
        }
        break;
    }
    case STATE_CONNECTION_SCREEN:
    {
        if (this->key->pressed == BUTTON_ESC)
        {
            current_state = STATE_MENU_SCREEN;
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_screen, guider_ui.menu_screen_del, &guider_ui.connect_screen_del, setup_scr_menu_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            update_menu_selection(menu_selected_item);
            update_data_gui(STATE_MENU_SCREEN);
            break;
        }
        STATE_CONNECTION:
        while(1)
        {
            if (is_found_channel)
            {
                lv_label_set_text(guider_ui.connect_screen_label_1, "Found channel");
                is_found_channel = false;
            }
            if (is_got_ssid_pswd)
            {
                lv_label_set_text(guider_ui.connect_screen_label_1, "Got SSID and password");
                is_got_ssid_pswd = false;
            }
            if (is_wifi_connected)
            {
                char buf[100] = {0};
                snprintf(buf, sizeof(buf), "Wi-Fi is connected to %s", ssid);
                lv_label_set_text(guider_ui.connect_screen_label_wifi_status, buf);
                break;
            }
        }

        break;
    }
    case STATE_DATA_SCREEN:
    {
        if (this->key->pressed == BUTTON_UP)
        {
            data_selected_item = (data_selected_item - 1 + 4) % 4;
            update_data_selection(data_selected_item);
        }
        else if (this->key->pressed == BUTTON_DOWN)
        {
            data_selected_item = (data_selected_item + 1) % 4;
            update_data_selection(data_selected_item);
        }
        else if (this->key->pressed == BUTTON_OK)
        {
            switch (data_selected_item)
            {
            case 0: // SAVE REPORT
            {
                save_report_to_csv((const char *)REPORT_CSV);
                current_state = STATE_FINISH_SCREEN;
                ui_load_scr_animation(&guider_ui, &guider_ui.finish_screen, guider_ui.finish_screen_del, &guider_ui.data_screen_del, setup_scr_finish_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
                break;
            }
            case 1: // Scan user data
            {
                load_data_from_database_to_users();
                current_state = STATE_USER_DATA_SCREEN;
                ui_load_scr_animation(&guider_ui, &guider_ui.usrdata_screen, guider_ui.usrdata_screen_del, &guider_ui.data_screen_del, _setup_scr_usrdata_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
                update_usr_data_selection(usr_data_selected_item);
                break;
            }
            case 2: // DOWNLOAD TEMPLATE
            {
                create_csv_template((const char *)TEMPLATE_CSV);
                current_state = STATE_FINISH_SCREEN;
                ui_load_scr_animation(&guider_ui, &guider_ui.finish_screen, guider_ui.finish_screen_del, &guider_ui.data_screen_del, setup_scr_finish_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
                break;
            }
            case 3: // UPLOAD TEMPLATE
            {
                delete_all_data();
                import_csv_to_db((const char *)TEMPLATE_CSV);
                current_state = STATE_FINISH_SCREEN;
                ui_load_scr_animation(&guider_ui, &guider_ui.finish_screen, guider_ui.finish_screen_del, &guider_ui.data_screen_del, setup_scr_finish_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
                break;
            }
            default:
                break;
            }
        }
        else if (this->key->pressed == BUTTON_ESC)
        {
            current_state = STATE_MENU_SCREEN;
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_screen, guider_ui.menu_screen_del, &guider_ui.data_screen_del, setup_scr_menu_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            update_menu_selection(menu_selected_item);
            update_data_gui(STATE_MENU_SCREEN);
        }

        break; 
    }
    case STATE_FINISH_SCREEN:
    {
        if (this->key->pressed == BUTTON_OK)
        {
            current_state = STATE_DATA_SCREEN;
            ui_load_scr_animation(&guider_ui, &guider_ui.data_screen, guider_ui.data_screen_del, &guider_ui.finish_screen_del, setup_scr_data_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            update_data_gui(STATE_DATA_SCREEN);
            update_data_selection(data_selected_item);
        }
        break;
    }
    case STATE_USER_DATA_SCREEN:
    {
        if (this->key->pressed == BUTTON_UP)
        {
            usr_data_selected_item = (usr_data_selected_item - 1 + n_users) % n_users;
            update_usr_data_selection(usr_data_selected_item);
        }
        else if (this->key->pressed == BUTTON_DOWN)
        {
            usr_data_selected_item = (usr_data_selected_item + 1) % n_users;
            update_usr_data_selection(usr_data_selected_item);
        }
        else if (this->key->pressed == BUTTON_OK)
        {
            current_state = STATE_USER_INFO_SCREEN;
            ui_load_scr_animation(&guider_ui, &guider_ui.usrinfo_screen, guider_ui.usrinfo_screen_del, &guider_ui.usrdata_screen_del, _setup_scr_usrinfo_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            update_usrinfo_selection(usr_info_selected_item);
        }
        else if (this->key->pressed == BUTTON_ESC)
        {
            current_state = STATE_DATA_SCREEN;
            ui_load_scr_animation(&guider_ui, &guider_ui.data_screen, guider_ui.data_screen_del, &guider_ui.usrdata_screen_del, setup_scr_data_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            update_data_selection(data_selected_item);
            update_data_gui(STATE_DATA_SCREEN);
        }
        break;
    }
    case STATE_USER_INFO_SCREEN:
    {
        if (this->key->pressed == BUTTON_UP)
        {
            usr_info_selected_item = (usr_info_selected_item - 1 + 4) % 4;
            update_usrinfo_selection(usr_info_selected_item);
        }
        else if (this->key->pressed == BUTTON_DOWN)
        {
            usr_info_selected_item = (usr_info_selected_item + 1) % 4;
            update_usrinfo_selection(usr_info_selected_item);
        }
        else if (this->key->pressed == BUTTON_OK)
        {
            switch (usr_info_selected_item)
            {
            case 0: // Finger
            {
                if (FingerprintDetectTaskHandle != NULL)
                {
                    vTaskDelete(FingerprintDetectTaskHandle);
                }
                r307_stop();
                vTaskDelay(pdMS_TO_TICKS(100));
                r307_run();

                current_state = STATE_FINGERPRINT_ENROLL_SCREEN;
                ui_load_scr_animation(&guider_ui, &guider_ui.finger_enroll_screen, guider_ui.finger_enroll_screen_del, &guider_ui.usrinfo_screen_del, _setup_scr_finger_enroll_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
                update_data_gui(STATE_FINGERPRINT_ENROLL_SCREEN);
                goto FINGERPRINT_ENROLL_STATE;

                break;
            }
            case 1: // Password
            {
                current_state = STATE_PW_ENTER_SCREEN;
                ui_load_scr_animation(&guider_ui, &guider_ui.pw_enter_screen, guider_ui.pw_enter_screen_del, &guider_ui.usrinfo_screen_del, _setup_scr_pw_enter_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
                update_data_gui(STATE_PW_ENTER_SCREEN);
                this->key->pressed = BUTTON_IDLE;
                goto PW_ENTER_STATE;
                break;
            }
            case 2: // FaceID
            {
                disable_lvgl();
                faceid_enroll_on = true;
                lcd_on = true;
                is_face_enrolled = false;
                current_state = STATE_FACEID_ENROLL_SCREEN;

                break;
            }
            case 3: // Role
            {
                current_state = STATE_SET_ROLE_SCREEN;
                ui_load_scr_animation(&guider_ui, &guider_ui.role_screen, guider_ui.role_screen_del, &guider_ui.usrinfo_screen_del, _setup_scr_role_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
                update_role_selection(role_selected_item);
                update_data_gui(STATE_SET_ROLE_SCREEN);
                break;
            }
            default:
                break;
            }
        }
        else if (this->key->pressed == BUTTON_ESC)
        {
            current_state = STATE_USER_DATA_SCREEN;
            ui_load_scr_animation(&guider_ui, &guider_ui.usrdata_screen, guider_ui.usrdata_screen_del, &guider_ui.usrinfo_screen_del, _setup_scr_usrdata_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            update_usr_data_selection(usr_data_selected_item);
            update_data_gui(STATE_USER_DATA_SCREEN);
        }
        break;
    }
    case STATE_FINGERPRINT_ENROLL_SCREEN:
    {
    FINGERPRINT_ENROLL_STATE:
        ESP_LOGE(TAG, "Fingerprint enroll screen");
        while (1)
        {
            lv_obj_set_style_text_color(guider_ui.finger_enroll_screen_label_info_fp, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(guider_ui.finger_enroll_screen_label_info_fp, "Please place your finger");
            while (GenImg(_default_address) != 0)
            {
            }
            uint8_t confirmation_code = Img2Tz(_default_address, _enroll_buffer_id_1);
            if (confirmation_code != 0)
            {
                lv_obj_set_style_text_color(guider_ui.finger_enroll_screen_label_info_fp, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_label_set_text(guider_ui.finger_enroll_screen_label_info_fp, "Failed! Please try again");
                lv_led_set_color(guider_ui.finger_enroll_screen_led_1, lv_color_hex(0x6b6c6b));
                lv_led_set_color(guider_ui.finger_enroll_screen_led_2, lv_color_hex(0x6b6c6b));
                vTaskDelay(pdMS_TO_TICKS(1000));
                continue;
            }
            lv_led_set_color(guider_ui.finger_enroll_screen_led_1, lv_color_hex(0x00239e));
            lv_label_set_text(guider_ui.finger_enroll_screen_label_info_fp, "Please remove your finger");
            while (GenImg(_default_address) == 0)
            {
            }
            lv_label_set_text(guider_ui.finger_enroll_screen_label_info_fp, "Please place your finger again");
            while (GenImg(_default_address) != 0)
            {
            }
            confirmation_code = Img2Tz(_default_address, _enroll_buffer_id_2);
            if (confirmation_code != 0)
            {
                lv_obj_set_style_text_color(guider_ui.finger_enroll_screen_label_info_fp, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_label_set_text(guider_ui.finger_enroll_screen_label_info_fp, "Failed! Please try again");
                lv_led_set_color(guider_ui.finger_enroll_screen_led_1, lv_color_hex(0x6b6c6b));
                lv_led_set_color(guider_ui.finger_enroll_screen_led_2, lv_color_hex(0x6b6c6b));
                vTaskDelay(pdMS_TO_TICKS(1000));
                continue;
            }
            lv_led_set_color(guider_ui.finger_enroll_screen_led_2, lv_color_hex(0x00239e));
            confirmation_code = RegModel(_default_address);
            if (confirmation_code == 0)
            {
                char _page_id[2] = {0};
                _page_id[0] = (char)((users[usr_data_selected_item].id >> 8) & 0xFF);
                _page_id[1] = (char)(users[usr_data_selected_item].id & 0xFF);
                confirmation_code = Store(_default_address, _enroll_buffer_id_1, _page_id);
                if (confirmation_code == 0)
                {
                    lv_label_set_text(guider_ui.finger_enroll_screen_label_info_fp, "Enroll success");
                    update_finger_print_to_db(users[usr_data_selected_item].id, 1);
                    vTaskDelay(pdMS_TO_TICKS(400));
                    users[usr_data_selected_item].fingerprint = 1;
                    break;
                }
                else
                {
                    lv_obj_set_style_text_color(guider_ui.finger_enroll_screen_label_info_fp, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(guider_ui.finger_enroll_screen_label_info_fp, "Failed! Please try again");
                    lv_led_set_color(guider_ui.finger_enroll_screen_led_1, lv_color_hex(0x6b6c6b));
                    lv_led_set_color(guider_ui.finger_enroll_screen_led_2, lv_color_hex(0x6b6c6b));
                    vTaskDelay(pdMS_TO_TICKS(1000));
                }
            }
            else
            {
                lv_obj_set_style_text_color(guider_ui.finger_enroll_screen_label_info_fp, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_label_set_text(guider_ui.finger_enroll_screen_label_info_fp, "Failed! Please try again");
                lv_led_set_color(guider_ui.finger_enroll_screen_led_1, lv_color_hex(0x6b6c6b));
                lv_led_set_color(guider_ui.finger_enroll_screen_led_2, lv_color_hex(0x6b6c6b));
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        }

        // Reactivate the fingerprint detection task
        r307_stop();
        vTaskDelay(pdMS_TO_TICKS(100));
        r307_run();
        fingerprint_detect_task_run();

        // Go back to user info screen
        current_state = STATE_USER_INFO_SCREEN;
        ui_load_scr_animation(&guider_ui, &guider_ui.usrinfo_screen, guider_ui.usrinfo_screen_del, &guider_ui.finger_enroll_screen_del, _setup_scr_usrinfo_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
        update_usrinfo_selection(usr_info_selected_item);
        update_data_gui(STATE_USER_INFO_SCREEN);
        break;
    }
    case STATE_PW_ENTER_SCREEN:
    {
    PW_ENTER_STATE:

        static char password1st[5] = {0};
        static char password2nd[5] = {0};
        static char password1st_hash_hex[65] = {0};
        static char password2nd_hash_hex[65] = {0};
        static int current_pw_length = 0;
        static bool is_first_pw_complete = false;

        if (this->key->pressed >= BUTTON_0 && this->key->pressed <= BUTTON_9)
        {
            if (current_pw_length < 4)
            {
                if (!is_first_pw_complete)
                {
                    password1st[current_pw_length] = '0' + (this->key->pressed - BUTTON_0);
                    ESP_LOGI(TAG, "Password1st: %s", password1st);
                }
                else
                {
                    password2nd[current_pw_length] = '0' + (this->key->pressed - BUTTON_0);
                    ESP_LOGI(TAG, "Password2nd: %s", password2nd);
                }

                current_pw_length++;
                char pwchar_string[5] = {0};
                generate_pwchar_string(pwchar_string, current_pw_length);
                if (!is_first_pw_complete)
                    lv_label_set_text(guider_ui.pw_enter_screen_label_pw_first, pwchar_string);
                else
                    lv_label_set_text(guider_ui.pw_enter_screen_label_pw_second, pwchar_string);
            }
        }
        else if (this->key->pressed == BUTTON_OK)
        {

            if (current_pw_length < 4)
            {
                lv_obj_set_style_text_color(guider_ui.pw_enter_screen_label_nofi, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_label_set_text(guider_ui.pw_enter_screen_label_nofi, "Password must be 4 characters");
                vTaskDelay(pdMS_TO_TICKS(500));
                lv_obj_set_style_text_color(guider_ui.pw_enter_screen_label_nofi, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_label_set_text(guider_ui.pw_enter_screen_label_nofi, "Please enter your password");
            }
            else if (current_pw_length == 4)
            {
                if (!is_first_pw_complete)
                {
                    hash_password(password1st, 4, password1st_hash_hex);

                    memset(password1st, 0, sizeof(password1st));

                    is_first_pw_complete = true;
                    current_pw_length = 0;
                    lv_label_set_text(guider_ui.pw_enter_screen_label_nofi, "Please re-enter your password");
                    lv_obj_set_style_bg_color(guider_ui.pw_enter_screen_label_pw_first, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(guider_ui.pw_enter_screen_label_pw_first, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_color(guider_ui.pw_enter_screen_label_pw_second, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(guider_ui.pw_enter_screen_label_pw_second, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                }
                else
                {
                    hash_password(password2nd, 4, password2nd_hash_hex);

                    memset(password2nd, 0, sizeof(password2nd));

                    if (strcmp(password1st_hash_hex, password2nd_hash_hex) == 0)
                    {
                        ESP_LOGI(TAG, "password1st_hash_hex: %s", password1st_hash_hex);
                        ESP_LOGI(TAG, "password2nd_hash_hex: %s", password2nd_hash_hex);

                        lv_label_set_text(guider_ui.pw_enter_screen_label_nofi, "Password matched! Enroll success");
                        update_password_to_db(users[usr_data_selected_item].id, password1st_hash_hex);
                        strcpy(users[usr_data_selected_item].password_hash, password1st_hash_hex);
                        memset(password1st_hash_hex, 0, sizeof(password1st_hash_hex));
                        memset(password2nd_hash_hex, 0, sizeof(password2nd_hash_hex));
                        vTaskDelay(pdMS_TO_TICKS(500));
                        goto ESC_PW_ENTER_STATE;
                    }
                    else
                    {
                        lv_obj_set_style_text_color(guider_ui.pw_enter_screen_label_nofi, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_label_set_text(guider_ui.pw_enter_screen_label_nofi, "Not matched! Please try again");
                        current_pw_length = 0;
                        memset(password1st, 0, sizeof(password1st));
                        memset(password2nd, 0, sizeof(password2nd));
                        vTaskDelay(pdMS_TO_TICKS(500));
                        lv_obj_set_style_text_color(guider_ui.pw_enter_screen_label_nofi, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_label_set_text(guider_ui.pw_enter_screen_label_pw_first, "----");
                        lv_label_set_text(guider_ui.pw_enter_screen_label_pw_second, "----");
                        lv_label_set_text(guider_ui.pw_enter_screen_label_nofi, "Please enter your password");
                        lv_obj_set_style_bg_color(guider_ui.pw_enter_screen_label_pw_first, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_text_color(guider_ui.pw_enter_screen_label_pw_first, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_bg_color(guider_ui.pw_enter_screen_label_pw_second, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                        lv_obj_set_style_text_color(guider_ui.pw_enter_screen_label_pw_second, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                        is_first_pw_complete = false;
                    }
                }
            }
        }
        else if (this->key->pressed == BUTTON_ESC)
        {
        ESC_PW_ENTER_STATE:
            current_pw_length = 0;
            is_first_pw_complete = false;
            memset(password1st, 0, sizeof(password1st));
            memset(password2nd, 0, sizeof(password2nd));

            // Go back to user info screen
            current_state = STATE_USER_INFO_SCREEN;
            ui_load_scr_animation(&guider_ui, &guider_ui.usrinfo_screen, guider_ui.usrinfo_screen_del, &guider_ui.pw_enter_screen_del, _setup_scr_usrinfo_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            update_usrinfo_selection(usr_info_selected_item);
            update_data_gui(STATE_USER_INFO_SCREEN);
        }
        break;
    }
    case STATE_FACEID_ENROLL_SCREEN:
    {
        if (this->key->pressed == BUTTON_ESC)
        {
            esc_faceid_enroll();
        }
        break;
    }
    case STATE_SET_ROLE_SCREEN:
    {
        if (this->key->pressed == BUTTON_UP)
        {
            role_selected_item = (role_selected_item - 1 + 2) % 2;
            update_role_selection(role_selected_item);
        }
        else if (this->key->pressed == BUTTON_DOWN)
        {
            role_selected_item = (role_selected_item + 1) % 2;
            update_role_selection(role_selected_item);
        }
        else if (this->key->pressed == BUTTON_OK)
        {
            ESP_LOGI(TAG, "Role selected item: %d", role_selected_item);
            if (role_selected_item == 0)
            {
                update_role_to_db(users[usr_data_selected_item].id, 0);
                users[usr_data_selected_item].role = 0;
            }
            else
            {
                update_role_to_db(users[usr_data_selected_item].id, 1);
                users[usr_data_selected_item].role = 1;
            }
        }
        else if (this->key->pressed == BUTTON_ESC)
        {
            current_state = STATE_USER_INFO_SCREEN;
            ui_load_scr_animation(&guider_ui, &guider_ui.usrinfo_screen, guider_ui.usrinfo_screen_del, &guider_ui.role_screen_del, _setup_scr_usrinfo_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 100, false, true);
            update_usrinfo_selection(usr_info_selected_item);
            update_data_gui(STATE_USER_INFO_SCREEN);
        }        
        break;
    }
    }
}
