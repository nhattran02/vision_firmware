#pragma once

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "__base__.hpp"
#include "camera.hpp"
#include "button.hpp"


#define LCD_PIXEL_CLOCK_HZ     (25 * 1000 * 1000)
#define LCD_BK_LIGHT_ON_LEVEL  1
#define LCD_BK_LIGHT_OFF_LEVEL !LCD_BK_LIGHT_ON_LEVEL
#define LCD_NUM_SCLK           GPIO_NUM_21
#define LCD_NUM_MOSI           GPIO_NUM_47
#define LCD_NUM_MISO           GPIO_NUM_NC
#define LCD_NUM_DC             GPIO_NUM_43
#define LCD_NUM_RST            GPIO_NUM_NC
#define LCD_NUM_CS             GPIO_NUM_44
#define LCD_NUM_BK_LIGHT       GPIO_NUM_48  
#define LCD_NUM_TOUCH_CS       GPIO_NUM_NC
#define LCD_H_RES              240 
#define LCD_V_RES              320
#define LCD_CMD_BITS           8
#define LCD_PARAM_BITS         8
#define LCD_HOST               SPI2_HOST

void disable_lvgl();
void enable_lvgl();
extern volatile bool lcd_on;
extern volatile bool faceid_enroll_on;
extern volatile bool authen_on;
extern volatile bool attendance_on;

class LCD : public Observer, public Frame
{
private:
    Button *key;
public:
    esp_lcd_panel_handle_t panel_handle;
    bool switch_on;
    bool paper_drawn;
    
    LCD(Button *key,
        QueueHandle_t xQueueFrameI = nullptr,
        QueueHandle_t xQueueFrameO = nullptr,
        void (*callback)(camera_fb_t *) = esp_camera_fb_return);

    void draw_wallpaper();
    void draw_color(int color);
    
    void update();

    void run();
};




