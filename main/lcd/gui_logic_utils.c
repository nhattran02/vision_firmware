#include "gui_logic_utils.h"
#include "esp_log.h"
#include <stdlib.h> 
#include "smartconfig_wifi.hpp"
#include "ntp_time.hpp"

char ntp_date[11] = {0};
char ntp_time[9] = {0};
char ntp_time_no_sec[6] = {0};
char ntp_day[10] = {0};

// Navigation variables
ui_state_t current_state = STATE_MAIN_SCREEN;
uint8_t menu_selected_item = 0;
uint8_t attendance_selected_item = 0;
uint8_t data_selected_item = 0;
uint8_t role_selected_item = 0;
uint16_t usr_data_selected_item = 0;
uint8_t usr_info_selected_item = 0;

EXT_RAM_BSS_ATTR user_data_t users[MAX_USERS] = {0};
EXT_RAM_BSS_ATTR attendance_data_t attendance_data[MAX_ATTENDANCE] = {0};
uint16_t n_users = 0;
uint16_t n_attendance = 0;
uint16_t n_attendance_actual = 0;


TaskHandle_t FingerprintDetectTaskHandle = NULL;

lv_obj_t **list_id_items = NULL;
lv_obj_t **list_name_items = NULL;
lv_obj_t **list_role_items = NULL;

bool compare_passwords(const char *pw1, const char *pw2, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        if (pw1[i] != pw2[i])
        {
            return false;
        }
    }
    return true;
}

void hash_to_hex(const uint8_t *hash, size_t hash_length, char *hex_output)
{
    for (size_t i = 0; i < hash_length; i++)
    {
        sprintf(hex_output + (i * 2), "%02x", hash[i]);
    }
    hex_output[hash_length * 2] = '\0';
}

void hash_password(const char *password, size_t length, char *output_hash_hex)
{
    uint8_t output_hash[32] = {0};
    mbedtls_sha256_context sha256_ctx;
    mbedtls_sha256_init(&sha256_ctx);
    mbedtls_sha256_starts(&sha256_ctx, false); 
    mbedtls_sha256_update(&sha256_ctx, (const unsigned char *)password, length);
    mbedtls_sha256_finish(&sha256_ctx, output_hash);
    mbedtls_sha256_free(&sha256_ctx);

    hash_to_hex(output_hash, 32, output_hash_hex);
}

void generate_pwchar_string(char *str, int number_of_pwchar) 
{
    // Set the first 'number_of_pwchar' characters to 'X'
    for (int i = 0; i < number_of_pwchar && i < 4; i++) {
        str[i] = 'X';
    }
    
    // Fill the rest with '-'
    for (int i = number_of_pwchar; i < 4; i++) {
        str[i] = '-';
    }
    
    // Null-terminate the string
    str[4] = '\0';
}

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

    char buf[50] = {0};

    for (int i = 0; i < n_users; i++) {
        snprintf(buf, sizeof(buf), "%d", users[i].id);
        lv_list_add_text(ui->usrdata_screen_list_id, buf);
        snprintf(buf, sizeof(buf), "%s", users[i].name);
        lv_list_add_text(ui->usrdata_screen_list_name, buf);
        snprintf(buf, sizeof(buf), "%d", users[i].role);
        lv_list_add_text(ui->usrdata_screen_list_role, buf);
    }


}




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

    char name_buf[50] = {0};
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
	lv_style_set_bg_color(&style_usrdata_screen_list_checked, lv_color_hex(/*0x969696*/0x000000));

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


