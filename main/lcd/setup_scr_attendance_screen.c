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



void setup_scr_attendance_screen(lv_ui *ui)
{
    //Write codes attendance_screen
    ui->attendance_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->attendance_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->attendance_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for attendance_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->attendance_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->attendance_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->attendance_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_label_time3
    ui->attendance_screen_label_time3 = lv_label_create(ui->attendance_screen);
    lv_label_set_text(ui->attendance_screen_label_time3, "11:00");
    lv_label_set_long_mode(ui->attendance_screen_label_time3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_label_time3, -31, 8);
    lv_obj_set_size(ui->attendance_screen_label_time3, 128, 20);

    //Write style for attendance_screen_label_time3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_label_time3, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_label_time3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_label_time3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_label_time3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_label_time3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_label_time3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_label_attendance_name
    ui->attendance_screen_label_attendance_name = lv_label_create(ui->attendance_screen);
    lv_label_set_text(ui->attendance_screen_label_attendance_name, "Attend");
    lv_label_set_long_mode(ui->attendance_screen_label_attendance_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_label_attendance_name, 96, 8);
    lv_obj_set_size(ui->attendance_screen_label_attendance_name, 128, 17);

    //Write style for attendance_screen_label_attendance_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_label_attendance_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_label_attendance_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_label_attendance_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_label_attendance_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_label_attendance_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_label_attendance_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_label_attendance_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_label_attendance_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_label_attendance_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_label_attendance_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_label_attendance_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_label_attendance_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_label_attendance_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_label_attendance_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_label_WIFI3
    ui->attendance_screen_label_WIFI3 = lv_label_create(ui->attendance_screen);
    lv_label_set_text(ui->attendance_screen_label_WIFI3, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->attendance_screen_label_WIFI3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_label_WIFI3, 284, 9);
    lv_obj_set_size(ui->attendance_screen_label_WIFI3, 41, 20);

    //Write style for attendance_screen_label_WIFI3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_label_WIFI3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_label_WIFI3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_label_WIFI3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_label_WIFI3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_label_WIFI3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_label_WIFI3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_label_WIFI3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_label_WIFI3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_label_WIFI3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_label_WIFI3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_label_WIFI3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_label_WIFI3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_label_WIFI3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_label_WIFI3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_label_BT3
    ui->attendance_screen_label_BT3 = lv_label_create(ui->attendance_screen);
    lv_label_set_text(ui->attendance_screen_label_BT3, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->attendance_screen_label_BT3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_label_BT3, 260, 9);
    lv_obj_set_size(ui->attendance_screen_label_BT3, 41, 20);

    //Write style for attendance_screen_label_BT3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_label_BT3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_label_BT3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_label_BT3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_label_BT3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_label_BT3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_label_BT3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_label_BT3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_label_BT3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_label_BT3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_label_BT3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_label_BT3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_label_BT3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_label_BT3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_label_BT3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_label_SD3
    ui->attendance_screen_label_SD3 = lv_label_create(ui->attendance_screen);
    lv_label_set_text(ui->attendance_screen_label_SD3, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->attendance_screen_label_SD3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_label_SD3, 232, 9);
    lv_obj_set_size(ui->attendance_screen_label_SD3, 41, 20);

    //Write style for attendance_screen_label_SD3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_label_SD3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_label_SD3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_label_SD3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_label_SD3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_label_SD3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_label_SD3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_label_SD3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_label_SD3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_label_SD3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_label_SD3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_label_SD3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_label_SD3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_label_SD3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_label_SD3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_label_USB3
    ui->attendance_screen_label_USB3 = lv_label_create(ui->attendance_screen);
    lv_label_set_text(ui->attendance_screen_label_USB3, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->attendance_screen_label_USB3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_label_USB3, 205, 9);
    lv_obj_set_size(ui->attendance_screen_label_USB3, 41, 20);

    //Write style for attendance_screen_label_USB3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_label_USB3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_label_USB3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_label_USB3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_label_USB3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_label_USB3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_label_USB3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_label_USB3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_label_USB3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_label_USB3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_label_USB3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_label_USB3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_label_USB3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_label_USB3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_label_USB3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_btn_esc3
    ui->attendance_screen_btn_esc3 = lv_btn_create(ui->attendance_screen);
    ui->attendance_screen_btn_esc3_label = lv_label_create(ui->attendance_screen_btn_esc3);
    lv_label_set_text(ui->attendance_screen_btn_esc3_label, "ESC");
    lv_label_set_long_mode(ui->attendance_screen_btn_esc3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->attendance_screen_btn_esc3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->attendance_screen_btn_esc3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->attendance_screen_btn_esc3_label, LV_PCT(100));
    lv_obj_set_pos(ui->attendance_screen_btn_esc3, 17, 204);
    lv_obj_set_size(ui->attendance_screen_btn_esc3, 100, 28);

    //Write style for attendance_screen_btn_esc3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->attendance_screen_btn_esc3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->attendance_screen_btn_esc3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->attendance_screen_btn_esc3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->attendance_screen_btn_esc3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->attendance_screen_btn_esc3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->attendance_screen_btn_esc3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->attendance_screen_btn_esc3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_btn_esc3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_btn_esc3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_btn_esc3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_btn_esc3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_btn_esc3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_btn_esc3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_btn_ok3
    ui->attendance_screen_btn_ok3 = lv_btn_create(ui->attendance_screen);
    ui->attendance_screen_btn_ok3_label = lv_label_create(ui->attendance_screen_btn_ok3);
    lv_label_set_text(ui->attendance_screen_btn_ok3_label, "OK");
    lv_label_set_long_mode(ui->attendance_screen_btn_ok3_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->attendance_screen_btn_ok3_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->attendance_screen_btn_ok3, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->attendance_screen_btn_ok3_label, LV_PCT(100));
    lv_obj_set_pos(ui->attendance_screen_btn_ok3, 205, 204);
    lv_obj_set_size(ui->attendance_screen_btn_ok3, 100, 28);

    //Write style for attendance_screen_btn_ok3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->attendance_screen_btn_ok3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->attendance_screen_btn_ok3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->attendance_screen_btn_ok3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->attendance_screen_btn_ok3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->attendance_screen_btn_ok3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->attendance_screen_btn_ok3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->attendance_screen_btn_ok3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_btn_ok3, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_btn_ok3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_btn_ok3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_btn_ok3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_btn_ok3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_btn_ok3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_cont_check_in
    ui->attendance_screen_cont_check_in = lv_obj_create(ui->attendance_screen);
    lv_obj_set_pos(ui->attendance_screen_cont_check_in, 10, 79);
    lv_obj_set_size(ui->attendance_screen_cont_check_in, 300, 35);
    lv_obj_set_scrollbar_mode(ui->attendance_screen_cont_check_in, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->attendance_screen_cont_check_in, LV_OBJ_FLAG_CHECKABLE);

    //Write style for attendance_screen_cont_check_in, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_cont_check_in, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->attendance_screen_cont_check_in, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->attendance_screen_cont_check_in, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->attendance_screen_cont_check_in, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_cont_check_in, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_cont_check_in, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->attendance_screen_cont_check_in, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->attendance_screen_cont_check_in, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_cont_check_in, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_cont_check_in, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_cont_check_in, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_cont_check_in, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_cont_check_in, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->attendance_screen_cont_check_in, lv_color_hex(0x686464), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->attendance_screen_cont_check_in, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->attendance_screen_cont_check_in, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->attendance_screen_cont_check_in, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->attendance_screen_cont_check_in, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_label_checkin_symbol
    ui->attendance_screen_label_checkin_symbol = lv_label_create(ui->attendance_screen_cont_check_in);
    lv_label_set_text(ui->attendance_screen_label_checkin_symbol, "" LV_SYMBOL_RIGHT "");
    lv_label_set_long_mode(ui->attendance_screen_label_checkin_symbol, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_label_checkin_symbol, 79, 7);
    lv_obj_set_size(ui->attendance_screen_label_checkin_symbol, 20, 20);

    //Write style for attendance_screen_label_checkin_symbol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_label_checkin_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_label_checkin_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_label_checkin_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_label_checkin_symbol, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_label_checkin_symbol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_label_checkin_symbol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_label_checkin_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_label_checkin_symbol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_label_checkin_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_label_checkin_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_label_checkin_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_label_checkin_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_label_checkin_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_label_checkin_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_label_checkin_text
    ui->attendance_screen_label_checkin_text = lv_label_create(ui->attendance_screen_cont_check_in);
    lv_label_set_text(ui->attendance_screen_label_checkin_text, "Check In\n");
    lv_label_set_long_mode(ui->attendance_screen_label_checkin_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_label_checkin_text, 98, 7);
    lv_obj_set_size(ui->attendance_screen_label_checkin_text, 134, 19);

    //Write style for attendance_screen_label_checkin_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_label_checkin_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_label_checkin_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_label_checkin_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_label_checkin_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_label_checkin_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_label_checkin_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_label_checkin_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_label_checkin_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_label_checkin_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_label_checkin_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_label_checkin_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_label_checkin_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_label_checkin_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_label_checkin_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_cont_check_out
    ui->attendance_screen_cont_check_out = lv_obj_create(ui->attendance_screen);
    lv_obj_set_pos(ui->attendance_screen_cont_check_out, 10, 119);
    lv_obj_set_size(ui->attendance_screen_cont_check_out, 300, 35);
    lv_obj_set_scrollbar_mode(ui->attendance_screen_cont_check_out, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->attendance_screen_cont_check_out, LV_OBJ_FLAG_CHECKABLE);

    //Write style for attendance_screen_cont_check_out, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_cont_check_out, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->attendance_screen_cont_check_out, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->attendance_screen_cont_check_out, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->attendance_screen_cont_check_out, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_cont_check_out, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_cont_check_out, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->attendance_screen_cont_check_out, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->attendance_screen_cont_check_out, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_cont_check_out, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_cont_check_out, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_cont_check_out, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_cont_check_out, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_cont_check_out, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->attendance_screen_cont_check_out, lv_color_hex(0x686464), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->attendance_screen_cont_check_out, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->attendance_screen_cont_check_out, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->attendance_screen_cont_check_out, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->attendance_screen_cont_check_out, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_label_checkout_symbol
    ui->attendance_screen_label_checkout_symbol = lv_label_create(ui->attendance_screen_cont_check_out);
    lv_label_set_text(ui->attendance_screen_label_checkout_symbol, "" LV_SYMBOL_LEFT "");
    lv_label_set_long_mode(ui->attendance_screen_label_checkout_symbol, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_label_checkout_symbol, 79, 7);
    lv_obj_set_size(ui->attendance_screen_label_checkout_symbol, 20, 20);

    //Write style for attendance_screen_label_checkout_symbol, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_label_checkout_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_label_checkout_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_label_checkout_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_label_checkout_symbol, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_label_checkout_symbol, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_label_checkout_symbol, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_label_checkout_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_label_checkout_symbol, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_label_checkout_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_label_checkout_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_label_checkout_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_label_checkout_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_label_checkout_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_label_checkout_symbol, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes attendance_screen_label_checkout_text
    ui->attendance_screen_label_checkout_text = lv_label_create(ui->attendance_screen_cont_check_out);
    lv_label_set_text(ui->attendance_screen_label_checkout_text, "Check Out");
    lv_label_set_long_mode(ui->attendance_screen_label_checkout_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->attendance_screen_label_checkout_text, 98, 7);
    lv_obj_set_size(ui->attendance_screen_label_checkout_text, 134, 19);

    //Write style for attendance_screen_label_checkout_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->attendance_screen_label_checkout_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->attendance_screen_label_checkout_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->attendance_screen_label_checkout_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->attendance_screen_label_checkout_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->attendance_screen_label_checkout_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->attendance_screen_label_checkout_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->attendance_screen_label_checkout_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->attendance_screen_label_checkout_text, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->attendance_screen_label_checkout_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->attendance_screen_label_checkout_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->attendance_screen_label_checkout_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->attendance_screen_label_checkout_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->attendance_screen_label_checkout_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->attendance_screen_label_checkout_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of attendance_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->attendance_screen);

}
