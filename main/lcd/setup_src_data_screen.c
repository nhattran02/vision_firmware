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



void setup_scr_data_screen(lv_ui *ui)
{
    //Write codes data_screen
    ui->data_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->data_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->data_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->data_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for data_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->data_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->data_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->data_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_time4
    ui->data_screen_label_time4 = lv_label_create(ui->data_screen);
    lv_label_set_text(ui->data_screen_label_time4, "11:00");
    lv_label_set_long_mode(ui->data_screen_label_time4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_time4, -31, 8);
    lv_obj_set_size(ui->data_screen_label_time4, 128, 20);

    //Write style for data_screen_label_time4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_time4, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_time4, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_time4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_time4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_time4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_time4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_data_name
    ui->data_screen_label_data_name = lv_label_create(ui->data_screen);
    lv_label_set_text(ui->data_screen_label_data_name, "Data");
    lv_label_set_long_mode(ui->data_screen_label_data_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_data_name, 96, 8);
    lv_obj_set_size(ui->data_screen_label_data_name, 128, 17);

    //Write style for data_screen_label_data_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_data_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_data_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_data_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_data_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_data_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_data_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_data_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_data_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_data_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_data_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_data_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_data_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_data_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_data_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_WIFI4
    ui->data_screen_label_WIFI4 = lv_label_create(ui->data_screen);
    lv_label_set_text(ui->data_screen_label_WIFI4, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->data_screen_label_WIFI4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_WIFI4, 284, 9);
    lv_obj_set_size(ui->data_screen_label_WIFI4, 41, 20);

    //Write style for data_screen_label_WIFI4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_WIFI4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_WIFI4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_WIFI4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_WIFI4, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_WIFI4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_WIFI4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_WIFI4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_WIFI4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_WIFI4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_WIFI4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_WIFI4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_WIFI4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_WIFI4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_WIFI4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_BT4
    ui->data_screen_label_BT4 = lv_label_create(ui->data_screen);
    lv_label_set_text(ui->data_screen_label_BT4, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->data_screen_label_BT4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_BT4, 260, 9);
    lv_obj_set_size(ui->data_screen_label_BT4, 41, 20);

    //Write style for data_screen_label_BT4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_BT4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_BT4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_BT4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_BT4, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_BT4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_BT4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_BT4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_BT4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_BT4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_BT4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_BT4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_BT4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_BT4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_BT4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_SD4
    ui->data_screen_label_SD4 = lv_label_create(ui->data_screen);
    lv_label_set_text(ui->data_screen_label_SD4, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->data_screen_label_SD4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_SD4, 232, 9);
    lv_obj_set_size(ui->data_screen_label_SD4, 41, 20);

    //Write style for data_screen_label_SD4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_SD4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_SD4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_SD4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_SD4, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_SD4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_SD4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_SD4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_SD4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_SD4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_SD4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_SD4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_SD4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_SD4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_SD4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_USB4
    ui->data_screen_label_USB4 = lv_label_create(ui->data_screen);
    lv_label_set_text(ui->data_screen_label_USB4, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->data_screen_label_USB4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_USB4, 205, 9);
    lv_obj_set_size(ui->data_screen_label_USB4, 41, 20);

    //Write style for data_screen_label_USB4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_USB4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_USB4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_USB4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_USB4, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_USB4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_USB4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_USB4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_USB4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_USB4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_USB4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_USB4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_USB4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_USB4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_USB4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_btn_esc4
    ui->data_screen_btn_esc4 = lv_btn_create(ui->data_screen);
    ui->data_screen_btn_esc4_label = lv_label_create(ui->data_screen_btn_esc4);
    lv_label_set_text(ui->data_screen_btn_esc4_label, "ESC");
    lv_label_set_long_mode(ui->data_screen_btn_esc4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->data_screen_btn_esc4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->data_screen_btn_esc4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->data_screen_btn_esc4_label, LV_PCT(100));
    lv_obj_set_pos(ui->data_screen_btn_esc4, 17, 204);
    lv_obj_set_size(ui->data_screen_btn_esc4, 100, 28);

    //Write style for data_screen_btn_esc4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->data_screen_btn_esc4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->data_screen_btn_esc4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->data_screen_btn_esc4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->data_screen_btn_esc4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->data_screen_btn_esc4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->data_screen_btn_esc4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->data_screen_btn_esc4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_btn_esc4, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_btn_esc4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_btn_esc4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_btn_esc4, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_btn_esc4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_btn_esc4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_btn_ok4
    ui->data_screen_btn_ok4 = lv_btn_create(ui->data_screen);
    ui->data_screen_btn_ok4_label = lv_label_create(ui->data_screen_btn_ok4);
    lv_label_set_text(ui->data_screen_btn_ok4_label, "OK");
    lv_label_set_long_mode(ui->data_screen_btn_ok4_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->data_screen_btn_ok4_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->data_screen_btn_ok4, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->data_screen_btn_ok4_label, LV_PCT(100));
    lv_obj_set_pos(ui->data_screen_btn_ok4, 205, 204);
    lv_obj_set_size(ui->data_screen_btn_ok4, 100, 28);

    //Write style for data_screen_btn_ok4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->data_screen_btn_ok4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->data_screen_btn_ok4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->data_screen_btn_ok4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->data_screen_btn_ok4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->data_screen_btn_ok4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->data_screen_btn_ok4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->data_screen_btn_ok4, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_btn_ok4, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_btn_ok4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_btn_ok4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_btn_ok4, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_btn_ok4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_btn_ok4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_cont_dwntemplate
    ui->data_screen_cont_dwntemplate = lv_obj_create(ui->data_screen);
    lv_obj_set_pos(ui->data_screen_cont_dwntemplate, 10, 119);
    lv_obj_set_size(ui->data_screen_cont_dwntemplate, 300, 35);
    lv_obj_set_scrollbar_mode(ui->data_screen_cont_dwntemplate, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->data_screen_cont_dwntemplate, LV_OBJ_FLAG_CHECKABLE);

    //Write style for data_screen_cont_dwntemplate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_cont_dwntemplate, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->data_screen_cont_dwntemplate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->data_screen_cont_dwntemplate, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->data_screen_cont_dwntemplate, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_cont_dwntemplate, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_cont_dwntemplate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->data_screen_cont_dwntemplate, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->data_screen_cont_dwntemplate, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_cont_dwntemplate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_cont_dwntemplate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_cont_dwntemplate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_cont_dwntemplate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_cont_dwntemplate, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->data_screen_cont_dwntemplate, lv_color_hex(0x686464), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->data_screen_cont_dwntemplate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->data_screen_cont_dwntemplate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->data_screen_cont_dwntemplate, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->data_screen_cont_dwntemplate, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_dwntemplate_symbol
    ui->data_screen_label_dwntemplate_symbol = lv_label_create(ui->data_screen_cont_dwntemplate);
    lv_label_set_text(ui->data_screen_label_dwntemplate_symbol, "" LV_SYMBOL_DOWNLOAD "");
    lv_label_set_long_mode(ui->data_screen_label_dwntemplate_symbol, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_dwntemplate_symbol, 66, 7);
    lv_obj_set_size(ui->data_screen_label_dwntemplate_symbol, 20, 20);

    //Write style for data_screen_label_dwntemplate_symbol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_dwntemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_dwntemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_dwntemplate_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_dwntemplate_symbol, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_dwntemplate_symbol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_dwntemplate_symbol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_dwntemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_dwntemplate_symbol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_dwntemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_dwntemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_dwntemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_dwntemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_dwntemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_dwntemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_dwntemplate_text
    ui->data_screen_label_dwntemplate_text = lv_label_create(ui->data_screen_cont_dwntemplate);
    lv_label_set_text(ui->data_screen_label_dwntemplate_text, "D/L Template");
    lv_label_set_long_mode(ui->data_screen_label_dwntemplate_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_dwntemplate_text, 89, 7);
    lv_obj_set_size(ui->data_screen_label_dwntemplate_text, 152, 19);

    //Write style for data_screen_label_dwntemplate_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_dwntemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_dwntemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_dwntemplate_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_dwntemplate_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_dwntemplate_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_dwntemplate_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_dwntemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_dwntemplate_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_dwntemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_dwntemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_dwntemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_dwntemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_dwntemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_dwntemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_cont_dwnreport
    ui->data_screen_cont_dwnreport = lv_obj_create(ui->data_screen);
    lv_obj_set_pos(ui->data_screen_cont_dwnreport, 10, 40);
    lv_obj_set_size(ui->data_screen_cont_dwnreport, 300, 35);
    lv_obj_set_scrollbar_mode(ui->data_screen_cont_dwnreport, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->data_screen_cont_dwnreport, LV_OBJ_FLAG_CHECKABLE);

    //Write style for data_screen_cont_dwnreport, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_cont_dwnreport, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->data_screen_cont_dwnreport, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->data_screen_cont_dwnreport, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->data_screen_cont_dwnreport, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_cont_dwnreport, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_cont_dwnreport, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->data_screen_cont_dwnreport, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->data_screen_cont_dwnreport, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_cont_dwnreport, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_cont_dwnreport, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_cont_dwnreport, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_cont_dwnreport, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_cont_dwnreport, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->data_screen_cont_dwnreport, lv_color_hex(0x686464), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->data_screen_cont_dwnreport, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->data_screen_cont_dwnreport, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->data_screen_cont_dwnreport, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->data_screen_cont_dwnreport, 1, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_dwnreport_symbol
    ui->data_screen_label_dwnreport_symbol = lv_label_create(ui->data_screen_cont_dwnreport);
    lv_label_set_text(ui->data_screen_label_dwnreport_symbol, "" LV_SYMBOL_SAVE "");
    lv_label_set_long_mode(ui->data_screen_label_dwnreport_symbol, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_dwnreport_symbol, 66, 7);
    lv_obj_set_size(ui->data_screen_label_dwnreport_symbol, 20, 20);

    //Write style for data_screen_label_dwnreport_symbol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_dwnreport_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_dwnreport_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_dwnreport_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_dwnreport_symbol, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_dwnreport_symbol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_dwnreport_symbol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_dwnreport_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_dwnreport_symbol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_dwnreport_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_dwnreport_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_dwnreport_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_dwnreport_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_dwnreport_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_dwnreport_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_dwnreport_text
    ui->data_screen_label_dwnreport_text = lv_label_create(ui->data_screen_cont_dwnreport);
    lv_label_set_text(ui->data_screen_label_dwnreport_text, "Save Report");
    lv_label_set_long_mode(ui->data_screen_label_dwnreport_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_dwnreport_text, 89, 7);
    lv_obj_set_size(ui->data_screen_label_dwnreport_text, 152, 19);

    //Write style for data_screen_label_dwnreport_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_dwnreport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_dwnreport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_dwnreport_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_dwnreport_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_dwnreport_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_dwnreport_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_dwnreport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_dwnreport_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_dwnreport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_dwnreport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_dwnreport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_dwnreport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_dwnreport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_dwnreport_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_cont_uptemplate
    ui->data_screen_cont_uptemplate = lv_obj_create(ui->data_screen);
    lv_obj_set_pos(ui->data_screen_cont_uptemplate, 10, 159);
    lv_obj_set_size(ui->data_screen_cont_uptemplate, 300, 35);
    lv_obj_set_scrollbar_mode(ui->data_screen_cont_uptemplate, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->data_screen_cont_uptemplate, LV_OBJ_FLAG_CHECKABLE);

    //Write style for data_screen_cont_uptemplate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_cont_uptemplate, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->data_screen_cont_uptemplate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->data_screen_cont_uptemplate, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->data_screen_cont_uptemplate, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_cont_uptemplate, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_cont_uptemplate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->data_screen_cont_uptemplate, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->data_screen_cont_uptemplate, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_cont_uptemplate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_cont_uptemplate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_cont_uptemplate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_cont_uptemplate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_cont_uptemplate, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->data_screen_cont_uptemplate, lv_color_hex(0x686464), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->data_screen_cont_uptemplate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->data_screen_cont_uptemplate, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->data_screen_cont_uptemplate, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->data_screen_cont_uptemplate, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_uptemplate_symbol
    ui->data_screen_label_uptemplate_symbol = lv_label_create(ui->data_screen_cont_uptemplate);
    lv_label_set_text(ui->data_screen_label_uptemplate_symbol, "" LV_SYMBOL_UPLOAD "");
    lv_label_set_long_mode(ui->data_screen_label_uptemplate_symbol, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_uptemplate_symbol, 66, 7);
    lv_obj_set_size(ui->data_screen_label_uptemplate_symbol, 20, 20);

    //Write style for data_screen_label_uptemplate_symbol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_uptemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_uptemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_uptemplate_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_uptemplate_symbol, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_uptemplate_symbol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_uptemplate_symbol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_uptemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_uptemplate_symbol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_uptemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_uptemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_uptemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_uptemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_uptemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_uptemplate_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_uptemplate_text
    ui->data_screen_label_uptemplate_text = lv_label_create(ui->data_screen_cont_uptemplate);
    lv_label_set_text(ui->data_screen_label_uptemplate_text, "U/L Template");
    lv_label_set_long_mode(ui->data_screen_label_uptemplate_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_uptemplate_text, 89, 7);
    lv_obj_set_size(ui->data_screen_label_uptemplate_text, 152, 19);

    //Write style for data_screen_label_uptemplate_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_uptemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_uptemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_uptemplate_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_uptemplate_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_uptemplate_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_uptemplate_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_uptemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_uptemplate_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_uptemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_uptemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_uptemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_uptemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_uptemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_uptemplate_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_cont_usrdata
    ui->data_screen_cont_usrdata = lv_obj_create(ui->data_screen);
    lv_obj_set_pos(ui->data_screen_cont_usrdata, 10, 79);
    lv_obj_set_size(ui->data_screen_cont_usrdata, 300, 35);
    lv_obj_set_scrollbar_mode(ui->data_screen_cont_usrdata, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->data_screen_cont_usrdata, LV_OBJ_FLAG_CHECKABLE);

    //Write style for data_screen_cont_usrdata, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_cont_usrdata, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->data_screen_cont_usrdata, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->data_screen_cont_usrdata, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->data_screen_cont_usrdata, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_cont_usrdata, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_cont_usrdata, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->data_screen_cont_usrdata, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->data_screen_cont_usrdata, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_cont_usrdata, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_cont_usrdata, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_cont_usrdata, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_cont_usrdata, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_cont_usrdata, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->data_screen_cont_usrdata, lv_color_hex(0x686464), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->data_screen_cont_usrdata, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->data_screen_cont_usrdata, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->data_screen_cont_usrdata, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->data_screen_cont_usrdata, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_usrdata_symbol
    ui->data_screen_label_usrdata_symbol = lv_label_create(ui->data_screen_cont_usrdata);
    lv_label_set_text(ui->data_screen_label_usrdata_symbol, "" LV_SYMBOL_LIST "");
    lv_label_set_long_mode(ui->data_screen_label_usrdata_symbol, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_usrdata_symbol, 66, 7);
    lv_obj_set_size(ui->data_screen_label_usrdata_symbol, 20, 20);

    //Write style for data_screen_label_usrdata_symbol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_usrdata_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_usrdata_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_usrdata_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_usrdata_symbol, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_usrdata_symbol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_usrdata_symbol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_usrdata_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_usrdata_symbol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_usrdata_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_usrdata_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_usrdata_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_usrdata_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_usrdata_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_usrdata_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes data_screen_label_usrdata_text
    ui->data_screen_label_usrdata_text = lv_label_create(ui->data_screen_cont_usrdata);
    lv_label_set_text(ui->data_screen_label_usrdata_text, "User Data");
    lv_label_set_long_mode(ui->data_screen_label_usrdata_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->data_screen_label_usrdata_text, 89, 7);
    lv_obj_set_size(ui->data_screen_label_usrdata_text, 152, 19);

    //Write style for data_screen_label_usrdata_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->data_screen_label_usrdata_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->data_screen_label_usrdata_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->data_screen_label_usrdata_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->data_screen_label_usrdata_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->data_screen_label_usrdata_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->data_screen_label_usrdata_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->data_screen_label_usrdata_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->data_screen_label_usrdata_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->data_screen_label_usrdata_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->data_screen_label_usrdata_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->data_screen_label_usrdata_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->data_screen_label_usrdata_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->data_screen_label_usrdata_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->data_screen_label_usrdata_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of data_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->data_screen);

    //Init events for screen.
    events_init_data_screen(ui);
}