void _setup_scr_usrinfo_screen(lv_ui *ui)
{
    //Write codes usrinfo_screen
    ui->usrinfo_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->usrinfo_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->usrinfo_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrinfo_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for usrinfo_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->usrinfo_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_time5
    ui->usrinfo_screen_label_time5 = lv_label_create(ui->usrinfo_screen);
    char buf[20] = {0};
    snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
    lv_label_set_text(ui->usrinfo_screen_label_time5, buf);
    // lv_label_set_text(ui->usrinfo_screen_label_time5, "11:00");
    lv_label_set_long_mode(ui->usrinfo_screen_label_time5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_time5, -31, 8);
    lv_obj_set_size(ui->usrinfo_screen_label_time5, 128, 20);

    //Write style for usrinfo_screen_label_time5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_time5, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_time5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_time5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_time5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_time5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_time5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_usrinfo_name
    ui->usrinfo_screen_label_usrinfo_name = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_usrinfo_name, "User Info");
    lv_label_set_long_mode(ui->usrinfo_screen_label_usrinfo_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_usrinfo_name, 96, 8);
    lv_obj_set_size(ui->usrinfo_screen_label_usrinfo_name, 128, 17);

    //Write style for usrinfo_screen_label_usrinfo_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_usrinfo_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_usrinfo_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_usrinfo_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_usrinfo_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_usrinfo_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_usrinfo_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_WIFI5
    ui->usrinfo_screen_label_WIFI5 = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_WIFI5, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->usrinfo_screen_label_WIFI5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_WIFI5, 284, 9);
    lv_obj_set_size(ui->usrinfo_screen_label_WIFI5, 41, 20);

    //Write style for usrinfo_screen_label_WIFI5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_WIFI5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_WIFI5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_WIFI5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_WIFI5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_WIFI5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_WIFI5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_BT5
    ui->usrinfo_screen_label_BT5 = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_BT5, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->usrinfo_screen_label_BT5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_BT5, 260, 9);
    lv_obj_set_size(ui->usrinfo_screen_label_BT5, 41, 20);

    //Write style for usrinfo_screen_label_BT5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_BT5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_BT5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_BT5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_BT5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_BT5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_BT5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_SD5
    ui->usrinfo_screen_label_SD5 = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_SD5, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->usrinfo_screen_label_SD5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_SD5, 232, 9);
    lv_obj_set_size(ui->usrinfo_screen_label_SD5, 41, 20);

    //Write style for usrinfo_screen_label_SD5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_SD5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_SD5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_SD5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_SD5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_SD5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_SD5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_USB5
    ui->usrinfo_screen_label_USB5 = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_USB5, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->usrinfo_screen_label_USB5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_USB5, 205, 9);
    lv_obj_set_size(ui->usrinfo_screen_label_USB5, 41, 20);

    //Write style for usrinfo_screen_label_USB5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_USB5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_USB5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_USB5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_USB5, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_USB5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_USB5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_btn_esc5
    ui->usrinfo_screen_btn_esc5 = lv_btn_create(ui->usrinfo_screen);
    ui->usrinfo_screen_btn_esc5_label = lv_label_create(ui->usrinfo_screen_btn_esc5);
    lv_label_set_text(ui->usrinfo_screen_btn_esc5_label, "ESC");
    lv_label_set_long_mode(ui->usrinfo_screen_btn_esc5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->usrinfo_screen_btn_esc5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->usrinfo_screen_btn_esc5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->usrinfo_screen_btn_esc5_label, LV_PCT(100));
    lv_obj_set_pos(ui->usrinfo_screen_btn_esc5, 17, 204);
    lv_obj_set_size(ui->usrinfo_screen_btn_esc5, 100, 28);

    //Write style for usrinfo_screen_btn_esc5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_btn_esc5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_btn_esc5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_btn_esc5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_btn_esc5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_btn_esc5, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_btn_esc5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_btn_esc5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_btn_esc5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_btn_esc5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_btn_esc5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_btn_esc5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_btn_esc5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_btn_esc5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_btn_ok5
    ui->usrinfo_screen_btn_ok5 = lv_btn_create(ui->usrinfo_screen);
    ui->usrinfo_screen_btn_ok5_label = lv_label_create(ui->usrinfo_screen_btn_ok5);
    lv_label_set_text(ui->usrinfo_screen_btn_ok5_label, "OK");
    lv_label_set_long_mode(ui->usrinfo_screen_btn_ok5_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->usrinfo_screen_btn_ok5_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->usrinfo_screen_btn_ok5, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->usrinfo_screen_btn_ok5_label, LV_PCT(100));
    lv_obj_set_pos(ui->usrinfo_screen_btn_ok5, 205, 204);
    lv_obj_set_size(ui->usrinfo_screen_btn_ok5, 100, 28);

    //Write style for usrinfo_screen_btn_ok5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_btn_ok5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_btn_ok5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_btn_ok5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->usrinfo_screen_btn_ok5, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_btn_ok5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_btn_ok5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_btn_ok5, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_btn_ok5, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_btn_ok5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_btn_ok5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_btn_ok5, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_btn_ok5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_btn_ok5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_cont_password
    ui->usrinfo_screen_cont_password = lv_obj_create(ui->usrinfo_screen);
    lv_obj_set_pos(ui->usrinfo_screen_cont_password, -2, 96);
    lv_obj_set_size(ui->usrinfo_screen_cont_password, 324, 35);
    lv_obj_set_scrollbar_mode(ui->usrinfo_screen_cont_password, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrinfo_screen_cont_password, LV_OBJ_FLAG_CHECKABLE);

    //Write style for usrinfo_screen_cont_password, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_cont_password, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_cont_password, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_cont_password, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->usrinfo_screen_cont_password, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_cont_password, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_cont_password, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_cont_password, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_cont_password, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_pw_text
    ui->usrinfo_screen_label_pw_text = lv_label_create(ui->usrinfo_screen_cont_password);
    lv_label_set_text(ui->usrinfo_screen_label_pw_text, "Password");
    lv_label_set_long_mode(ui->usrinfo_screen_label_pw_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_pw_text, 3, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_pw_text, 104, 20);

    //Write style for usrinfo_screen_label_pw_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_pw_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_pw_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_pw_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_pw_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_pw_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_pw_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_pw_value

    // strcpy(users[usr_data_selected_item].password_hash, "8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92");
    ui->usrinfo_screen_label_pw_value = lv_label_create(ui->usrinfo_screen_cont_password);
    if (users[usr_data_selected_item].password_hash[0] != '\0')
    {
        lv_label_set_text(ui->usrinfo_screen_label_pw_value, "Set");
    }
    else
    {
        lv_label_set_text(ui->usrinfo_screen_label_pw_value, "Not Set");
    }

    // lv_label_set_text(ui->usrinfo_screen_label_pw_value, "Not Set");
    lv_label_set_long_mode(ui->usrinfo_screen_label_pw_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_pw_value, 228, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_pw_value, 90, 19);

    //Write style for usrinfo_screen_label_pw_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_pw_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_pw_value, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_pw_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_pw_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_pw_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_pw_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_cont_faceid
    ui->usrinfo_screen_cont_faceid = lv_obj_create(ui->usrinfo_screen);
    lv_obj_set_pos(ui->usrinfo_screen_cont_faceid, -2, 131);
    lv_obj_set_size(ui->usrinfo_screen_cont_faceid, 324, 35);
    lv_obj_set_scrollbar_mode(ui->usrinfo_screen_cont_faceid, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrinfo_screen_cont_faceid, LV_OBJ_FLAG_CHECKABLE);

    //Write style for usrinfo_screen_cont_faceid, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_cont_faceid, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_cont_faceid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_cont_faceid, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_cont_faceid, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_cont_faceid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_cont_faceid, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_cont_faceid, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_cont_faceid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_faceid_text
    ui->usrinfo_screen_label_faceid_text = lv_label_create(ui->usrinfo_screen_cont_faceid);
    lv_label_set_text(ui->usrinfo_screen_label_faceid_text, "FaceID");
    lv_label_set_long_mode(ui->usrinfo_screen_label_faceid_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_faceid_text, 3, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_faceid_text, 104, 20);

    //Write style for usrinfo_screen_label_faceid_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_faceid_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_faceid_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_faceid_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_faceid_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_faceid_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_faceid_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_faceid_value


    ui->usrinfo_screen_label_faceid_value = lv_label_create(ui->usrinfo_screen_cont_faceid);
    
    if (users[usr_data_selected_item].faceid == 1)
    {
        lv_label_set_text(ui->usrinfo_screen_label_faceid_value, "Set");
    }
    else
    {
        lv_label_set_text(ui->usrinfo_screen_label_faceid_value, "Not Set");
    }
    
    // lv_label_set_text(ui->usrinfo_screen_label_faceid_value, "Not Set");
    lv_label_set_long_mode(ui->usrinfo_screen_label_faceid_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_faceid_value, 228, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_faceid_value, 90, 19);

    //Write style for usrinfo_screen_label_faceid_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_faceid_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_faceid_value, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_faceid_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_faceid_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_faceid_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_faceid_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_cont_finger
    ui->usrinfo_screen_cont_finger = lv_obj_create(ui->usrinfo_screen);
    lv_obj_set_pos(ui->usrinfo_screen_cont_finger, -2, 61);
    lv_obj_set_size(ui->usrinfo_screen_cont_finger, 324, 35);
    lv_obj_set_scrollbar_mode(ui->usrinfo_screen_cont_finger, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrinfo_screen_cont_finger, LV_OBJ_FLAG_CHECKABLE);

    //Write style for usrinfo_screen_cont_finger, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_cont_finger, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_cont_finger, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_cont_finger, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_cont_finger, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_cont_finger, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_cont_finger, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_cont_finger, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_cont_finger, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_finger_text
    ui->usrinfo_screen_label_finger_text = lv_label_create(ui->usrinfo_screen_cont_finger);
    lv_label_set_text(ui->usrinfo_screen_label_finger_text, "Finger\n");
    lv_label_set_long_mode(ui->usrinfo_screen_label_finger_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_finger_text, 3, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_finger_text, 104, 20);

    //Write style for usrinfo_screen_label_finger_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_finger_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_finger_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_finger_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_finger_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_finger_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_finger_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_finger_value

    ui->usrinfo_screen_label_finger_value = lv_label_create(ui->usrinfo_screen_cont_finger);
    if (users[usr_data_selected_item].fingerprint == 0)
    {
        lv_label_set_text(ui->usrinfo_screen_label_finger_value, "0/1");
    }
    else
    {
        lv_label_set_text(ui->usrinfo_screen_label_finger_value, "1/1");
    }
    // lv_label_set_text(ui->usrinfo_screen_label_finger_value, "0/1");
    lv_label_set_long_mode(ui->usrinfo_screen_label_finger_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_finger_value, 288, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_finger_value, 32, 19);

    //Write style for usrinfo_screen_label_finger_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_finger_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_finger_value, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_finger_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_finger_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_finger_value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_finger_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_usrid
    char id_text[10] = {0};
    snprintf(id_text, sizeof(id_text), "ID: %d", users[usr_data_selected_item].id);
    ui->usrinfo_screen_label_usrid = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_usrid, id_text);
    lv_label_set_long_mode(ui->usrinfo_screen_label_usrid, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_usrid, 3, 39);
    lv_obj_set_size(ui->usrinfo_screen_label_usrid, 87, 19);

    //Write style for usrinfo_screen_label_usrid, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_usrid, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_usrid, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_usrid, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_usrid, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_usrid, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_usrid, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_usrname
    char name_text[50] = {0};
    snprintf(name_text, sizeof(name_text), "%s", users[usr_data_selected_item].name);
    ui->usrinfo_screen_label_usrname = lv_label_create(ui->usrinfo_screen);
    lv_label_set_text(ui->usrinfo_screen_label_usrname, name_text);
    lv_label_set_long_mode(ui->usrinfo_screen_label_usrname, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_usrname, 60, 39);
    lv_obj_set_size(ui->usrinfo_screen_label_usrname, 255, 19);

    //Write style for usrinfo_screen_label_usrname, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_usrname, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_usrname, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_usrname, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_usrname, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_usrname, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_usrname, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_cont_role
    ui->usrinfo_screen_cont_role = lv_obj_create(ui->usrinfo_screen);
    lv_obj_set_pos(ui->usrinfo_screen_cont_role, -2, 166);
    lv_obj_set_size(ui->usrinfo_screen_cont_role, 324, 35);
    lv_obj_set_scrollbar_mode(ui->usrinfo_screen_cont_role, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->usrinfo_screen_cont_role, LV_OBJ_FLAG_CHECKABLE);

    //Write style for usrinfo_screen_cont_role, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_cont_role, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->usrinfo_screen_cont_role, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->usrinfo_screen_cont_role, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->usrinfo_screen_cont_role, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->usrinfo_screen_cont_role, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->usrinfo_screen_cont_role, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->usrinfo_screen_cont_role, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_cont_role, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_role_text
    ui->usrinfo_screen_label_role_text = lv_label_create(ui->usrinfo_screen_cont_role);
    lv_label_set_text(ui->usrinfo_screen_label_role_text, "Role");
    lv_label_set_long_mode(ui->usrinfo_screen_label_role_text, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_role_text, 3, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_role_text, 104, 20);

    //Write style for usrinfo_screen_label_role_text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_role_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_role_text, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_role_text, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_role_text, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_role_text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_role_text, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes usrinfo_screen_label_role_value
    ui->usrinfo_screen_label_role_value = lv_label_create(ui->usrinfo_screen_cont_role);
    if (users[usr_data_selected_item].role == 0)
    {
        lv_label_set_text(ui->usrinfo_screen_label_role_value, "User");
    }
    else
    {
        lv_label_set_text(ui->usrinfo_screen_label_role_value, "Admin");
    }
    // lv_label_set_text(ui->usrinfo_screen_label_role_value, "User");
    lv_label_set_long_mode(ui->usrinfo_screen_label_role_value, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->usrinfo_screen_label_role_value, 228, 7);
    lv_obj_set_size(ui->usrinfo_screen_label_role_value, 90, 19);
                
    //Write style for usrinfo_screen_label_role_value, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->usrinfo_screen_label_role_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->usrinfo_screen_label_role_value, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->usrinfo_screen_label_role_value, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->usrinfo_screen_label_role_value, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->usrinfo_screen_label_role_value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->usrinfo_screen_label_role_value, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of usrinfo_screen.
    

    //Update current screen layout.
    lv_obj_update_layout(ui->usrinfo_screen);

}


