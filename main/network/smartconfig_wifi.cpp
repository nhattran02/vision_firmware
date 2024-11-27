#include "smartconfig_wifi.hpp"
#include "nvs_flash.h"
#include "nvs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mqtt_client.hpp"

#define WIFI_MAXIMUM_RETRY 2

static int s_retry_num = 0;
EventGroupHandle_t s_wifi_event_group;

const int CONNECTED_BIT = BIT0;
const int ESPTOUCH_DONE_BIT = BIT1;
const int FAIL_BIT = BIT2;

static const char *TAG = "smartconfig_wifi";

volatile bool is_smart_config_run = false;
volatile bool is_wifi_connected = false;
volatile bool is_wifi_changed = false;
volatile bool is_found_channel = false;
volatile bool is_got_ssid_pswd = false;


char ssid[33] = {0};
char password[65] = {0};

static void save_wifi_credentials(const char *ssid, const char *password)
{
    nvs_handle_t nvs_handle;
    ESP_ERROR_CHECK(nvs_open("storage", NVS_READWRITE, &nvs_handle));

    ESP_ERROR_CHECK(nvs_set_str(nvs_handle, "wifi_ssid", ssid));
    ESP_ERROR_CHECK(nvs_set_str(nvs_handle, "wifi_password", password));

    ESP_LOGI(TAG, "WiFi credentials saved to NVS");

    ESP_ERROR_CHECK(nvs_commit(nvs_handle));
    nvs_close(nvs_handle);
}

static esp_err_t load_wifi_credentials(char *ssid, size_t ssid_len, char *password, size_t password_len)
{
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open("storage", NVS_READONLY, &nvs_handle);
    if (err != ESP_OK)
    {
        ESP_LOGI(TAG, "No saved WiFi credentials");
        return err;
    }

    err = nvs_get_str(nvs_handle, "wifi_ssid", ssid, &ssid_len);
    if (err == ESP_OK)
    {
        err = nvs_get_str(nvs_handle, "wifi_password", password, &password_len);
    }

    nvs_close(nvs_handle);
    return err;
}

static void connect_to_saved_wifi(void)
{

    if (load_wifi_credentials(ssid, sizeof(ssid), password, sizeof(password)) == ESP_OK)
    {
        is_smart_config_run = false;
        ESP_LOGI(TAG, "Connecting to saved WiFi: SSID=%s, PASSWORD=%s", ssid, password);

        wifi_config_t wifi_config;
        bzero(&wifi_config, sizeof(wifi_config_t));

        strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid));
        strncpy((char *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password));

        ESP_ERROR_CHECK(esp_wifi_start());
        ESP_ERROR_CHECK(esp_wifi_disconnect());
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
        ESP_ERROR_CHECK(esp_wifi_connect());
        while (!is_wifi_changed)
        {
        }
        if (!is_wifi_connected)
        {
            goto SMART_CONFIG;
        }
    }
    else
    {
        SMART_CONFIG:
        is_smart_config_run = true;
        ESP_LOGI(TAG, "No saved WiFi credentials found, starting SmartConfig");
        // ESP_ERROR_CHECK(esp_wifi_stop());
        // ESP_ERROR_CHECK(esp_wifi_start());
    }
}

static void smartconfig_task(void *parm)
{
    EventBits_t uxBits;
    ESP_ERROR_CHECK(esp_smartconfig_set_type(SC_TYPE_ESPTOUCH));
    smartconfig_start_config_t cfg = SMARTCONFIG_START_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_smartconfig_start(&cfg));
    while (1)
    {
        uxBits = xEventGroupWaitBits(s_wifi_event_group, CONNECTED_BIT | ESPTOUCH_DONE_BIT, true, false, portMAX_DELAY);
        if (uxBits & CONNECTED_BIT)
        {
            ESP_LOGI(TAG, "WiFi Connected to ap");
        }
        if (uxBits & ESPTOUCH_DONE_BIT)
        {
            ESP_LOGI(TAG, "smartconfig over");
            esp_smartconfig_stop();
            vTaskDelete(NULL);
        }
    }
}

static void event_handler(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
    {
        if (is_smart_config_run == true)
        {
            ESP_LOGI(TAG, "Smart config start");
            xTaskCreate(smartconfig_task, "smartconfig_task", 4096, NULL, 3, NULL);
        }
    }
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
    {
        ESP_LOGI(TAG, "STA disconnected");
        if (s_retry_num < WIFI_MAXIMUM_RETRY)
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        }
        else
        {
            is_wifi_changed = true;
            is_wifi_connected = false;
            ESP_LOGI(TAG, "connect to the AP fail");
            xEventGroupSetBits(s_wifi_event_group, FAIL_BIT);
        }
    }
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        is_wifi_changed = true;
        is_wifi_connected = true;
        ESP_LOGI(TAG, "STA got ip");
        xEventGroupSetBits(s_wifi_event_group, CONNECTED_BIT);
    }
    else if (event_base == SC_EVENT && event_id == SC_EVENT_SCAN_DONE)
    {
        ESP_LOGI(TAG, "Scan done");
    }
    else if (event_base == SC_EVENT && event_id == SC_EVENT_FOUND_CHANNEL)
    {
        is_found_channel = true;
        ESP_LOGI(TAG, "Found channel");
    }
    else if (event_base == SC_EVENT && event_id == SC_EVENT_GOT_SSID_PSWD)
    {
        is_got_ssid_pswd = true;
        ESP_LOGI(TAG, "Got SSID and password");

        smartconfig_event_got_ssid_pswd_t *evt = (smartconfig_event_got_ssid_pswd_t *)event_data;
        wifi_config_t wifi_config;

        uint8_t rvd_data[33] = {0};

        bzero(&wifi_config, sizeof(wifi_config_t));
        memcpy(wifi_config.sta.ssid, evt->ssid, sizeof(wifi_config.sta.ssid));
        memcpy(wifi_config.sta.password, evt->password, sizeof(wifi_config.sta.password));

#ifdef CONFIG_SET_MAC_ADDRESS_OF_TARGET_AP
        wifi_config.sta.bssid_set = evt->bssid_set;
        if (wifi_config.sta.bssid_set == true)
        {
            ESP_LOGI(TAG, "Set MAC address of target AP: " MACSTR " ", MAC2STR(evt->bssid));
            memcpy(wifi_config.sta.bssid, evt->bssid, sizeof(wifi_config.sta.bssid));
        }
#endif

        memcpy(ssid, evt->ssid, sizeof(evt->ssid));
        memcpy(password, evt->password, sizeof(evt->password));
        ESP_LOGI(TAG, "SSID:%s", ssid);
        ESP_LOGI(TAG, "PASSWORD:%s", password);

        save_wifi_credentials((const char *)ssid, (const char *)password);

        ESP_ERROR_CHECK(esp_wifi_disconnect());
        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
        esp_wifi_connect();
    }
    else if (event_base == SC_EVENT && event_id == SC_EVENT_SEND_ACK_DONE)
    {
        ESP_LOGI(TAG, "ACK sent");
        xEventGroupSetBits(s_wifi_event_group, ESPTOUCH_DONE_BIT);
    }
}


void initialise_wifi(void)
{
    /* Initialize NVS partition */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        /* NVS partition was truncated
         * and needs to be erased */
        ESP_ERROR_CHECK(nvs_flash_erase());

        /* Retry nvs_flash_init */
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    ESP_ERROR_CHECK(esp_netif_init());
    s_wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(SC_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));

    connect_to_saved_wifi();

    // ESP_LOGI(TAG, "wifi start");
    // ESP_ERROR_CHECK(esp_wifi_start());
}
