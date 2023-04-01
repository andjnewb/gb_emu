#include "cpu.h"
#include "disassemble.h"

void init_cpu(cpu_state * state, struct romBytes * bytes)
{
    state->regs.a = 0;
    state->regs.b = 0x0;
    state->regs.c = 0x0;
    state->regs.d = 0x0;
    state->regs.e = 0x0;
    state->regs.f = 0x0;
    state->regs.h = 0x0;
    state->regs.l = 0x0;
    state->regs.pc = 0x100;
    state->regs.sp = 0x0;

    state->fetched_data = 0x0;
    state->curr_inst.op_code = bytes->bytes[state->regs.pc];
    state->halt = 0;
    state->memory_dest = 0x0;
    state->step = 1;
}

int step_cpu()
{
    
}

int decode_instruction(cpu_state * state, struct romBytes *bytes)
{

    

    return 0;
}
