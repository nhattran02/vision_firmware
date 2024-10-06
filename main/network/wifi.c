#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_mac.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "sdkconfig.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/ip4_addr.h"
#include "mdns.h"
#include "wifi.h"


 /* The examples use WiFi configuration that you can set via 'make menuconfig'.

    If you'd rather not, just change the below entries to strings with
    the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
 */
#define EXAMPLE_ESP_WIFI_SSID CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS CONFIG_ESP_WIFI_PASSWORD
#define EXAMPLE_ESP_MAXIMUM_RETRY CONFIG_ESP_MAXIMUM_RETRY
#define EXAMPLE_ESP_WIFI_AP_SSID CONFIG_ESP_WIFI_AP_SSID
#define EXAMPLE_ESP_WIFI_AP_PASS CONFIG_ESP_WIFI_AP_PASSWORD
#define EXAMPLE_MAX_STA_CONN CONFIG_MAX_STA_CONN
#define EXAMPLE_IP_ADDR CONFIG_SERVER_IP
#define EXAMPLE_ESP_WIFI_AP_CHANNEL CONFIG_ESP_WIFI_AP_CHANNEL

static const char* TAG = "wifi";

static int s_retry_num = 0;
/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group = NULL;
static esp_netif_t* ap_netif = NULL;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
    int32_t event_id, void* event_data)
{
    switch (event_id) {
    case WIFI_EVENT_AP_STACONNECTED:
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*)event_data;
        ESP_LOGI(TAG, "station:" MACSTR " join, AID=%d", MAC2STR(event->mac), event->aid);
        break;

    case WIFI_EVENT_AP_STADISCONNECTED:
        wifi_event_ap_stadisconnected_t* ds_event = (wifi_event_ap_stadisconnected_t*)event_data;
        ESP_LOGI(TAG, "station:" MACSTR "leave, AID=%d", MAC2STR(ds_event->mac), ds_event->aid);
        break;

    case WIFI_EVENT_STA_START:
        ESP_LOGI(TAG, "WIFI_EVENT_STA_START");
        esp_wifi_connect();
        break;

    case WIFI_EVENT_STA_DISCONNECTED:
        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY)
        {
            esp_wifi_connect();
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        }
        else {
            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        }
        ESP_LOGI(TAG, "connect to the AP fail");
        break;
    default:
        break;
    }
    // mdns_handle_system_event(ctx, event);
    return;
}


static void ip_event_handler(void* arg, esp_event_base_t event_base,
    int32_t event_id, void* event_data)
{
    ip_event_got_ip_t* event;

    switch (event_id) {
    case IP_EVENT_STA_GOT_IP:
        event = (ip_event_got_ip_t*)event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR "\n", IP2STR(&event->ip_info.ip));
        s_retry_num = 0;
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        break;
    default:
        break;
    }
    return;
}

void wifi_init_softap(esp_netif_t* netif)
{
    if (strcmp(EXAMPLE_IP_ADDR, "192.168.4.1"))
    {
        int a, b, c, d;
        sscanf(EXAMPLE_IP_ADDR, "%d.%d.%d.%d", &a, &b, &c, &d);
        esp_netif_ip_info_t ip_info;
        IP4_ADDR(&ip_info.ip, a, b, c, d);
        IP4_ADDR(&ip_info.gw, a, b, c, d);
        IP4_ADDR(&ip_info.netmask, 255, 255, 255, 0);
        ESP_ERROR_CHECK(esp_netif_dhcps_stop(netif));
        ESP_ERROR_CHECK(esp_netif_set_ip_info(netif, &ip_info));
        ESP_ERROR_CHECK(esp_netif_dhcps_start(netif));
    }
    wifi_config_t wifi_config = {
        .ap.ssid = EXAMPLE_ESP_WIFI_AP_SSID,
        .ap.password = EXAMPLE_ESP_WIFI_AP_PASS,
        .ap.ssid_len = strlen((char*)wifi_config.ap.ssid),
        .ap.channel = 1,
        .ap.authmode = WIFI_AUTH_WPA2_PSK,
        // .ap.max_connection = EXAMPLE_MAX_STA_CONN,
        .ap.max_connection = 4,
        .ap.beacon_interval = 100,
    };

    if (strlen(EXAMPLE_ESP_WIFI_AP_PASS) == 0)
    {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }
    if (strlen(EXAMPLE_ESP_WIFI_AP_CHANNEL))
    {
        int channel;
        sscanf(EXAMPLE_ESP_WIFI_AP_CHANNEL, "%d", &channel);
        wifi_config.ap.channel = channel;
    }

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));

    ESP_LOGI(TAG, "wifi_init_softap finished.SSID:%s password:%s",
        EXAMPLE_ESP_WIFI_AP_SSID, EXAMPLE_ESP_WIFI_AP_PASS);
}


void wifi_init_sta()
{
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .password = EXAMPLE_ESP_WIFI_PASS
        },
    };

    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:%s password:%s",
        EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
}

void app_wifi_main()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    wifi_mode_t mode = WIFI_MODE_NULL;

    if (strlen(EXAMPLE_ESP_WIFI_AP_SSID) && strlen(EXAMPLE_ESP_WIFI_SSID))
    {
        mode = WIFI_MODE_APSTA;
    }
    else if (strlen(EXAMPLE_ESP_WIFI_AP_SSID))
    {
        mode = WIFI_MODE_AP;
    }
    else if (strlen(EXAMPLE_ESP_WIFI_SSID))
    {
        mode = WIFI_MODE_STA;
    }

    if (mode == WIFI_MODE_NULL)
    {
        ESP_LOGW(TAG, "Neither AP nor STA have been configured. WiFi will be off.");
        return;
    }

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());

    s_wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &ip_event_handler, NULL));
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(mode));

    if (mode & WIFI_MODE_AP)
    {
        ap_netif = esp_netif_create_default_wifi_ap();
        wifi_init_softap(ap_netif);
    }

    if (mode & WIFI_MODE_STA)
    {
        esp_netif_create_default_wifi_sta();
        wifi_init_sta();
    }
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));
    ESP_LOGI(TAG, "wifi init finished.");

    if (mode & WIFI_MODE_STA) {
        xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
            pdFALSE,
            pdFALSE,
            portMAX_DELAY);
    }
    vEventGroupDelete(s_wifi_event_group);
    s_wifi_event_group = NULL;
}

void app_wifi_stop()
{
    ESP_LOGI(TAG, "Stopping Wi-Fi...");

    // Stop and deinitialize Wi-Fi
    ESP_ERROR_CHECK(esp_wifi_stop());
    ESP_ERROR_CHECK(esp_wifi_deinit());

    // Unregister Wi-Fi and IP event handlers
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler));
    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &ip_event_handler));

    esp_netif_destroy_default_wifi(ap_netif);
    ap_netif = NULL;

    // Deinitialize network interface
    esp_netif_deinit();

    // Delete event group if it was created
    if (s_wifi_event_group) {
        vEventGroupDelete(s_wifi_event_group);
        s_wifi_event_group = NULL;
        ESP_LOGI(TAG, "Wi-Fi event group deleted.");
    }

    // Deinitialize the default event loop if no other components need it
    ESP_ERROR_CHECK(esp_event_loop_delete_default());

    esp_err_t ret = nvs_flash_deinit();
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "NVS flash deinitialized.");
    }
    else {
        ESP_LOGW(TAG, "NVS flash deinit failed or wasn't initialized: %s", esp_err_to_name(ret));
    }

    ESP_LOGI(TAG, "Wi-Fi stopped and deinitialized.");

}


