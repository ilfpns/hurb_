#include "dht11.h"

#define DHT11_PIN 4

int dht11_read(int *h, int *t) {
    uint8_t d[5] = {0};

    // start signal
    gpio_set_direction(DHT11_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(DHT11_PIN, 0);
    ets_delay_us(20000);
    gpio_set_level(DHT11_PIN, 1);
    ets_delay_us(30);
    gpio_set_direction(DHT11_PIN, GPIO_MODE_INPUT);

    int timeout = 0;
    while (gpio_get_level(DHT11_PIN) == 1) if (++timeout > 100) return 0;

    for (int i = 0; i < 40; i++) {
        while (gpio_get_level(DHT11_PIN) == 0);
        int count = 0;
        while (gpio_get_level(DHT11_PIN) == 1) count++;
        if (count > 20)
            d[i / 8] |= (1 << (7 - (i % 8)));
    }

    if (d[4] != ((d[0] + d[1] + d[2] + d[3]) & 0xFF))
        return 0;

    *h = d[0];
    *t = d[2];
    return 1;
}