void _setup_scr_finger_enroll_screen(lv_ui *ui)
{
    //Write codes finger_enroll_screen
    ui->finger_enroll_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->finger_enroll_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->finger_enroll_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->finger_enroll_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for finger_enroll_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->finger_enroll_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->finger_enroll_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_time6
    ui->finger_enroll_screen_label_time6 = lv_label_create(ui->finger_enroll_screen);
    char buf[20] = {0};
    snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
    lv_label_set_text(ui->finger_enroll_screen_label_time6, buf);
    // lv_label_set_text(ui->finger_enroll_screen_label_time6, "11:00");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_time6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_time6, -31, 8);
    lv_obj_set_size(ui->finger_enroll_screen_label_time6, 128, 20);

    //Write style for finger_enroll_screen_label_time6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_time6, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_time6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_time6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_time6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_time6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_time6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_fpenroll_name
    ui->finger_enroll_screen_label_fpenroll_name = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_fpenroll_name, "FP Enroll");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_fpenroll_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_fpenroll_name, 96, 8);
    lv_obj_set_size(ui->finger_enroll_screen_label_fpenroll_name, 128, 17);

    //Write style for finger_enroll_screen_label_fpenroll_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_fpenroll_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_fpenroll_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_fpenroll_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_fpenroll_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_fpenroll_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_fpenroll_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_WIFI6
    ui->finger_enroll_screen_label_WIFI6 = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_WIFI6, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_WIFI6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_WIFI6, 284, 9);
    lv_obj_set_size(ui->finger_enroll_screen_label_WIFI6, 41, 20);

    //Write style for finger_enroll_screen_label_WIFI6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_WIFI6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_WIFI6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_WIFI6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_WIFI6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_WIFI6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_WIFI6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_BT6
    ui->finger_enroll_screen_label_BT6 = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_BT6, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_BT6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_BT6, 260, 9);
    lv_obj_set_size(ui->finger_enroll_screen_label_BT6, 41, 20);

    //Write style for finger_enroll_screen_label_BT6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_BT6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_BT6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_BT6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_BT6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_BT6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_BT6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_SD6
    ui->finger_enroll_screen_label_SD6 = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_SD6, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_SD6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_SD6, 232, 9);
    lv_obj_set_size(ui->finger_enroll_screen_label_SD6, 41, 20);

    //Write style for finger_enroll_screen_label_SD6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_SD6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_SD6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_SD6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_SD6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_SD6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_SD6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_USB6
    ui->finger_enroll_screen_label_USB6 = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_USB6, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_USB6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_USB6, 205, 9);
    lv_obj_set_size(ui->finger_enroll_screen_label_USB6, 41, 20);

    //Write style for finger_enroll_screen_label_USB6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_USB6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_USB6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_USB6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_USB6, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_USB6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_USB6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_btn_esc6
    ui->finger_enroll_screen_btn_esc6 = lv_btn_create(ui->finger_enroll_screen);
    ui->finger_enroll_screen_btn_esc6_label = lv_label_create(ui->finger_enroll_screen_btn_esc6);
    lv_label_set_text(ui->finger_enroll_screen_btn_esc6_label, "ESC");
    lv_label_set_long_mode(ui->finger_enroll_screen_btn_esc6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->finger_enroll_screen_btn_esc6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->finger_enroll_screen_btn_esc6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->finger_enroll_screen_btn_esc6_label, LV_PCT(100));
    lv_obj_set_pos(ui->finger_enroll_screen_btn_esc6, 17, 204);
    lv_obj_set_size(ui->finger_enroll_screen_btn_esc6, 100, 28);

    //Write style for finger_enroll_screen_btn_esc6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_btn_esc6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->finger_enroll_screen_btn_esc6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->finger_enroll_screen_btn_esc6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->finger_enroll_screen_btn_esc6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->finger_enroll_screen_btn_esc6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->finger_enroll_screen_btn_esc6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->finger_enroll_screen_btn_esc6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_btn_esc6, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_btn_esc6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_btn_esc6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_btn_esc6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_btn_esc6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_btn_esc6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_btn_ok6
    ui->finger_enroll_screen_btn_ok6 = lv_btn_create(ui->finger_enroll_screen);
    ui->finger_enroll_screen_btn_ok6_label = lv_label_create(ui->finger_enroll_screen_btn_ok6);
    lv_label_set_text(ui->finger_enroll_screen_btn_ok6_label, "OK");
    lv_label_set_long_mode(ui->finger_enroll_screen_btn_ok6_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->finger_enroll_screen_btn_ok6_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->finger_enroll_screen_btn_ok6, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->finger_enroll_screen_btn_ok6_label, LV_PCT(100));
    lv_obj_set_pos(ui->finger_enroll_screen_btn_ok6, 205, 204);
    lv_obj_set_size(ui->finger_enroll_screen_btn_ok6, 100, 28);

    //Write style for finger_enroll_screen_btn_ok6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_btn_ok6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->finger_enroll_screen_btn_ok6, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->finger_enroll_screen_btn_ok6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->finger_enroll_screen_btn_ok6, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->finger_enroll_screen_btn_ok6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->finger_enroll_screen_btn_ok6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->finger_enroll_screen_btn_ok6, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_btn_ok6, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_btn_ok6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_btn_ok6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_btn_ok6, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_btn_ok6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_btn_ok6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_id_fp
    char id_text[60] = {0};
    snprintf(id_text, sizeof(id_text), "ID-%d  %s", users[usr_data_selected_item].id, users[usr_data_selected_item].name);
    ui->finger_enroll_screen_label_id_fp = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_id_fp, id_text);
    lv_label_set_long_mode(ui->finger_enroll_screen_label_id_fp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_id_fp, 0, 69);
    lv_obj_set_size(ui->finger_enroll_screen_label_id_fp, 320, 19);

    //Write style for finger_enroll_screen_label_id_fp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_id_fp, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_id_fp, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_id_fp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_id_fp, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_id_fp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_id_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_label_info_fp
    ui->finger_enroll_screen_label_info_fp = lv_label_create(ui->finger_enroll_screen);
    lv_label_set_text(ui->finger_enroll_screen_label_info_fp, "Please place your finger");
    lv_label_set_long_mode(ui->finger_enroll_screen_label_info_fp, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->finger_enroll_screen_label_info_fp, 0, 98);
    lv_obj_set_size(ui->finger_enroll_screen_label_info_fp, 320, 19);

    //Write style for finger_enroll_screen_label_info_fp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->finger_enroll_screen_label_info_fp, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->finger_enroll_screen_label_info_fp, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->finger_enroll_screen_label_info_fp, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->finger_enroll_screen_label_info_fp, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->finger_enroll_screen_label_info_fp, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->finger_enroll_screen_label_info_fp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes finger_enroll_screen_led_1
    ui->finger_enroll_screen_led_1 = lv_led_create(ui->finger_enroll_screen);
    lv_led_set_brightness(ui->finger_enroll_screen_led_1, 255);
    lv_led_set_color(ui->finger_enroll_screen_led_1, lv_color_hex(0x6b6c6b));
    lv_obj_set_pos(ui->finger_enroll_screen_led_1, 120, 137);
    lv_obj_set_size(ui->finger_enroll_screen_led_1, 20, 20);

    //Write codes finger_enroll_screen_led_2
    ui->finger_enroll_screen_led_2 = lv_led_create(ui->finger_enroll_screen);
    lv_led_set_brightness(ui->finger_enroll_screen_led_2, 255);
    lv_led_set_color(ui->finger_enroll_screen_led_2, lv_color_hex(0x6b6c6b));
    lv_obj_set_pos(ui->finger_enroll_screen_led_2, 179, 137);
    lv_obj_set_size(ui->finger_enroll_screen_led_2, 20, 20);

    //The custom code of finger_enroll_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->finger_enroll_screen);

}

