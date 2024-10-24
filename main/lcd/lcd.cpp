#include "lcd.hpp"
#include <string.h>
#include <stdio.h>
#include "esp_log.h"
#include "esp_camera.h"
#include "logo_en_240x240_lcd.h"
#include "esp_lcd_ili9341.h"
#include "esp_timer.h"
#include "lvgl.h"
extern "C"
{
    #include "gui_guider.h"
    #include "events_init.h"
    #include "gui_logic_utils.h"
}


#define USE_LVGL 1

#if USE_LVGL

#define LVGL_TICK_PERIOD_MS    2
static lv_disp_draw_buf_t disp_buf;
static lv_disp_drv_t disp_drv;
static lv_indev_t * indev_keypad;
static lv_group_t *g_key_op_group = NULL;

static bool notify_lvgl_flush_ready(esp_lcd_panel_io_handle_t panel_io, esp_lcd_panel_io_event_data_t *edata, void *user_ctx)
{
    lv_disp_drv_t *disp_driver = (lv_disp_drv_t *)user_ctx;
    lv_disp_flush_ready(disp_driver);
    return false;
}

/* Rotate display and touch, when rotated screen in LVGL. Called when driver parameters are updated. */
static void lvgl_port_update_callback(lv_disp_drv_t *drv)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;

    switch (drv->rotated) {
    case LV_DISP_ROT_NONE:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, true, false);
#if CONFIG_EXAMPLE_LCD_TOUCH_ENABLED
        // Rotate LCD touch
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
#endif
        break;
    case LV_DISP_ROT_90:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, true, true);
#if CONFIG_EXAMPLE_LCD_TOUCH_ENABLED
        // Rotate LCD touch
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
#endif
        break;
    case LV_DISP_ROT_180:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, false);
        esp_lcd_panel_mirror(panel_handle, false, true);
#if CONFIG_EXAMPLE_LCD_TOUCH_ENABLED
        // Rotate LCD touch
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
#endif
        break;
    case LV_DISP_ROT_270:
        // Rotate LCD display
        esp_lcd_panel_swap_xy(panel_handle, true);
        esp_lcd_panel_mirror(panel_handle, false, false);
#if CONFIG_EXAMPLE_LCD_TOUCH_ENABLED
        // Rotate LCD touch
        esp_lcd_touch_set_mirror_y(tp, false);
        esp_lcd_touch_set_mirror_x(tp, false);
#endif
        break;
    }
}

static void lvgl_flush_cb(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t) drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    // copy a buffer's content to a specific area of the display
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}

static void increase_lvgl_tick(void *arg)
{
    /* Tell LVGL how many milliseconds has elapsed */
    lv_tick_inc(LVGL_TICK_PERIOD_MS);
}

static void keyboard_read(struct _lv_indev_drv_t *indev, lv_indev_data_t *data)
{
    static uint32_t last_key = 0;
    uint32_t key_pr = detect_key();
    if (key_pr > BUTTON_IDLE)
    {
        last_key = key_pr;
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
    data->btn_id = last_key;
}

#endif // USE_LVGL


static const char TAG[] = "lcd";

static void lvgl_timer_task(LCD *self)
{
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));
        lv_timer_handler();
    }
}

