#ifndef CPU_H
#define CPU_H
#include <inttypes.h>
#include "instructions.h"
#include <disassemble.h>
typedef struct 
{
    //8 bit registers. Can also be addressed in 16 bit pairs.
    uint8_t a;
    uint8_t f;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;

    //16 bit registers. 
    uint16_t pc;
    uint16_t sp;
}registers;

typedef struct 
{
    registers regs;//Current state of CPU registers.

    uint16_t fetched_data;//Data fetched by current instruction.
    uint16_t memory_dest;//Instructions may or may not interact with this. Only trust it's value if the current instruction interacts with it.
    instruction curr_inst;

    int halt;//If this is true, no instructions will execute.
    int step;//If we are in stepping mode, only execute one instruction and wait.

}cpu_state;

void init_cpu();
int step_cpu();
int decode_instruction(cpu_state * state, struct romBytes * bytes);
#endif