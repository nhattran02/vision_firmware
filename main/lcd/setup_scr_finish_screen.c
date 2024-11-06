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



void setup_scr_finish_screen(lv_ui *ui)
{
    //Write codes finish_screen
    ui->finish_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->finish_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->finish_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for finish_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->finish_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->finish_screen, lv_color_hex(0xF3F8FE), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->finish_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finish_screen_cont_bg4
    ui->finish_screen_cont_bg4 = lv_obj_create(ui->finish_screen);
    lv_obj_set_pos(ui->finish_screen_cont_bg4, 0, 0);
    lv_obj_set_size(ui->finish_screen_cont_bg4, 320, 240);
    lv_obj_set_scrollbar_mode(ui->finish_screen_cont_bg4, LV_SCROLLBAR_MODE_OFF);

    //Write style for finish_screen_cont_bg4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finish_screen_cont_bg4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finish_screen_cont_bg4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finish_screen_cont_bg4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->finish_screen_cont_bg4, lv_color_hex(0x28b620), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->finish_screen_cont_bg4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finish_screen_cont_bg4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finish_screen_cont_bg4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finish_screen_cont_bg4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finish_screen_cont_bg4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finish_screen_cont_bg4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finish_screen_btn_next
    ui->finish_screen_btn_next = lv_btn_create(ui->finish_screen_cont_bg4);
    ui->finish_screen_btn_next_label = lv_label_create(ui->finish_screen_btn_next);
    lv_label_set_text(ui->finish_screen_btn_next_label, "OK");
    lv_label_set_long_mode(ui->finish_screen_btn_next_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->finish_screen_btn_next_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->finish_screen_btn_next, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->finish_screen_btn_next_label, LV_PCT(100));
    lv_obj_set_pos(ui->finish_screen_btn_next, 80, 170);
    lv_obj_set_size(ui->finish_screen_btn_next, 160, 40);

    //Write style for finish_screen_btn_next, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->finish_screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->finish_screen_btn_next, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->finish_screen_btn_next, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->finish_screen_btn_next, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->finish_screen_btn_next, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finish_screen_btn_next, 19, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finish_screen_btn_next, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finish_screen_btn_next, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finish_screen_btn_next, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finish_screen_btn_next, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finish_screen_btn_next, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finish_screen_label_prompt4
    ui->finish_screen_label_prompt4 = lv_label_create(ui->finish_screen);
    lv_label_set_text(ui->finish_screen_label_prompt4, "Done");
    lv_label_set_long_mode(ui->finish_screen_label_prompt4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finish_screen_label_prompt4, 17, 130);
    lv_obj_set_size(ui->finish_screen_label_prompt4, 286, 28);

    //Write style for finish_screen_label_prompt4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finish_screen_label_prompt4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finish_screen_label_prompt4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finish_screen_label_prompt4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finish_screen_label_prompt4, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finish_screen_label_prompt4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finish_screen_label_prompt4, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finish_screen_label_prompt4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finish_screen_label_prompt4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finish_screen_label_prompt4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finish_screen_label_prompt4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finish_screen_label_prompt4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finish_screen_label_prompt4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finish_screen_label_prompt4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finish_screen_label_prompt4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finish_screen_img_icon_ok
    ui->finish_screen_img_icon_ok = lv_img_create(ui->finish_screen);
    lv_obj_add_flag(ui->finish_screen_img_icon_ok, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->finish_screen_img_icon_ok, &_ready_alpha_80x80);
    lv_img_set_pivot(ui->finish_screen_img_icon_ok, 50,50);
    lv_img_set_angle(ui->finish_screen_img_icon_ok, 0);
    lv_obj_set_pos(ui->finish_screen_img_icon_ok, 121, 35);
    lv_obj_set_size(ui->finish_screen_img_icon_ok, 80, 80);

    //Write style for finish_screen_img_icon_ok, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->finish_screen_img_icon_ok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->finish_screen_img_icon_ok, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finish_screen_img_icon_ok, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->finish_screen_img_icon_ok, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of finish_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->finish_screen);

}
