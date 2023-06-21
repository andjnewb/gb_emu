#include "stack.h"
#include "cpu.h"

void stack_push(uint8_t data, cpu_state * state)
{
    state->regs.sp--;
    state->address_space[state->regs.sp] = data;//
}
void stack_push16(uint16_t data, cpu_state * state)
{
    stack_push((data >> 8) & 0xFF, state);
    stack_push(data & 0xFF, state);
}

uint8_t stack_pop(cpu_state * state)
{
    return state->address_space[state->regs.sp++];
}

uint16_t stack_pop_16(cpu_state * state)
{
    uint16_t low = stack_pop(state);
    uint16_t hi = stack_pop(state);

    return (hi << 8) | (low & 0x00ff);
}