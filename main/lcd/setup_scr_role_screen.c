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



void setup_scr_role_screen(lv_ui *ui)
{
    //Write codes role_screen
    ui->role_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->role_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->role_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->role_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for role_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->role_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->role_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->role_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_time9
    ui->role_screen_label_time9 = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_time9, "11:00");
    lv_label_set_long_mode(ui->role_screen_label_time9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_time9, -31, 8);
    lv_obj_set_size(ui->role_screen_label_time9, 128, 20);

    //Write style for role_screen_label_time9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_time9, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_time9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_time9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_time9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_time9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_authen_name
    ui->role_screen_label_authen_name = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_authen_name, "Set Role");
    lv_label_set_long_mode(ui->role_screen_label_authen_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_authen_name, 97, 8);
    lv_obj_set_size(ui->role_screen_label_authen_name, 128, 17);

    //Write style for role_screen_label_authen_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_authen_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_authen_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_authen_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_authen_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_authen_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_WIFI8
    ui->role_screen_label_WIFI8 = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_WIFI8, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->role_screen_label_WIFI8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_WIFI8, 284, 9);
    lv_obj_set_size(ui->role_screen_label_WIFI8, 41, 20);

    //Write style for role_screen_label_WIFI8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_WIFI8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_WIFI8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_WIFI8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_WIFI8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_WIFI8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_BT8
    ui->role_screen_label_BT8 = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_BT8, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->role_screen_label_BT8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_BT8, 260, 9);
    lv_obj_set_size(ui->role_screen_label_BT8, 41, 20);

    //Write style for role_screen_label_BT8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_BT8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_BT8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_BT8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_BT8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_BT8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_SD8
    ui->role_screen_label_SD8 = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_SD8, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->role_screen_label_SD8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_SD8, 232, 9);
    lv_obj_set_size(ui->role_screen_label_SD8, 41, 20);

    //Write style for role_screen_label_SD8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_SD8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_SD8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_SD8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_SD8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_SD8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_USB8
    ui->role_screen_label_USB8 = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_USB8, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->role_screen_label_USB8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_USB8, 205, 9);
    lv_obj_set_size(ui->role_screen_label_USB8, 41, 20);

    //Write style for role_screen_label_USB8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_USB8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_USB8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_USB8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_USB8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_USB8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_btn_esc8
    ui->role_screen_btn_esc8 = lv_btn_create(ui->role_screen);
    ui->role_screen_btn_esc8_label = lv_label_create(ui->role_screen_btn_esc8);
    lv_label_set_text(ui->role_screen_btn_esc8_label, "ESC");
    lv_label_set_long_mode(ui->role_screen_btn_esc8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->role_screen_btn_esc8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->role_screen_btn_esc8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->role_screen_btn_esc8_label, LV_PCT(100));
    lv_obj_set_pos(ui->role_screen_btn_esc8, 17, 204);
    lv_obj_set_size(ui->role_screen_btn_esc8, 100, 28);

    //Write style for role_screen_btn_esc8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->role_screen_btn_esc8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->role_screen_btn_esc8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->role_screen_btn_esc8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->role_screen_btn_esc8, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->role_screen_btn_esc8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->role_screen_btn_esc8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->role_screen_btn_esc8, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_btn_esc8, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_btn_esc8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_btn_esc8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_btn_esc8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_btn_esc8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_btn_esc8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_btn_ok8
    ui->role_screen_btn_ok8 = lv_btn_create(ui->role_screen);
    ui->role_screen_btn_ok8_label = lv_label_create(ui->role_screen_btn_ok8);
    lv_label_set_text(ui->role_screen_btn_ok8_label, "OK");
    lv_label_set_long_mode(ui->role_screen_btn_ok8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->role_screen_btn_ok8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->role_screen_btn_ok8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->role_screen_btn_ok8_label, LV_PCT(100));
    lv_obj_set_pos(ui->role_screen_btn_ok8, 205, 204);
    lv_obj_set_size(ui->role_screen_btn_ok8, 100, 28);

    //Write style for role_screen_btn_ok8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->role_screen_btn_ok8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->role_screen_btn_ok8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->role_screen_btn_ok8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->role_screen_btn_ok8, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->role_screen_btn_ok8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->role_screen_btn_ok8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->role_screen_btn_ok8, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_btn_ok8, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_btn_ok8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_btn_ok8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_btn_ok8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_btn_ok8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_btn_ok8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_cont_normal_user
    ui->role_screen_cont_normal_user = lv_obj_create(ui->role_screen);
    lv_obj_set_pos(ui->role_screen_cont_normal_user, -2, 92);
    lv_obj_set_size(ui->role_screen_cont_normal_user, 324, 35);
    lv_obj_set_scrollbar_mode(ui->role_screen_cont_normal_user, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->role_screen_cont_normal_user, LV_OBJ_FLAG_CHECKABLE);

    //Write style for role_screen_cont_normal_user, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_cont_normal_user, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->role_screen_cont_normal_user, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->role_screen_cont_normal_user, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->role_screen_cont_normal_user, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_cont_normal_user, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->role_screen_cont_normal_user, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->role_screen_cont_normal_user, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_text_normal_user
    ui->role_screen_text_normal_user = lv_label_create(ui->role_screen_cont_normal_user);
    lv_label_set_text(ui->role_screen_text_normal_user, "User");
    lv_label_set_long_mode(ui->role_screen_text_normal_user, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_text_normal_user, 10, 7);
    lv_obj_set_size(ui->role_screen_text_normal_user, 300, 20);

    //Write style for role_screen_text_normal_user, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_text_normal_user, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_text_normal_user, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_text_normal_user, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_text_normal_user, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_text_normal_user, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_cont_admin
    ui->role_screen_cont_admin = lv_obj_create(ui->role_screen);
    lv_obj_set_pos(ui->role_screen_cont_admin, -2, 127);
    lv_obj_set_size(ui->role_screen_cont_admin, 324, 35);
    lv_obj_set_scrollbar_mode(ui->role_screen_cont_admin, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->role_screen_cont_admin, LV_OBJ_FLAG_CHECKABLE);

    //Write style for role_screen_cont_admin, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_cont_admin, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->role_screen_cont_admin, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->role_screen_cont_admin, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->role_screen_cont_admin, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_cont_admin, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->role_screen_cont_admin, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->role_screen_cont_admin, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_text_admin
    ui->role_screen_text_admin = lv_label_create(ui->role_screen_cont_admin);
    lv_label_set_text(ui->role_screen_text_admin, "Admin");
    lv_label_set_long_mode(ui->role_screen_text_admin, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_text_admin, 10, 7);
    lv_obj_set_size(ui->role_screen_text_admin, 300, 20);

    //Write style for role_screen_text_admin, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_text_admin, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_text_admin, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_text_admin, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_text_admin, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_text_admin, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label
    ui->role_screen_label = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label, "Please set role");
    lv_label_set_long_mode(ui->role_screen_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label, 10, 39);
    lv_obj_set_size(ui->role_screen_label, 300, 18);

    //Write style for role_screen_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of role_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->role_screen);

}
