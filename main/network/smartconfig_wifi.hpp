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


extern char ssid[33];
extern char password[65];

extern volatile bool is_smart_config_run;
extern volatile bool is_wifi_connected;
extern volatile bool is_wifi_changed;
extern volatile bool is_found_channel;
extern volatile bool is_got_ssid_pswd;
extern EventGroupHandle_t s_wifi_event_group;

extern const int CONNECTED_BIT;
extern const int ESPTOUCH_DONE_BIT;
extern const int FAIL_BIT;

void initialise_wifi(void);


#ifdef __cplusplus
}
#endif

#endif