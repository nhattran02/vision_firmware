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



void setup_scr_connect_screen(lv_ui *ui)
{
    //Write codes connect_screen
    ui->connect_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->connect_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->connect_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->connect_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for connect_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->connect_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->connect_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->connect_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_time9
    ui->connect_screen_label_time9 = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_time9, "11:00");
    lv_label_set_long_mode(ui->connect_screen_label_time9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_time9, -31, 8);
    lv_obj_set_size(ui->connect_screen_label_time9, 128, 20);

    //Write style for connect_screen_label_time9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_time9, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_time9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_time9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_time9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_time9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_connect_name
    ui->connect_screen_label_connect_name = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_connect_name, "Wi-Fi");
    lv_label_set_long_mode(ui->connect_screen_label_connect_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_connect_name, 97, 8);
    lv_obj_set_size(ui->connect_screen_label_connect_name, 128, 17);

    //Write style for connect_screen_label_connect_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_connect_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_connect_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_connect_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_connect_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_connect_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_WIFI9
    ui->connect_screen_label_WIFI9 = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_WIFI9, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->connect_screen_label_WIFI9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_WIFI9, 284, 9);
    lv_obj_set_size(ui->connect_screen_label_WIFI9, 41, 20);

    //Write style for connect_screen_label_WIFI9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_WIFI9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_WIFI9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_WIFI9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_WIFI9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_WIFI9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_BT9
    ui->connect_screen_label_BT9 = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_BT9, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->connect_screen_label_BT9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_BT9, 260, 9);
    lv_obj_set_size(ui->connect_screen_label_BT9, 41, 20);

    //Write style for connect_screen_label_BT9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_BT9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_BT9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_BT9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_BT9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_BT9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_SD9
    ui->connect_screen_label_SD9 = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_SD9, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->connect_screen_label_SD9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_SD9, 232, 9);
    lv_obj_set_size(ui->connect_screen_label_SD9, 41, 20);

    //Write style for connect_screen_label_SD9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_SD9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_SD9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_SD9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_SD9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_SD9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_USB9
    ui->connect_screen_label_USB9 = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_USB9, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->connect_screen_label_USB9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_USB9, 205, 9);
    lv_obj_set_size(ui->connect_screen_label_USB9, 41, 20);

    //Write style for connect_screen_label_USB9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_USB9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_USB9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_USB9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_USB9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_USB9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_cont_wifi
    ui->connect_screen_cont_wifi = lv_obj_create(ui->connect_screen);
    lv_obj_set_pos(ui->connect_screen_cont_wifi, 10, 39);
    lv_obj_set_size(ui->connect_screen_cont_wifi, 300, 170);
    lv_obj_set_scrollbar_mode(ui->connect_screen_cont_wifi, LV_SCROLLBAR_MODE_OFF);

    //Write style for connect_screen_cont_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_cont_wifi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->connect_screen_cont_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->connect_screen_cont_wifi, lv_color_hex(0xb0b0b0), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->connect_screen_cont_wifi, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_cont_wifi, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_cont_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->connect_screen_cont_wifi, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->connect_screen_cont_wifi, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_cont_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_cont_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_cont_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_cont_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_cont_wifi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->connect_screen_cont_wifi, lv_color_hex(0xb0b0b0), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->connect_screen_cont_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->connect_screen_cont_wifi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->connect_screen_cont_wifi, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->connect_screen_cont_wifi, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_wifi_status
    ui->connect_screen_label_wifi_status = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_wifi_status, "Wi-Fi is connected to 808");
    lv_label_set_long_mode(ui->connect_screen_label_wifi_status, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_wifi_status, 10, 46);
    lv_obj_set_size(ui->connect_screen_label_wifi_status, 300, 40);

    //Write style for connect_screen_label_wifi_status, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_wifi_status, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_wifi_status, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_wifi_status, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_wifi_status, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_wifi_status, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_1
    ui->connect_screen_label_1 = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_1, "Device already connected to cloud");
    lv_label_set_long_mode(ui->connect_screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_1, 10, 113);
    lv_obj_set_size(ui->connect_screen_label_1, 300, 50);

    //Write style for connect_screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_1, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of connect_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->connect_screen);

}
