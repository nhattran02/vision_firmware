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



void setup_scr_usrinfo_screen(lv_ui *ui)
{
    //Write codes usrinfo_screen
    ui->usrinfo_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->usrinfo_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->usrinfo_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrinfo_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for usrinfo_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->usrinfo_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_time5
    ui->usrinfo_screen_label_time5 = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_time5, "11:00");
    lv_label_set_long_mode(ui->usrinfo_screen_label_time5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_time5, -31, 8);
    lv_obj_set_size(ui->usrinfo_screen_label_time5, 128, 20);

    //Write style for usrinfo_screen_label_time5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_time5, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_time5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_time5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_time5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_time5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_usrinfo_name
    ui->usrinfo_screen_label_usrinfo_name = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_usrinfo_name, "User Info");
    lv_label_set_long_mode(ui->usrinfo_screen_label_usrinfo_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_usrinfo_name, 96, 8);
    lv_obj_set_size(ui->usrinfo_screen_label_usrinfo_name, 128, 17);

    //Write style for usrinfo_screen_label_usrinfo_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_usrinfo_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_usrinfo_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_usrinfo_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_usrinfo_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_usrinfo_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_WIFI5
    ui->usrinfo_screen_label_WIFI5 = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_WIFI5, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->usrinfo_screen_label_WIFI5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_WIFI5, 284, 9);
    lv_obj_set_size(ui->usrinfo_screen_label_WIFI5, 41, 20);

    //Write style for usrinfo_screen_label_WIFI5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_WIFI5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_WIFI5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_WIFI5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_WIFI5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_WIFI5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_BT5
    ui->usrinfo_screen_label_BT5 = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_BT5, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->usrinfo_screen_label_BT5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_BT5, 260, 9);
    lv_obj_set_size(ui->usrinfo_screen_label_BT5, 41, 20);

    //Write style for usrinfo_screen_label_BT5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_BT5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_BT5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_BT5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_BT5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_BT5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_SD5
    ui->usrinfo_screen_label_SD5 = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_SD5, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->usrinfo_screen_label_SD5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_SD5, 232, 9);
    lv_obj_set_size(ui->usrinfo_screen_label_SD5, 41, 20);

    //Write style for usrinfo_screen_label_SD5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_SD5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_SD5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_SD5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_SD5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_SD5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_USB5
    ui->usrinfo_screen_label_USB5 = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_USB5, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->usrinfo_screen_label_USB5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_USB5, 205, 9);
    lv_obj_set_size(ui->usrinfo_screen_label_USB5, 41, 20);

    //Write style for usrinfo_screen_label_USB5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_USB5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_USB5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_USB5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_USB5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_USB5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_btn_esc5
    ui->usrinfo_screen_btn_esc5 = lv_btn_create(ui->usrinfo_screen);
    ui->usrinfo_screen_btn_esc5_label = lv_label_create(ui->usrinfo_screen_btn_esc5);
    lv_label_set_text(ui->usrinfo_screen_btn_esc5_label, "ESC");
    lv_label_set_long_mode(ui->usrinfo_screen_btn_esc5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->usrinfo_screen_btn_esc5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->usrinfo_screen_btn_esc5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->usrinfo_screen_btn_esc5_label, LV_PCT(100));
    lv_obj_set_pos(ui->usrinfo_screen_btn_esc5, 17, 204);
    lv_obj_set_size(ui->usrinfo_screen_btn_esc5, 100, 28);

    //Write style for usrinfo_screen_btn_esc5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_btn_esc5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_btn_esc5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_btn_esc5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->usrinfo_screen_btn_esc5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_btn_esc5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_btn_esc5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_btn_esc5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_btn_esc5, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_btn_esc5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_btn_esc5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_btn_esc5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_btn_esc5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_btn_esc5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_btn_ok5
    ui->usrinfo_screen_btn_ok5 = lv_btn_create(ui->usrinfo_screen);
    ui->usrinfo_screen_btn_ok5_label = lv_label_create(ui->usrinfo_screen_btn_ok5);
    lv_label_set_text(ui->usrinfo_screen_btn_ok5_label, "OK");
    lv_label_set_long_mode(ui->usrinfo_screen_btn_ok5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->usrinfo_screen_btn_ok5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->usrinfo_screen_btn_ok5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->usrinfo_screen_btn_ok5_label, LV_PCT(100));
    lv_obj_set_pos(ui->usrinfo_screen_btn_ok5, 205, 204);
    lv_obj_set_size(ui->usrinfo_screen_btn_ok5, 100, 28);

    //Write style for usrinfo_screen_btn_ok5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_btn_ok5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_btn_ok5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_btn_ok5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->usrinfo_screen_btn_ok5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_btn_ok5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_btn_ok5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_btn_ok5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_btn_ok5, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_btn_ok5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_btn_ok5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_btn_ok5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_btn_ok5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_btn_ok5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_cont_password
    ui->usrinfo_screen_cont_password = lv_obj_create(ui->usrinfo_screen);
    lv_obj_set_pos(ui->usrinfo_screen_cont_password, -2, 96);
    lv_obj_set_size(ui->usrinfo_screen_cont_password, 324, 35);
    lv_obj_set_scrollbar_mode(ui->usrinfo_screen_cont_password, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrinfo_screen_cont_password, LV_OBJ_FLAG_CHECKABLE);

    //Write style for usrinfo_screen_cont_password, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_cont_password, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_cont_password, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_cont_password, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_cont_password, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_cont_password, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_cont_password, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_cont_password, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_pw_text
    ui->usrinfo_screen_label_pw_text = lv_label_create(ui->usrinfo_screen_cont_password);
    lv_label_set_text(ui->usrinfo_screen_label_pw_text, "Password");
    lv_label_set_long_mode(ui->usrinfo_screen_label_pw_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_pw_text, 3, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_pw_text, 104, 20);

    //Write style for usrinfo_screen_label_pw_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_pw_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_pw_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_pw_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_pw_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_pw_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_pw_value
    ui->usrinfo_screen_label_pw_value = lv_label_create(ui->usrinfo_screen_cont_password);
    lv_label_set_text(ui->usrinfo_screen_label_pw_value, "Not Set");
    lv_label_set_long_mode(ui->usrinfo_screen_label_pw_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_pw_value, 230, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_pw_value, 90, 19);

    //Write style for usrinfo_screen_label_pw_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_pw_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_pw_value, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_pw_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_pw_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_pw_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_cont_faceid
    ui->usrinfo_screen_cont_faceid = lv_obj_create(ui->usrinfo_screen);
    lv_obj_set_pos(ui->usrinfo_screen_cont_faceid, -2, 131);
    lv_obj_set_size(ui->usrinfo_screen_cont_faceid, 324, 35);
    lv_obj_set_scrollbar_mode(ui->usrinfo_screen_cont_faceid, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrinfo_screen_cont_faceid, LV_OBJ_FLAG_CHECKABLE);

    //Write style for usrinfo_screen_cont_faceid, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_cont_faceid, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_cont_faceid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_cont_faceid, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_cont_faceid, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_cont_faceid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_cont_faceid, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_cont_faceid, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_faceid_text
    ui->usrinfo_screen_label_faceid_text = lv_label_create(ui->usrinfo_screen_cont_faceid);
    lv_label_set_text(ui->usrinfo_screen_label_faceid_text, "FaceID");
    lv_label_set_long_mode(ui->usrinfo_screen_label_faceid_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_faceid_text, 3, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_faceid_text, 104, 20);

    //Write style for usrinfo_screen_label_faceid_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_faceid_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_faceid_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_faceid_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_faceid_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_faceid_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_faceid_value
    ui->usrinfo_screen_label_faceid_value = lv_label_create(ui->usrinfo_screen_cont_faceid);
    lv_label_set_text(ui->usrinfo_screen_label_faceid_value, "Not Set");
    lv_label_set_long_mode(ui->usrinfo_screen_label_faceid_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_faceid_value, 230, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_faceid_value, 90, 19);

    //Write style for usrinfo_screen_label_faceid_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_faceid_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_faceid_value, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_faceid_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_faceid_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_faceid_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_cont_finger
    ui->usrinfo_screen_cont_finger = lv_obj_create(ui->usrinfo_screen);
    lv_obj_set_pos(ui->usrinfo_screen_cont_finger, -2, 61);
    lv_obj_set_size(ui->usrinfo_screen_cont_finger, 324, 35);
    lv_obj_set_scrollbar_mode(ui->usrinfo_screen_cont_finger, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrinfo_screen_cont_finger, LV_OBJ_FLAG_CHECKABLE);

    //Write style for usrinfo_screen_cont_finger, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_cont_finger, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_cont_finger, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_cont_finger, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_cont_finger, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_cont_finger, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_cont_finger, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_cont_finger, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_finger_text
    ui->usrinfo_screen_label_finger_text = lv_label_create(ui->usrinfo_screen_cont_finger);
    lv_label_set_text(ui->usrinfo_screen_label_finger_text, "Finger\n");
    lv_label_set_long_mode(ui->usrinfo_screen_label_finger_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_finger_text, 3, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_finger_text, 104, 20);

    //Write style for usrinfo_screen_label_finger_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_finger_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_finger_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_finger_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_finger_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_finger_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_finger_value
    ui->usrinfo_screen_label_finger_value = lv_label_create(ui->usrinfo_screen_cont_finger);
    lv_label_set_text(ui->usrinfo_screen_label_finger_value, "0/1");
    lv_label_set_long_mode(ui->usrinfo_screen_label_finger_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_finger_value, 290, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_finger_value, 32, 19);

    //Write style for usrinfo_screen_label_finger_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_finger_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_finger_value, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_finger_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_finger_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_finger_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_usrid
    ui->usrinfo_screen_label_usrid = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_usrid, "ID: 5");
    lv_label_set_long_mode(ui->usrinfo_screen_label_usrid, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_usrid, 3, 39);
    lv_obj_set_size(ui->usrinfo_screen_label_usrid, 87, 19);

    //Write style for usrinfo_screen_label_usrid, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_usrid, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_usrid, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_usrid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_usrid, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_usrid, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_usrname
    ui->usrinfo_screen_label_usrname = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_usrname, "Tran Minh Nhat");
    lv_label_set_long_mode(ui->usrinfo_screen_label_usrname, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_usrname, 60, 39);
    lv_obj_set_size(ui->usrinfo_screen_label_usrname, 255, 19);

    //Write style for usrinfo_screen_label_usrname, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_usrname, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_usrname, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_usrname, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_usrname, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_usrname, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_cont_role
    ui->usrinfo_screen_cont_role = lv_obj_create(ui->usrinfo_screen);
    lv_obj_set_pos(ui->usrinfo_screen_cont_role, -2, 166);
    lv_obj_set_size(ui->usrinfo_screen_cont_role, 324, 35);
    lv_obj_set_scrollbar_mode(ui->usrinfo_screen_cont_role, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrinfo_screen_cont_role, LV_OBJ_FLAG_CHECKABLE);

    //Write style for usrinfo_screen_cont_role, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_cont_role, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_cont_role, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_cont_role, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_cont_role, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_cont_role, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_cont_role, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_cont_role, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_role_text
    ui->usrinfo_screen_label_role_text = lv_label_create(ui->usrinfo_screen_cont_role);
    lv_label_set_text(ui->usrinfo_screen_label_role_text, "Role");
    lv_label_set_long_mode(ui->usrinfo_screen_label_role_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_role_text, 3, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_role_text, 104, 20);

    //Write style for usrinfo_screen_label_role_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_role_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_role_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_role_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_role_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_role_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_role_value
    ui->usrinfo_screen_label_role_value = lv_label_create(ui->usrinfo_screen_cont_role);
    lv_label_set_text(ui->usrinfo_screen_label_role_value, "User");
    lv_label_set_long_mode(ui->usrinfo_screen_label_role_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_role_value, 230, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_role_value, 90, 19);

    //Write style for usrinfo_screen_label_role_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_role_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_role_value, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_role_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_role_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_role_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of usrinfo_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->usrinfo_screen);

    //Init events for screen.
    events_init_usrinfo_screen(ui);
}
