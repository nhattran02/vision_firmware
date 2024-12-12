#include <stdio.h>
#include "fingerprint.hpp"
#include "esp_log.h"
#include "esp_mac.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_timer.h" 
#include "sdcard.hpp"
extern "C"
{
#include "r307.h"
}
#include "gui_logic_utils.h"
#include "lcd.hpp"

#define TOTAL_DATA_LENGTH   40044
#define ACK_PACKET_SIZE     12      
#define DATA_PACKET_SIZE    127    
#define BUFFER_SIZE         4096

static const char TAG[] = "fingerprint";

uint8_t esp_chip_id[6];
char mac_address[20];


char default_address[4] = {0xFF, 0xFF, 0xFF, 0xFF};
char default_password[4] = {0x00, 0x00, 0x00, 0x00};
char enroll_buffer_id_1[1] = {0x01};
char enroll_buffer_id_2[1] = {0x02};
volatile bool finger_detected = false;
volatile bool is_finger_true = false;

Fingerprint::Fingerprint(Button *key,
                         QueueHandle_t queue_i,
                         QueueHandle_t queue_o,
                         void (*callback)(camera_fb_t *)) : Frame(queue_i, queue_o, callback),
                                                            key(key)
{
    r307_init();

    esp_efuse_mac_get_default(esp_chip_id);
    sprintf(mac_address, "%02x:%02x:%02x:%02x:%02x:%02x", esp_chip_id[0], esp_chip_id[1], esp_chip_id[2], esp_chip_id[3], esp_chip_id[4], esp_chip_id[5]);
    ESP_LOGI(TAG, "MAC Address is %s", mac_address);

    uint8_t confirmation_code = 1;
    confirmation_code = VfyPwd(default_address, default_password);

    if (confirmation_code == 0x00)
    {
        ESP_LOGI(TAG, "Detected R307 Fingerprint Module");
    }
    // SetBaudrate115200(default_address);
    // ReadSysPara(default_address);
}

void r307_stop()
{
    r307_deinit();
}

void r307_run()
{
    r307_init();
}

void Fingerprint::update()
{
}

static void get_fingerprint_image()
{
    int64_t start_time = esp_timer_get_time();
    uint8_t confirmation_code = UpImage(default_address);
    if (confirmation_code != 0x00) 
    {
        ESP_LOGE(TAG, "Failed to get fingerprint image. Confirmation code: %d", confirmation_code);
        return;
    }

    uint8_t *received_package = (uint8_t *)malloc(BUFFER_SIZE + 1);
    uint8_t *image_data = (uint8_t *)malloc(TOTAL_DATA_LENGTH);
    uint8_t *image_buf = (uint8_t *)malloc(TOTAL_DATA_LENGTH);
    if (received_package == NULL || image_data == NULL || image_buf == NULL)
    {
        ESP_LOGE(TAG, "Failed to allocate memory");
        free(received_package);
        free(image_data);
        free(image_buf);
        received_package = NULL;
        image_data = NULL;
        image_buf = NULL;
        return;
    }

    int total_bytes_received = 0;
    while(total_bytes_received < TOTAL_DATA_LENGTH)
    {
        int rxBytes = uart_read_bytes(UART_NUM_1, received_package, BUFFER_SIZE, pdMS_TO_TICKS(50));
        if (rxBytes > 0)
        {
            memcpy(image_data + total_bytes_received, received_package, rxBytes);
            total_bytes_received += rxBytes;
        }
    }

    int total_data_copied = 0;
    int i = 0;

    while (i < total_bytes_received)
    {
        if (image_data[i] == 0xef && image_data[i + 1] == 0x01 &&
            image_data[i + 2] == 0xff && image_data[i + 3] == 0xff &&
            image_data[i + 4] == 0xff && image_data[i + 5] == 0xff)
        {
            i += 12; 
            continue;
        }

        image_buf[total_data_copied++] = image_data[i++];
    }

    // save_fingerprint_to_sdcard(image_buf);

    int64_t end_time = esp_timer_get_time();
    int64_t total_time_ms = (end_time - start_time) / 1000;
    ESP_LOGI(TAG, "Total time to read fingerprint image: %lld ms", total_time_ms);

    // ESP_LOGE(TAG, "Image Data");
    // ESP_LOG_BUFFER_HEXDUMP(TAG, image_data, TOTAL_DATA_LENGTH, ESP_LOG_INFO);    
    ESP_LOGE(TAG, "Image Buf | Size = %d", total_data_copied);
    ESP_LOG_BUFFER_HEXDUMP(TAG, image_buf, total_data_copied, ESP_LOG_INFO);     
    free(received_package);
    free(image_data);
    free(image_buf);
    received_package = NULL;
    image_data = NULL;
    image_buf = NULL;
}

