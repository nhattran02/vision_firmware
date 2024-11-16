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



void setup_scr_usrdata_screen(lv_ui *ui)
{
    //Write codes usrdata_screen
    ui->usrdata_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->usrdata_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->usrdata_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrdata_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for usrdata_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->usrdata_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrdata_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrdata_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrdata_screen_list_id
    ui->usrdata_screen_list_id = lv_list_create(ui->usrdata_screen);
    ui->usrdata_screen_list_id_item0 =lv_list_add_text(ui->usrdata_screen_list_id, "ID");
    ui->usrdata_screen_list_id_item1 =lv_list_add_text(ui->usrdata_screen_list_id, "1");
    ui->usrdata_screen_list_id_item2 =lv_list_add_text(ui->usrdata_screen_list_id, "2");
    ui->usrdata_screen_list_id_item3 =lv_list_add_text(ui->usrdata_screen_list_id, "3");
    ui->usrdata_screen_list_id_item4 =lv_list_add_text(ui->usrdata_screen_list_id, "4");
    ui->usrdata_screen_list_id_item5 =lv_list_add_text(ui->usrdata_screen_list_id, "5");
    ui->usrdata_screen_list_id_item6 =lv_list_add_text(ui->usrdata_screen_list_id, "6");
    ui->usrdata_screen_list_id_item7 =lv_list_add_text(ui->usrdata_screen_list_id, "7");
    ui->usrdata_screen_list_id_item8 =lv_list_add_text(ui->usrdata_screen_list_id, "8");
    ui->usrdata_screen_list_id_item9 =lv_list_add_text(ui->usrdata_screen_list_id, "9");
    ui->usrdata_screen_list_id_item10 =lv_list_add_text(ui->usrdata_screen_list_id, "10");
    lv_obj_set_pos(ui->usrdata_screen_list_id, 0, 10);
    lv_obj_set_size(ui->usrdata_screen_list_id, 41, 240);
    lv_obj_set_scrollbar_mode(ui->usrdata_screen_list_id, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_id_main_main_default
    static lv_style_t style_usrdata_screen_list_id_main_main_default;
    ui_init_style(&style_usrdata_screen_list_id_main_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_id_main_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_id_main_main_default, 0);
    lv_style_set_pad_right(&style_usrdata_screen_list_id_main_main_default, 0);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_id_main_main_default, 5);
    lv_style_set_bg_opa(&style_usrdata_screen_list_id_main_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_id_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_id_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_usrdata_screen_list_id_main_main_default, 0);
    lv_style_set_radius(&style_usrdata_screen_list_id_main_main_default, 0);
    lv_style_set_shadow_width(&style_usrdata_screen_list_id_main_main_default, 0);
    lv_obj_add_style(ui->usrdata_screen_list_id, &style_usrdata_screen_list_id_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_id_main_scrollbar_default
    static lv_style_t style_usrdata_screen_list_id_main_scrollbar_default;
    ui_init_style(&style_usrdata_screen_list_id_main_scrollbar_default);

    lv_style_set_radius(&style_usrdata_screen_list_id_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_usrdata_screen_list_id_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_id_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_id_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->usrdata_screen_list_id, &style_usrdata_screen_list_id_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_id_extra_btns_main_default
    static lv_style_t style_usrdata_screen_list_id_extra_btns_main_default;
    ui_init_style(&style_usrdata_screen_list_id_extra_btns_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_id_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_id_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_usrdata_screen_list_id_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_id_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_usrdata_screen_list_id_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_usrdata_screen_list_id_extra_btns_main_default, lv_color_hex(0x2f3243));
    lv_style_set_text_font(&style_usrdata_screen_list_id_extra_btns_main_default, &lv_font_montserrat_16);
    lv_style_set_text_opa(&style_usrdata_screen_list_id_extra_btns_main_default, 255);
    lv_style_set_radius(&style_usrdata_screen_list_id_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_usrdata_screen_list_id_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_id_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_id_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_id_extra_texts_main_default
    static lv_style_t style_usrdata_screen_list_id_extra_texts_main_default;
    ui_init_style(&style_usrdata_screen_list_id_extra_texts_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_id_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_id_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_usrdata_screen_list_id_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_id_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_usrdata_screen_list_id_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_usrdata_screen_list_id_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_usrdata_screen_list_id_extra_texts_main_default, &lv_font_montserrat_12);
    lv_style_set_text_opa(&style_usrdata_screen_list_id_extra_texts_main_default, 255);
    lv_style_set_radius(&style_usrdata_screen_list_id_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_usrdata_screen_list_id_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_usrdata_screen_list_id_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_id_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_id_extra_texts_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->usrdata_screen_list_id_item10, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_id_item9, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_id_item8, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_id_item7, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_id_item6, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_id_item5, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_id_item4, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_id_item3, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_id_item2, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_id_item1, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_id_item0, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrdata_screen_list_name
    ui->usrdata_screen_list_name = lv_list_create(ui->usrdata_screen);
    ui->usrdata_screen_list_name_item0 =lv_list_add_text(ui->usrdata_screen_list_name, "Name");
    ui->usrdata_screen_list_name_item1 =lv_list_add_text(ui->usrdata_screen_list_name, "Tran Minh Nhat");
    ui->usrdata_screen_list_name_item2 =lv_list_add_text(ui->usrdata_screen_list_name, "Tran Quoc Vinh Quang");
    ui->usrdata_screen_list_name_item3 =lv_list_add_text(ui->usrdata_screen_list_name, "Pham Tran Phuc Hau");
    ui->usrdata_screen_list_name_item4 =lv_list_add_text(ui->usrdata_screen_list_name, "Pham Anh Tuan");
    ui->usrdata_screen_list_name_item5 =lv_list_add_text(ui->usrdata_screen_list_name, "Nguyen Tran Trung Kien");
    ui->usrdata_screen_list_name_item6 =lv_list_add_text(ui->usrdata_screen_list_name, "Phan Duong Quoc Trong");
    ui->usrdata_screen_list_name_item7 =lv_list_add_text(ui->usrdata_screen_list_name, "Pham Thanh Duong");
    ui->usrdata_screen_list_name_item8 =lv_list_add_text(ui->usrdata_screen_list_name, "Do Chi Bao");
    ui->usrdata_screen_list_name_item9 =lv_list_add_text(ui->usrdata_screen_list_name, "Le Duc Minh");
    ui->usrdata_screen_list_name_item10 =lv_list_add_text(ui->usrdata_screen_list_name, "Nguyen Thien Phu");
    lv_obj_set_pos(ui->usrdata_screen_list_name, 40, 10);
    lv_obj_set_size(ui->usrdata_screen_list_name, 221, 240);
    lv_obj_set_scrollbar_mode(ui->usrdata_screen_list_name, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_name_main_main_default
    static lv_style_t style_usrdata_screen_list_name_main_main_default;
    ui_init_style(&style_usrdata_screen_list_name_main_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_name_main_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_name_main_main_default, 0);
    lv_style_set_pad_right(&style_usrdata_screen_list_name_main_main_default, 0);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_name_main_main_default, 5);
    lv_style_set_bg_opa(&style_usrdata_screen_list_name_main_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_name_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_name_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_usrdata_screen_list_name_main_main_default, 0);
    lv_style_set_radius(&style_usrdata_screen_list_name_main_main_default, 0);
    lv_style_set_shadow_width(&style_usrdata_screen_list_name_main_main_default, 0);
    lv_obj_add_style(ui->usrdata_screen_list_name, &style_usrdata_screen_list_name_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_name_main_scrollbar_default
    static lv_style_t style_usrdata_screen_list_name_main_scrollbar_default;
    ui_init_style(&style_usrdata_screen_list_name_main_scrollbar_default);

    lv_style_set_radius(&style_usrdata_screen_list_name_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_usrdata_screen_list_name_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_name_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_name_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->usrdata_screen_list_name, &style_usrdata_screen_list_name_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_name_extra_btns_main_default
    static lv_style_t style_usrdata_screen_list_name_extra_btns_main_default;
    ui_init_style(&style_usrdata_screen_list_name_extra_btns_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_name_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_name_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_usrdata_screen_list_name_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_name_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_usrdata_screen_list_name_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_usrdata_screen_list_name_extra_btns_main_default, lv_color_hex(0x2f3243));
    lv_style_set_text_font(&style_usrdata_screen_list_name_extra_btns_main_default, &lv_font_montserrat_16);
    lv_style_set_text_opa(&style_usrdata_screen_list_name_extra_btns_main_default, 255);
    lv_style_set_radius(&style_usrdata_screen_list_name_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_usrdata_screen_list_name_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_name_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_name_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_name_extra_texts_main_default
    static lv_style_t style_usrdata_screen_list_name_extra_texts_main_default;
    ui_init_style(&style_usrdata_screen_list_name_extra_texts_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_name_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_name_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_usrdata_screen_list_name_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_name_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_usrdata_screen_list_name_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_usrdata_screen_list_name_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_usrdata_screen_list_name_extra_texts_main_default, &lv_font_montserrat_12);
    lv_style_set_text_opa(&style_usrdata_screen_list_name_extra_texts_main_default, 255);
    lv_style_set_radius(&style_usrdata_screen_list_name_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_usrdata_screen_list_name_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_usrdata_screen_list_name_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_name_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_name_extra_texts_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->usrdata_screen_list_name_item10, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_name_item9, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_name_item8, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_name_item7, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_name_item6, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_name_item5, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_name_item4, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_name_item3, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_name_item2, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_name_item1, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_name_item0, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrdata_screen_list_role
    ui->usrdata_screen_list_role = lv_list_create(ui->usrdata_screen);
    ui->usrdata_screen_list_role_item0 =lv_list_add_text(ui->usrdata_screen_list_role, "Role");
    ui->usrdata_screen_list_role_item1 =lv_list_add_text(ui->usrdata_screen_list_role, "Admin");
    ui->usrdata_screen_list_role_item2 =lv_list_add_text(ui->usrdata_screen_list_role, "User");
    ui->usrdata_screen_list_role_item3 =lv_list_add_text(ui->usrdata_screen_list_role, "User");
    ui->usrdata_screen_list_role_item4 =lv_list_add_text(ui->usrdata_screen_list_role, "User");
    ui->usrdata_screen_list_role_item5 =lv_list_add_text(ui->usrdata_screen_list_role, "User");
    ui->usrdata_screen_list_role_item6 =lv_list_add_text(ui->usrdata_screen_list_role, "User");
    ui->usrdata_screen_list_role_item7 =lv_list_add_text(ui->usrdata_screen_list_role, "User");
    ui->usrdata_screen_list_role_item8 =lv_list_add_text(ui->usrdata_screen_list_role, "User");
    ui->usrdata_screen_list_role_item9 =lv_list_add_text(ui->usrdata_screen_list_role, "User");
    ui->usrdata_screen_list_role_item10 =lv_list_add_text(ui->usrdata_screen_list_role, "User");
    lv_obj_set_pos(ui->usrdata_screen_list_role, 260, 10);
    lv_obj_set_size(ui->usrdata_screen_list_role, 60, 240);
    lv_obj_set_scrollbar_mode(ui->usrdata_screen_list_role, LV_SCROLLBAR_MODE_OFF);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_role_main_main_default
    static lv_style_t style_usrdata_screen_list_role_main_main_default;
    ui_init_style(&style_usrdata_screen_list_role_main_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_role_main_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_role_main_main_default, 0);
    lv_style_set_pad_right(&style_usrdata_screen_list_role_main_main_default, 0);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_role_main_main_default, 5);
    lv_style_set_bg_opa(&style_usrdata_screen_list_role_main_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_role_main_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_role_main_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_usrdata_screen_list_role_main_main_default, 0);
    lv_style_set_radius(&style_usrdata_screen_list_role_main_main_default, 0);
    lv_style_set_shadow_width(&style_usrdata_screen_list_role_main_main_default, 0);
    lv_obj_add_style(ui->usrdata_screen_list_role, &style_usrdata_screen_list_role_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_role_main_scrollbar_default
    static lv_style_t style_usrdata_screen_list_role_main_scrollbar_default;
    ui_init_style(&style_usrdata_screen_list_role_main_scrollbar_default);

    lv_style_set_radius(&style_usrdata_screen_list_role_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_usrdata_screen_list_role_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_role_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_role_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->usrdata_screen_list_role, &style_usrdata_screen_list_role_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_role_extra_btns_main_default
    static lv_style_t style_usrdata_screen_list_role_extra_btns_main_default;
    ui_init_style(&style_usrdata_screen_list_role_extra_btns_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_role_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_role_extra_btns_main_default, 5);
    lv_style_set_pad_right(&style_usrdata_screen_list_role_extra_btns_main_default, 5);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_role_extra_btns_main_default, 5);
    lv_style_set_border_width(&style_usrdata_screen_list_role_extra_btns_main_default, 0);
    lv_style_set_text_color(&style_usrdata_screen_list_role_extra_btns_main_default, lv_color_hex(0x2f3243));
    lv_style_set_text_font(&style_usrdata_screen_list_role_extra_btns_main_default, &lv_font_montserrat_16);
    lv_style_set_text_opa(&style_usrdata_screen_list_role_extra_btns_main_default, 255);
    lv_style_set_radius(&style_usrdata_screen_list_role_extra_btns_main_default, 3);
    lv_style_set_bg_opa(&style_usrdata_screen_list_role_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_role_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_role_extra_btns_main_default, LV_GRAD_DIR_NONE);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_role_extra_texts_main_default
    static lv_style_t style_usrdata_screen_list_role_extra_texts_main_default;
    ui_init_style(&style_usrdata_screen_list_role_extra_texts_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_role_extra_texts_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_role_extra_texts_main_default, 5);
    lv_style_set_pad_right(&style_usrdata_screen_list_role_extra_texts_main_default, 5);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_role_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_usrdata_screen_list_role_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_usrdata_screen_list_role_extra_texts_main_default, lv_color_hex(0x0D3055));
    lv_style_set_text_font(&style_usrdata_screen_list_role_extra_texts_main_default, &lv_font_montserrat_12);
    lv_style_set_text_opa(&style_usrdata_screen_list_role_extra_texts_main_default, 255);
    lv_style_set_radius(&style_usrdata_screen_list_role_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_usrdata_screen_list_role_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_usrdata_screen_list_role_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_role_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_role_extra_texts_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->usrdata_screen_list_role_item10, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_role_item9, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_role_item8, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_role_item7, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_role_item6, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_role_item5, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_role_item4, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_role_item3, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_role_item2, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_role_item1, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->usrdata_screen_list_role_item0, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of usrdata_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->usrdata_screen);

    //Init events for screen.
    events_init_usrdata_screen(ui);
}
