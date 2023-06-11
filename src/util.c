#include "util.h"

uint8_t setBit(uint8_t num, uint8_t bit)
{   
    return (num | (1 << (bit - 1)));
}

uint8_t clearBit(uint8_t num, uint8_t bit)
{
    return (num & (~(1 << (bit - 1))));
}

uint8_t checkBit(uint8_t num, uint8_t bit)
{
    if((((num) >> bit) & 1) == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
