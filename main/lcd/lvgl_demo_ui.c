/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

// This demo UI is adapted from LVGL official example: https://docs.lvgl.io/master/widgets/extra/meter.html#simple-meter

#include "lvgl.h"
#include "lvgl_demo_ui.h"

static lv_obj_t *meter;
static lv_obj_t * btn;
static lv_disp_rot_t rotation = LV_DISP_ROT_NONE;

static void set_value(void *indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}

static void btn_cb(lv_event_t * e)
{
    lv_disp_t *disp = lv_event_get_user_data(e);
    rotation++;
    if (rotation > LV_DISP_ROT_270) {
        rotation = LV_DISP_ROT_NONE;
    }
    lv_disp_set_rotation(disp, rotation);
}

void lvgl_demo_ui(lv_disp_t *disp)
{
    lv_disp_set_rotation(disp, LV_DISP_ROT_270);
    lv_obj_t *scr = lv_disp_get_scr_act(disp);

    

}
