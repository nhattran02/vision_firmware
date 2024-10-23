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


void setup_scr_attendance_screen(lv_ui *ui)
{
    //Write codes attendance_screen
    ui->attendance_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->attendance_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->attendance_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for attendance_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->attendance_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->attendance_screen, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->attendance_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_data2_con
    ui->attendance_screen_data2_con = lv_obj_create(ui->attendance_screen);
    lv_obj_set_pos(ui->attendance_screen_data2_con, 0, 30);
    lv_obj_set_size(ui->attendance_screen_data2_con, 320, 180);
    lv_obj_set_scrollbar_mode(ui->attendance_screen_data2_con, LV_SCROLLBAR_MODE_OFF);

    //Write style for attendance_screen_data2_con, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_data2_con, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->attendance_screen_data2_con, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->attendance_screen_data2_con, lv_color_hex(0x78797a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->attendance_screen_data2_con, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_data2_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_data2_con, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->attendance_screen_data2_con, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->attendance_screen_data2_con, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_data2_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_data2_con, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_data2_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_data2_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_data2_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_esc_label3
    ui->attendance_screen_esc_label3 = lv_label_create(ui->attendance_screen);
    lv_label_set_text(ui->attendance_screen_esc_label3, "ESC\n");
    lv_label_set_long_mode(ui->attendance_screen_esc_label3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_esc_label3, 3, 217);
    lv_obj_set_size(ui->attendance_screen_esc_label3, 127, 17);
    lv_obj_add_flag(ui->attendance_screen_esc_label3, LV_OBJ_FLAG_CLICKABLE);

    //Write style for attendance_screen_esc_label3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_esc_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_esc_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_esc_label3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_esc_label3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_esc_label3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_esc_label3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_esc_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_esc_label3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_esc_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_esc_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_esc_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_esc_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_esc_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_esc_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_ok_label3
    ui->attendance_screen_ok_label3 = lv_label_create(ui->attendance_screen);
    lv_label_set_text(ui->attendance_screen_ok_label3, "OK");
    lv_label_set_long_mode(ui->attendance_screen_ok_label3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_ok_label3, 189, 217);
    lv_obj_set_size(ui->attendance_screen_ok_label3, 127, 17);

    //Write style for attendance_screen_ok_label3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_ok_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_ok_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_ok_label3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_ok_label3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_ok_label3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_ok_label3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_ok_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_ok_label3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_ok_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_ok_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_ok_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_ok_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_ok_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_ok_label3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_menu_attendance
    ui->attendance_screen_menu_attendance = lv_menu_create(ui->attendance_screen);

    //Create sidebar page for menu attendance_screen_menu_attendance
    ui->attendance_screen_menu_attendance_sidebar_page = lv_menu_page_create(ui->attendance_screen_menu_attendance, "Attendance");
    lv_menu_set_sidebar_page(ui->attendance_screen_menu_attendance, ui->attendance_screen_menu_attendance_sidebar_page);
    lv_obj_set_scrollbar_mode(ui->attendance_screen_menu_attendance_sidebar_page, LV_SCROLLBAR_MODE_OFF);

    //Create subpage for attendance_screen_menu_attendance
    ui->attendance_screen_menu_attendance_subpage_1 = lv_menu_page_create(ui->attendance_screen_menu_attendance, NULL);
    ui->attendance_screen_menu_attendance_cont_1 = lv_menu_cont_create(ui->attendance_screen_menu_attendance_sidebar_page);
    ui->attendance_screen_menu_attendance_label_1 = lv_label_create(ui->attendance_screen_menu_attendance_cont_1);
    lv_label_set_text(ui->attendance_screen_menu_attendance_label_1, "Check in");
    lv_obj_set_size(ui->attendance_screen_menu_attendance_label_1, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->attendance_screen_menu_attendance_subpage_1, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->attendance_screen_menu_attendance, ui->attendance_screen_menu_attendance_cont_1, ui->attendance_screen_menu_attendance_subpage_1);

    //Create subpage for attendance_screen_menu_attendance
    ui->attendance_screen_menu_attendance_subpage_2 = lv_menu_page_create(ui->attendance_screen_menu_attendance, NULL);
    ui->attendance_screen_menu_attendance_cont_2 = lv_menu_cont_create(ui->attendance_screen_menu_attendance_sidebar_page);
    ui->attendance_screen_menu_attendance_label_2 = lv_label_create(ui->attendance_screen_menu_attendance_cont_2);
    lv_label_set_text(ui->attendance_screen_menu_attendance_label_2, "Check out");
    lv_obj_set_size(ui->attendance_screen_menu_attendance_label_2, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->attendance_screen_menu_attendance_subpage_2, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->attendance_screen_menu_attendance, ui->attendance_screen_menu_attendance_cont_2, ui->attendance_screen_menu_attendance_subpage_2);
    lv_event_send(ui->attendance_screen_menu_attendance_cont_1, LV_EVENT_CLICKED, NULL);
    lv_obj_set_pos(ui->attendance_screen_menu_attendance, 0, -2);
    lv_obj_set_size(ui->attendance_screen_menu_attendance, 1065, 190);
    lv_obj_set_scrollbar_mode(ui->attendance_screen_menu_attendance, LV_SCROLLBAR_MODE_OFF);

    //Write style for attendance_screen_menu_attendance, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->attendance_screen_menu_attendance, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->attendance_screen_menu_attendance, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->attendance_screen_menu_attendance, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_menu_attendance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_menu_attendance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_attendance_screen_menu_attendance_extra_sidebar_page_main_default
    static lv_style_t style_attendance_screen_menu_attendance_extra_sidebar_page_main_default;
    ui_init_style(&style_attendance_screen_menu_attendance_extra_sidebar_page_main_default);

    lv_style_set_bg_opa(&style_attendance_screen_menu_attendance_extra_sidebar_page_main_default, 255);
    lv_style_set_bg_color(&style_attendance_screen_menu_attendance_extra_sidebar_page_main_default, lv_color_hex(0xf2f2f2));
    lv_style_set_bg_grad_dir(&style_attendance_screen_menu_attendance_extra_sidebar_page_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_radius(&style_attendance_screen_menu_attendance_extra_sidebar_page_main_default, 0);
    lv_obj_add_style(ui->attendance_screen_menu_attendance_sidebar_page, &style_attendance_screen_menu_attendance_extra_sidebar_page_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_attendance_screen_menu_attendance_extra_option_btns_main_default
    static lv_style_t style_attendance_screen_menu_attendance_extra_option_btns_main_default;
    ui_init_style(&style_attendance_screen_menu_attendance_extra_option_btns_main_default);

    lv_style_set_text_color(&style_attendance_screen_menu_attendance_extra_option_btns_main_default, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_attendance_screen_menu_attendance_extra_option_btns_main_default, &lv_font_montserrat_18);
    lv_style_set_text_opa(&style_attendance_screen_menu_attendance_extra_option_btns_main_default, 255);
    lv_style_set_text_align(&style_attendance_screen_menu_attendance_extra_option_btns_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_top(&style_attendance_screen_menu_attendance_extra_option_btns_main_default, 6);
    lv_style_set_pad_bottom(&style_attendance_screen_menu_attendance_extra_option_btns_main_default, 7);
    lv_obj_add_style(ui->attendance_screen_menu_attendance_cont_2, &style_attendance_screen_menu_attendance_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->attendance_screen_menu_attendance_cont_1, &style_attendance_screen_menu_attendance_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_attendance_screen_menu_attendance_extra_option_btns_main_checked
    static lv_style_t style_attendance_screen_menu_attendance_extra_option_btns_main_checked;
    ui_init_style(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked);

    lv_style_set_text_color(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, &lv_font_montserrat_20);
    lv_style_set_text_opa(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, 255);
    lv_style_set_text_align(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, LV_TEXT_ALIGN_CENTER);
    lv_style_set_border_width(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, 2);
    lv_style_set_border_opa(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, 255);
    lv_style_set_border_color(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, lv_color_hex(0x000000));
    lv_style_set_border_side(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, 2);
    lv_style_set_bg_opa(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, 255);
    lv_style_set_bg_color(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, lv_color_hex(0xd2d2d2));
    lv_style_set_bg_grad_dir(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, LV_GRAD_DIR_HOR);
    lv_style_set_bg_grad_color(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, lv_color_hex(0xffffff));
    lv_style_set_bg_main_stop(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, 0);
    lv_style_set_bg_grad_stop(&style_attendance_screen_menu_attendance_extra_option_btns_main_checked, 255);
    lv_obj_add_style(ui->attendance_screen_menu_attendance_cont_2, &style_attendance_screen_menu_attendance_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->attendance_screen_menu_attendance_cont_1, &style_attendance_screen_menu_attendance_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_attendance_screen_menu_attendance_extra_main_title_main_default
    static lv_style_t style_attendance_screen_menu_attendance_extra_main_title_main_default;
    ui_init_style(&style_attendance_screen_menu_attendance_extra_main_title_main_default);

    lv_style_set_text_color(&style_attendance_screen_menu_attendance_extra_main_title_main_default, lv_color_hex(0x3f4657));
    lv_style_set_text_font(&style_attendance_screen_menu_attendance_extra_main_title_main_default, &lv_font_montserrat_24);
    lv_style_set_text_opa(&style_attendance_screen_menu_attendance_extra_main_title_main_default, 255);
    lv_style_set_text_align(&style_attendance_screen_menu_attendance_extra_main_title_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_bg_opa(&style_attendance_screen_menu_attendance_extra_main_title_main_default, 255);
    lv_style_set_bg_color(&style_attendance_screen_menu_attendance_extra_main_title_main_default, lv_color_hex(0xd0d0d0));
    lv_style_set_bg_grad_dir(&style_attendance_screen_menu_attendance_extra_main_title_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_pad_top(&style_attendance_screen_menu_attendance_extra_main_title_main_default, 7);
    lv_style_set_pad_bottom(&style_attendance_screen_menu_attendance_extra_main_title_main_default, 7);
    lv_menu_t * attendance_screen_menu_attendance_menu= (lv_menu_t *)ui->attendance_screen_menu_attendance;
    lv_obj_t * attendance_screen_menu_attendance_title = attendance_screen_menu_attendance_menu->sidebar_header_title;
    lv_obj_set_size(attendance_screen_menu_attendance_title, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_add_style(lv_menu_get_sidebar_header(ui->attendance_screen_menu_attendance), &style_attendance_screen_menu_attendance_extra_main_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);





    //Write codes attendance_screen_btn3_wifi
    ui->attendance_screen_btn3_wifi = lv_btn_create(ui->attendance_screen);
    ui->attendance_screen_btn3_wifi_label = lv_label_create(ui->attendance_screen_btn3_wifi);
    lv_label_set_text(ui->attendance_screen_btn3_wifi_label, "");
    lv_label_set_long_mode(ui->attendance_screen_btn3_wifi_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->attendance_screen_btn3_wifi_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->attendance_screen_btn3_wifi, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->attendance_screen_btn3_wifi_label, LV_PCT(100));
    lv_obj_set_pos(ui->attendance_screen_btn3_wifi, 54, 8);
    lv_obj_set_size(ui->attendance_screen_btn3_wifi, 10, 10);
    lv_obj_add_flag(ui->attendance_screen_btn3_wifi, LV_OBJ_FLAG_CLICKABLE);

    //Write style for attendance_screen_btn3_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->attendance_screen_btn3_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->attendance_screen_btn3_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_btn3_wifi, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_btn3_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_btn3_wifi, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_btn3_wifi, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_btn3_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_btn3_wifi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_wifi3_ok_icon
    ui->attendance_screen_wifi3_ok_icon = lv_img_create(ui->attendance_screen);
    lv_obj_add_flag(ui->attendance_screen_wifi3_ok_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->attendance_screen_wifi3_ok_icon, &_wifi_alpha_24x24);
    lv_img_set_pivot(ui->attendance_screen_wifi3_ok_icon, 50,50);
    lv_img_set_angle(ui->attendance_screen_wifi3_ok_icon, 0);
    lv_obj_set_pos(ui->attendance_screen_wifi3_ok_icon, 14, 3);
    lv_obj_set_size(ui->attendance_screen_wifi3_ok_icon, 24, 24);
    lv_obj_add_flag(ui->attendance_screen_wifi3_ok_icon, LV_OBJ_FLAG_HIDDEN);

    //Write style for attendance_screen_wifi3_ok_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->attendance_screen_wifi3_ok_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->attendance_screen_wifi3_ok_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_wifi3_ok_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->attendance_screen_wifi3_ok_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_wifi3_fail_icon
    ui->attendance_screen_wifi3_fail_icon = lv_img_create(ui->attendance_screen);
    lv_obj_add_flag(ui->attendance_screen_wifi3_fail_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->attendance_screen_wifi3_fail_icon, &_wifi_off_alpha_24x24);
    lv_img_set_pivot(ui->attendance_screen_wifi3_fail_icon, 50,50);
    lv_img_set_angle(ui->attendance_screen_wifi3_fail_icon, 0);
    lv_obj_set_pos(ui->attendance_screen_wifi3_fail_icon, 14, 3);
    lv_obj_set_size(ui->attendance_screen_wifi3_fail_icon, 24, 24);

    //Write style for attendance_screen_wifi3_fail_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->attendance_screen_wifi3_fail_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->attendance_screen_wifi3_fail_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_wifi3_fail_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->attendance_screen_wifi3_fail_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_btn_menu_up3
    ui->attendance_screen_btn_menu_up3 = lv_btn_create(ui->attendance_screen);
    ui->attendance_screen_btn_menu_up3_label = lv_label_create(ui->attendance_screen_btn_menu_up3);
    lv_label_set_text(ui->attendance_screen_btn_menu_up3_label, "");
    lv_label_set_long_mode(ui->attendance_screen_btn_menu_up3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->attendance_screen_btn_menu_up3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->attendance_screen_btn_menu_up3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->attendance_screen_btn_menu_up3_label, LV_PCT(100));
    lv_obj_set_pos(ui->attendance_screen_btn_menu_up3, 233, 18);
    lv_obj_set_size(ui->attendance_screen_btn_menu_up3, 14, 14);
    lv_obj_add_flag(ui->attendance_screen_btn_menu_up3, LV_OBJ_FLAG_CLICKABLE);

    //Write style for attendance_screen_btn_menu_up3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->attendance_screen_btn_menu_up3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->attendance_screen_btn_menu_up3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_btn_menu_up3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_btn_menu_up3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_btn_menu_up3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_btn_menu_up3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_btn_menu_up3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_btn_menu_up3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_btn_menu_dwn3
    ui->attendance_screen_btn_menu_dwn3 = lv_btn_create(ui->attendance_screen);
    ui->attendance_screen_btn_menu_dwn3_label = lv_label_create(ui->attendance_screen_btn_menu_dwn3);
    lv_label_set_text(ui->attendance_screen_btn_menu_dwn3_label, "");
    lv_label_set_long_mode(ui->attendance_screen_btn_menu_dwn3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->attendance_screen_btn_menu_dwn3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->attendance_screen_btn_menu_dwn3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->attendance_screen_btn_menu_dwn3_label, LV_PCT(100));
    lv_obj_set_pos(ui->attendance_screen_btn_menu_dwn3, 296, 18);
    lv_obj_set_size(ui->attendance_screen_btn_menu_dwn3, 12, 14);
    lv_obj_add_flag(ui->attendance_screen_btn_menu_dwn3, LV_OBJ_FLAG_CLICKABLE);

    //Write style for attendance_screen_btn_menu_dwn3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->attendance_screen_btn_menu_dwn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->attendance_screen_btn_menu_dwn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_btn_menu_dwn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_btn_menu_dwn3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_btn_menu_dwn3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_btn_menu_dwn3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_btn_menu_dwn3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_btn_menu_dwn3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of attendance_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->attendance_screen);

    //Init events for screen.
    events_init_attendance_screen(ui);
}
