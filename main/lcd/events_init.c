/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void main_screen_btn_wifi_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.main_screen_wifi_fail_icon, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.main_screen_wifi_ok_icon, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void main_screen_btn_next_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.menu_screen, guider_ui.menu_screen_del, &guider_ui.main_screen_del, setup_scr_menu_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_main_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->main_screen_btn_wifi, main_screen_btn_wifi_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->main_screen_btn_next_screen, main_screen_btn_next_screen_event_handler, LV_EVENT_ALL, ui);
}

static void menu_screen_esc_label_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.main_screen, guider_ui.main_screen_del, &guider_ui.menu_screen_del, setup_scr_main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, false, true);
        break;
    }
    default:
        break;
    }
}

static void menu_screen_btn2_wifi_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.menu_screen_wifi2_fail_icon, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.menu_screen_wifi2_ok_icon, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

static void menu_screen_btn_menu_dwn_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        break;
    }
    default:
        break;
    }
}

static void menu_screen_btn_next_screen2_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.attendance_screen, guider_ui.attendance_screen_del, &guider_ui.menu_screen_del, setup_scr_attendance_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_menu_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->menu_screen_esc_label, menu_screen_esc_label_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_screen_btn2_wifi, menu_screen_btn2_wifi_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_screen_btn_menu_dwn, menu_screen_btn_menu_dwn_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_screen_btn_next_screen2, menu_screen_btn_next_screen2_event_handler, LV_EVENT_ALL, ui);
}

static void attendance_screen_esc_label3_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.main_screen, guider_ui.main_screen_del, &guider_ui.attendance_screen_del, setup_scr_main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void attendance_screen_btn3_wifi_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        lv_obj_add_flag(guider_ui.attendance_screen_wifi3_fail_icon, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(guider_ui.attendance_screen_wifi3_ok_icon, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}

void events_init_attendance_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->attendance_screen_esc_label3, attendance_screen_esc_label3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->attendance_screen_btn3_wifi, attendance_screen_btn3_wifi_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
