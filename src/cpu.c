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
void set_flag(int num, int position, cpu_state * state)
{
    int mask = 1 << position;
    state->regs.f = num | mask;

}
void call_func(cpu_state * state, instruction ins)
{
    switch(ins.op_code)
    {
        case 0xc3:
        jp_nocond(state);

        case 0x0:
        break;

        default:
        printf("Non implemented instruction at %x: 0x%hhx %s\n", state->regs.pc , ins.op_code, ins.mnmemonic);
        state->halt = 1;//
        break;
    }
}

void jp_nocond(cpu_state * state)
{
    state->regs.pc = state->fetched_data;
}
