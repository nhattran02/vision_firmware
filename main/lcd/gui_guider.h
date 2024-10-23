/*
* Copyright 2024 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *main_screen;
	bool main_screen_del;
	lv_obj_t *main_screen_data_con;
	lv_obj_t *main_screen_label_date;
	lv_obj_t *main_screen_label_day;
	lv_obj_t *main_screen_labe_menu_name;
	lv_obj_t *main_screen_label_time;
	lv_obj_t *main_screen_wifi_ok_icon;
	lv_obj_t *main_screen_wifi_fail_icon;
	lv_obj_t *main_screen_btn_wifi;
	lv_obj_t *main_screen_btn_wifi_label;
	lv_obj_t *main_screen_btn_next_screen;
	lv_obj_t *main_screen_btn_next_screen_label;
	lv_obj_t *menu_screen;
	bool menu_screen_del;
	lv_obj_t *menu_screen_data2_con;
	lv_obj_t *menu_screen_esc_label;
	lv_obj_t *menu_screen_ok_label;
	lv_obj_t *menu_screen_menu_root;
	lv_obj_t *menu_screen_menu_root_sidebar_page;
	lv_obj_t *menu_screen_menu_root_subpage_1;
	lv_obj_t *menu_screen_menu_root_cont_1;
	lv_obj_t *menu_screen_menu_root_label_1;
	lv_obj_t *menu_screen_menu_root_subpage_2;
	lv_obj_t *menu_screen_menu_root_cont_2;
	lv_obj_t *menu_screen_menu_root_label_2;
	lv_obj_t *menu_screen_menu_root_subpage_3;
	lv_obj_t *menu_screen_menu_root_cont_3;
	lv_obj_t *menu_screen_menu_root_label_3;
	lv_obj_t *menu_screen_menu_root_subpage_4;
	lv_obj_t *menu_screen_menu_root_cont_4;
	lv_obj_t *menu_screen_menu_root_label_4;
	lv_obj_t *menu_screen_btn2_wifi;
	lv_obj_t *menu_screen_btn2_wifi_label;
	lv_obj_t *menu_screen_wifi2_ok_icon;
	lv_obj_t *menu_screen_wifi2_fail_icon;
	lv_obj_t *menu_screen_btn_menu_up;
	lv_obj_t *menu_screen_btn_menu_up_label;
	lv_obj_t *menu_screen_btn_menu_dwn;
	lv_obj_t *menu_screen_btn_menu_dwn_label;
	lv_obj_t *menu_screen_btn_next_screen2;
	lv_obj_t *menu_screen_btn_next_screen2_label;
	lv_obj_t *attendance_screen;
	bool attendance_screen_del;
	lv_obj_t *attendance_screen_data2_con;
	lv_obj_t *attendance_screen_esc_label3;
	lv_obj_t *attendance_screen_ok_label3;
	lv_obj_t *attendance_screen_menu_attendance;
	lv_obj_t *attendance_screen_menu_attendance_sidebar_page;
	lv_obj_t *attendance_screen_menu_attendance_subpage_1;
	lv_obj_t *attendance_screen_menu_attendance_cont_1;
	lv_obj_t *attendance_screen_menu_attendance_label_1;
	lv_obj_t *attendance_screen_menu_attendance_subpage_2;
	lv_obj_t *attendance_screen_menu_attendance_cont_2;
	lv_obj_t *attendance_screen_menu_attendance_label_2;
	lv_obj_t *attendance_screen_btn3_wifi;
	lv_obj_t *attendance_screen_btn3_wifi_label;
	lv_obj_t *attendance_screen_wifi3_ok_icon;
	lv_obj_t *attendance_screen_wifi3_fail_icon;
	lv_obj_t *attendance_screen_btn_menu_up3;
	lv_obj_t *attendance_screen_btn_menu_up3_label;
	lv_obj_t *attendance_screen_btn_menu_dwn3;
	lv_obj_t *attendance_screen_btn_menu_dwn3_label;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;


void setup_scr_main_screen(lv_ui *ui);
void setup_scr_menu_screen(lv_ui *ui);
void setup_scr_attendance_screen(lv_ui *ui);
LV_IMG_DECLARE(_wifi_alpha_24x24);
LV_IMG_DECLARE(_wifi_off_alpha_24x24);
LV_IMG_DECLARE(_wifi_alpha_24x24);
LV_IMG_DECLARE(_wifi_off_alpha_24x24);
LV_IMG_DECLARE(_wifi_alpha_24x24);
LV_IMG_DECLARE(_wifi_off_alpha_24x24);

LV_FONT_DECLARE(lv_font_montserrat_16)
LV_FONT_DECLARE(lv_font_montserrat_48)
LV_FONT_DECLARE(lv_font_montserrat_12)
LV_FONT_DECLARE(lv_font_montserrat_18)
LV_FONT_DECLARE(lv_font_montserrat_20)
LV_FONT_DECLARE(lv_font_montserrat_24)


#ifdef __cplusplus
}
#endif
#endif
