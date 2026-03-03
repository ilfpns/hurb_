#include "gas.h"

static const char *TAG = "GAS_SENSOR";

void read_gas_sensor(void* pvParameter) {
    adc_oneshot_unit_handle_t adc1_handle;
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_DEFAULT,
        .atten = ADC_ATTEN_DB_12, 
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_6, &config));

    int adc_raw;
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, ADC_CHANNEL_6, &adc_raw));

    float voltage = (float)adc_raw * 3.3 / 4095.0;
    float rs_gas = ((5.0 / voltage) - 1.0) * 1.0;

    // 원시 값, 센서 출력 전압, 가스 센서 값
    ESP_LOGI(TAG, "ADC: %d, Voltage: %.2fV, Rs: %.2f", adc_raw, voltage, rs_gas);
}