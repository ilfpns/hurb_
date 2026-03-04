#pragma once 

#include "esp_adc/adc_oneshot.h"
#include "esp_log.h" 
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

typedef struct gas_data {
    int adc;
    float voltage;
    float rs;
} gas_data;

void read_gas_sensor(void* pvParameter);