#include <time.h>
#include <sys/time.h>
#include "esp_sntp.h"
#include "esp_log.h"
#include "ntp_time.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "smartconfig_wifi.hpp"
extern "C"
{
#include "gui_logic_utils.h"
}
const char *TAG = "NTP";

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "Time synchronized\n");
}

void initialize_sntp(void)
{
    ESP_LOGI(TAG, "Initializing SNTP\n");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_set_time_sync_notification_cb(time_sync_notification_cb);
    sntp_init();
}

void format_date_time(char *date_str, char *time_str, char *time_no_sec_str, char *day_str)
{
    time_t now;
    struct tm timeinfo;
    char strftime_buf[64];

    time(&now);

    now += 7 * 3600;

    localtime_r(&now, &timeinfo);

    strftime(date_str, 11, "%d/%m/%Y", &timeinfo);

    strftime(time_str, 9, "%H:%M:%S", &timeinfo);

    strftime(time_no_sec_str, 6, "%H:%M", &timeinfo);

    strftime(day_str, 10, "%A", &timeinfo);
}

void sntp_task(void *pvParameters)
{
    initialize_sntp();

    while (1)
    {
        format_date_time(ntp_date, ntp_time, ntp_time_no_sec, ntp_day);
        // ESP_LOGI(TAG, "Date: %s, Time: %s, TimeNoSec: %s\n", ntp_date, ntp_time, ntp_time_no_sec);
        update_time_to_gui();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void sntp_task_run(void)
{
    const int timeout_ms = 5000;
    const int delay_ms = 100;
    int elapsed_time = 0;

    while (!is_wifi_connected && elapsed_time < timeout_ms)
    {
        vTaskDelay(delay_ms / portTICK_PERIOD_MS);
        elapsed_time += delay_ms;
    }

    if (is_wifi_connected)
    {
        ESP_LOGI("SNTP", "Wi-Fi connected, starting SNTP task...");
        xTaskCreate(&sntp_task, "sntp_task", 4096 * 2, NULL, 5, NULL);
    }
    else
    {
        ESP_LOGW("SNTP", "Timeout waiting for Wi-Fi connection");
    }
}