void _setup_scr_pw_enter_screen(lv_ui *ui)
{
    //Write codes pw_enter_screen
    ui->pw_enter_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->pw_enter_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->pw_enter_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->pw_enter_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for pw_enter_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->pw_enter_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pw_enter_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->pw_enter_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_time7
    ui->pw_enter_screen_label_time7 = lv_label_create(ui->pw_enter_screen);
    char buf[20] = {0};
    snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
    lv_label_set_text(ui->pw_enter_screen_label_time7, buf);    
    // lv_label_set_text(ui->pw_enter_screen_label_time7, "11:00");
    lv_label_set_long_mode(ui->pw_enter_screen_label_time7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_time7, -31, 8);
    lv_obj_set_size(ui->pw_enter_screen_label_time7, 128, 20);

    //Write style for pw_enter_screen_label_time7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_time7, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_time7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_time7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_time7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_time7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_time7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_pwenter_name
    ui->pw_enter_screen_label_pwenter_name = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_pwenter_name, "Password");
    lv_label_set_long_mode(ui->pw_enter_screen_label_pwenter_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_pwenter_name, 96, 8);
    lv_obj_set_size(ui->pw_enter_screen_label_pwenter_name, 128, 17);

    //Write style for pw_enter_screen_label_pwenter_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_pwenter_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_pwenter_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_pwenter_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_pwenter_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_pwenter_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_pwenter_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_WIFI7
    ui->pw_enter_screen_label_WIFI7 = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_WIFI7, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->pw_enter_screen_label_WIFI7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_WIFI7, 284, 9);
    lv_obj_set_size(ui->pw_enter_screen_label_WIFI7, 41, 20);

    //Write style for pw_enter_screen_label_WIFI7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_WIFI7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_WIFI7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_WIFI7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_WIFI7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_WIFI7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_WIFI7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_BT7
    ui->pw_enter_screen_label_BT7 = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_BT7, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->pw_enter_screen_label_BT7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_BT7, 260, 9);
    lv_obj_set_size(ui->pw_enter_screen_label_BT7, 41, 20);

    //Write style for pw_enter_screen_label_BT7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_BT7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_BT7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_BT7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_BT7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_BT7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_BT7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_SD7
    ui->pw_enter_screen_label_SD7 = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_SD7, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->pw_enter_screen_label_SD7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_SD7, 232, 9);
    lv_obj_set_size(ui->pw_enter_screen_label_SD7, 41, 20);

    //Write style for pw_enter_screen_label_SD7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_SD7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_SD7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_SD7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_SD7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_SD7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_SD7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_USB7
    ui->pw_enter_screen_label_USB7 = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_USB7, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->pw_enter_screen_label_USB7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_USB7, 205, 9);
    lv_obj_set_size(ui->pw_enter_screen_label_USB7, 41, 20);

    //Write style for pw_enter_screen_label_USB7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_USB7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_USB7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_USB7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_USB7, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_USB7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_USB7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_btn_esc7
    ui->pw_enter_screen_btn_esc7 = lv_btn_create(ui->pw_enter_screen);
    ui->pw_enter_screen_btn_esc7_label = lv_label_create(ui->pw_enter_screen_btn_esc7);
    lv_label_set_text(ui->pw_enter_screen_btn_esc7_label, "ESC");
    lv_label_set_long_mode(ui->pw_enter_screen_btn_esc7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->pw_enter_screen_btn_esc7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->pw_enter_screen_btn_esc7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->pw_enter_screen_btn_esc7_label, LV_PCT(100));
    lv_obj_set_pos(ui->pw_enter_screen_btn_esc7, 17, 204);
    lv_obj_set_size(ui->pw_enter_screen_btn_esc7, 100, 28);

    //Write style for pw_enter_screen_btn_esc7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_btn_esc7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pw_enter_screen_btn_esc7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->pw_enter_screen_btn_esc7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pw_enter_screen_btn_esc7, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->pw_enter_screen_btn_esc7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->pw_enter_screen_btn_esc7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->pw_enter_screen_btn_esc7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_btn_esc7, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_btn_esc7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_btn_esc7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_btn_esc7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_btn_esc7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_btn_esc7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_btn_ok7
    ui->pw_enter_screen_btn_ok7 = lv_btn_create(ui->pw_enter_screen);
    ui->pw_enter_screen_btn_ok7_label = lv_label_create(ui->pw_enter_screen_btn_ok7);
    lv_label_set_text(ui->pw_enter_screen_btn_ok7_label, "OK");
    lv_label_set_long_mode(ui->pw_enter_screen_btn_ok7_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->pw_enter_screen_btn_ok7_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->pw_enter_screen_btn_ok7, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->pw_enter_screen_btn_ok7_label, LV_PCT(100));
    lv_obj_set_pos(ui->pw_enter_screen_btn_ok7, 205, 205);
    lv_obj_set_size(ui->pw_enter_screen_btn_ok7, 100, 28);

    //Write style for pw_enter_screen_btn_ok7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_btn_ok7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pw_enter_screen_btn_ok7, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->pw_enter_screen_btn_ok7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->pw_enter_screen_btn_ok7, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->pw_enter_screen_btn_ok7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->pw_enter_screen_btn_ok7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->pw_enter_screen_btn_ok7, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_btn_ok7, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_btn_ok7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_btn_ok7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_btn_ok7, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_btn_ok7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_btn_ok7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_nofi
    ui->pw_enter_screen_label_nofi = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_nofi, "Please enter your password");
    lv_label_set_long_mode(ui->pw_enter_screen_label_nofi, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_nofi, 0, 162);
    lv_obj_set_size(ui->pw_enter_screen_label_nofi, 320, 18);

    //Write style for pw_enter_screen_label_nofi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_nofi, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_nofi, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_nofi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_nofi, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_nofi, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_nofi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_id_name
    char id_text[60] = {0};
    snprintf(id_text, sizeof(id_text), "ID-%d  %s", users[usr_data_selected_item].id, users[usr_data_selected_item].name);
    ui->pw_enter_screen_label_id_name = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_id_name, id_text);
    lv_label_set_long_mode(ui->pw_enter_screen_label_id_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_id_name, 10, 49);
    lv_obj_set_size(ui->pw_enter_screen_label_id_name, 300, 18);

    //Write style for pw_enter_screen_label_id_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_id_name, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_id_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_id_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_id_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_id_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_id_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_pw_first
    ui->pw_enter_screen_label_pw_first = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_pw_first, "----");
    lv_label_set_long_mode(ui->pw_enter_screen_label_pw_first, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_pw_first, 70, 84);
    lv_obj_set_size(ui->pw_enter_screen_label_pw_first, 180, 30);

    //Write style for pw_enter_screen_label_pw_first, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_pw_first, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_pw_first, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_pw_first, &lv_font_montserrat_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_pw_first, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_pw_first, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_pw_first, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_pw_first, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pw_enter_screen_label_pw_first, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->pw_enter_screen_label_pw_first, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_pw_first, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes pw_enter_screen_label_pw_second
    ui->pw_enter_screen_label_pw_second = lv_label_create(ui->pw_enter_screen);
    lv_label_set_text(ui->pw_enter_screen_label_pw_second, "----");
    lv_label_set_long_mode(ui->pw_enter_screen_label_pw_second, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->pw_enter_screen_label_pw_second, 70, 122);
    lv_obj_set_size(ui->pw_enter_screen_label_pw_second, 180, 30);

    //Write style for pw_enter_screen_label_pw_second, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->pw_enter_screen_label_pw_second, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->pw_enter_screen_label_pw_second, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->pw_enter_screen_label_pw_second, &lv_font_montserrat_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->pw_enter_screen_label_pw_second, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->pw_enter_screen_label_pw_second, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->pw_enter_screen_label_pw_second, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->pw_enter_screen_label_pw_second, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->pw_enter_screen_label_pw_second, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->pw_enter_screen_label_pw_second, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->pw_enter_screen_label_pw_second, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of pw_enter_screen.

    //Update current screen layout.
    lv_obj_update_layout(ui->pw_enter_screen);

}



