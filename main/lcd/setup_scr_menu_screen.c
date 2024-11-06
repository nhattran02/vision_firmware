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
#include "widgets_init.h"
#include "custom.h"



void setup_scr_menu_screen(lv_ui *ui)
{
    //Write codes menu_screen
    ui->menu_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->menu_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->menu_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for menu_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_time2
    ui->menu_screen_label_time2 = lv_label_create(ui->menu_screen);
    lv_label_set_text(ui->menu_screen_label_time2, "11:00");
    lv_label_set_long_mode(ui->menu_screen_label_time2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_time2, -31, 8);
    lv_obj_set_size(ui->menu_screen_label_time2, 128, 20);

    //Write style for menu_screen_label_time2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_time2, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_time2, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_time2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_time2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_time2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_time2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_menu_name
    ui->menu_screen_label_menu_name = lv_label_create(ui->menu_screen);
    lv_label_set_text(ui->menu_screen_label_menu_name, "Menu");
    lv_label_set_long_mode(ui->menu_screen_label_menu_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_menu_name, 96, 8);
    lv_obj_set_size(ui->menu_screen_label_menu_name, 128, 17);

    //Write style for menu_screen_label_menu_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_menu_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_menu_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_menu_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_menu_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_menu_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_menu_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_WIFI2
    ui->menu_screen_label_WIFI2 = lv_label_create(ui->menu_screen);
    lv_label_set_text(ui->menu_screen_label_WIFI2, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->menu_screen_label_WIFI2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_WIFI2, 284, 9);
    lv_obj_set_size(ui->menu_screen_label_WIFI2, 41, 20);

    //Write style for menu_screen_label_WIFI2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_WIFI2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_WIFI2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_WIFI2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_WIFI2, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_WIFI2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_WIFI2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_WIFI2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_WIFI2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_WIFI2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_WIFI2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_WIFI2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_WIFI2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_WIFI2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_WIFI2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_BT2
    ui->menu_screen_label_BT2 = lv_label_create(ui->menu_screen);
    lv_label_set_text(ui->menu_screen_label_BT2, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->menu_screen_label_BT2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_BT2, 260, 9);
    lv_obj_set_size(ui->menu_screen_label_BT2, 41, 20);

    //Write style for menu_screen_label_BT2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_BT2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_BT2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_BT2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_BT2, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_BT2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_BT2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_BT2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_BT2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_BT2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_BT2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_BT2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_BT2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_BT2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_BT2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_SD2
    ui->menu_screen_label_SD2 = lv_label_create(ui->menu_screen);
    lv_label_set_text(ui->menu_screen_label_SD2, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->menu_screen_label_SD2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_SD2, 232, 9);
    lv_obj_set_size(ui->menu_screen_label_SD2, 41, 20);

    //Write style for menu_screen_label_SD2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_SD2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_SD2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_SD2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_SD2, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_SD2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_SD2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_SD2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_SD2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_SD2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_SD2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_SD2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_SD2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_SD2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_SD2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_USB2
    ui->menu_screen_label_USB2 = lv_label_create(ui->menu_screen);
    lv_label_set_text(ui->menu_screen_label_USB2, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->menu_screen_label_USB2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_USB2, 205, 9);
    lv_obj_set_size(ui->menu_screen_label_USB2, 41, 20);

    //Write style for menu_screen_label_USB2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_USB2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_USB2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_USB2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_USB2, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_USB2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_USB2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_USB2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_USB2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_USB2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_USB2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_USB2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_USB2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_USB2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_USB2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_btn_esc2
    ui->menu_screen_btn_esc2 = lv_btn_create(ui->menu_screen);
    ui->menu_screen_btn_esc2_label = lv_label_create(ui->menu_screen_btn_esc2);
    lv_label_set_text(ui->menu_screen_btn_esc2_label, "ESC");
    lv_label_set_long_mode(ui->menu_screen_btn_esc2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_screen_btn_esc2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_screen_btn_esc2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_screen_btn_esc2_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_screen_btn_esc2, 17, 204);
    lv_obj_set_size(ui->menu_screen_btn_esc2, 100, 28);

    //Write style for menu_screen_btn_esc2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_btn_esc2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_btn_esc2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_btn_esc2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_screen_btn_esc2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_screen_btn_esc2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_screen_btn_esc2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_screen_btn_esc2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_btn_esc2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_btn_esc2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_btn_esc2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_btn_esc2, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_btn_esc2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_btn_esc2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_btn_ok2
    ui->menu_screen_btn_ok2 = lv_btn_create(ui->menu_screen);
    ui->menu_screen_btn_ok2_label = lv_label_create(ui->menu_screen_btn_ok2);
    lv_label_set_text(ui->menu_screen_btn_ok2_label, "OK");
    lv_label_set_long_mode(ui->menu_screen_btn_ok2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_screen_btn_ok2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_screen_btn_ok2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_screen_btn_ok2_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_screen_btn_ok2, 205, 204);
    lv_obj_set_size(ui->menu_screen_btn_ok2, 100, 28);

    //Write style for menu_screen_btn_ok2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_screen_btn_ok2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_btn_ok2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_btn_ok2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_screen_btn_ok2, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_screen_btn_ok2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_screen_btn_ok2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_screen_btn_ok2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_btn_ok2, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_btn_ok2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_btn_ok2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_btn_ok2, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_btn_ok2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_btn_ok2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_cont_connection
    ui->menu_screen_cont_connection = lv_obj_create(ui->menu_screen);
    lv_obj_set_pos(ui->menu_screen_cont_connection, 10, 79);
    lv_obj_set_size(ui->menu_screen_cont_connection, 300, 35);
    lv_obj_set_scrollbar_mode(ui->menu_screen_cont_connection, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_screen_cont_connection, LV_OBJ_FLAG_CHECKABLE);

    //Write style for menu_screen_cont_connection, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_cont_connection, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_screen_cont_connection, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_screen_cont_connection, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_screen_cont_connection, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_cont_connection, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_cont_connection, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_cont_connection, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_cont_connection, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_cont_connection, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_cont_connection, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_cont_connection, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_cont_connection, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_cont_connection, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->menu_screen_cont_connection, lv_color_hex(0x686464), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->menu_screen_cont_connection, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->menu_screen_cont_connection, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->menu_screen_cont_connection, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->menu_screen_cont_connection, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_connection_symbol
    ui->menu_screen_label_connection_symbol = lv_label_create(ui->menu_screen_cont_connection);
    lv_label_set_text(ui->menu_screen_label_connection_symbol, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->menu_screen_label_connection_symbol, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_connection_symbol, 79, 7);
    lv_obj_set_size(ui->menu_screen_label_connection_symbol, 20, 20);

    //Write style for menu_screen_label_connection_symbol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_connection_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_connection_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_connection_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_connection_symbol, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_connection_symbol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_connection_symbol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_connection_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_connection_symbol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_connection_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_connection_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_connection_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_connection_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_connection_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_connection_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_connection_text
    ui->menu_screen_label_connection_text = lv_label_create(ui->menu_screen_cont_connection);
    lv_label_set_text(ui->menu_screen_label_connection_text, "Connection");
    lv_label_set_long_mode(ui->menu_screen_label_connection_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_connection_text, 98, 7);
    lv_obj_set_size(ui->menu_screen_label_connection_text, 134, 19);

    //Write style for menu_screen_label_connection_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_connection_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_connection_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_connection_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_connection_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_connection_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_connection_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_connection_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_connection_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_connection_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_connection_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_connection_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_connection_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_connection_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_connection_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_cont_attendance
    ui->menu_screen_cont_attendance = lv_obj_create(ui->menu_screen);
    lv_obj_set_pos(ui->menu_screen_cont_attendance, 10, 40);
    lv_obj_set_size(ui->menu_screen_cont_attendance, 300, 35);
    lv_obj_set_scrollbar_mode(ui->menu_screen_cont_attendance, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_screen_cont_attendance, LV_OBJ_FLAG_CHECKABLE);

    //Write style for menu_screen_cont_attendance, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_cont_attendance, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_screen_cont_attendance, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_screen_cont_attendance, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_screen_cont_attendance, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_cont_attendance, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_cont_attendance, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_cont_attendance, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_cont_attendance, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_cont_attendance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_cont_attendance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_cont_attendance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_cont_attendance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_cont_attendance, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->menu_screen_cont_attendance, lv_color_hex(0x686464), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->menu_screen_cont_attendance, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->menu_screen_cont_attendance, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->menu_screen_cont_attendance, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->menu_screen_cont_attendance, 1, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_attendance_symbol
    ui->menu_screen_label_attendance_symbol = lv_label_create(ui->menu_screen_cont_attendance);
    lv_label_set_text(ui->menu_screen_label_attendance_symbol, "" LV_SYMBOL_OK "");
    lv_label_set_long_mode(ui->menu_screen_label_attendance_symbol, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_attendance_symbol, 79, 7);
    lv_obj_set_size(ui->menu_screen_label_attendance_symbol, 20, 20);

    //Write style for menu_screen_label_attendance_symbol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_attendance_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_attendance_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_attendance_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_attendance_symbol, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_attendance_symbol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_attendance_symbol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_attendance_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_attendance_symbol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_attendance_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_attendance_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_attendance_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_attendance_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_attendance_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_attendance_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_attendance_text
    ui->menu_screen_label_attendance_text = lv_label_create(ui->menu_screen_cont_attendance);
    lv_label_set_text(ui->menu_screen_label_attendance_text, "Attendance");
    lv_label_set_long_mode(ui->menu_screen_label_attendance_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_attendance_text, 98, 7);
    lv_obj_set_size(ui->menu_screen_label_attendance_text, 134, 19);

    //Write style for menu_screen_label_attendance_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_attendance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_attendance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_attendance_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_attendance_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_attendance_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_attendance_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_attendance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_attendance_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_attendance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_attendance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_attendance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_attendance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_attendance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_attendance_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_cont_data
    ui->menu_screen_cont_data = lv_obj_create(ui->menu_screen);
    lv_obj_set_pos(ui->menu_screen_cont_data, 10, 119);
    lv_obj_set_size(ui->menu_screen_cont_data, 300, 35);
    lv_obj_set_scrollbar_mode(ui->menu_screen_cont_data, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_screen_cont_data, LV_OBJ_FLAG_CHECKABLE);

    //Write style for menu_screen_cont_data, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_cont_data, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_screen_cont_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_screen_cont_data, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_screen_cont_data, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_cont_data, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_cont_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_cont_data, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_cont_data, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_cont_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_cont_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_cont_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_cont_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_cont_data, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->menu_screen_cont_data, lv_color_hex(0x686464), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->menu_screen_cont_data, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->menu_screen_cont_data, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->menu_screen_cont_data, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->menu_screen_cont_data, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_data_symbol
    ui->menu_screen_label_data_symbol = lv_label_create(ui->menu_screen_cont_data);
    lv_label_set_text(ui->menu_screen_label_data_symbol, "" LV_SYMBOL_DIRECTORY "");
    lv_label_set_long_mode(ui->menu_screen_label_data_symbol, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_data_symbol, 79, 7);
    lv_obj_set_size(ui->menu_screen_label_data_symbol, 20, 20);

    //Write style for menu_screen_label_data_symbol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_data_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_data_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_data_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_data_symbol, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_data_symbol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_data_symbol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_data_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_data_symbol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_data_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_data_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_data_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_data_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_data_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_data_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_data_text
    ui->menu_screen_label_data_text = lv_label_create(ui->menu_screen_cont_data);
    lv_label_set_text(ui->menu_screen_label_data_text, "Data");
    lv_label_set_long_mode(ui->menu_screen_label_data_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_data_text, 98, 7);
    lv_obj_set_size(ui->menu_screen_label_data_text, 134, 19);

    //Write style for menu_screen_label_data_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_data_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_data_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_data_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_data_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_data_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_data_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_data_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_data_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_data_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_data_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_data_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_data_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_data_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_data_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_cont_setting
    ui->menu_screen_cont_setting = lv_obj_create(ui->menu_screen);
    lv_obj_set_pos(ui->menu_screen_cont_setting, 10, 159);
    lv_obj_set_size(ui->menu_screen_cont_setting, 300, 35);
    lv_obj_set_scrollbar_mode(ui->menu_screen_cont_setting, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->menu_screen_cont_setting, LV_OBJ_FLAG_CHECKABLE);

    //Write style for menu_screen_cont_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_cont_setting, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->menu_screen_cont_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->menu_screen_cont_setting, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->menu_screen_cont_setting, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_cont_setting, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_cont_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_screen_cont_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_screen_cont_setting, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_cont_setting, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->menu_screen_cont_setting, lv_color_hex(0x686464), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->menu_screen_cont_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->menu_screen_cont_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->menu_screen_cont_setting, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->menu_screen_cont_setting, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_setting_symbol
    ui->menu_screen_label_setting_symbol = lv_label_create(ui->menu_screen_cont_setting);
    lv_label_set_text(ui->menu_screen_label_setting_symbol, "" LV_SYMBOL_SETTINGS "");
    lv_label_set_long_mode(ui->menu_screen_label_setting_symbol, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_setting_symbol, 79, 7);
    lv_obj_set_size(ui->menu_screen_label_setting_symbol, 20, 20);

    //Write style for menu_screen_label_setting_symbol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_setting_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_setting_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_setting_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_setting_symbol, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_setting_symbol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_setting_symbol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_setting_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_setting_symbol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_setting_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_setting_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_setting_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_setting_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_setting_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_setting_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_screen_label_setting_text
    ui->menu_screen_label_setting_text = lv_label_create(ui->menu_screen_cont_setting);
    lv_label_set_text(ui->menu_screen_label_setting_text, "Setting");
    lv_label_set_long_mode(ui->menu_screen_label_setting_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_screen_label_setting_text, 98, 7);
    lv_obj_set_size(ui->menu_screen_label_setting_text, 134, 19);

    //Write style for menu_screen_label_setting_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_screen_label_setting_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_screen_label_setting_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_screen_label_setting_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_screen_label_setting_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_screen_label_setting_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_screen_label_setting_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_screen_label_setting_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_screen_label_setting_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_screen_label_setting_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_screen_label_setting_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_screen_label_setting_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_screen_label_setting_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_screen_label_setting_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_screen_label_setting_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of menu_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->menu_screen);

    //Init events for screen.
    events_init_menu_screen(ui);
}
