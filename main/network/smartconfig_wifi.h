#ifndef _SMARTCONFIG_WIFI_H_
#define _SMARTCONFIG_WIFI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_eap_client.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_smartconfig.h"
#include "esp_mac.h"


#define MAX_WIFI_LIST 20

typedef struct
{
    char ssid[33];
    char password[65];
} wifi_cred_t;

typedef struct
{
    wifi_cred_t wifi_list[MAX_WIFI_LIST];
    int wifi_count;
} wifi_store_t;

void initialise_wifi(void);


#ifdef __cplusplus
}
#endif

#endif