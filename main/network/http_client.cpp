#include "http_client.hpp"
#include <list>
#include "esp_http_client.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "fb_gfx.h"
#include "app_mdns.h"
#include "sdkconfig.h"
#include "esp_log.h"

#define SERVER_URL "http://192.168.0.108:5000/video_upload"
#define USERNAME "username"
#define PASSWORD "password"
#define PART_BOUNDARY "123456789000000000000987654321"
static const char* _STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char* _STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char* _STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\nX-Timestamp: %d.%06d\r\n\r\n";


static const char *TAG = "http client";


static QueueHandle_t xQueueFrameI = NULL;
static QueueHandle_t xQueueFrameO = NULL;
static bool gReturnFB = true;
static esp_http_client_handle_t client = NULL;


static void stream_to_server_task(void *pvparameters)
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
            esp_http_client_set_header(client, "Content-Type", "image/jpeg");
            esp_http_client_set_post_field(client, (const char *)_jpg_buf, _jpg_buf_len);            
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
            ESP_LOGE(TAG, "Error occurred, retrying in 5 seconds...");
            vTaskDelay(5000 / portTICK_PERIOD_MS);
            continue;
        }
    }
}

esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ERROR:
        ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
        ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
        break;
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
        break;
    default:
        break;
    }
    return ESP_OK;
}

void register_http_client(const QueueHandle_t frame_i, const QueueHandle_t frame_o, const bool return_fb)
{
    xQueueFrameI = frame_i;
    xQueueFrameO = frame_o;
    gReturnFB = return_fb;

    esp_http_client_config_t config = {
        .url = SERVER_URL,
        .method = HTTP_METHOD_POST,
        .event_handler = _http_event_handler,
    };

    client = esp_http_client_init(&config);

    if (esp_http_client_open(client, 0) != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open HTTP connection");
        esp_http_client_cleanup(client);
        return;
    }

    ESP_LOGI(TAG, "Starting stream to server task");
    xTaskCreate(&stream_to_server_task, "stream_to_server_task", 8192, NULL, 5, NULL);
}

