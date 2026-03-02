#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "dht11.h"
#include "file.h"

static QueueHandle_t dhtQueue = NULL;

static const char *TAG = "Main";

void app_main(void) {
    QueueMold data;
    if ((xQueueCreate(10, sizeof(QueueMold))) != pdPASS) {
        ESP_LOGE(TAG, "DHT11 queue 생성 실패");
    }
    xTaskCreate(dht11_read, "dht_task", 4096, &dhtQueue, 5, NULL);

    if (xQueueReceive(dhtQueue, &data, 0) == pdPASS) {
        ESP_LOGI(TAG, "H : %d / T : %d", data.H, data.T);
        file_w(data);
    }
}