void _setup_scr_connect_screen(lv_ui *ui)
{
    //Write codes connect_screen
    ui->connect_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->connect_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->connect_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->connect_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for connect_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->connect_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->connect_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->connect_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_time9
    ui->connect_screen_label_time9 = lv_label_create(ui->connect_screen);
    char buf[20] = {0};
    snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
    lv_label_set_text(ui->connect_screen_label_time9, buf);
    // lv_label_set_text(ui->connect_screen_label_time9, "11:00");
    lv_label_set_long_mode(ui->connect_screen_label_time9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_time9, -31, 8);
    lv_obj_set_size(ui->connect_screen_label_time9, 128, 20);

    //Write style for connect_screen_label_time9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_time9, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_time9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_time9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_time9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_time9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_connect_name
    ui->connect_screen_label_connect_name = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_connect_name, "Wi-Fi");
    lv_label_set_long_mode(ui->connect_screen_label_connect_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_connect_name, 97, 8);
    lv_obj_set_size(ui->connect_screen_label_connect_name, 128, 17);

    //Write style for connect_screen_label_connect_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_connect_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_connect_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_connect_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_connect_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_connect_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_connect_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_WIFI9
    ui->connect_screen_label_WIFI9 = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_WIFI9, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->connect_screen_label_WIFI9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_WIFI9, 284, 9);
    lv_obj_set_size(ui->connect_screen_label_WIFI9, 41, 20);

    //Write style for connect_screen_label_WIFI9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_WIFI9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_WIFI9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_WIFI9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_WIFI9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_WIFI9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_WIFI9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_BT9
    ui->connect_screen_label_BT9 = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_BT9, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->connect_screen_label_BT9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_BT9, 260, 9);
    lv_obj_set_size(ui->connect_screen_label_BT9, 41, 20);

    //Write style for connect_screen_label_BT9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_BT9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_BT9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_BT9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_BT9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_BT9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_BT9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_SD9
    ui->connect_screen_label_SD9 = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_SD9, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->connect_screen_label_SD9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_SD9, 232, 9);
    lv_obj_set_size(ui->connect_screen_label_SD9, 41, 20);

    //Write style for connect_screen_label_SD9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_SD9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_SD9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_SD9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_SD9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_SD9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_SD9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_USB9
    ui->connect_screen_label_USB9 = lv_label_create(ui->connect_screen);
    lv_label_set_text(ui->connect_screen_label_USB9, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->connect_screen_label_USB9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_USB9, 205, 9);
    lv_obj_set_size(ui->connect_screen_label_USB9, 41, 20);

    //Write style for connect_screen_label_USB9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_USB9, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_USB9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_USB9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_USB9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_USB9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_USB9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_cont_wifi
    ui->connect_screen_cont_wifi = lv_obj_create(ui->connect_screen);
    lv_obj_set_pos(ui->connect_screen_cont_wifi, 10, 39);
    lv_obj_set_size(ui->connect_screen_cont_wifi, 300, 170);
    lv_obj_set_scrollbar_mode(ui->connect_screen_cont_wifi, LV_SCROLLBAR_MODE_OFF);

    //Write style for connect_screen_cont_wifi, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_cont_wifi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->connect_screen_cont_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->connect_screen_cont_wifi, lv_color_hex(0xb0b0b0), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->connect_screen_cont_wifi, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_cont_wifi, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_cont_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->connect_screen_cont_wifi, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->connect_screen_cont_wifi, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_cont_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_cont_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_cont_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_cont_wifi, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_cont_wifi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->connect_screen_cont_wifi, lv_color_hex(0xb0b0b0), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->connect_screen_cont_wifi, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->connect_screen_cont_wifi, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->connect_screen_cont_wifi, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->connect_screen_cont_wifi, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_wifi_status
    ui->connect_screen_label_wifi_status = lv_label_create(ui->connect_screen);
    char _buf[100] = {0};
    snprintf(_buf, sizeof(_buf), "Wi-Fi is connected to %s", ssid);
    if (is_wifi_connected)
    {
        lv_label_set_text(ui->connect_screen_label_wifi_status, _buf);
    }
    else
    {
        ESP_ERROR_CHECK(esp_wifi_stop());
        ESP_ERROR_CHECK(esp_wifi_start());    
        lv_label_set_text(ui->connect_screen_label_wifi_status, "Wi-Fi is disconnected");
    }

    lv_label_set_long_mode(ui->connect_screen_label_wifi_status, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_wifi_status, 10, 46);
    lv_obj_set_size(ui->connect_screen_label_wifi_status, 300, 40);

    //Write style for connect_screen_label_wifi_status, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_wifi_status, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_wifi_status, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_wifi_status, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_wifi_status, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_wifi_status, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_wifi_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes connect_screen_label_1
    ui->connect_screen_label_1 = lv_label_create(ui->connect_screen);
    if (!is_wifi_connected)
    {
        lv_label_set_text(ui->connect_screen_label_1, "Smart config is scanning...");
    }else{
        lv_label_set_text(ui->connect_screen_label_1, "...");
    }
    lv_label_set_long_mode(ui->connect_screen_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->connect_screen_label_1, 10, 113);
    lv_obj_set_size(ui->connect_screen_label_1, 300, 50);

    //Write style for connect_screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->connect_screen_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->connect_screen_label_1, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->connect_screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->connect_screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->connect_screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of connect_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->connect_screen);

}



