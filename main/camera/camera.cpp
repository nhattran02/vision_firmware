#include "camera.hpp"
#include "esp_log.h"
#include "esp_system.h"

static const char* TAG = "camera";
static sensor_t *s = nullptr;
static QueueHandle_t xQueueFrameO = NULL;
static TaskHandle_t xTaskProcess = NULL;
volatile bool is_camera_allow_run = false;

Camera::Camera(const pixformat_t pixel_format,
               const framesize_t frame_size,
               const uint8_t fb_count,
               QueueHandle_t queue_o) : Frame(nullptr, queue_o, nullptr)
{
    ESP_LOGI(TAG, "Camera module is %s", CAMERA_MODULE_NAME);

#if CONFIG_CAMERA_MODEL_ESP_EYE || CONFIG_CAMERA_MODEL_ESP32_CAM_BOARD
    /* IO13, IO14 is designed for JTAG by default,
     * to use it as generalized input,
     * firstly declair it as pullup input */
    gpio_config_t conf;
    conf.mode = GPIO_MODE_INPUT;
    conf.pull_up_en = GPIO_PULLUP_ENABLE;
    conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    conf.intr_type = GPIO_INTR_DISABLE;
    conf.pin_bit_mask = 1LL << 13;
    gpio_config(&conf);
    conf.pin_bit_mask = 1LL << 14;
    gpio_config(&conf);
#endif

    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = CAMERA_PIN_D0;
    config.pin_d1 = CAMERA_PIN_D1;
    config.pin_d2 = CAMERA_PIN_D2;
    config.pin_d3 = CAMERA_PIN_D3;
    config.pin_d4 = CAMERA_PIN_D4;
    config.pin_d5 = CAMERA_PIN_D5;
    config.pin_d6 = CAMERA_PIN_D6;
    config.pin_d7 = CAMERA_PIN_D7;
    config.pin_xclk = CAMERA_PIN_XCLK;
    config.pin_pclk = CAMERA_PIN_PCLK;
    config.pin_vsync = CAMERA_PIN_VSYNC;
    config.pin_href = CAMERA_PIN_HREF;
    config.pin_sscb_sda = CAMERA_PIN_SIOD;
    config.pin_sscb_scl = CAMERA_PIN_SIOC;
    config.pin_pwdn = CAMERA_PIN_PWDN;
    config.pin_reset = CAMERA_PIN_RESET;
    config.xclk_freq_hz = XCLK_FREQ_HZ;
    config.pixel_format = pixel_format;
    config.frame_size = frame_size;
    config.jpeg_quality = 0;
    config.fb_count = fb_count;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY; 
    
    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Camera init failed with error 0x%x", err);
        return;
    }       

    is_camera_allow_run = true;

    s = esp_camera_sensor_get();
    if (s->id.PID == OV3660_PID || s->id.PID == OV2640_PID) {
        s->set_vflip(s, 1); //flip it back    
    }
    else if (s->id.PID == GC0308_PID) {
        s->set_hmirror(s, 0);
    }
    else if (s->id.PID == GC032A_PID) {
        s->set_vflip(s, 1);
    }

    // initial sensors are flipped vertically and colors are a bit saturated
    if (s->id.PID == OV3660_PID)
    {
        s->set_brightness(s, 1);  //up the brightness just a bit
        s->set_saturation(s, -2); //lower the saturation
    }        
}

static void camera_task(Camera *self)
{
    ESP_LOGI(TAG, "Start");
    while (true)
    {
        if (is_camera_allow_run == true)
        {
            if (self->queue_o == nullptr)
                break;

            camera_fb_t *frame = esp_camera_fb_get();
            if (frame)
            {
                xQueueSend(self->queue_o, &frame, portMAX_DELAY);
            }
        }
        else 
        {
            vTaskDelay(pdMS_TO_TICKS(10));
        }
    }
    ESP_LOGI(TAG, "Stop");
    vTaskDelete(NULL);
}

void Camera::run()
{
    xTaskCreatePinnedToCore((TaskFunction_t)camera_task, TAG, 3 * 1024, this, 5, NULL, 0);
}




// -----------------------------------

static void task_process_handler(void* arg)
{
    while (true)
    {
        camera_fb_t* frame = esp_camera_fb_get();
        if (frame)
            xQueueSend(xQueueFrameO, &frame, portMAX_DELAY);
    }
}

void register_camera(const pixformat_t pixel_fromat,
    const framesize_t frame_size,
    const uint8_t fb_count,
    const QueueHandle_t frame_o)
{
    ESP_LOGI(TAG, "Camera module is %s", CAMERA_MODULE_NAME);
#if 1
#if CONFIG_CAMERA_MODULE_ESP_EYE || CONFIG_CAMERA_MODULE_ESP32_CAM_BOARD
    /* IO13, IO14 is designed for JTAG by default,
     * to use it as generalized input,
     * firstly declare it as pullup input */
    gpio_config_t conf;
    conf.mode = GPIO_MODE_INPUT;
    conf.pull_up_en = GPIO_PULLUP_ENABLE;
    conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    conf.intr_type = GPIO_INTR_DISABLE;
    conf.pin_bit_mask = 1LL << 13;
    gpio_config(&conf);
    conf.pin_bit_mask = 1LL << 14;
    gpio_config(&conf);
#endif
    
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = CAMERA_PIN_D0;
    config.pin_d1 = CAMERA_PIN_D1;
    config.pin_d2 = CAMERA_PIN_D2;
    config.pin_d3 = CAMERA_PIN_D3;
    config.pin_d4 = CAMERA_PIN_D4;
    config.pin_d5 = CAMERA_PIN_D5;
    config.pin_d6 = CAMERA_PIN_D6;
    config.pin_d7 = CAMERA_PIN_D7;
    config.pin_xclk = CAMERA_PIN_XCLK;
    config.pin_pclk = CAMERA_PIN_PCLK;
    config.pin_vsync = CAMERA_PIN_VSYNC;
    config.pin_href = CAMERA_PIN_HREF;
    config.pin_sscb_sda = CAMERA_PIN_SIOD;
    config.pin_sscb_scl = CAMERA_PIN_SIOC;
    config.pin_pwdn = CAMERA_PIN_PWDN;
    config.pin_reset = CAMERA_PIN_RESET;
    config.xclk_freq_hz = XCLK_FREQ_HZ;
    config.pixel_format = pixel_fromat;
    config.frame_size = frame_size;
    config.jpeg_quality = 0;
    config.fb_count = fb_count;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Camera init failed with error 0x%x", err);
        return;
    }
#endif

    sensor_t* s = esp_camera_sensor_get();

    if (s->id.PID == OV3660_PID || s->id.PID == OV2640_PID) {
        s->set_vflip(s, 1); //flip it back    
    }
    else if (s->id.PID == GC0308_PID) {
        s->set_hmirror(s, 0);
    }
    else if (s->id.PID == GC032A_PID) {
        s->set_vflip(s, 1);
    }

    //initial sensors are flipped vertically and colors are a bit saturated
    if (s->id.PID == OV3660_PID)
    {
        s->set_brightness(s, 1);  //up the brightness just a bit
        s->set_saturation(s, -2); //lower the saturation
    }

    xQueueFrameO = frame_o;
    xTaskCreatePinnedToCore(task_process_handler, TAG, 3 * 1024, NULL, 5, &xTaskProcess, 1);
}

void unregister_camera(void)
{
    if (xTaskProcess != NULL)
    {
        vTaskDelete(xTaskProcess);
        xTaskProcess = NULL;
    }

    esp_camera_deinit();
}