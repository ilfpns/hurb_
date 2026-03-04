#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "dht11.h"
#include "file.h"
#include "gas.h"

static const char *TAG = "Main";

all_data all;

void app_main(void) {
    dht_data dht;
    gas_data gas;
    static QueueHandle_t dhtQueue = NULL;
    static QueueHandle_t gasQueue = NULL;

    dhtQueue = xQueueCreate(10, sizeof(dht_data));
    gasQueue = xQueueCreate(10, sizeof(gas_data));

    xTaskCreate(dht11_read, "dht_task", 4096, &dhtQueue, 5, NULL);
    xTaskCreate(read_gas_sensor, "gas_task", 4096, &gasQueue, 5, NULL);

    while(1) {
        if (xQueueReceive(dhtQueue, &dht, 0) == pdPASS) {
            ESP_LOGI(TAG, "H : %d / T : %d", dht.H, dht.T);
            all.H = dht.H; all.T = dht.T;
        }

        if (xQueueReceive(gasQueue, &gas, 0) == pdPASS) {
            ESP_LOGI(TAG, "ADC: %d, Voltage: %.2fV, Rs: %.2f", gas.adc, gas.voltage, gas.rs);
            all.rs = gas.rs;
        }

        file_w(all);
    }
}
