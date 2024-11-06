/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}

void load_finish_screen_cb()
{
    lv_obj_t * act_scr = lv_scr_act();
    lv_disp_t * d = lv_obj_get_disp(act_scr);
    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
        if (guider_ui.finish_screen_del == true) {
          setup_scr_finish_screen(&guider_ui);
        }
        lv_scr_load_anim(guider_ui.finish_screen, LV_SCR_LOAD_ANIM_FADE_ON, 400, 100, true);
        guider_ui.finish_screen_del = true;
    }
}

void anim_label_update(lv_obj_t *obj, uint16_t value) 
{
    char buf[8];
    snprintf(buf, sizeof(buf), "%d%%", value);  
    lv_label_set_text(obj, buf);
}