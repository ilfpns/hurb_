#pragma once

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "freertos/queue.h"
#include "rom/ets_sys.h"

#define DHT11_PIN 4

typedef struct QueueMold {
    int H;
    int T;
} QueueMold;


void dht11_read(void* pvParameters);
