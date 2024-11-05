#include "gui_logic_utils.h"
#include "lvgl.h"
#include "wifi.h"
#include "esp_log.h"
#include "gui_guider.h"


#define MAX_SCREEN_HISTORY 10


// Navigation variables
ui_state_t current_state = STATE_MAIN_SCREEN;
uint8_t menu_selected_item = 0;
uint8_t attendance_selected_item = 0;
uint8_t data_selected_item = 0;


void update_data_gui(ui_state_t current_screen)
{
    update_wifi_status(wifi_connected, current_screen);

}

void menu_screen_attendance_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_attendance, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_attendance_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_attendance_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);    
     
}

void menu_screen_connection_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_connection, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_connection_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_connection_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);

}

void menu_screen_data_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_data, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_data_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_data_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);        
}


void menu_screen_setting_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_setting, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_setting_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_setting_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);  
}

void menu_screen_attendance_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_attendance, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_attendance_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_attendance_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void menu_screen_connection_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_connection, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_connection_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_connection_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void menu_screen_data_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_data, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_data_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_data_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}


void menu_screen_setting_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_setting_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_setting_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void attendance_screen_checkin_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.attendance_screen_cont_check_in, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkin_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkin_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void attendance_screen_checkout_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.attendance_screen_cont_check_out, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkout_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkout_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void attendance_screen_checkin_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.attendance_screen_cont_check_in, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkin_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkin_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void attendance_screen_checkout_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.attendance_screen_cont_check_out, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkout_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkout_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}


void data_screen_dwnreport_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_dwnreport, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwnreport_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwnreport_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_dwntemplate_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_dwntemplate, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwntemplate_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwntemplate_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_uptemplate_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_uptemplate, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_uptemplate_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_uptemplate_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_deletedb_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_deletedb, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_deletedb_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_deletedb_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_dwnreport_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_dwnreport, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwnreport_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwnreport_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_dwntemplate_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_dwntemplate, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwntemplate_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwntemplate_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_uptemplate_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_uptemplate, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_uptemplate_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_uptemplate_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_deletedb_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_deletedb, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_deletedb_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_deletedb_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}
