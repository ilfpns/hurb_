#pragma once

#include <stdio.h>
#include "dht11.h"  

typedef struct all_data {
    int H;
    int T;
    float rs;
} all_data;

void file_w(all_data data);