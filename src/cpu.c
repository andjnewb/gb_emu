#include "cpu.h"
#include "disassemble.h"

void init_cpu(cpu_state * state, struct romBytes * bytes)
{
    state->regs.a = 0;
    state->regs.b = 0x0;
    state->regs.c = 0x0;
    state->regs.d = 0x0;
    state->regs.e = 0x0;
    
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
void set_flag(int toSet, char flag[2], cpu_state * state)
{
   if(flag == "z")
   {
        state->regs.z_flag = toSet;
   }

   else if(flag == "n")
    {
        state->regs.n_flag = toSet;
    }

    else if(flag == "h")
    {
        state->regs.h_flag = toSet;
    }

    else if(flag == "c")
    {
        state->regs.c_flag == toSet;
    }
}
void call_func(cpu_state * state, instruction ins)
{
    switch(ins.op_code)
    {

        case 0x5:
        dec_b(state);


        case 0x32:
        ld_hl_decrement_a(state);
        state->regs.pc += ins.length;

        break;

        case 0x6:
        ld_b_d8(state);
        state->regs.pc += ins.length;
        break;

        case 0xc3:
        jp_nocond(state);
        break;

        case 0xe:
        ld_c_d8(state);
        state->regs.pc += ins.length;
        break;


        case 0x21:
        ld_hl_d16(state);
        state->regs.pc += ins.length;

        break;

        case 0xaf:
        xor_a(state);
        state->regs.pc += ins.length;
        break;

        case 0x0:
        state->regs.pc += ins.length;
        break;

        default:
        printf("Non implemented instruction at 0x%x: 0x%x %s\n", state->regs.pc , ins.op_code, ins.mnmemonic);
        state->halt = 1;//
        break;
    }
}

void jp_nocond(cpu_state * state)
{
    state->regs.pc = state->fetched_data;
}

void xor_a(cpu_state * state)
{
    //This is effectively a NOP

    uint8_t result = state->regs.a ^ state->regs.a;

    if(result == 1)
    {
        set_flag(1, "z", state);
    }
    else
    {
        set_flag(0, "z", state);
    }

    set_flag(0,"n",state);
    set_flag(0,"h",state);
    set_flag(0,"c",state);
}

void ld_hl_d16(cpu_state * state)
{
    state->regs.hl = state->fetched_data;
}

void ld_c_d8(cpu_state * state)
{
    state->regs.c = state->fetched_data;
}

void ld_b_d8(cpu_state * state)
{
    state->regs.b = state->fetched_data;
}

void ld_hl_decrement_a(cpu_state * state)
{

    state->address_space[state->regs.hl] = state->regs.a;
    state->regs.hl--;
}

void dec_b(cpu_state * state)
{
    state->regs.b--;
}