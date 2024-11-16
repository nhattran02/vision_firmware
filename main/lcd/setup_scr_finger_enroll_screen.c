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



void setup_scr_finger_enroll_screen(lv_ui *ui)
{
    //Write codes finger_enroll_screen
    ui->finger_enroll_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->finger_enroll_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->finger_enroll_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->finger_enroll_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for finger_enroll_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->finger_enroll_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->finger_enroll_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_time6
    ui->finger_enroll_screen_label_time6 = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_time6, "11:00");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_time6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_time6, -31, 8);
    lv_obj_set_size(ui->finger_enroll_screen_label_time6, 128, 20);

    //Write style for finger_enroll_screen_label_time6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_time6, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_time6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_time6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_time6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_time6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_fpenroll_name
    ui->finger_enroll_screen_label_fpenroll_name = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_fpenroll_name, "FP Enroll");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_fpenroll_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_fpenroll_name, 96, 8);
    lv_obj_set_size(ui->finger_enroll_screen_label_fpenroll_name, 128, 17);

    //Write style for finger_enroll_screen_label_fpenroll_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_fpenroll_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_fpenroll_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_fpenroll_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_fpenroll_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_fpenroll_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_WIFI6
    ui->finger_enroll_screen_label_WIFI6 = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_WIFI6, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_WIFI6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_WIFI6, 284, 9);
    lv_obj_set_size(ui->finger_enroll_screen_label_WIFI6, 41, 20);

    //Write style for finger_enroll_screen_label_WIFI6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_WIFI6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_WIFI6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_WIFI6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_WIFI6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_WIFI6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_BT6
    ui->finger_enroll_screen_label_BT6 = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_BT6, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_BT6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_BT6, 260, 9);
    lv_obj_set_size(ui->finger_enroll_screen_label_BT6, 41, 20);

    //Write style for finger_enroll_screen_label_BT6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_BT6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_BT6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_BT6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_BT6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_BT6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_SD6
    ui->finger_enroll_screen_label_SD6 = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_SD6, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_SD6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_SD6, 232, 9);
    lv_obj_set_size(ui->finger_enroll_screen_label_SD6, 41, 20);

    //Write style for finger_enroll_screen_label_SD6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_SD6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_SD6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_SD6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_SD6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_SD6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_USB6
    ui->finger_enroll_screen_label_USB6 = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_USB6, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_USB6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_USB6, 205, 9);
    lv_obj_set_size(ui->finger_enroll_screen_label_USB6, 41, 20);

    //Write style for finger_enroll_screen_label_USB6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_USB6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_USB6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_USB6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_USB6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_USB6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_btn_esc6
    ui->finger_enroll_screen_btn_esc6 = lv_btn_create(ui->finger_enroll_screen);
    ui->finger_enroll_screen_btn_esc6_label = lv_label_create(ui->finger_enroll_screen_btn_esc6);
    lv_label_set_text(ui->finger_enroll_screen_btn_esc6_label, "ESC");
    lv_label_set_long_mode(ui->finger_enroll_screen_btn_esc6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->finger_enroll_screen_btn_esc6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->finger_enroll_screen_btn_esc6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->finger_enroll_screen_btn_esc6_label, LV_PCT(100));
    lv_obj_set_pos(ui->finger_enroll_screen_btn_esc6, 17, 204);
    lv_obj_set_size(ui->finger_enroll_screen_btn_esc6, 100, 28);

    //Write style for finger_enroll_screen_btn_esc6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_btn_esc6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->finger_enroll_screen_btn_esc6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->finger_enroll_screen_btn_esc6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->finger_enroll_screen_btn_esc6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->finger_enroll_screen_btn_esc6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->finger_enroll_screen_btn_esc6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->finger_enroll_screen_btn_esc6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_btn_esc6, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_btn_esc6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_btn_esc6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_btn_esc6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_btn_esc6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_btn_esc6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_btn_ok6
    ui->finger_enroll_screen_btn_ok6 = lv_btn_create(ui->finger_enroll_screen);
    ui->finger_enroll_screen_btn_ok6_label = lv_label_create(ui->finger_enroll_screen_btn_ok6);
    lv_label_set_text(ui->finger_enroll_screen_btn_ok6_label, "OK");
    lv_label_set_long_mode(ui->finger_enroll_screen_btn_ok6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->finger_enroll_screen_btn_ok6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->finger_enroll_screen_btn_ok6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->finger_enroll_screen_btn_ok6_label, LV_PCT(100));
    lv_obj_set_pos(ui->finger_enroll_screen_btn_ok6, 205, 204);
    lv_obj_set_size(ui->finger_enroll_screen_btn_ok6, 100, 28);

    //Write style for finger_enroll_screen_btn_ok6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_btn_ok6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->finger_enroll_screen_btn_ok6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->finger_enroll_screen_btn_ok6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->finger_enroll_screen_btn_ok6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->finger_enroll_screen_btn_ok6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->finger_enroll_screen_btn_ok6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->finger_enroll_screen_btn_ok6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_btn_ok6, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_btn_ok6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_btn_ok6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_btn_ok6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_btn_ok6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_btn_ok6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_id_fp
    ui->finger_enroll_screen_label_id_fp = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_id_fp, "ID-1  FP-2");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_id_fp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_id_fp, 87, 69);
    lv_obj_set_size(ui->finger_enroll_screen_label_id_fp, 146, 19);

    //Write style for finger_enroll_screen_label_id_fp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_id_fp, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_id_fp, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_id_fp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_id_fp, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_id_fp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_info_fp
    ui->finger_enroll_screen_label_info_fp = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_info_fp, "Please place your finger");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_info_fp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_info_fp, 9, 98);
    lv_obj_set_size(ui->finger_enroll_screen_label_info_fp, 300, 19);

    //Write style for finger_enroll_screen_label_info_fp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_info_fp, lv_color_hex(0x28b620), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_info_fp, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_info_fp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_info_fp, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_info_fp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_led_1
    ui->finger_enroll_screen_led_1 = lv_led_create(ui->finger_enroll_screen);
    lv_led_set_brightness(ui->finger_enroll_screen_led_1, 255);
    lv_led_set_color(ui->finger_enroll_screen_led_1, lv_color_hex(0x6b6c6b));
    lv_obj_set_pos(ui->finger_enroll_screen_led_1, 120, 137);
    lv_obj_set_size(ui->finger_enroll_screen_led_1, 20, 20);

    //Write codes finger_enroll_screen_led_2
    ui->finger_enroll_screen_led_2 = lv_led_create(ui->finger_enroll_screen);
    lv_led_set_brightness(ui->finger_enroll_screen_led_2, 255);
    lv_led_set_color(ui->finger_enroll_screen_led_2, lv_color_hex(0xb70000));
    lv_obj_set_pos(ui->finger_enroll_screen_led_2, 179, 137);
    lv_obj_set_size(ui->finger_enroll_screen_led_2, 20, 20);

    //The custom code of finger_enroll_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->finger_enroll_screen);

}
