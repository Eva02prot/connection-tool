#pragma once
#include <stdint.h>
#include <stdlib.h>

//generate random num from 100000 to 999999
inline int32_t GenerateRanNum() {
    return ((float)(rand() % RAND_MAX) / (float)RAND_MAX) * 899999 + 100000;
}
