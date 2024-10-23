/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"


void setup_scr_main_screen(lv_ui *ui)
{
    //Write codes main_screen
    ui->main_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->main_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->main_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for main_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_data_con
    ui->main_screen_data_con = lv_obj_create(ui->main_screen);
    lv_obj_set_pos(ui->main_screen_data_con, 0, 30);
    lv_obj_set_size(ui->main_screen_data_con, 320, 180);
    lv_obj_set_scrollbar_mode(ui->main_screen_data_con, LV_SCROLLBAR_MODE_OFF);

    //Write style for main_screen_data_con, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_data_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_data_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_data_con, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_data_con, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_data_con, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_data_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_data_con, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_data_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_data_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_data_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_date
    ui->main_screen_label_date = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_date, "21-10-2024");
    lv_label_set_long_mode(ui->main_screen_label_date, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_date, 3, 217);
    lv_obj_set_size(ui->main_screen_label_date, 127, 17);

    //Write style for main_screen_label_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_date, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_date, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_day
    ui->main_screen_label_day = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_day, "Monday");
    lv_label_set_long_mode(ui->main_screen_label_day, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_day, 189, 217);
    lv_obj_set_size(ui->main_screen_label_day, 127, 17);

    //Write style for main_screen_label_day, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_day, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_day, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_day, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_day, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_day, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_labe_menu_name
    ui->main_screen_labe_menu_name = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_labe_menu_name, "Home");
    lv_label_set_long_mode(ui->main_screen_labe_menu_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_labe_menu_name, 96, 8);
    lv_obj_set_size(ui->main_screen_labe_menu_name, 128, 17);
    lv_obj_add_flag(ui->main_screen_labe_menu_name, LV_OBJ_FLAG_CLICKABLE);

    //Write style for main_screen_labe_menu_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_labe_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_labe_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_labe_menu_name, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_labe_menu_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_labe_menu_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_labe_menu_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_labe_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_labe_menu_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_labe_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_labe_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_labe_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_labe_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_labe_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_labe_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_time
    ui->main_screen_label_time = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_time, "11:00");
    lv_label_set_long_mode(ui->main_screen_label_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_time, 91, 99);
    lv_obj_set_size(ui->main_screen_label_time, 142, 46);

    //Write style for main_screen_label_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_time, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_time, &lv_font_montserrat_48, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_wifi_ok_icon
    ui->main_screen_wifi_ok_icon = lv_img_create(ui->main_screen);
    lv_obj_add_flag(ui->main_screen_wifi_ok_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_screen_wifi_ok_icon, &_wifi_alpha_24x24);
    lv_img_set_pivot(ui->main_screen_wifi_ok_icon, 50,50);
    lv_img_set_angle(ui->main_screen_wifi_ok_icon, 0);
    lv_obj_set_pos(ui->main_screen_wifi_ok_icon, 14, 3);
    lv_obj_set_size(ui->main_screen_wifi_ok_icon, 24, 24);
    lv_obj_add_flag(ui->main_screen_wifi_ok_icon, LV_OBJ_FLAG_HIDDEN);

    //Write style for main_screen_wifi_ok_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_screen_wifi_ok_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_screen_wifi_ok_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_wifi_ok_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_screen_wifi_ok_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);
    
    //Write codes main_screen_wifi_fail_icon
    ui->main_screen_wifi_fail_icon = lv_img_create(ui->main_screen);
    lv_obj_add_flag(ui->main_screen_wifi_fail_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->main_screen_wifi_fail_icon, &_wifi_off_alpha_24x24);
    lv_img_set_pivot(ui->main_screen_wifi_fail_icon, 50,50);
    lv_img_set_angle(ui->main_screen_wifi_fail_icon, 0);
    lv_obj_set_pos(ui->main_screen_wifi_fail_icon, 14, 3);
    lv_obj_set_size(ui->main_screen_wifi_fail_icon, 24, 24);

    //Write style for main_screen_wifi_fail_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->main_screen_wifi_fail_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->main_screen_wifi_fail_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_wifi_fail_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->main_screen_wifi_fail_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_btn_wifi
    ui->main_screen_btn_wifi = lv_btn_create(ui->main_screen);
    ui->main_screen_btn_wifi_label = lv_label_create(ui->main_screen_btn_wifi);
    lv_label_set_text(ui->main_screen_btn_wifi_label, "");
    lv_label_set_long_mode(ui->main_screen_btn_wifi_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->main_screen_btn_wifi_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->main_screen_btn_wifi, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->main_screen_btn_wifi_label, LV_PCT(100));
    lv_obj_set_pos(ui->main_screen_btn_wifi, 54, 8);
    lv_obj_set_size(ui->main_screen_btn_wifi, 10, 10);

    //Write style for main_screen_btn_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_btn_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_btn_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_btn_wifi, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_btn_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_btn_wifi, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_btn_wifi, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_btn_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_btn_wifi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_btn_next_screen
    ui->main_screen_btn_next_screen = lv_btn_create(ui->main_screen);
    ui->main_screen_btn_next_screen_label = lv_label_create(ui->main_screen_btn_next_screen);
    lv_label_set_text(ui->main_screen_btn_next_screen_label, "");
    lv_label_set_long_mode(ui->main_screen_btn_next_screen_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->main_screen_btn_next_screen_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->main_screen_btn_next_screen, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->main_screen_btn_next_screen_label, LV_PCT(100));
    lv_obj_set_pos(ui->main_screen_btn_next_screen, 241, 8);
    lv_obj_set_size(ui->main_screen_btn_next_screen, 10, 10);

    //Write style for main_screen_btn_next_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen_btn_next_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->main_screen_btn_next_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_btn_next_screen, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_btn_next_screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_btn_next_screen, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_btn_next_screen, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_btn_next_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_btn_next_screen, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of main_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->main_screen);

    //Init events for screen.
    events_init_main_screen(ui);
}