static void fingerprint_enroll_task(Fingerprint *self)
{
    uint8_t user_id = 2;
    uint8_t confirmation_code = 0;
    char page_id[2] = {0};
    page_id[0] = (char)((user_id >> 8) & 0xFF);
    page_id[1] = (char)(user_id & 0xFF);

    while (1)
    {
        ESP_LOGI(TAG, "Please place your finger");
        while (GenImg(default_address) != 0)
        {

        }

        confirmation_code = Img2Tz(default_address, enroll_buffer_id_1);
        if (confirmation_code != 0)
        {
            continue;
        }

        ESP_LOGI(TAG, "Please remove your finger");

        while (GenImg(default_address) == 0)
        {

        }
        ESP_LOGI(TAG, "Please place the same finger on the sensor again.");

        while (GenImg(default_address) != 0)
        {

        }

        confirmation_code = Img2Tz(default_address, enroll_buffer_id_2);
        if (confirmation_code != 0)
        {
            continue;
        }

        confirmation_code = RegModel(default_address);
        if (confirmation_code == 0)
        {
            confirmation_code = Store(default_address, enroll_buffer_id_1, page_id);
            if (confirmation_code == 0)
            {
                ESP_LOGI(TAG, "Enroll success! Stored template with ID: %d", user_id);
                break;
            }
            else
            {
                ESP_LOGI(TAG, "Error: Cannot store template | %d", confirmation_code);
            }
        }
    }

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}

void finger_delete_all()
{
    uint8_t confirmation_code;
    char start_page[2] = {0x00, 0x00};
    char page_number[2] = {0x00, 0xC8};

    confirmation_code = DeletChar(default_address, start_page, page_number);
    if (confirmation_code != 0)
    {
        ESP_LOGE(TAG, "Failed to delete all templates");
    }
    ESP_LOGI(TAG, "Deleted all Fingerprint templates");
}

void test()
{
    uint8_t confirmation_code;
    char start_page[2] = {0x00, 0x09};
    char page_number[2] = {0x00, 0x05};

    confirmation_code = DeletChar(default_address, start_page, page_number);
    if (confirmation_code != 0)
    {
        ESP_LOGE(TAG, "Failed to delete all templates");
    }
    ESP_LOGI(TAG, "Deleted all Fingerprint templates");    
}

static void fingerprint_detect_task(Fingerprint *self)
{
    uint8_t confirmation_code;
    char start_page[2] = {0x00, 0x00};      // Specify the start page for the search
    char page_number[2] = {0x00, 0xC8};     // Specify the page range for the search
    
    while (1)
    {
        while (GenImg(default_address) != 0)
        {
            finger_detected = false;
        }

        confirmation_code = Img2Tz(default_address, enroll_buffer_id_1);
        if (confirmation_code != 0)
        {
            continue;
        }

        confirmation_code = Search(default_address, enroll_buffer_id_1, start_page, page_number);
        if (confirmation_code == 0)
        {
            if (current_state == STATE_MAIN_SCREEN)
            {

            }
            else if (current_state == STATE_CAMERA_SCREEN)
            {
                ESP_LOGI(TAG, "Fingerprint detected! User ID: %d", _page_id);
                if (authen_on == true)
                {
                    if (_page_id > 0 && users[_page_id - 1].role == 1)
                    {
                        is_finger_true = true;
                    }
                    else
                    {
                        is_finger_true = false;
                    }
                }
                else // attend or enroll
                {
                    if (_page_id > 0)
                    {
                        is_finger_true = true;
                    }
                    else
                    {
                        is_finger_true = false;
                    }
                }
            }
        }
        else 
        {
            is_finger_true = false;
        }
        finger_detected = true;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }  
}


void Fingerprint::fingerprint_enroll_run()
{
    xTaskCreate((TaskFunction_t)fingerprint_enroll_task, "fingerprint_enroll_task", 5 * 1024, this, 5, NULL);
}

void Fingerprint::fingerprint_detect_run()
{
    xTaskCreate((TaskFunction_t)fingerprint_detect_task, "fingerprint_enroll_task", 5 * 1024, this, 5, &FingerprintDetectTaskHandle);
}

void fingerprint_detect_task_run()
{
    xTaskCreate((TaskFunction_t)fingerprint_detect_task, "fingerprint_enroll_task", 5 * 1024, NULL, 5, &FingerprintDetectTaskHandle);
}