LCD::LCD(/* Button *key ,*/
         QueueHandle_t queue_i,
         QueueHandle_t queue_o,
         void (*callback)(camera_fb_t *)) : Frame(queue_i, queue_o, callback),
                                            /* key(key), */
                                            panel_handle(NULL),
                                            switch_on(false)
{
    do
    {
        ESP_LOGI(TAG, "Turn off LCD backlight");
        ESP_ERROR_CHECK(gpio_reset_pin(LCD_NUM_BK_LIGHT));
        ESP_ERROR_CHECK(gpio_set_direction(LCD_NUM_BK_LIGHT, GPIO_MODE_OUTPUT));
        ESP_ERROR_CHECK(gpio_set_level(LCD_NUM_BK_LIGHT, LCD_BK_LIGHT_OFF_LEVEL));

        ESP_LOGI(TAG, "Initialize SPI bus");
        spi_bus_config_t bus_conf = {
            .mosi_io_num = LCD_NUM_MOSI,
            .miso_io_num = LCD_NUM_MISO,
            .sclk_io_num = LCD_NUM_SCLK,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
            .max_transfer_sz = LCD_H_RES * LCD_V_RES * sizeof(uint16_t),
        };
        ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &bus_conf, SPI_DMA_CH_AUTO));

        ESP_LOGI(TAG, "Install panel IO");
        esp_lcd_panel_io_handle_t io_handle = NULL;
        esp_lcd_panel_io_spi_config_t io_config = {
            .cs_gpio_num = LCD_NUM_CS,
            .dc_gpio_num = LCD_NUM_DC,
            .spi_mode = 0,
            .pclk_hz = LCD_PIXEL_CLOCK_HZ,
            .trans_queue_depth = 10,       
#if USE_LVGL
            .on_color_trans_done = notify_lvgl_flush_ready,
            .user_ctx = &disp_drv,            
#endif // USE_LVGL
            .lcd_cmd_bits = LCD_CMD_BITS,
            .lcd_param_bits = LCD_PARAM_BITS,
        };

        // Attach the LCD to the SPI bus
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));
        
        ESP_LOGI(TAG, "Install ILI9341 panel driver");
        esp_lcd_panel_dev_config_t panel_config = {
            .reset_gpio_num = LCD_NUM_RST,
            .rgb_endian = LCD_RGB_ENDIAN_BGR,
            .bits_per_pixel = 16,
        };
        ESP_ERROR_CHECK(esp_lcd_new_panel_ili9341(io_handle, &panel_config, &panel_handle));
        ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
        ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
        ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel_handle, true));
        
        // turn on display
        esp_lcd_panel_disp_on_off(panel_handle, true);

        ESP_LOGI(TAG, "Turn on LCD backlight");
        gpio_set_level(LCD_NUM_BK_LIGHT, LCD_BK_LIGHT_ON_LEVEL);


#if USE_LVGL
        ESP_LOGI(TAG, "Initialize LVGL library");
        lv_init();
        // alloc draw buffers used by LVGL
        // it's recommended to choose the size of the draw buffer(s) to be at least 1/10 screen sized
        lv_color_t *buf1 = (lv_color_t *) heap_caps_malloc(LCD_H_RES * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA);
        assert(buf1);
        lv_color_t *buf2 = (lv_color_t *) heap_caps_malloc(LCD_H_RES * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA);
        assert(buf2);
        // initialize LVGL draw buffers
        lv_disp_draw_buf_init(&disp_buf, buf1, buf2, LCD_H_RES * 20);

        ESP_LOGI(TAG, "Register display driver to LVGL");
        lv_disp_drv_init(&disp_drv);
        disp_drv.hor_res = LCD_H_RES;
        disp_drv.ver_res = LCD_V_RES;
        disp_drv.flush_cb = lvgl_flush_cb;
        disp_drv.drv_update_cb = lvgl_port_update_callback;
        disp_drv.draw_buf = &disp_buf;
        disp_drv.user_data = panel_handle;
        lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

        ESP_LOGI(TAG, "Install LVGL tick timer");
        // Tick interface for LVGL (using esp_timer to generate 2ms periodic event)
        const esp_timer_create_args_t lvgl_tick_timer_args = {
            .callback = &increase_lvgl_tick,
            .name = "lvgl_tick"
        };
        esp_timer_handle_t lvgl_tick_timer = NULL;
        ESP_ERROR_CHECK(esp_timer_create(&lvgl_tick_timer_args, &lvgl_tick_timer));
        ESP_ERROR_CHECK(esp_timer_start_periodic(lvgl_tick_timer, LVGL_TICK_PERIOD_MS * 1000));    

    #if 0 // USE_MATRIX_BUTTON
        // Register matrix button input device 
        matrix_button_init();
        static lv_indev_drv_t indev_drv;
        lv_indev_drv_init(&indev_drv);  
        indev_drv.type = LV_INDEV_TYPE_BUTTON;
        indev_drv.read_cb = keyboard_read;
        indev_keypad = lv_indev_drv_register(&indev_drv);


        /*Assign keys to points on the screen*/
        static const lv_point_t key_points[17] = {
            {0, 0},    //BUTTON_IDLE
            {0, 0},   //BUTTON_0
            {0, 0},   //BUTTON_1
            {0, 0},   //BUTTON_2
            {0, 0},   //BUTTON_3
            {0, 0},   //BUTTON_4
            {0, 0},   //BUTTON_5
            {0, 0},   //BUTTON_6
            {0, 0},   //BUTTON_7
            {0, 0},   //BUTTON_8
            {0, 0},   //BUTTON_9
            {60, 10},   //BUTTON_STAR
            {0, 0},   //BUTTON_SHARP (OK)
            {5, 220},   //BUTTON_ESC (A)
            {245, 10},   //BUTTON_MENU (B)
            {0, 0},   // BUTTON_UP (C)
            {0, 0},   // BUTTON_DOWN (D)
        };
        lv_indev_set_button_points(indev_keypad, key_points);
    #endif // USE_MATRIX_BUTTON

        ESP_LOGI(TAG, "Run LVGL UI");
        push_screen_to_history(STATE_MAIN_SCREEN);
        lv_disp_set_rotation(disp, LV_DISP_ROT_90);
        setup_ui(&guider_ui);

        xTaskCreate((TaskFunction_t)lvgl_timer_task, "lvgl timer task", 5 * 1024, this, 5, NULL);

