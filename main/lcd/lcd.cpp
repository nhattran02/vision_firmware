#include "lcd.hpp"
#include <string.h>
#include <stdio.h>
#include "esp_log.h"
#include "esp_camera.h"
#include "logo_en_240x240_lcd.h"
#include "esp_lcd_ili9341.h"
#include "esp_timer.h"


static const char TAG[] = "lcd";


LCD::LCD(Button *key,
         QueueHandle_t queue_i,
         QueueHandle_t queue_o,
         void (*callback)(camera_fb_t *)) : Frame(queue_i, queue_o, callback),
                                            key(key),
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
            .lcd_cmd_bits = LCD_CMD_BITS,
            .lcd_param_bits = LCD_PARAM_BITS,
        };

        // Attach the LCD to the SPI bus
        ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));
        
        ESP_LOGI(TAG, "Install ILI9341 panel driver");
        esp_lcd_panel_dev_config_t panel_config = {
            .reset_gpio_num = LCD_NUM_RST,
            .rgb_endian = LCD_RGB_ENDIAN_RGB, 
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

        this->draw_wallpaper();
        vTaskDelay(pdMS_TO_TICKS(1000));
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


