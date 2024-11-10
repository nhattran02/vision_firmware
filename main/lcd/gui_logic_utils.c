#include "gui_logic_utils.h"
#include "wifi.h"
#include "esp_log.h"
#include <stdlib.h> 


// Navigation variables
ui_state_t current_state = STATE_MAIN_SCREEN;
uint8_t menu_selected_item = 0;
uint8_t attendance_selected_item = 0;
uint8_t data_selected_item = 0;
uint16_t usr_data_selected_item = 0;

user_data_t users[MAX_USERS] = {0};
uint16_t n_users = 0;



void update_usrdata_screen(lv_ui *ui)
{
    if (ui->usrdata_screen_list_id != NULL) {
        lv_obj_clean(ui->usrdata_screen_list_id);
    } 
    if (ui->usrdata_screen_list_name != NULL) {
        lv_obj_clean(ui->usrdata_screen_list_name);
    }
    if (ui->usrdata_screen_list_role != NULL) {
        lv_obj_clean(ui->usrdata_screen_list_role);
    }

    char buf[40] = {0};

    for (int i = 0; i < n_users; i++) {
        snprintf(buf, sizeof(buf), "%d", users[i].id);
        lv_list_add_text(ui->usrdata_screen_list_id, buf);
        snprintf(buf, sizeof(buf), "%s", users[i].name);
        lv_list_add_text(ui->usrdata_screen_list_name, buf);
        snprintf(buf, sizeof(buf), "%d", users[i].role);
        lv_list_add_text(ui->usrdata_screen_list_role, buf);
    }


}


lv_obj_t **list_id_items = NULL;
lv_obj_t **list_name_items = NULL;
lv_obj_t **list_role_items = NULL;

