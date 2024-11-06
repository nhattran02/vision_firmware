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
#include "custom.h"

static void main_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.menu_screen, guider_ui.menu_screen_del, &guider_ui.main_screen_del, setup_scr_menu_screen, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
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

static void loader_screen_dwnreport_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        lv_anim_t loader_arc;
        lv_anim_init(&loader_arc);
        lv_anim_set_exec_cb(&loader_arc, (lv_anim_exec_xcb_t)lv_arc_set_end_angle);
        lv_anim_set_values(&loader_arc, 0, 360);
        lv_anim_set_time(&loader_arc, 2000);
        lv_anim_set_delay(&loader_arc, 100);
        lv_anim_set_var(&loader_arc, guider_ui.loader_screen_dwnreport_arc_loader1);
        lv_anim_start(&loader_arc);

        lv_anim_t loader_label;
        lv_anim_init(&loader_label);
        lv_anim_set_exec_cb(&loader_label, (lv_anim_exec_xcb_t)anim_label_update);
        lv_anim_set_values(&loader_label, 0, 100);
        lv_anim_set_time(&loader_label, 2000);
        lv_anim_set_delay(&loader_label, 100);
        lv_anim_set_var(&loader_label, guider_ui.loader_screen_dwnreport_label_loader1);
        lv_anim_start(&loader_label);

        break;
    }
    default:
        break;
    }
}

void events_init_loader_screen_dwnreport (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->loader_screen_dwnreport, loader_screen_dwnreport_event_handler, LV_EVENT_ALL, ui);
}

static void loader_screen_dwntemplate_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        lv_anim_t loader_arc;
        lv_anim_init(&loader_arc);
        lv_anim_set_exec_cb(&loader_arc, (lv_anim_exec_xcb_t)lv_arc_set_end_angle);
        lv_anim_set_values(&loader_arc, 0, 360);
        lv_anim_set_time(&loader_arc, 2000);
        lv_anim_set_delay(&loader_arc, 100);
        lv_anim_set_var(&loader_arc, guider_ui.loader_screen_dwntemplate_arc_loader2);
        lv_anim_start(&loader_arc);

        lv_anim_t loader_label;
        lv_anim_init(&loader_label);
        lv_anim_set_exec_cb(&loader_label, (lv_anim_exec_xcb_t)anim_label_update);
        lv_anim_set_values(&loader_label, 0, 100);
        lv_anim_set_time(&loader_label, 2000);
        lv_anim_set_delay(&loader_label, 100);
        lv_anim_set_var(&loader_label, guider_ui.loader_screen_dwntemplate_label_loader2);
        lv_anim_start(&loader_label);        
        break;
    }
    default:
        break;
    }
}

void events_init_loader_screen_dwntemplate (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->loader_screen_dwntemplate, loader_screen_dwntemplate_event_handler, LV_EVENT_ALL, ui);
}

static void loader_screen_uptemplate_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        lv_anim_t loader_arc;
        lv_anim_init(&loader_arc);
        lv_anim_set_exec_cb(&loader_arc, (lv_anim_exec_xcb_t)lv_arc_set_end_angle);
        lv_anim_set_values(&loader_arc, 0, 360);
        lv_anim_set_time(&loader_arc, 2000);
        lv_anim_set_delay(&loader_arc, 100);
        lv_anim_set_var(&loader_arc, guider_ui.loader_screen_uptemplate_arc_loader3);
        lv_anim_start(&loader_arc);  

        lv_anim_t loader_label;
        lv_anim_init(&loader_label);
        lv_anim_set_exec_cb(&loader_label, (lv_anim_exec_xcb_t)anim_label_update);
        lv_anim_set_values(&loader_label, 0, 100);
        lv_anim_set_time(&loader_label, 2000);
        lv_anim_set_delay(&loader_label, 100);
        lv_anim_set_var(&loader_label, guider_ui.loader_screen_uptemplate_label_loader3);
        lv_anim_start(&loader_label);                
        break;
    }
    default:
        break;
    }
}

void events_init_loader_screen_uptemplate (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->loader_screen_uptemplate, loader_screen_uptemplate_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
