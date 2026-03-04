#include "gas.h"

static const char *TAG = "GAS_SENSOR"; 

void read_gas_sensor(void* pvParameter) {
    QueueHandle_t queue = (QueueHandle_t)pvParameter;
    gas_data data;
    adc_oneshot_unit_handle_t adc1_handle;
    // adc 1사용
    // => WiFi와 함께 사용 가능
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT, // 기본 해상도 (정밀도)
        .atten = ADC_ATTEN_DB_12,         // 감쇠       (입력 전압 감쇄)
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_6, &config));

    while(1) {
        int adc_raw;
        
        ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, ADC_CHANNEL_6, &adc_raw));

        // 12bit 디지털 값(0~4095)을 실제 전압(0~3.3V)으로 환산
        float voltage = (float)adc_raw * 3.3 / 4095.0; 
        
        // 전압 분배 법칙을 이용해 센서 내부 저항값(Rs) 계산
        float rs = 10.0 * (3.3 - voltage) / voltage;

        // 원시 값, 전압, 가스 정보
        data.adc = adc_raw; data.voltage = voltage; data.rs = rs;
        if((xQueueSend(queue, &data, 0)) != pdPASS) {
            ESP_LOGE(TAG, "Queue send 실패");
        }
        vTaskDelay(pdMS_TO_TICKS(100));


    }
}