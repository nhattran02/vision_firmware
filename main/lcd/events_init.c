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


static void main_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.attendance_screen, guider_ui.attendance_screen_del, &guider_ui.main_screen_del, setup_scr_attendance_screen, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_main_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->main_screen, main_screen_event_handler, LV_EVENT_ALL, ui);
}

static void menu_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.main_screen, guider_ui.main_screen_del, &guider_ui.menu_screen_del, setup_scr_main_screen, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_menu_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->menu_screen, menu_screen_event_handler, LV_EVENT_ALL, ui);
}

static void data_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.usrdata_screen, guider_ui.usrdata_screen_del, &guider_ui.data_screen_del, setup_scr_usrdata_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_data_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->data_screen, data_screen_event_handler, LV_EVENT_ALL, ui);
}

static void usrdata_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.data_screen, guider_ui.data_screen_del, &guider_ui.usrdata_screen_del, setup_scr_data_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_usrdata_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->usrdata_screen, usrdata_screen_event_handler, LV_EVENT_ALL, ui);
}

static void usrinfo_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.usrdata_screen, guider_ui.usrdata_screen_del, &guider_ui.usrinfo_screen_del, setup_scr_usrdata_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_usrinfo_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->usrinfo_screen, usrinfo_screen_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
