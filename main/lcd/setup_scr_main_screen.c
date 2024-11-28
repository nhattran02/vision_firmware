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



void setup_scr_main_screen(lv_ui *ui)
{
    //Write codes main_screen
    ui->main_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->main_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->main_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for main_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_cont_1
    ui->main_screen_cont_1 = lv_obj_create(ui->main_screen);
    lv_obj_set_pos(ui->main_screen_cont_1, 10, 35);
    lv_obj_set_size(ui->main_screen_cont_1, 300, 170);
    lv_obj_set_scrollbar_mode(ui->main_screen_cont_1, LV_SCROLLBAR_MODE_OFF);
    
    //Write style for main_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_cont_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->main_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->main_screen_cont_1, lv_color_hex(0xb0b0b0), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->main_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_cont_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_cont_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->main_screen_cont_1, lv_color_hex(0xb0b0b0), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->main_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->main_screen_cont_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->main_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->main_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_date
    ui->main_screen_label_date = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_date, "21-10-2024");
    lv_label_set_long_mode(ui->main_screen_label_date, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_date, 3, 217);
    lv_obj_set_size(ui->main_screen_label_date, 127, 17);

    //Write style for main_screen_label_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_date, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
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
    lv_obj_set_style_text_color(ui->main_screen_label_day, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
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

    //Write codes main_screen_label_time
    ui->main_screen_label_time = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_time, "11:00");
    lv_label_set_long_mode(ui->main_screen_label_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_time, 51, 99);
    lv_obj_set_size(ui->main_screen_label_time, 225, 46);

    //Write style for main_screen_label_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_time, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
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

    //Write codes main_screen_label_home_name
    ui->main_screen_label_home_name = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_home_name, "Home");
    lv_label_set_long_mode(ui->main_screen_label_home_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_home_name, 96, 8);
    lv_obj_set_size(ui->main_screen_label_home_name, 128, 17);

    //Write style for main_screen_label_home_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_home_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_home_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_home_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_home_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_home_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_WIFI
    ui->main_screen_label_WIFI = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_WIFI, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->main_screen_label_WIFI, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_WIFI, 284, 9);
    lv_obj_set_size(ui->main_screen_label_WIFI, 41, 20);

    //Write style for main_screen_label_WIFI, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_WIFI, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_WIFI, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_WIFI, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_WIFI, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_WIFI, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_BT
    ui->main_screen_label_BT = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_BT, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->main_screen_label_BT, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_BT, 260, 9);
    lv_obj_set_size(ui->main_screen_label_BT, 41, 20);

    //Write style for main_screen_label_BT, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_BT, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_BT, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_BT, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_BT, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_BT, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_SD
    ui->main_screen_label_SD = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_SD, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->main_screen_label_SD, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_SD, 232, 9);
    lv_obj_set_size(ui->main_screen_label_SD, 41, 20);

    //Write style for main_screen_label_SD, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_SD, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_SD, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_SD, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_SD, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_SD, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_USB
    ui->main_screen_label_USB = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_USB, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->main_screen_label_USB, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_USB, 205, 9);
    lv_obj_set_size(ui->main_screen_label_USB, 41, 20);

    //Write style for main_screen_label_USB, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_USB, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_USB, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_USB, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_USB, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_USB, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of main_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->main_screen);

    //Init events for screen.
    events_init_main_screen(ui);
}
