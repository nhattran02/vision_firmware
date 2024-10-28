#include <stdio.h>
#include "fingerprint.hpp"
#include "esp_log.h"
#include "esp_mac.h"
extern "C"
{
    #include "r307.h"
}

#define R307_ADDRESS        "0xFFFFFFFF" 
#define ENROLL_BUFFER_ID    "1" 
#define DETECT_BUFFER_ID    "1" 


static const char TAG[] = "fingerprint";

uint8_t esp_chip_id[6];
char mac_address[20];

char default_address[4] = {0xFF, 0xFF, 0xFF, 0xFF};
char default_password[4] = {0x00, 0x00, 0x00, 0x00};

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

    if(confirmation_code == 0x00)
    {
        ESP_LOGI(TAG, "Detected R307 Fingerprint Module");
    }
}

void Fingerprint::update()
{

}


static void fingerprint_enroll_task(Fingerprint *self)
{
    uint8_t user_id = 1;
    
    while (1)
    {
        ESP_LOGI(TAG, "Enrolling user %d...", user_id);
        if (GenImg(default_address) == 0)
        {
            ESP_LOGI(TAG, "Finger detected");
            if (Img2Tz(default_address, ENROLL_BUFFER_ID) == 0) {
                ESP_LOGI(TAG, "Created feature from image");
                
                if (Store(default_address, ENROLL_BUFFER_ID, (char*)&user_id) == 0) {
                    ESP_LOGI(TAG, "Enroll success! Stored template with ID: %d", user_id);
                    user_id++;
                } else {
                    ESP_LOGI(TAG, "Error: Cannot store template");
                }
            } else {
                ESP_LOGI(TAG, "Error: Cannot create feature from image");
            }            
        }
        else 
        {
            ESP_LOGI(TAG, "No finger detected");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void fingerprint_detect_task(Fingerprint *self)
{
   
}

void Fingerprint::fingerprint_enroll_run()
{
    xTaskCreate((TaskFunction_t)fingerprint_enroll_task, "fingerprint_enroll_task", 5 * 1024, this, 5, NULL);
}

void Fingerprint::fingerprint_detect_run()
{
    xTaskCreate((TaskFunction_t)fingerprint_detect_task, "fingerprint_enroll_task", 5 * 1024, this, 5, NULL);    
}