void _setup_scr_usrdata_screen(lv_ui *ui)
{
    //Write codes usrdata_screen

    // if (ui->usrdata_screen != NULL) {
    //     lv_obj_clean(ui->usrdata_screen);
    // }

    ui->usrdata_screen = lv_obj_create(NULL);

    lv_obj_set_size(ui->usrdata_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->usrdata_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrdata_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for usrdata_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->usrdata_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrdata_screen, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrdata_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrdata_screen_list_id
    ui->usrdata_screen_list_id = lv_list_create(ui->usrdata_screen);
    ui->usrdata_screen_list_id_item0 = lv_list_add_text(ui->usrdata_screen_list_id, "ID");

    list_id_items = (lv_obj_t **)malloc(n_users * sizeof(lv_obj_t *));
    if (list_id_items == NULL) {
        printf("Failed to allocate memory for list id items!\n");
        return;
    }
  
    char id_buf[8] = {0};

    for (int i = 0; i < n_users; i++) {
        snprintf(id_buf, sizeof(id_buf), "%d", users[i].id);
        list_id_items[i] = lv_list_add_text(ui->usrdata_screen_list_id, id_buf);
    }

    lv_obj_set_pos(ui->usrdata_screen_list_id, 0, 10);
    lv_obj_set_size(ui->usrdata_screen_list_id, 41, 240);
    lv_obj_set_scrollbar_mode(ui->usrdata_screen_list_id, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_text_align(ui->usrdata_screen_list_id, LV_TEXT_ALIGN_CENTER, 0);

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

    lv_style_set_pad_top(&style_usrdata_screen_list_id_main_main_default, 5);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_id_main_main_default, 5);
    lv_style_set_radius(&style_usrdata_screen_list_id_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_usrdata_screen_list_id_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_id_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_id_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->usrdata_screen_list_id, &style_usrdata_screen_list_id_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_id_extra_btns_main_default
    static lv_style_t style_usrdata_screen_list_id_extra_btns_main_default;
    ui_init_style(&style_usrdata_screen_list_id_extra_btns_main_default);
    
    lv_style_set_pad_top(&style_usrdata_screen_list_id_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_id_extra_btns_main_default, 0);
    lv_style_set_pad_right(&style_usrdata_screen_list_id_extra_btns_main_default, 0);
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
    lv_style_set_pad_left(&style_usrdata_screen_list_id_extra_texts_main_default, 0);
    lv_style_set_pad_right(&style_usrdata_screen_list_id_extra_texts_main_default, 0);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_id_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_usrdata_screen_list_id_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_usrdata_screen_list_id_extra_texts_main_default, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_usrdata_screen_list_id_extra_texts_main_default, &lv_font_montserrat_16);
    lv_style_set_text_opa(&style_usrdata_screen_list_id_extra_texts_main_default, 255);
    lv_style_set_radius(&style_usrdata_screen_list_id_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_usrdata_screen_list_id_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_usrdata_screen_list_id_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_id_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_id_extra_texts_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->usrdata_screen_list_id_item0, &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    for (int i = 0; i < n_users; i++) {
        lv_obj_add_style(list_id_items[i], &style_usrdata_screen_list_id_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    }
    
    //Write codes usrdata_screen_list_name
    ui->usrdata_screen_list_name = lv_list_create(ui->usrdata_screen);
    ui->usrdata_screen_list_name_item0 =lv_list_add_text(ui->usrdata_screen_list_name, "Name");

    list_name_items = (lv_obj_t **)malloc(n_users * sizeof(lv_obj_t *));
    if (list_name_items == NULL) {
        printf("Failed to allocate memory for list name items!\n");
        return;
    }  

    char name_buf[40] = {0};
    for (int i = 0; i < n_users; i++) {
        snprintf(name_buf, sizeof(name_buf), "%s", users[i].name);
        list_name_items[i] = lv_list_add_text(ui->usrdata_screen_list_name, name_buf);
    }


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

    lv_style_set_pad_top(&style_usrdata_screen_list_id_main_main_default, 5);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_id_main_main_default, 5);
    lv_style_set_radius(&style_usrdata_screen_list_name_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_usrdata_screen_list_name_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_name_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_name_main_scrollbar_default, LV_GRAD_DIR_NONE);
     lv_obj_add_style(ui->usrdata_screen_list_name, &style_usrdata_screen_list_name_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_name_extra_btns_main_default
    static lv_style_t style_usrdata_screen_list_name_extra_btns_main_default;
    ui_init_style(&style_usrdata_screen_list_name_extra_btns_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_name_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_name_extra_btns_main_default, 0);
    lv_style_set_pad_right(&style_usrdata_screen_list_name_extra_btns_main_default, 0);
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
    lv_style_set_pad_left(&style_usrdata_screen_list_name_extra_texts_main_default, 0);
    lv_style_set_pad_right(&style_usrdata_screen_list_name_extra_texts_main_default, 0);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_name_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_usrdata_screen_list_name_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_usrdata_screen_list_name_extra_texts_main_default, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_usrdata_screen_list_name_extra_texts_main_default, &lv_font_montserrat_16);
    lv_style_set_text_opa(&style_usrdata_screen_list_name_extra_texts_main_default, 255);
    lv_style_set_radius(&style_usrdata_screen_list_name_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_usrdata_screen_list_name_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_usrdata_screen_list_name_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_name_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_name_extra_texts_main_default, LV_GRAD_DIR_NONE);

    lv_obj_add_style(ui->usrdata_screen_list_name_item0, &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    for (int i = 0; i < n_users; i++) {
        lv_obj_add_style(list_name_items[i], &style_usrdata_screen_list_name_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    }

    //Write codes usrdata_screen_list_role
    ui->usrdata_screen_list_role = lv_list_create(ui->usrdata_screen);
    ui->usrdata_screen_list_role_item0 =lv_list_add_text(ui->usrdata_screen_list_role, "Role");

    list_role_items = (lv_obj_t **)malloc(n_users * sizeof(lv_obj_t *));
    if (list_role_items == NULL) {
        printf("Failed to allocate memory for list role items!\n");
        return;
    }  

    char role_buf[8] = {0};
    for (int i = 0; i < n_users; i++) {
        if (users[i].role == 1) {
            snprintf(role_buf, sizeof(role_buf), "Admin");
        } else {
            snprintf(role_buf, sizeof(role_buf), "User");
        }
        list_role_items[i] = lv_list_add_text(ui->usrdata_screen_list_role, role_buf);
    }

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

    lv_style_set_pad_top(&style_usrdata_screen_list_id_main_main_default, 5);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_id_main_main_default, 5);
    lv_style_set_radius(&style_usrdata_screen_list_role_main_scrollbar_default, 3);
    lv_style_set_bg_opa(&style_usrdata_screen_list_role_main_scrollbar_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_role_main_scrollbar_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_role_main_scrollbar_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->usrdata_screen_list_role, &style_usrdata_screen_list_role_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_usrdata_screen_list_role_extra_btns_main_default
    static lv_style_t style_usrdata_screen_list_role_extra_btns_main_default;
    ui_init_style(&style_usrdata_screen_list_role_extra_btns_main_default);

    lv_style_set_pad_top(&style_usrdata_screen_list_role_extra_btns_main_default, 5);
    lv_style_set_pad_left(&style_usrdata_screen_list_role_extra_btns_main_default, 0);
    lv_style_set_pad_right(&style_usrdata_screen_list_role_extra_btns_main_default, 0);
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
    lv_style_set_pad_left(&style_usrdata_screen_list_role_extra_texts_main_default, 0);
    lv_style_set_pad_right(&style_usrdata_screen_list_role_extra_texts_main_default, 0);
    lv_style_set_pad_bottom(&style_usrdata_screen_list_role_extra_texts_main_default, 5);
    lv_style_set_border_width(&style_usrdata_screen_list_role_extra_texts_main_default, 0);
    lv_style_set_text_color(&style_usrdata_screen_list_role_extra_texts_main_default, lv_color_hex(0x000000));
    lv_style_set_text_font(&style_usrdata_screen_list_role_extra_texts_main_default, &lv_font_montserrat_16);
    lv_style_set_text_opa(&style_usrdata_screen_list_role_extra_texts_main_default, 255);
    lv_style_set_radius(&style_usrdata_screen_list_role_extra_texts_main_default, 3);
    lv_style_set_transform_width(&style_usrdata_screen_list_role_extra_texts_main_default, 0);
    lv_style_set_bg_opa(&style_usrdata_screen_list_role_extra_texts_main_default, 255);
    lv_style_set_bg_color(&style_usrdata_screen_list_role_extra_texts_main_default, lv_color_hex(0xffffff));
    lv_style_set_bg_grad_dir(&style_usrdata_screen_list_role_extra_texts_main_default, LV_GRAD_DIR_NONE);
    lv_obj_add_style(ui->usrdata_screen_list_role_item0, &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    for (int i = 0; i < n_users; i++) {
        lv_obj_add_style(list_role_items[i], &style_usrdata_screen_list_role_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    }

    //The custom code of usrdata_screen.

    // Nhat add style for check state
    static lv_style_t style_usrdata_screen_list_checked;
	ui_init_style(&style_usrdata_screen_list_checked);
	lv_style_set_pad_top(&style_usrdata_screen_list_checked, 5);
	lv_style_set_pad_left(&style_usrdata_screen_list_checked, 0);
	lv_style_set_pad_right(&style_usrdata_screen_list_checked, 0);
	lv_style_set_pad_bottom(&style_usrdata_screen_list_checked, 5);
	lv_style_set_border_width(&style_usrdata_screen_list_checked, 0); 
	lv_style_set_text_color(&style_usrdata_screen_list_checked, lv_color_hex(0xffffff));
	lv_style_set_text_font(&style_usrdata_screen_list_checked, lv_obj_get_style_text_font(ui->usrdata_screen_list_id_item0, LV_PART_MAIN|LV_STATE_DEFAULT));
	lv_style_set_radius(&style_usrdata_screen_list_checked, 0);
	lv_style_set_bg_opa(&style_usrdata_screen_list_checked, 255);
	lv_style_set_bg_color(&style_usrdata_screen_list_checked, lv_color_hex(0x969696));    

    for (int i = 0; i < n_users; i++) {
        lv_obj_add_style(ui->usrdata_screen_list_id_item0, &style_usrdata_screen_list_checked, LV_PART_MAIN|LV_STATE_CHECKED);
        lv_obj_add_style(list_id_items[i], &style_usrdata_screen_list_checked, LV_PART_MAIN|LV_STATE_CHECKED);
        lv_obj_add_style(ui->usrdata_screen_list_name_item0, &style_usrdata_screen_list_checked, LV_PART_MAIN|LV_STATE_CHECKED);
        lv_obj_add_style(list_name_items[i], &style_usrdata_screen_list_checked, LV_PART_MAIN|LV_STATE_CHECKED);
        lv_obj_add_style(ui->usrdata_screen_list_role_item0, &style_usrdata_screen_list_checked, LV_PART_MAIN|LV_STATE_CHECKED);
        lv_obj_add_style(list_role_items[i], &style_usrdata_screen_list_checked, LV_PART_MAIN|LV_STATE_CHECKED);
    }

    // lv_obj_add_state(list_id_items[4], LV_STATE_CHECKED);

    //Update current screen layout.
    lv_obj_update_layout(ui->usrdata_screen);

}



void update_data_gui(ui_state_t current_screen)
{
    update_wifi_status(wifi_connected, current_screen);
}

void menu_screen_attendance_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_attendance, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_attendance_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_attendance_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);    
     
}

void menu_screen_connection_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_connection, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_connection_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_connection_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);

}

void menu_screen_data_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_data, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_data_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_data_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);        
}


