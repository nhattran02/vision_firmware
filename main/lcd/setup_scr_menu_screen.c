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



void setup_scr_menu_screen(lv_ui *ui)
{
    //Write codes menu_screen
    ui->menu_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->menu_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->menu_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_data2_con
    ui->menu_screen_data2_con = lv_obj_create(ui->menu_screen);
    lv_obj_set_pos(ui->menu_screen_data2_con, 0, 30);
    lv_obj_set_size(ui->menu_screen_data2_con, 320, 180);
    lv_obj_set_scrollbar_mode(ui->menu_screen_data2_con, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_screen_data2_con, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_data2_con, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_screen_data2_con, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_screen_data2_con, lv_color_hex(0x78797a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_screen_data2_con, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_data2_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_data2_con, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_data2_con, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_data2_con, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_data2_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_data2_con, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_data2_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_data2_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_data2_con, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_esc_label
    ui->menu_screen_esc_label = lv_label_create(ui->menu_screen);
    lv_label_set_text(ui->menu_screen_esc_label, "ESC\n");
    lv_label_set_long_mode(ui->menu_screen_esc_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_esc_label, 3, 217);
    lv_obj_set_size(ui->menu_screen_esc_label, 127, 17);
    lv_obj_add_flag(ui->menu_screen_esc_label, LV_OBJ_FLAG_CLICKABLE);

    //Write style for menu_screen_esc_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_esc_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_esc_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_esc_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_esc_label, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_esc_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_esc_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_esc_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_esc_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_esc_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_esc_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_esc_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_esc_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_esc_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_esc_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_ok_label
    ui->menu_screen_ok_label = lv_label_create(ui->menu_screen);
    lv_label_set_text(ui->menu_screen_ok_label, "OK");
    lv_label_set_long_mode(ui->menu_screen_ok_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_ok_label, 189, 217);
    lv_obj_set_size(ui->menu_screen_ok_label, 127, 17);

    //Write style for menu_screen_ok_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_ok_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_ok_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_ok_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_ok_label, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_ok_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_ok_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_ok_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_ok_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_ok_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_ok_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_ok_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_ok_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_ok_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_ok_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_menu_root
    ui->menu_screen_menu_root = lv_menu_create(ui->menu_screen);

    //Create sidebar page for menu menu_screen_menu_root
    ui->menu_screen_menu_root_sidebar_page = lv_menu_page_create(ui->menu_screen_menu_root, "Menu");
    lv_menu_set_sidebar_page(ui->menu_screen_menu_root, ui->menu_screen_menu_root_sidebar_page);
    lv_obj_set_scrollbar_mode(ui->menu_screen_menu_root_sidebar_page, LV_SCROLLBAR_MODE_OFF);

    //Create subpage for menu_screen_menu_root
    ui->menu_screen_menu_root_subpage_1 = lv_menu_page_create(ui->menu_screen_menu_root, NULL);
    ui->menu_screen_menu_root_cont_1 = lv_menu_cont_create(ui->menu_screen_menu_root_sidebar_page);
    ui->menu_screen_menu_root_label_1 = lv_label_create(ui->menu_screen_menu_root_cont_1);
    lv_label_set_text(ui->menu_screen_menu_root_label_1, "Attendance");
    lv_obj_set_size(ui->menu_screen_menu_root_label_1, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->menu_screen_menu_root_subpage_1, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->menu_screen_menu_root, ui->menu_screen_menu_root_cont_1, ui->menu_screen_menu_root_subpage_1);

    //Create subpage for menu_screen_menu_root
    ui->menu_screen_menu_root_subpage_2 = lv_menu_page_create(ui->menu_screen_menu_root, NULL);
    ui->menu_screen_menu_root_cont_2 = lv_menu_cont_create(ui->menu_screen_menu_root_sidebar_page);
    ui->menu_screen_menu_root_label_2 = lv_label_create(ui->menu_screen_menu_root_cont_2);
    lv_label_set_text(ui->menu_screen_menu_root_label_2, "Wireless Connection");
    lv_obj_set_size(ui->menu_screen_menu_root_label_2, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->menu_screen_menu_root_subpage_2, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->menu_screen_menu_root, ui->menu_screen_menu_root_cont_2, ui->menu_screen_menu_root_subpage_2);

    //Create subpage for menu_screen_menu_root
    ui->menu_screen_menu_root_subpage_3 = lv_menu_page_create(ui->menu_screen_menu_root, NULL);
    ui->menu_screen_menu_root_cont_3 = lv_menu_cont_create(ui->menu_screen_menu_root_sidebar_page);
    ui->menu_screen_menu_root_label_3 = lv_label_create(ui->menu_screen_menu_root_cont_3);
    lv_label_set_text(ui->menu_screen_menu_root_label_3, "Data Management");
    lv_obj_set_size(ui->menu_screen_menu_root_label_3, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->menu_screen_menu_root_subpage_3, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->menu_screen_menu_root, ui->menu_screen_menu_root_cont_3, ui->menu_screen_menu_root_subpage_3);

    //Create subpage for menu_screen_menu_root
    ui->menu_screen_menu_root_subpage_4 = lv_menu_page_create(ui->menu_screen_menu_root, NULL);
    ui->menu_screen_menu_root_cont_4 = lv_menu_cont_create(ui->menu_screen_menu_root_sidebar_page);
    ui->menu_screen_menu_root_label_4 = lv_label_create(ui->menu_screen_menu_root_cont_4);
    lv_label_set_text(ui->menu_screen_menu_root_label_4, "Setting");
    lv_obj_set_size(ui->menu_screen_menu_root_label_4, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_scrollbar_mode(ui->menu_screen_menu_root_subpage_4, LV_SCROLLBAR_MODE_OFF);
    lv_menu_set_load_page_event(ui->menu_screen_menu_root, ui->menu_screen_menu_root_cont_4, ui->menu_screen_menu_root_subpage_4);
    lv_event_send(ui->menu_screen_menu_root_cont_1, LV_EVENT_CLICKED, NULL);
    lv_obj_set_pos(ui->menu_screen_menu_root, 0, -2);
    lv_obj_set_size(ui->menu_screen_menu_root, 1065, 200);
    lv_obj_set_scrollbar_mode(ui->menu_screen_menu_root, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_screen_menu_root, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_menu_root, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_menu_root, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_menu_root, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_menu_root, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_menu_root, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_menu_screen_menu_root_extra_sidebar_page_main_default
    static lv_style_t style_menu_screen_menu_root_extra_sidebar_page_main_default;
    ui_init_style(&style_menu_screen_menu_root_extra_sidebar_page_main_default);

    lv_style_set_bg_opa(&style_menu_screen_menu_root_extra_sidebar_page_main_default, 255);
    lv_style_set_bg_color(&style_menu_screen_menu_root_extra_sidebar_page_main_default, lv_color_hex(0xf2f2f2));
    lv_style_set_bg_grad_dir(&style_menu_screen_menu_root_extra_sidebar_page_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_radius(&style_menu_screen_menu_root_extra_sidebar_page_main_default, 0);
    lv_obj_add_style(ui->menu_screen_menu_root_sidebar_page, &style_menu_screen_menu_root_extra_sidebar_page_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_menu_screen_menu_root_extra_option_btns_main_default
    static lv_style_t style_menu_screen_menu_root_extra_option_btns_main_default;
    ui_init_style(&style_menu_screen_menu_root_extra_option_btns_main_default);

    lv_style_set_text_color(&style_menu_screen_menu_root_extra_option_btns_main_default, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_menu_screen_menu_root_extra_option_btns_main_default, &lv_font_montserrat_18);
    lv_style_set_text_opa(&style_menu_screen_menu_root_extra_option_btns_main_default, 255);
    lv_style_set_text_align(&style_menu_screen_menu_root_extra_option_btns_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_top(&style_menu_screen_menu_root_extra_option_btns_main_default, 6);
    lv_style_set_pad_bottom(&style_menu_screen_menu_root_extra_option_btns_main_default, 7);
    lv_obj_add_style(ui->menu_screen_menu_root_cont_4, &style_menu_screen_menu_root_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->menu_screen_menu_root_cont_3, &style_menu_screen_menu_root_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->menu_screen_menu_root_cont_2, &style_menu_screen_menu_root_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->menu_screen_menu_root_cont_1, &style_menu_screen_menu_root_extra_option_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_CHECKED for &style_menu_screen_menu_root_extra_option_btns_main_checked
    static lv_style_t style_menu_screen_menu_root_extra_option_btns_main_checked;
    ui_init_style(&style_menu_screen_menu_root_extra_option_btns_main_checked);

    lv_style_set_text_color(&style_menu_screen_menu_root_extra_option_btns_main_checked, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_menu_screen_menu_root_extra_option_btns_main_checked, &lv_font_montserrat_20);
    lv_style_set_text_opa(&style_menu_screen_menu_root_extra_option_btns_main_checked, 255);
    lv_style_set_text_align(&style_menu_screen_menu_root_extra_option_btns_main_checked, LV_TEXT_ALIGN_CENTER);
    lv_style_set_border_width(&style_menu_screen_menu_root_extra_option_btns_main_checked, 2);
    lv_style_set_border_opa(&style_menu_screen_menu_root_extra_option_btns_main_checked, 255);
    lv_style_set_border_color(&style_menu_screen_menu_root_extra_option_btns_main_checked, lv_color_hex(0x000000));
    lv_style_set_border_side(&style_menu_screen_menu_root_extra_option_btns_main_checked, LV_BORDER_SIDE_BOTTOM);
    lv_style_set_radius(&style_menu_screen_menu_root_extra_option_btns_main_checked, 2);
    lv_style_set_bg_opa(&style_menu_screen_menu_root_extra_option_btns_main_checked, 255);
    lv_style_set_bg_color(&style_menu_screen_menu_root_extra_option_btns_main_checked, lv_color_hex(0xd2d2d2));
    lv_style_set_bg_grad_dir(&style_menu_screen_menu_root_extra_option_btns_main_checked, LV_GRAD_DIR_HOR);
    lv_style_set_bg_grad_color(&style_menu_screen_menu_root_extra_option_btns_main_checked, lv_color_hex(0xffffff));
    lv_style_set_bg_main_stop(&style_menu_screen_menu_root_extra_option_btns_main_checked, 0);
    lv_style_set_bg_grad_stop(&style_menu_screen_menu_root_extra_option_btns_main_checked, 255);
    lv_obj_add_style(ui->menu_screen_menu_root_cont_4, &style_menu_screen_menu_root_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->menu_screen_menu_root_cont_3, &style_menu_screen_menu_root_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->menu_screen_menu_root_cont_2, &style_menu_screen_menu_root_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    lv_obj_add_style(ui->menu_screen_menu_root_cont_1, &style_menu_screen_menu_root_extra_option_btns_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);

    //Write style state: LV_STATE_DEFAULT for &style_menu_screen_menu_root_extra_main_title_main_default
    static lv_style_t style_menu_screen_menu_root_extra_main_title_main_default;
    ui_init_style(&style_menu_screen_menu_root_extra_main_title_main_default);

    lv_style_set_text_color(&style_menu_screen_menu_root_extra_main_title_main_default, lv_color_hex(0x3f4657));
    lv_style_set_text_font(&style_menu_screen_menu_root_extra_main_title_main_default, &lv_font_montserrat_24);
    lv_style_set_text_opa(&style_menu_screen_menu_root_extra_main_title_main_default, 255);
    lv_style_set_text_align(&style_menu_screen_menu_root_extra_main_title_main_default, LV_TEXT_ALIGN_CENTER);
    lv_style_set_bg_opa(&style_menu_screen_menu_root_extra_main_title_main_default, 255);
    lv_style_set_bg_color(&style_menu_screen_menu_root_extra_main_title_main_default, lv_color_hex(0xd0d0d0));
    lv_style_set_bg_grad_dir(&style_menu_screen_menu_root_extra_main_title_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_pad_top(&style_menu_screen_menu_root_extra_main_title_main_default, 7);
    lv_style_set_pad_bottom(&style_menu_screen_menu_root_extra_main_title_main_default, 7);
    lv_menu_t * menu_screen_menu_root_menu= (lv_menu_t *)ui->menu_screen_menu_root;
    lv_obj_t * menu_screen_menu_root_title = menu_screen_menu_root_menu->sidebar_header_title;
    lv_obj_set_size(menu_screen_menu_root_title, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_add_style(lv_menu_get_sidebar_header(ui->menu_screen_menu_root), &style_menu_screen_menu_root_extra_main_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);









    //Write codes menu_screen_btn2_wifi
    ui->menu_screen_btn2_wifi = lv_btn_create(ui->menu_screen);
    ui->menu_screen_btn2_wifi_label = lv_label_create(ui->menu_screen_btn2_wifi);
    lv_label_set_text(ui->menu_screen_btn2_wifi_label, "");
    lv_label_set_long_mode(ui->menu_screen_btn2_wifi_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_screen_btn2_wifi_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_screen_btn2_wifi, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_screen_btn2_wifi_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_screen_btn2_wifi, 54, 8);
    lv_obj_set_size(ui->menu_screen_btn2_wifi, 10, 10);

    //Write style for menu_screen_btn2_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_btn2_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_screen_btn2_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_btn2_wifi, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_btn2_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_btn2_wifi, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_btn2_wifi, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_btn2_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_btn2_wifi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_wifi2_ok_icon
    ui->menu_screen_wifi2_ok_icon = lv_img_create(ui->menu_screen);
    lv_obj_add_flag(ui->menu_screen_wifi2_ok_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_screen_wifi2_ok_icon, &_wifi_alpha_24x24);
    lv_img_set_pivot(ui->menu_screen_wifi2_ok_icon, 50,50);
    lv_img_set_angle(ui->menu_screen_wifi2_ok_icon, 0);
    lv_obj_set_pos(ui->menu_screen_wifi2_ok_icon, 14, 3);
    lv_obj_set_size(ui->menu_screen_wifi2_ok_icon, 24, 24);
    lv_obj_add_flag(ui->menu_screen_wifi2_ok_icon, LV_OBJ_FLAG_HIDDEN);

    //Write style for menu_screen_wifi2_ok_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_screen_wifi2_ok_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_screen_wifi2_ok_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_wifi2_ok_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_screen_wifi2_ok_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_wifi2_fail_icon
    ui->menu_screen_wifi2_fail_icon = lv_img_create(ui->menu_screen);
    lv_obj_add_flag(ui->menu_screen_wifi2_fail_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_screen_wifi2_fail_icon, &_wifi_off_alpha_24x24);
    lv_img_set_pivot(ui->menu_screen_wifi2_fail_icon, 50,50);
    lv_img_set_angle(ui->menu_screen_wifi2_fail_icon, 0);
    lv_obj_set_pos(ui->menu_screen_wifi2_fail_icon, 14, 3);
    lv_obj_set_size(ui->menu_screen_wifi2_fail_icon, 24, 24);

    //Write style for menu_screen_wifi2_fail_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_screen_wifi2_fail_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_screen_wifi2_fail_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_wifi2_fail_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_screen_wifi2_fail_icon, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_btn_menu_up
    ui->menu_screen_btn_menu_up = lv_btn_create(ui->menu_screen);
    ui->menu_screen_btn_menu_up_label = lv_label_create(ui->menu_screen_btn_menu_up);
    lv_label_set_text(ui->menu_screen_btn_menu_up_label, "");
    lv_label_set_long_mode(ui->menu_screen_btn_menu_up_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_screen_btn_menu_up_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_screen_btn_menu_up, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_screen_btn_menu_up_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_screen_btn_menu_up, 269, 18);
    lv_obj_set_size(ui->menu_screen_btn_menu_up, 14, 14);
    lv_obj_add_flag(ui->menu_screen_btn_menu_up, LV_OBJ_FLAG_CLICKABLE);

    //Write style for menu_screen_btn_menu_up, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_btn_menu_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_screen_btn_menu_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_btn_menu_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_btn_menu_up, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_btn_menu_up, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_btn_menu_up, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_btn_menu_up, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_btn_menu_up, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_btn_menu_dwn
    ui->menu_screen_btn_menu_dwn = lv_btn_create(ui->menu_screen);
    ui->menu_screen_btn_menu_dwn_label = lv_label_create(ui->menu_screen_btn_menu_dwn);
    lv_label_set_text(ui->menu_screen_btn_menu_dwn_label, "");
    lv_label_set_long_mode(ui->menu_screen_btn_menu_dwn_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_screen_btn_menu_dwn_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_screen_btn_menu_dwn, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_screen_btn_menu_dwn_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_screen_btn_menu_dwn, 296, 18);
    lv_obj_set_size(ui->menu_screen_btn_menu_dwn, 12, 14);
    lv_obj_add_flag(ui->menu_screen_btn_menu_dwn, LV_OBJ_FLAG_CLICKABLE);

    //Write style for menu_screen_btn_menu_dwn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_btn_menu_dwn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_screen_btn_menu_dwn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_btn_menu_dwn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_btn_menu_dwn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_btn_menu_dwn, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_btn_menu_dwn, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_btn_menu_dwn, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_btn_menu_dwn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_btn_next_screen2
    ui->menu_screen_btn_next_screen2 = lv_btn_create(ui->menu_screen);
    ui->menu_screen_btn_next_screen2_label = lv_label_create(ui->menu_screen_btn_next_screen2);
    lv_label_set_text(ui->menu_screen_btn_next_screen2_label, "");
    lv_label_set_long_mode(ui->menu_screen_btn_next_screen2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_screen_btn_next_screen2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_screen_btn_next_screen2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_screen_btn_next_screen2_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_screen_btn_next_screen2, 241, 8);
    lv_obj_set_size(ui->menu_screen_btn_next_screen2, 12, 14);
    lv_obj_add_flag(ui->menu_screen_btn_next_screen2, LV_OBJ_FLAG_CLICKABLE);

    //Write style for menu_screen_btn_next_screen2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_btn_next_screen2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_screen_btn_next_screen2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_btn_next_screen2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_btn_next_screen2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_btn_next_screen2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_btn_next_screen2, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_btn_next_screen2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_btn_next_screen2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of menu_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->menu_screen);

    //Init events for screen.
    events_init_menu_screen(ui);
}
