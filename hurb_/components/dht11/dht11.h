#pragma once

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "rom/ets_sys.h"

#define DHT_GPIO 4 
#define GREEN_LED_GPIO 16
#define RED_LED_GPIO 17
#define btn_GPIO 2

int dht11_read(int *h, int *t);