void _setup_scr_main_screen(lv_ui *ui)
{
    //Write codes main_screen
    ui->main_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->main_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->main_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->main_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for main_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->main_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_cont_1
    ui->main_screen_cont_1 = lv_obj_create(ui->main_screen);
    lv_obj_set_pos(ui->main_screen_cont_1, 10, 35);
    lv_obj_set_size(ui->main_screen_cont_1, 300, 170);
    lv_obj_set_scrollbar_mode(ui->main_screen_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for main_screen_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_cont_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->main_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->main_screen_cont_1, lv_color_hex(0xb0b0b0), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->main_screen_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_cont_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_screen_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->main_screen_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_cont_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->main_screen_cont_1, lv_color_hex(0xb0b0b0), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->main_screen_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->main_screen_cont_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->main_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->main_screen_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_date
    ui->main_screen_label_date = lv_label_create(ui->main_screen);
    char buf[20] = {0};
    if (ntp_time[0] != '\0')
    {
        snprintf(buf, sizeof(buf), "%s", ntp_date);
        lv_label_set_text(ui->main_screen_label_date, buf);
    }
    else
    {
        lv_label_set_text(ui->main_screen_label_date, "01-01-1970");
    }
    // lv_label_set_text(ui->main_screen_label_date, "21-10-2024");
    lv_label_set_long_mode(ui->main_screen_label_date, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_date, 3, 217);
    lv_obj_set_size(ui->main_screen_label_date, 127, 17);

    //Write style for main_screen_label_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_date, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_date, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_date, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_date, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_day
    ui->main_screen_label_day = lv_label_create(ui->main_screen);
    if (ntp_time[0] != '\0')
    {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%s", ntp_day);
        lv_label_set_text(ui->main_screen_label_day, buf);
    }
    else
    {
        lv_label_set_text(ui->main_screen_label_day, "Monday");
    }
    // lv_label_set_text(ui->main_screen_label_day, "Monday");
    lv_label_set_long_mode(ui->main_screen_label_day, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_day, 189, 217);
    lv_obj_set_size(ui->main_screen_label_day, 127, 17);

    //Write style for main_screen_label_day, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_day, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_day, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_day, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_day, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_day, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_day, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_time
    ui->main_screen_label_time = lv_label_create(ui->main_screen);
    if (ntp_time[0] != '\0')
    {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%s", ntp_time);
        lv_label_set_text(ui->main_screen_label_time, buf);
    }
    else
    {
        lv_label_set_text(ui->main_screen_label_time, "07:00");
    }
    // lv_label_set_text(ui->main_screen_label_time, "11:00");
    lv_label_set_long_mode(ui->main_screen_label_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_time, 51, 99);
    lv_obj_set_size(ui->main_screen_label_time, 230, 46);

    //Write style for main_screen_label_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_time, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_time, &lv_font_montserrat_48, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_home_name
    ui->main_screen_label_home_name = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_home_name, "Home");
    lv_label_set_long_mode(ui->main_screen_label_home_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_home_name, 96, 8);
    lv_obj_set_size(ui->main_screen_label_home_name, 128, 17);

    //Write style for main_screen_label_home_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_home_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_home_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_home_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_home_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_home_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_home_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_WIFI
    ui->main_screen_label_WIFI = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_WIFI, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->main_screen_label_WIFI, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_WIFI, 284, 9);
    lv_obj_set_size(ui->main_screen_label_WIFI, 41, 20);

    //Write style for main_screen_label_WIFI, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_WIFI, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_WIFI, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_WIFI, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_WIFI, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_WIFI, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_WIFI, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_BT
    ui->main_screen_label_BT = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_BT, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->main_screen_label_BT, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_BT, 260, 9);
    lv_obj_set_size(ui->main_screen_label_BT, 41, 20);

    //Write style for main_screen_label_BT, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_BT, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_BT, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_BT, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_BT, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_BT, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_BT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_SD
    ui->main_screen_label_SD = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_SD, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->main_screen_label_SD, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_SD, 232, 9);
    lv_obj_set_size(ui->main_screen_label_SD, 41, 20);

    //Write style for main_screen_label_SD, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_SD, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_SD, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_SD, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_SD, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_SD, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_SD, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes main_screen_label_USB
    ui->main_screen_label_USB = lv_label_create(ui->main_screen);
    lv_label_set_text(ui->main_screen_label_USB, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->main_screen_label_USB, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->main_screen_label_USB, 205, 9);
    lv_obj_set_size(ui->main_screen_label_USB, 41, 20);

    //Write style for main_screen_label_USB, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->main_screen_label_USB, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->main_screen_label_USB, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->main_screen_label_USB, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->main_screen_label_USB, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->main_screen_label_USB, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->main_screen_label_USB, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of main_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->main_screen);

    //Init events for screen.
    events_init_main_screen(ui);
}


