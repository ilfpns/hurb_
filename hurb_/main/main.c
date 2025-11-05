#include <stdio.h>

#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "dht.h"

#include "esp_log.h"

#define DHT_GPIO 4 
#define GREEN_LED_GPIO 16
#define RED_LED_GPIO 17

static const char* TAG = "DHT";

static TaskHandle_t dht_task = NULL;
volatile int32_t led_status = 0;

volatile bool run_sensor = true;
volatile float h, t;

void dht_run(void *pvParameter);
void test(void *pvParameter);


void dht_run(void *pvParameter) {           
    UBaseType_t unused = uxTaskGetStackHighWaterMark(NULL);
    ESP_LOGI(TAG, "남은 스택: %u 워드", unused);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(500));
        if ((dht_read_float_data(DHT_TYPE_DHT11, DHT_GPIO, &h, &t) == ESP_OK) && run_sensor) {
            ESP_LOGI(TAG, "습도 : %f, 온도 : %f", h, t);
            if (h > 50.0f) {
                led_status = 1;
                ESP_LOGI(TAG, "습도 50%% 넘음"); 
            }
            else {
                led_status = 0;
            }
        }
        else {
            ESP_LOGE(TAG, "DHT 에러");
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}  

void test(void *pvParameter) { 
    ESP_LOGI(TAG, "TEST 시작");
    vTaskDelay(pdMS_TO_TICKS(1000));

    ESP_LOGI(TAG, "센서 정지");
    run_sensor = false;
    vTaskDelay(pdMS_TO_TICKS(1000));

    ESP_LOGI(TAG, "센서 가동");
    run_sensor = true;

    vTaskDelete(NULL);
} 

void onLed(int32_t status) {
    vTaskDelay(pdMS_TO_TICKS(500));
    gpio_set_level(status, 1);

    vTaskDelay(pdMS_TO_TICKS(500));
    gpio_set_level(status, 0); 
}

void LED(void* vpParameter) {
    gpio_reset_pin(GREEN_LED_GPIO);
    gpio_reset_pin(RED_LED_GPIO);

    gpio_set_direction(GREEN_LED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(RED_LED_GPIO, GPIO_MODE_OUTPUT);

    while(1) {
        if (led_status == 0) {
            onLed(GREEN_LED_GPIO);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        else {
            onLed(RED_LED_GPIO);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}

void app_main(void)
{
    xTaskCreate(dht_run, "dht_task", 4096, NULL, 5, &dht_task);
    xTaskCreate(test, "Test func", 4096, NULL, 4, NULL);
    xTaskCreate(LED, "LED", 4096, NULL, 6, NULL);
}