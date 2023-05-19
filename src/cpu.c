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
        case 0x15:
        dec_d(state);
        state->regs.pc += ins.length;
        break;

        case 0x7b:
        ld_a_e(state);
        state->regs.pc += ins.length;
        break;

        case 0x14:
        inc_d(state);
        state->regs.pc += ins.length;
        break;

        case 0xb0:
        or_b(state);
        state->regs.pc += ins.length;
        break;

        case 0x25:
        dec_h(state);
        state->regs.pc += ins.length;

        case 0x1f:
        rra(state);
        state->regs.pc += ins.length;
        break;

        case 0x16:
        ld_d_d8(state);
        state->regs.pc += ins.length;
        break;

        case 0x1d:
        dec_e(state);
        state->regs.pc += ins.length;
        break;

        case 0x20:
        jr_nz_r8(state);
        break;

        case 0x5:
        dec_b(state);
        state->regs.pc += ins.length;
        break;

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

void or_b(cpu_state * state)
{
    uint8_t result = state->regs.a | state->regs.b;

    state->regs.a = result;

    if(result == 0)
    {
        set_flag(1, "z", state);
    }
    else
    {
        set_flag(0, "z", state);
    }

    state->regs.n_flag = 0;
    state->regs.h_flag = 0;
    state->regs.c_flag = 0;
}

void inc_d(cpu_state *state)
{
    unsigned char result = state->regs.d + 1;
    state->regs.d = result;
    //printf("Result: %uc", state->regs.d);

    if(result == 0)
    {
        set_flag(1, "z", state);
    }
    else
    {
        set_flag(0, "z", state);
    }

    set_flag(1, "n", state);

    if(result & (1<<3))
    {
        set_flag(1, "h", state);
    }
    else
    {
        set_flag(0, "h", state);
    }

}

void dec_d(cpu_state *state)
{

    unsigned char result= state->regs.d - 1;
    state->regs.d = result;

    if(result == 0)
    {
        set_flag(1, "z", state);
    }
    else
    {
        set_flag(0, "z", state);
    }

    set_flag(1, "n", state);

    if(result & (1<<3))
    {
        set_flag(1, "h", state);
    }
    else
    {
        set_flag(0, "h", state);
    }

}

void rra(cpu_state * state)
{
    state->regs.c_flag = (state->regs.a >> 0) & 1;

    state->regs.a = (state->regs.a >> 1)|(state -> regs.a << (8 - 1));

    state->regs.z_flag = 0;
    state->regs.n_flag = 0;
    state->regs.h_flag = 0;

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

void ld_d_d8(cpu_state * state)
{
    state->regs.d = state->fetched_data;
}


void ld_hl_decrement_a(cpu_state * state)
{

    state->address_space[state->regs.hl] = state->regs.a;
    state->regs.hl--;
}

void ld_a_e(cpu_state *state)
{
    state->regs.a = state->regs.e;
}

void dec_b(cpu_state * state)
{
    //state->regs.b--;


    unsigned char result= state->regs.b - 1;
    state->regs.b = result;

    if(result == 0)
    {
        set_flag(1, "z", state);
    }
    else
    {
        set_flag(0, "z", state);
    }

    set_flag(1, "n", state);

    if(result & (1<<3))
    {
        set_flag(1, "h", state);
    }
    else
    {
        set_flag(0, "h", state);
    }


}

void dec_h(cpu_state * state)
{
    //state->regs.b--;


    unsigned char result = state->regs.h - 1;
    state->regs.h = result;

    if(result == 0)
    {
        set_flag(1, "z", state);
    }
    else
    {
        set_flag(0, "z", state);
    }

    set_flag(1, "n", state);

    if(result & (1<<3))
    {
        set_flag(1, "h", state);
    }
    else
    {
        set_flag(0, "h", state);
    }


}

void dec_e(cpu_state * state)
{
    //state->regs.b--;


    unsigned char result = state->regs.e - 1;
    state->regs.e = result;

    if(result == 0)
    {
        set_flag(1, "z", state);
    }
    else
    {
        set_flag(0, "z", state);
    }

    set_flag(1, "n", state);

    if(result & (1<<3))
    {
        set_flag(1, "h", state);
    }
    else
    {
        set_flag(0, "h", state);
    }


}

void jr_nz_r8(cpu_state * state)
{
///FIX ME
    
    if(state->regs.n_flag == 1 && state->regs.h_flag == 1)
    {
        state->regs.pc += state->fetched_data;
    }
}