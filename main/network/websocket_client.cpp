#include "websocket_client.hpp"
#include <list>
#include "esp_timer.h"
#include "img_converters.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_websocket_client.h"
#include "esp_event.h"
#include <cJSON.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

#define NO_DATA_TIMEOUT_SEC 5
#define WEBSOCKET_URI       "ws://192.168.0.108:8885"

static const char *TAG = "websocket_client";
static TimerHandle_t shutdown_signal_timer;
static SemaphoreHandle_t shutdown_semaphore;
static QueueHandle_t xQueueFrameI = NULL;
static QueueHandle_t xQueueFrameO = NULL;
static esp_websocket_client_handle_t client;
static bool gReturnFB = true;

static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0)
    {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

static void shutdown_signaler(TimerHandle_t xTimer)
{
    ESP_LOGI(TAG, "No data received for %d seconds, signaling shutdown", NO_DATA_TIMEOUT_SEC);
    xSemaphoreGive(shutdown_semaphore);
}

static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
    switch (event_id)
    {
    case WEBSOCKET_EVENT_CONNECTED:
    {
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_CONNECTED");
        break;
    }
    case WEBSOCKET_EVENT_DISCONNECTED:
    {
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_DISCONNECTED");
        log_error_if_nonzero("HTTP status code", data->error_handle.esp_ws_handshake_status_code);
        if (data->error_handle.error_type == WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT)
        {
            log_error_if_nonzero("reported from esp-tls", data->error_handle.esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", data->error_handle.esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno", data->error_handle.esp_transport_sock_errno);
        }
        break;
    }
    case WEBSOCKET_EVENT_DATA:
    {
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_DATA");
        ESP_LOGI(TAG, "Received opcode=%d", data->op_code);
        if (data->op_code == 0x08 && data->data_len == 2)
        {
            ESP_LOGW(TAG, "Received closed message with code=%d", 256 * data->data_ptr[0] + data->data_ptr[1]);
        }
        else
        {
            ESP_LOGW(TAG, "Received=%.*s\n\n", data->data_len, (char *)data->data_ptr);
        }

        // If received data contains json structure it succeed to parse
        cJSON *root = cJSON_Parse(data->data_ptr);
        if (root)
        {
            for (int i = 0; i < cJSON_GetArraySize(root); i++)
            {
                cJSON *elem = cJSON_GetArrayItem(root, i);
                cJSON *id = cJSON_GetObjectItem(elem, "id");
                cJSON *name = cJSON_GetObjectItem(elem, "name");
                ESP_LOGW(TAG, "Json={'id': '%s', 'name': '%s'}", id->valuestring, name->valuestring);
            }
            cJSON_Delete(root);
        }

        ESP_LOGW(TAG, "Total payload length=%d, data_len=%d, current payload offset=%d\r\n", data->payload_len, data->data_len, data->payload_offset);

        xTimerReset(shutdown_signal_timer, portMAX_DELAY);
        break;
    }
    case WEBSOCKET_EVENT_ERROR:
    {
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_ERROR");
        log_error_if_nonzero("HTTP status code", data->error_handle.esp_ws_handshake_status_code);
        if (data->error_handle.error_type == WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT)
        {
            log_error_if_nonzero("reported from esp-tls", data->error_handle.esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", data->error_handle.esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno", data->error_handle.esp_transport_sock_errno);
        }
        break;
    }
    }
}

static void stream_task(void *pvparameters)
{
    camera_fb_t *frame = NULL;
    esp_err_t ret = ESP_OK;
    size_t _jpg_buf_len = 0;
    uint8_t *_jpg_buf = NULL;

    while (true)
    {
        if (xQueueReceive(xQueueFrameI, &frame, portMAX_DELAY))
        {
            if (frame->format == PIXFORMAT_JPEG)
            {
                _jpg_buf = frame->buf;
                _jpg_buf_len = frame->len;
            }
            else if (!frame2jpg(frame, 80, &_jpg_buf, &_jpg_buf_len))
            {
                ESP_LOGE(TAG, "JPEG compression failed");
                ret = ESP_FAIL;
            }
        }
        else
        {
            ret = ESP_FAIL;
        }

        if (ret == ESP_OK)
        {
            if (esp_websocket_client_is_connected(client))
            {
                ret = esp_websocket_client_send_bin(client, (const char *)_jpg_buf, _jpg_buf_len, portMAX_DELAY) == -1 ? ESP_FAIL : ESP_OK;
            }
        }

        if (frame->format != PIXFORMAT_JPEG)
        {
            free(_jpg_buf);
            _jpg_buf = NULL;
        }

        if (xQueueFrameO)
        {
            xQueueSend(xQueueFrameO, &frame, portMAX_DELAY);
        }
        else if (gReturnFB)
        {
            esp_camera_fb_return(frame);
        }
        else
        {
            free(frame);
        }

        if (ret != ESP_OK)
        {
            break;
        }
    }
    
    xSemaphoreTake(shutdown_semaphore, portMAX_DELAY);
    esp_websocket_client_close(client, portMAX_DELAY);
    ESP_LOGE(TAG, "Websocket Stopped");
    esp_websocket_client_destroy(client);
    vTaskDelete(NULL);
}

void register_websocket_client(const QueueHandle_t frame_i, const QueueHandle_t frame_o, const bool return_fb)
{
    xQueueFrameI = frame_i;
    xQueueFrameO = frame_o;
    gReturnFB = return_fb;

    esp_websocket_client_config_t websocket_cfg = {};
    shutdown_signal_timer = xTimerCreate("Websocket shutdown timer", NO_DATA_TIMEOUT_SEC * 1000 / portTICK_PERIOD_MS,
                                         pdFALSE, NULL, shutdown_signaler);
    shutdown_semaphore = xSemaphoreCreateBinary();

    websocket_cfg.uri = WEBSOCKET_URI;

    ESP_LOGI(TAG, "Connecting to %s...", websocket_cfg.uri);

    client = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);

    esp_websocket_client_start(client);
    xTimerStart(shutdown_signal_timer, portMAX_DELAY);

    ESP_LOGI(TAG, "Starting stream to websocket server");
    xTaskCreate(&stream_task, "stream_task", 8192, NULL, 5, NULL);
}