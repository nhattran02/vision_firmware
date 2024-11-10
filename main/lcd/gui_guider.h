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
	lv_obj_t *main_screen_cont_1;
	lv_obj_t *main_screen_label_date;
	lv_obj_t *main_screen_label_day;
	lv_obj_t *main_screen_label_time;
	lv_obj_t *main_screen_label_home_name;
	lv_obj_t *main_screen_label_WIFI;
	lv_obj_t *main_screen_label_BT;
	lv_obj_t *main_screen_label_SD;
	lv_obj_t *main_screen_label_USB;
	lv_obj_t *menu_screen;
	bool menu_screen_del;
	lv_obj_t *menu_screen_label_time2;
	lv_obj_t *menu_screen_label_menu_name;
	lv_obj_t *menu_screen_label_WIFI2;
	lv_obj_t *menu_screen_label_BT2;
	lv_obj_t *menu_screen_label_SD2;
	lv_obj_t *menu_screen_label_USB2;
	lv_obj_t *menu_screen_btn_esc2;
	lv_obj_t *menu_screen_btn_esc2_label;
	lv_obj_t *menu_screen_btn_ok2;
	lv_obj_t *menu_screen_btn_ok2_label;
	lv_obj_t *menu_screen_cont_connection;
	lv_obj_t *menu_screen_label_connection_symbol;
	lv_obj_t *menu_screen_label_connection_text;
	lv_obj_t *menu_screen_cont_attendance;
	lv_obj_t *menu_screen_label_attendance_symbol;
	lv_obj_t *menu_screen_label_attendance_text;
	lv_obj_t *menu_screen_cont_data;
	lv_obj_t *menu_screen_label_data_symbol;
	lv_obj_t *menu_screen_label_data_text;
	lv_obj_t *menu_screen_cont_setting;
	lv_obj_t *menu_screen_label_setting_symbol;
	lv_obj_t *menu_screen_label_setting_text;
	lv_obj_t *attendance_screen;
	bool attendance_screen_del;
	lv_obj_t *attendance_screen_label_time3;
	lv_obj_t *attendance_screen_label_attendance_name;
	lv_obj_t *attendance_screen_label_WIFI3;
	lv_obj_t *attendance_screen_label_BT3;
	lv_obj_t *attendance_screen_label_SD3;
	lv_obj_t *attendance_screen_label_USB3;
	lv_obj_t *attendance_screen_btn_esc3;
	lv_obj_t *attendance_screen_btn_esc3_label;
	lv_obj_t *attendance_screen_btn_ok3;
	lv_obj_t *attendance_screen_btn_ok3_label;
	lv_obj_t *attendance_screen_cont_check_in;
	lv_obj_t *attendance_screen_label_checkin_symbol;
	lv_obj_t *attendance_screen_label_checkin_text;
	lv_obj_t *attendance_screen_cont_check_out;
	lv_obj_t *attendance_screen_label_checkout_symbol;
	lv_obj_t *attendance_screen_label_checkout_text;
	lv_obj_t *data_screen;
	bool data_screen_del;
	lv_obj_t *data_screen_label_time4;
	lv_obj_t *data_screen_label_data_name;
	lv_obj_t *data_screen_label_WIFI4;
	lv_obj_t *data_screen_label_BT4;
	lv_obj_t *data_screen_label_SD4;
	lv_obj_t *data_screen_label_USB4;
	lv_obj_t *data_screen_btn_esc4;
	lv_obj_t *data_screen_btn_esc4_label;
	lv_obj_t *data_screen_btn_ok4;
	lv_obj_t *data_screen_btn_ok4_label;
	lv_obj_t *data_screen_cont_dwntemplate;
	lv_obj_t *data_screen_label_dwntemplate_symbol;
	lv_obj_t *data_screen_label_dwntemplate_text;
	lv_obj_t *data_screen_cont_dwnreport;
	lv_obj_t *data_screen_label_dwnreport_symbol;
	lv_obj_t *data_screen_label_dwnreport_text;
	lv_obj_t *data_screen_cont_uptemplate;
	lv_obj_t *data_screen_label_uptemplate_symbol;
	lv_obj_t *data_screen_label_uptemplate_text;
	lv_obj_t *data_screen_cont_usrdata;
	lv_obj_t *data_screen_label_usrdata_symbol;
	lv_obj_t *data_screen_label_usrdata_text;
	lv_obj_t *finish_screen;
	bool finish_screen_del;
	lv_obj_t *finish_screen_cont_bg4;
	lv_obj_t *finish_screen_btn_next;
	lv_obj_t *finish_screen_btn_next_label;
	lv_obj_t *finish_screen_label_prompt4;
	lv_obj_t *finish_screen_img_icon_ok;
	lv_obj_t *usrdata_screen;
	bool usrdata_screen_del;
	lv_obj_t *usrdata_screen_list_id;
	lv_obj_t *usrdata_screen_list_id_item0;
	lv_obj_t *usrdata_screen_list_id_item1;
	lv_obj_t *usrdata_screen_list_id_item2;
	lv_obj_t *usrdata_screen_list_id_item3;
	lv_obj_t *usrdata_screen_list_id_item4;
	lv_obj_t *usrdata_screen_list_id_item5;
	lv_obj_t *usrdata_screen_list_id_item6;
	lv_obj_t *usrdata_screen_list_name;
	lv_obj_t *usrdata_screen_list_name_item0;
	lv_obj_t *usrdata_screen_list_name_item1;
	lv_obj_t *usrdata_screen_list_name_item2;
	lv_obj_t *usrdata_screen_list_name_item3;
	lv_obj_t *usrdata_screen_list_name_item4;
	lv_obj_t *usrdata_screen_list_name_item5;
	lv_obj_t *usrdata_screen_list_name_item6;
	lv_obj_t *usrdata_screen_list_role;
	lv_obj_t *usrdata_screen_label_id;
	lv_obj_t *usrdata_screen_label_name;
	lv_obj_t *usrdata_screen_label_role;
	lv_obj_t *usrdata_screen_list_role_item0;
	lv_obj_t *usrinfo_screen;
	bool usrinfo_screen_del;
	lv_obj_t *usrinfo_screen_label_time5;
	lv_obj_t *usrinfo_screen_label_usrinfo_name;
	lv_obj_t *usrinfo_screen_label_WIFI5;
	lv_obj_t *usrinfo_screen_label_BT5;
	lv_obj_t *usrinfo_screen_label_SD5;
	lv_obj_t *usrinfo_screen_label_USB5;
	lv_obj_t *usrinfo_screen_btn_esc5;
	lv_obj_t *usrinfo_screen_btn_esc5_label;
	lv_obj_t *usrinfo_screen_btn_ok5;
	lv_obj_t *usrinfo_screen_btn_ok5_label;
	lv_obj_t *usrinfo_screen_cont_password;
	lv_obj_t *usrinfo_screen_label_pw_text;
	lv_obj_t *usrinfo_screen_label_pw_value;
	lv_obj_t *usrinfo_screen_cont_faceid;
	lv_obj_t *usrinfo_screen_label_faceid_text;
	lv_obj_t *usrinfo_screen_label_faceid_value;
	lv_obj_t *usrinfo_screen_cont_finger;
	lv_obj_t *usrinfo_screen_label_finger_text;
	lv_obj_t *usrinfo_screen_label_finger_value;
	lv_obj_t *usrinfo_screen_label_usrid;
	lv_obj_t *usrinfo_screen_label_usrname;
	lv_obj_t *usrinfo_screen_cont_role;
	lv_obj_t *usrinfo_screen_label_role_text;
	lv_obj_t *usrinfo_screen_label_role_value;
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
void setup_scr_data_screen(lv_ui *ui);
void setup_scr_finish_screen(lv_ui *ui);
void setup_scr_usrdata_screen(lv_ui *ui);
void setup_scr_usrinfo_screen(lv_ui *ui);
LV_IMG_DECLARE(_ready_alpha_80x80);

LV_FONT_DECLARE(lv_font_montserrat_16)
LV_FONT_DECLARE(lv_font_montserrat_48)
LV_FONT_DECLARE(lv_font_montserrat_12)


#ifdef __cplusplus
}
#endif
#endif
