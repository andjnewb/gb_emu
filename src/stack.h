#ifndef STACK_H_
#define STACK_H_
#include <inttypes.h>
#include "cpu.h"

void stack_push(uint8_t data , cpu_state * state);
void stack_push16(uint16_t data, cpu_state * state);

uint8_t stack_pop(cpu_state * state);
uint16_t stack_pop_16(cpu_state * state);



#endif