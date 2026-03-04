#include "dht11.h"

static const char *TAG = "dht11";

void dht11_read(void* pvParameters) {
    QueueHandle_t Queue = (QueueHandle_t)pvParameters;
    dht_data data;
    uint8_t d[5] = {0};

    ESP_LOGI(TAG, "dht 초기화 성공");
    while (1) {
        gpio_set_direction(DHT11_PIN, GPIO_MODE_OUTPUT);
        gpio_set_level(DHT11_PIN, 0);
        ets_delay_us(20000);
        gpio_set_level(DHT11_PIN, 1);
        ets_delay_us(30);
        gpio_set_direction(DHT11_PIN, GPIO_MODE_INPUT);

        while (gpio_get_level(DHT11_PIN));
        while (!gpio_get_level(DHT11_PIN));
        while (gpio_get_level(DHT11_PIN));

        for (int i = 0; i < 40; i++) {
            while (!gpio_get_level(DHT11_PIN));
            int count = 0;
            while (gpio_get_level(DHT11_PIN)) count++;
            if (count > 20)
                d[i / 8] |= (1 << (7 - (i % 8)));
        }

        if (d[4] == (uint8_t)(d[0] + d[1] + d[2] + d[3])) {
            data.H = d[0];
            data.T = d[2];
            xQueueSend(Queue, &data, 0);
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}