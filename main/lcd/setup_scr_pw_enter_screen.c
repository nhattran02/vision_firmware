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



void setup_scr_pw_enter_screen(lv_ui *ui)
{
    //Write codes pw_enter_screen
    ui->pw_enter_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->pw_enter_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->pw_enter_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->pw_enter_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for pw_enter_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->pw_enter_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pw_enter_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->pw_enter_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_time7
    ui->pw_enter_screen_label_time7 = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_time7, "11:00");
    lv_label_set_long_mode(ui->pw_enter_screen_label_time7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_time7, -31, 8);
    lv_obj_set_size(ui->pw_enter_screen_label_time7, 128, 20);

    //Write style for pw_enter_screen_label_time7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_time7, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_time7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_time7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_time7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_time7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_pwenter_name
    ui->pw_enter_screen_label_pwenter_name = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_pwenter_name, "Password");
    lv_label_set_long_mode(ui->pw_enter_screen_label_pwenter_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_pwenter_name, 96, 8);
    lv_obj_set_size(ui->pw_enter_screen_label_pwenter_name, 128, 17);

    //Write style for pw_enter_screen_label_pwenter_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_pwenter_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_pwenter_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_pwenter_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_pwenter_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_pwenter_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_WIFI7
    ui->pw_enter_screen_label_WIFI7 = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_WIFI7, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->pw_enter_screen_label_WIFI7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_WIFI7, 284, 9);
    lv_obj_set_size(ui->pw_enter_screen_label_WIFI7, 41, 20);

    //Write style for pw_enter_screen_label_WIFI7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_WIFI7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_WIFI7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_WIFI7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_WIFI7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_WIFI7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_BT7
    ui->pw_enter_screen_label_BT7 = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_BT7, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->pw_enter_screen_label_BT7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_BT7, 260, 9);
    lv_obj_set_size(ui->pw_enter_screen_label_BT7, 41, 20);

    //Write style for pw_enter_screen_label_BT7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_BT7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_BT7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_BT7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_BT7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_BT7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_SD7
    ui->pw_enter_screen_label_SD7 = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_SD7, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->pw_enter_screen_label_SD7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_SD7, 232, 9);
    lv_obj_set_size(ui->pw_enter_screen_label_SD7, 41, 20);

    //Write style for pw_enter_screen_label_SD7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_SD7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_SD7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_SD7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_SD7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_SD7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_USB7
    ui->pw_enter_screen_label_USB7 = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_USB7, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->pw_enter_screen_label_USB7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_USB7, 205, 9);
    lv_obj_set_size(ui->pw_enter_screen_label_USB7, 41, 20);

    //Write style for pw_enter_screen_label_USB7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_USB7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_USB7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_USB7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_USB7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_USB7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_btn_esc7
    ui->pw_enter_screen_btn_esc7 = lv_btn_create(ui->pw_enter_screen);
    ui->pw_enter_screen_btn_esc7_label = lv_label_create(ui->pw_enter_screen_btn_esc7);
    lv_label_set_text(ui->pw_enter_screen_btn_esc7_label, "ESC");
    lv_label_set_long_mode(ui->pw_enter_screen_btn_esc7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->pw_enter_screen_btn_esc7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->pw_enter_screen_btn_esc7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->pw_enter_screen_btn_esc7_label, LV_PCT(100));
    lv_obj_set_pos(ui->pw_enter_screen_btn_esc7, 17, 204);
    lv_obj_set_size(ui->pw_enter_screen_btn_esc7, 100, 28);

    //Write style for pw_enter_screen_btn_esc7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_btn_esc7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pw_enter_screen_btn_esc7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->pw_enter_screen_btn_esc7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pw_enter_screen_btn_esc7, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->pw_enter_screen_btn_esc7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->pw_enter_screen_btn_esc7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->pw_enter_screen_btn_esc7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_btn_esc7, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_btn_esc7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_btn_esc7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_btn_esc7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_btn_esc7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_btn_esc7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_btn_ok7
    ui->pw_enter_screen_btn_ok7 = lv_btn_create(ui->pw_enter_screen);
    ui->pw_enter_screen_btn_ok7_label = lv_label_create(ui->pw_enter_screen_btn_ok7);
    lv_label_set_text(ui->pw_enter_screen_btn_ok7_label, "OK");
    lv_label_set_long_mode(ui->pw_enter_screen_btn_ok7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->pw_enter_screen_btn_ok7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->pw_enter_screen_btn_ok7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->pw_enter_screen_btn_ok7_label, LV_PCT(100));
    lv_obj_set_pos(ui->pw_enter_screen_btn_ok7, 205, 205);
    lv_obj_set_size(ui->pw_enter_screen_btn_ok7, 100, 28);

    //Write style for pw_enter_screen_btn_ok7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_btn_ok7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pw_enter_screen_btn_ok7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->pw_enter_screen_btn_ok7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pw_enter_screen_btn_ok7, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->pw_enter_screen_btn_ok7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->pw_enter_screen_btn_ok7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->pw_enter_screen_btn_ok7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_btn_ok7, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_btn_ok7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_btn_ok7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_btn_ok7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_btn_ok7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_btn_ok7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_nofi
    ui->pw_enter_screen_label_nofi = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_nofi, "Please enter your password");
    lv_label_set_long_mode(ui->pw_enter_screen_label_nofi, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_nofi, 10, 162);
    lv_obj_set_size(ui->pw_enter_screen_label_nofi, 300, 18);

    //Write style for pw_enter_screen_label_nofi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_nofi, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_nofi, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_nofi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_nofi, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_nofi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_id_name
    ui->pw_enter_screen_label_id_name = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_id_name, "ID-1  Tran Minh Nhat");
    lv_label_set_long_mode(ui->pw_enter_screen_label_id_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_id_name, 10, 49);
    lv_obj_set_size(ui->pw_enter_screen_label_id_name, 300, 18);

    //Write style for pw_enter_screen_label_id_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_id_name, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_id_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_id_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_id_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_id_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_pw_first
    ui->pw_enter_screen_label_pw_first = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_pw_first, "xxxxxxxx");
    lv_label_set_long_mode(ui->pw_enter_screen_label_pw_first, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_pw_first, 70, 84);
    lv_obj_set_size(ui->pw_enter_screen_label_pw_first, 180, 28);

    //Write style for pw_enter_screen_label_pw_first, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_pw_first, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_pw_first, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_pw_first, &lv_font_montserrat_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_pw_first, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_pw_first, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_pw_first, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_pw_first, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pw_enter_screen_label_pw_first, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->pw_enter_screen_label_pw_first, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_pw_second
    ui->pw_enter_screen_label_pw_second = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_pw_second, "xxxxxxxx");
    lv_label_set_long_mode(ui->pw_enter_screen_label_pw_second, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_pw_second, 70, 122);
    lv_obj_set_size(ui->pw_enter_screen_label_pw_second, 180, 28);

    //Write style for pw_enter_screen_label_pw_second, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_pw_second, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_pw_second, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_pw_second, &lv_font_montserrat_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_pw_second, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_pw_second, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_pw_second, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_pw_second, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pw_enter_screen_label_pw_second, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->pw_enter_screen_label_pw_second, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of pw_enter_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->pw_enter_screen);

}