void _setup_scr_role_screen(lv_ui *ui)
{
    //Write codes role_screen
    ui->role_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->role_screen, 320, 240);
    lv_obj_set_scrollbar_mode(ui->role_screen, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->role_screen, LV_OBJ_FLAG_CLICKABLE);

    //Write style for role_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->role_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->role_screen, lv_color_hex(0xd5d9de), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->role_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_time9
    ui->role_screen_label_time9 = lv_label_create(ui->role_screen);
    char buf[20] = {0};
    snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
    lv_label_set_text(ui->role_screen_label_time9, buf);
    // lv_label_set_text(ui->role_screen_label_time9, "11:00");
    lv_label_set_long_mode(ui->role_screen_label_time9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_time9, -31, 8);
    lv_obj_set_size(ui->role_screen_label_time9, 128, 20);

    //Write style for role_screen_label_time9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_time9, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_time9, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_time9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_time9, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_time9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_time9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_authen_name
    ui->role_screen_label_authen_name = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_authen_name, "Set Role");
    lv_label_set_long_mode(ui->role_screen_label_authen_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_authen_name, 97, 8);
    lv_obj_set_size(ui->role_screen_label_authen_name, 128, 17);

    //Write style for role_screen_label_authen_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_authen_name, lv_color_hex(0x07080A), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_authen_name, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_authen_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_authen_name, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_authen_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_authen_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_WIFI8
    ui->role_screen_label_WIFI8 = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_WIFI8, "" LV_SYMBOL_WIFI "");
    lv_label_set_long_mode(ui->role_screen_label_WIFI8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_WIFI8, 284, 9);
    lv_obj_set_size(ui->role_screen_label_WIFI8, 41, 20);

    //Write style for role_screen_label_WIFI8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_WIFI8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_WIFI8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_WIFI8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_WIFI8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_WIFI8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_WIFI8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_BT8
    ui->role_screen_label_BT8 = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_BT8, "" LV_SYMBOL_BLUETOOTH " ");
    lv_label_set_long_mode(ui->role_screen_label_BT8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_BT8, 260, 9);
    lv_obj_set_size(ui->role_screen_label_BT8, 41, 20);

    //Write style for role_screen_label_BT8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_BT8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_BT8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_BT8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_BT8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_BT8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_BT8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_SD8
    ui->role_screen_label_SD8 = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_SD8, "" LV_SYMBOL_SD_CARD "");
    lv_label_set_long_mode(ui->role_screen_label_SD8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_SD8, 232, 9);
    lv_obj_set_size(ui->role_screen_label_SD8, 41, 20);

    //Write style for role_screen_label_SD8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_SD8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_SD8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_SD8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_SD8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_SD8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_SD8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label_USB8
    ui->role_screen_label_USB8 = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label_USB8, "" LV_SYMBOL_USB "");
    lv_label_set_long_mode(ui->role_screen_label_USB8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label_USB8, 205, 9);
    lv_obj_set_size(ui->role_screen_label_USB8, 41, 20);

    //Write style for role_screen_label_USB8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label_USB8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label_USB8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label_USB8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label_USB8, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label_USB8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label_USB8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_btn_esc8
    ui->role_screen_btn_esc8 = lv_btn_create(ui->role_screen);
    ui->role_screen_btn_esc8_label = lv_label_create(ui->role_screen_btn_esc8);
    lv_label_set_text(ui->role_screen_btn_esc8_label, "ESC");
    lv_label_set_long_mode(ui->role_screen_btn_esc8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->role_screen_btn_esc8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->role_screen_btn_esc8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->role_screen_btn_esc8_label, LV_PCT(100));
    lv_obj_set_pos(ui->role_screen_btn_esc8, 17, 204);
    lv_obj_set_size(ui->role_screen_btn_esc8, 100, 28);

    //Write style for role_screen_btn_esc8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->role_screen_btn_esc8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->role_screen_btn_esc8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->role_screen_btn_esc8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->role_screen_btn_esc8, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->role_screen_btn_esc8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->role_screen_btn_esc8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->role_screen_btn_esc8, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_btn_esc8, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_btn_esc8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_btn_esc8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_btn_esc8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_btn_esc8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_btn_esc8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_btn_ok8
    ui->role_screen_btn_ok8 = lv_btn_create(ui->role_screen);
    ui->role_screen_btn_ok8_label = lv_label_create(ui->role_screen_btn_ok8);
    lv_label_set_text(ui->role_screen_btn_ok8_label, "OK");
    lv_label_set_long_mode(ui->role_screen_btn_ok8_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->role_screen_btn_ok8_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->role_screen_btn_ok8, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->role_screen_btn_ok8_label, LV_PCT(100));
    lv_obj_set_pos(ui->role_screen_btn_ok8, 205, 204);
    lv_obj_set_size(ui->role_screen_btn_ok8, 100, 28);

    //Write style for role_screen_btn_ok8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->role_screen_btn_ok8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->role_screen_btn_ok8, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->role_screen_btn_ok8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->role_screen_btn_ok8, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->role_screen_btn_ok8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->role_screen_btn_ok8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->role_screen_btn_ok8, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_btn_ok8, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_btn_ok8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_btn_ok8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_btn_ok8, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_btn_ok8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_btn_ok8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_cont_normal_user
    ui->role_screen_cont_normal_user = lv_obj_create(ui->role_screen);
    lv_obj_set_pos(ui->role_screen_cont_normal_user, -2, 92);
    lv_obj_set_size(ui->role_screen_cont_normal_user, 324, 35);
    lv_obj_set_scrollbar_mode(ui->role_screen_cont_normal_user, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->role_screen_cont_normal_user, LV_OBJ_FLAG_CHECKABLE);

    //Write style for role_screen_cont_normal_user, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_cont_normal_user, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->role_screen_cont_normal_user, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->role_screen_cont_normal_user, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->role_screen_cont_normal_user, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_cont_normal_user, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->role_screen_cont_normal_user, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->role_screen_cont_normal_user, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_cont_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_text_normal_user
    ui->role_screen_text_normal_user = lv_label_create(ui->role_screen_cont_normal_user);
    lv_label_set_text(ui->role_screen_text_normal_user, "User");
    lv_label_set_long_mode(ui->role_screen_text_normal_user, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_text_normal_user, 10, 7);
    lv_obj_set_size(ui->role_screen_text_normal_user, 300, 20);

    //Write style for role_screen_text_normal_user, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_text_normal_user, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_text_normal_user, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_text_normal_user, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_text_normal_user, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_text_normal_user, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_text_normal_user, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_cont_admin
    ui->role_screen_cont_admin = lv_obj_create(ui->role_screen);
    lv_obj_set_pos(ui->role_screen_cont_admin, -2, 127);
    lv_obj_set_size(ui->role_screen_cont_admin, 324, 35);
    lv_obj_set_scrollbar_mode(ui->role_screen_cont_admin, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_flag(ui->role_screen_cont_admin, LV_OBJ_FLAG_CHECKABLE);

    //Write style for role_screen_cont_admin, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_cont_admin, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->role_screen_cont_admin, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->role_screen_cont_admin, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->role_screen_cont_admin, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_cont_admin, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->role_screen_cont_admin, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->role_screen_cont_admin, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_cont_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_text_admin
    ui->role_screen_text_admin = lv_label_create(ui->role_screen_cont_admin);
    lv_label_set_text(ui->role_screen_text_admin, "Admin");
    lv_label_set_long_mode(ui->role_screen_text_admin, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_text_admin, 10, 7);
    lv_obj_set_size(ui->role_screen_text_admin, 300, 20);

    //Write style for role_screen_text_admin, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_text_admin, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_text_admin, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_text_admin, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_text_admin, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_text_admin, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_text_admin, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes role_screen_label
    ui->role_screen_label = lv_label_create(ui->role_screen);
    lv_label_set_text(ui->role_screen_label, "Please set role");
    lv_label_set_long_mode(ui->role_screen_label, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->role_screen_label, 10, 39);
    lv_obj_set_size(ui->role_screen_label, 300, 18);

    //Write style for role_screen_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->role_screen_label, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->role_screen_label, &lv_font_montserrat_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->role_screen_label, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->role_screen_label, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->role_screen_label, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->role_screen_label, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of role_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->role_screen);

}


