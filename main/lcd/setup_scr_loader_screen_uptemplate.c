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



void setup_scr_loader_screen_uptemplate(lv_ui *ui)
{
    //Write codes loader_screen_uptemplate
    ui->loader_screen_uptemplate = lv_obj_create(NULL);
    lv_obj_set_size(ui->loader_screen_uptemplate, 320, 240);
    lv_obj_set_scrollbar_mode(ui->loader_screen_uptemplate, LV_SCROLLBAR_MODE_OFF);

    //Write style for loader_screen_uptemplate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->loader_screen_uptemplate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->loader_screen_uptemplate, lv_color_hex(0xF3F8FE), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->loader_screen_uptemplate, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes loader_screen_uptemplate_cont_bg3
    ui->loader_screen_uptemplate_cont_bg3 = lv_obj_create(ui->loader_screen_uptemplate);
    lv_obj_set_pos(ui->loader_screen_uptemplate_cont_bg3, 0, 0);
    lv_obj_set_size(ui->loader_screen_uptemplate_cont_bg3, 320, 240);
    lv_obj_set_scrollbar_mode(ui->loader_screen_uptemplate_cont_bg3, LV_SCROLLBAR_MODE_OFF);

    //Write style for loader_screen_uptemplate_cont_bg3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->loader_screen_uptemplate_cont_bg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->loader_screen_uptemplate_cont_bg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->loader_screen_uptemplate_cont_bg3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->loader_screen_uptemplate_cont_bg3, lv_color_hex(0x0a2c6a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->loader_screen_uptemplate_cont_bg3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->loader_screen_uptemplate_cont_bg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->loader_screen_uptemplate_cont_bg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->loader_screen_uptemplate_cont_bg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->loader_screen_uptemplate_cont_bg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->loader_screen_uptemplate_cont_bg3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes loader_screen_uptemplate_arc_loader3
    ui->loader_screen_uptemplate_arc_loader3 = lv_arc_create(ui->loader_screen_uptemplate);
    lv_arc_set_mode(ui->loader_screen_uptemplate_arc_loader3, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->loader_screen_uptemplate_arc_loader3, 0, 100);
    lv_arc_set_bg_angles(ui->loader_screen_uptemplate_arc_loader3, 0, 360);
    lv_arc_set_value(ui->loader_screen_uptemplate_arc_loader3, 70);
    lv_arc_set_rotation(ui->loader_screen_uptemplate_arc_loader3, 270);
    lv_obj_set_pos(ui->loader_screen_uptemplate_arc_loader3, 100, 60);
    lv_obj_set_size(ui->loader_screen_uptemplate_arc_loader3, 120, 120);

    //Write style for loader_screen_uptemplate_arc_loader3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->loader_screen_uptemplate_arc_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->loader_screen_uptemplate_arc_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->loader_screen_uptemplate_arc_loader3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->loader_screen_uptemplate_arc_loader3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->loader_screen_uptemplate_arc_loader3, lv_color_hex(0x0a2c6a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->loader_screen_uptemplate_arc_loader3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->loader_screen_uptemplate_arc_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->loader_screen_uptemplate_arc_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->loader_screen_uptemplate_arc_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->loader_screen_uptemplate_arc_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->loader_screen_uptemplate_arc_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for loader_screen_uptemplate_arc_loader3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->loader_screen_uptemplate_arc_loader3, 6, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->loader_screen_uptemplate_arc_loader3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->loader_screen_uptemplate_arc_loader3, lv_color_hex(0xffffff), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for loader_screen_uptemplate_arc_loader3, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->loader_screen_uptemplate_arc_loader3, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->loader_screen_uptemplate_arc_loader3, 0, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes loader_screen_uptemplate_label_prompt3
    ui->loader_screen_uptemplate_label_prompt3 = lv_label_create(ui->loader_screen_uptemplate);
    lv_label_set_text(ui->loader_screen_uptemplate_label_prompt3, "" LV_SYMBOL_UPLOAD " Uploading from Template...");
    lv_label_set_long_mode(ui->loader_screen_uptemplate_label_prompt3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->loader_screen_uptemplate_label_prompt3, 17, 201);
    lv_obj_set_size(ui->loader_screen_uptemplate_label_prompt3, 286, 28);

    //Write style for loader_screen_uptemplate_label_prompt3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->loader_screen_uptemplate_label_prompt3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->loader_screen_uptemplate_label_prompt3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->loader_screen_uptemplate_label_prompt3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->loader_screen_uptemplate_label_prompt3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->loader_screen_uptemplate_label_prompt3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->loader_screen_uptemplate_label_prompt3, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->loader_screen_uptemplate_label_prompt3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->loader_screen_uptemplate_label_prompt3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->loader_screen_uptemplate_label_prompt3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->loader_screen_uptemplate_label_prompt3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->loader_screen_uptemplate_label_prompt3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->loader_screen_uptemplate_label_prompt3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->loader_screen_uptemplate_label_prompt3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->loader_screen_uptemplate_label_prompt3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes loader_screen_uptemplate_label_loader3
    ui->loader_screen_uptemplate_label_loader3 = lv_label_create(ui->loader_screen_uptemplate);
    lv_label_set_text(ui->loader_screen_uptemplate_label_loader3, "0%");
    lv_label_set_long_mode(ui->loader_screen_uptemplate_label_loader3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->loader_screen_uptemplate_label_loader3, 120, 114);
    lv_obj_set_size(ui->loader_screen_uptemplate_label_loader3, 80, 28);

    //Write style for loader_screen_uptemplate_label_loader3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->loader_screen_uptemplate_label_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->loader_screen_uptemplate_label_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->loader_screen_uptemplate_label_loader3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->loader_screen_uptemplate_label_loader3, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->loader_screen_uptemplate_label_loader3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->loader_screen_uptemplate_label_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->loader_screen_uptemplate_label_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->loader_screen_uptemplate_label_loader3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->loader_screen_uptemplate_label_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->loader_screen_uptemplate_label_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->loader_screen_uptemplate_label_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->loader_screen_uptemplate_label_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->loader_screen_uptemplate_label_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->loader_screen_uptemplate_label_loader3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of loader_screen_uptemplate.


    //Update current screen layout.
    lv_obj_update_layout(ui->loader_screen_uptemplate);

    //Init events for screen.
    events_init_loader_screen_uptemplate(ui);
}