void menu_screen_setting_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_setting, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_setting_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_setting_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);  
}

void menu_screen_attendance_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_attendance, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_attendance_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_attendance_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void menu_screen_connection_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_connection, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_connection_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_connection_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void menu_screen_data_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_data, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_data_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_data_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}


void menu_screen_setting_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.menu_screen_cont_setting, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_setting_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.menu_screen_label_setting_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void attendance_screen_checkin_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.attendance_screen_cont_check_in, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkin_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkin_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void attendance_screen_checkout_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.attendance_screen_cont_check_out, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkout_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkout_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void attendance_screen_checkin_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.attendance_screen_cont_check_in, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkin_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkin_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void attendance_screen_checkout_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.attendance_screen_cont_check_out, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkout_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.attendance_screen_label_checkout_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}


void data_screen_dwnreport_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_dwnreport, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwnreport_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwnreport_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_dwntemplate_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_dwntemplate, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwntemplate_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwntemplate_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_uptemplate_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_uptemplate, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_uptemplate_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_uptemplate_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_usrdata_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_usrdata, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_usrdata_symbol, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_usrdata_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_dwnreport_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_dwnreport, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwnreport_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwnreport_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_dwntemplate_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_dwntemplate, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwntemplate_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_dwntemplate_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_uptemplate_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_uptemplate, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_uptemplate_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_uptemplate_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void data_screen_usrdata_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.data_screen_cont_usrdata, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_usrdata_symbol, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.data_screen_label_usrdata_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}