void update_wifi_gui(ui_state_t current_screen)
{
    switch (current_screen)
    {
    case STATE_MAIN_SCREEN:
    {
        if (is_wifi_connected)  
            lv_obj_clear_flag(guider_ui.main_screen_label_WIFI, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(guider_ui.main_screen_label_WIFI, LV_OBJ_FLAG_HIDDEN);

        break;
    }
    case STATE_MENU_SCREEN:
    {
        if (is_wifi_connected)  
            lv_obj_clear_flag(guider_ui.menu_screen_label_WIFI2, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(guider_ui.menu_screen_label_WIFI2, LV_OBJ_FLAG_HIDDEN);        
        break;
    }
    case STATE_DATA_SCREEN:
    {
        if (is_wifi_connected)  
            lv_obj_clear_flag(guider_ui.data_screen_label_WIFI4, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(guider_ui.data_screen_label_WIFI4, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case STATE_USER_INFO_SCREEN:
    {
        if (is_wifi_connected)  
            lv_obj_clear_flag(guider_ui.usrinfo_screen_label_WIFI5, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(guider_ui.usrinfo_screen_label_WIFI5, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case STATE_FINGERPRINT_ENROLL_SCREEN:
    {
        if (is_wifi_connected)  
            lv_obj_clear_flag(guider_ui.finger_enroll_screen_label_WIFI6, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(guider_ui.finger_enroll_screen_label_WIFI6, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case STATE_PW_ENTER_SCREEN:
    {
        if (is_wifi_connected)  
            lv_obj_clear_flag(guider_ui.pw_enter_screen_label_WIFI7, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(guider_ui.pw_enter_screen_label_WIFI7, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case STATE_SET_ROLE_SCREEN:
    {
        if (is_wifi_connected)  
            lv_obj_clear_flag(guider_ui.role_screen_label_WIFI8, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(guider_ui.role_screen_label_WIFI8, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    case STATE_CONNECTION_SCREEN:
    {
        if (is_wifi_connected)  
            lv_obj_clear_flag(guider_ui.connect_screen_label_WIFI9, LV_OBJ_FLAG_HIDDEN);
        else
            lv_obj_add_flag(guider_ui.connect_screen_label_WIFI9, LV_OBJ_FLAG_HIDDEN);
        break;
    }
    default:
        break;
    }
}


void update_data_gui(ui_state_t current_screen)
{
    update_wifi_gui(current_screen);
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


void usrinfo_screen_finger_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.usrinfo_screen_cont_finger, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_finger_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_finger_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void usrinfo_screen_password_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.usrinfo_screen_cont_password, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_pw_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_pw_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void usrinfo_screen_faceid_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.usrinfo_screen_cont_faceid, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_faceid_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_faceid_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void usrinfo_screen_role_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.usrinfo_screen_cont_role, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_role_text, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_role_value, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void usrinfo_screen_finger_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.usrinfo_screen_cont_finger, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_finger_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_finger_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void usrinfo_screen_password_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.usrinfo_screen_cont_password, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_pw_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_pw_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void usrinfo_screen_faceid_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.usrinfo_screen_cont_faceid, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_faceid_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_faceid_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void usrinfo_screen_role_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.usrinfo_screen_cont_role, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_role_text, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.usrinfo_screen_label_role_value, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void role_screen_cont_normal_user_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.role_screen_cont_normal_user, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.role_screen_text_normal_user, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void role_screen_cont_admin_default(void)
{
    lv_obj_set_style_bg_color(guider_ui.role_screen_cont_admin, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.role_screen_text_admin, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void role_screen_cont_normal_user_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.role_screen_cont_normal_user, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.role_screen_text_normal_user, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void role_screen_cont_admin_check(void)
{
    lv_obj_set_style_bg_color(guider_ui.role_screen_cont_admin, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(guider_ui.role_screen_text_admin, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
}

void update_time_to_gui(void)
{
    char buf[50] = {0};
    if (current_state == STATE_MAIN_SCREEN)
    {
        if (ntp_time[0] != '\0')
        {
            snprintf(buf, sizeof(buf), "%s", ntp_time);
            lv_label_set_text(guider_ui.main_screen_label_time, buf);

            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s", ntp_date);
            lv_label_set_text(guider_ui.main_screen_label_date, buf);

            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s", ntp_day);
            lv_label_set_text(guider_ui.main_screen_label_day, buf);
        }
    }
    else if (current_state == STATE_MENU_SCREEN)
    {
        if (ntp_time[0] != '\0')
        {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
            lv_label_set_text(guider_ui.menu_screen_label_time2, buf);
        }
    }
    else if (current_state == STATE_CONNECTION_SCREEN)
    {
        if (ntp_time[0] != '\0')
        {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
            lv_label_set_text(guider_ui.connect_screen_label_time9, buf);
        }
    }
    else if (current_state == STATE_SET_ROLE_SCREEN)
    {
        if (ntp_time[0] != '\0')
        {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
            lv_label_set_text(guider_ui.role_screen_label_time9, buf);
        }
    }
    else if (current_state == STATE_DATA_SCREEN)
    {
        if (ntp_time[0] != '\0')
        {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
            lv_label_set_text(guider_ui.data_screen_label_time4, buf);
        }
    }
    else if (current_state == STATE_USER_INFO_SCREEN)
    {
        if (ntp_time[0] != '\0')
        {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
            lv_label_set_text(guider_ui.usrinfo_screen_label_time5, buf);
        }
    }
    else if (current_state == STATE_FINGERPRINT_ENROLL_SCREEN)
    {
        if (ntp_time[0] != '\0')
        {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
            lv_label_set_text(guider_ui.finger_enroll_screen_label_time6, buf);
        }
    }
    else if (current_state == STATE_PW_ENTER_SCREEN)
    {
        if (ntp_time[0] != '\0')
        {
            memset(buf, 0, sizeof(buf));
            snprintf(buf, sizeof(buf), "%s", ntp_time_no_sec);
            lv_label_set_text(guider_ui.pw_enter_screen_label_time7, buf);
        }
    }
}