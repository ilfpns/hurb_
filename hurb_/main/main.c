#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "dht11.h"
static TaskHandle_t dht_task = NULL;

void app_main(void) {
    // xTaskCreate(dht_run, "dht_task", 4096, NULL, 5, &dht_task);
}