#else 
        this->draw_wallpaper();
        vTaskDelay(pdMS_TO_TICKS(1000));
#endif // USE_LVGL
    } while (0);
}

void LCD::draw_wallpaper()
{
    this->draw_color(0xffffff);

    uint16_t *pixels = (uint16_t *)heap_caps_malloc((logo_en_240x240_lcd_width * logo_en_240x240_lcd_height) * sizeof(uint16_t), MALLOC_CAP_8BIT | MALLOC_CAP_SPIRAM);
    if (NULL == pixels)
    {
        ESP_LOGE(TAG, "Memory for bitmap is not enough");
        return;
    }
    memcpy(pixels, logo_en_240x240_lcd, (logo_en_240x240_lcd_width * logo_en_240x240_lcd_height) * sizeof(uint16_t));
    int x_offset = (LCD_V_RES - LCD_H_RES) / 2;

    esp_lcd_panel_draw_bitmap(panel_handle, x_offset, 0, x_offset + LCD_H_RES, logo_en_240x240_lcd_height, (uint16_t *)pixels);
    heap_caps_free(pixels);

    this->paper_drawn = true;
}

void LCD::draw_color(int color)
{
    uint16_t *buffer = (uint16_t *)malloc(LCD_V_RES * sizeof(uint16_t));
    if (NULL == buffer)
    {
        ESP_LOGE(TAG, "Memory for bitmap is not enough");
    }
    else
    {
        for (size_t i = 0; i < LCD_V_RES; i++)
        {
            buffer[i] = color;
        }

        for (int y = 0; y < LCD_H_RES; y++)
        {
            esp_lcd_panel_draw_bitmap(panel_handle, 0, y, LCD_V_RES, y + 1, buffer);
        }

        free(buffer);
    }
}

void LCD::update()
{
    if (this->key->pressed > BUTTON_IDLE)
    {
        if (this->key->pressed == BUTTON_MENU)
        {
            this->switch_on = (this->key->menu == MENU_STOP_WORKING) ? false : true;
            ESP_LOGI(TAG, "%s", this->switch_on ? "ON" : "OFF");
        }
    }

    if (this->switch_on == false)
    {
        this->paper_drawn = false;
    }
}

static void lcd_task(LCD *self)
{
    ESP_LOGI(TAG, "Start");

    camera_fb_t *frame = nullptr;
    while (true)
    {
        if (self->queue_i == nullptr)
            break;

        if (xQueueReceive(self->queue_i, &frame, portMAX_DELAY))
        {
            if (self->switch_on)
                esp_lcd_panel_draw_bitmap(self->panel_handle, 0, 0, frame->width, frame->height, (uint16_t *)frame->buf);
            else if (self->paper_drawn == false)
               self->draw_wallpaper();

            if (self->queue_o)
                xQueueSend(self->queue_o, &frame, portMAX_DELAY);
            else
                self->callback(frame);
        }
    }
    ESP_LOGI(TAG, "Stop");
    self->draw_wallpaper();
    vTaskDelete(NULL);
}

void LCD::run()
{
    xTaskCreatePinnedToCore((TaskFunction_t)lcd_task, TAG, 3 * 1024, this, 5, NULL, 1);
}
