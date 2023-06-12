#include "util.h"

uint8_t setBit(uint8_t num, uint8_t bit)
{   
    return (num | (1 << (bit)));
}

uint8_t clearBit(uint8_t num, uint8_t bit)
{
    return (num & (~(1 << (bit))));
}

uint8_t checkBit(uint8_t num, uint8_t bit)
{
    if(num & (1 << bit))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
