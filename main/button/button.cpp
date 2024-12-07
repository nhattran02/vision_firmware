#include "button.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "esp_timer.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mcp23017.h"

#define PRESS_INTERVAL              200000
#define I2C_MASTER_SCL_IO           41          /*!< gpio number for I2C master clock IO21*/
#define I2C_MASTER_SDA_IO           42          /*!< gpio number for I2C master data  IO15*/
#define I2C_MASTER_NUM              I2C_NUM_0   /*!< I2C port number for master dev */
#define I2C_MASTER_TX_BUF_DISABLE   0           /*!< I2C master do not need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0           /*!< I2C master do not need buffer */
#define I2C_MASTER_FREQ_HZ          100000      /*!< I2C master clock frequency */

static const char *TAG = "button";
static i2c_bus_handle_t i2c_bus = NULL;
static mcp23017_handle_t device = NULL;
static uint8_t col_pins[4] = {0x01, 0x02, 0x04, 0x08}; // from row 0 to row 3
static uint8_t row_pins[4] = {0x10, 0x20, 0x40, 0x80}; // from col 0 to col 3

const char* button_names[] = {
    "BUTTON_IDLE", "BUTTON_0", "BUTTON_1", "BUTTON_2", "BUTTON_3",
    "BUTTON_4", "BUTTON_5", "BUTTON_6", "BUTTON_7", "BUTTON_8",
    "BUTTON_9", "BUTTON_STAR", "BUTTON_OK", "BUTTON_ESC",
    "BUTTON_MENU", "BUTTON_UP", "BUTTON_DOWN"
};

Button::Button() : key_configs({{BUTTON_0}, {BUTTON_1}, {BUTTON_2}, {BUTTON_3}, 
                                {BUTTON_4}, {BUTTON_5}, {BUTTON_6}, {BUTTON_7}, 
                                {BUTTON_8}, {BUTTON_9}, {BUTTON_STAR}, {BUTTON_OK}, 
                                {BUTTON_ESC}, {BUTTON_MENU}, {BUTTON_UP}, {BUTTON_DOWN}}),
                                pressed(BUTTON_IDLE), menu(0)
{   
    i2c_config_t conf = {
        I2C_MODE_MASTER, 
        I2C_MASTER_SDA_IO,
        I2C_MASTER_SCL_IO,
        GPIO_PULLUP_ENABLE,
        GPIO_PULLUP_ENABLE, 
        {I2C_MASTER_FREQ_HZ}, 
        0
    };
    
    i2c_bus = i2c_bus_create(I2C_MASTER_NUM, &conf);
    device = mcp23017_create(i2c_bus, MCP23017_I2C_ADDRESS_DEFAULT);

    if (i2c_bus == NULL || device == NULL)
    {
        ESP_LOGE(TAG, "I2C bus or device creation failed");
        return;
    }

    ESP_ERROR_CHECK(mcp23017_check_present(device));

    ESP_ERROR_CHECK(mcp23017_set_io_dir(device, 0xF0, MCP23017_GPIOB)); 
    ESP_ERROR_CHECK(mcp23017_set_pullup(device, 0xFFFF));

}

static button_name_t get_button_pressed(int col, uint8_t row_state)
{
    static const button_name_t button_map[4][4] = {
        {BUTTON_1, BUTTON_4, BUTTON_7, BUTTON_STAR},
        {BUTTON_2, BUTTON_5, BUTTON_8, BUTTON_0},
        {BUTTON_3, BUTTON_6, BUTTON_9, BUTTON_OK},
        {BUTTON_ESC, BUTTON_MENU, BUTTON_UP, BUTTON_DOWN}};

    for (int row = 0; row < 4; row++)
    {
        if ((row_state & (1 << row)) == 0)
        {
            return button_map[col][row];
        }
    }

    return BUTTON_IDLE; // No button pressed
}

static void button_task(Button *self)
{
    int64_t last_time = esp_timer_get_time();
    uint8_t menu_count = 0;

    while (true)
    {
        int64_t backup_time = esp_timer_get_time();

        for (int col = 0; col < 4; col++)
        {
            ESP_ERROR_CHECK(mcp23017_write_io(device, ~(col_pins[col]), MCP23017_GPIOB));
            vTaskDelay(pdMS_TO_TICKS(1));
                            
            uint8_t data = mcp23017_read_io(device, MCP23017_GPIOB);
            uint8_t row_state = (data & 0xF0) >> 4;

            if (row_state != 0x0F && (backup_time - last_time) > PRESS_INTERVAL)
            {
                self->pressed = get_button_pressed(col, row_state);

                if (self->pressed != BUTTON_IDLE)
                {
                    if (self->pressed == BUTTON_MENU)
                    {
                        self->menu++;
                        self->menu %= (MENU_MOTION_DETECTION + 1);
                    }

                    last_time = backup_time;
                    self->notify();
                    self->pressed = BUTTON_IDLE; // Reset button state
                    break;                       // Exit the column loop once a button is pressed
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}


void Button::run()
{
    xTaskCreatePinnedToCore((TaskFunction_t)button_task, TAG, 8 * 1024, this, 5, NULL, 0);
}
