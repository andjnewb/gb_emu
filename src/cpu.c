#include "cpu.h"
#include "disassemble.h"

void init_cpu(cpu_state * state, struct romBytes * bytes)
{

    //These initial register values are based on the DMG(original) gameboy.
    state->regs.af = 0x01b0;
    state->regs.bc = 0x0013;
    state->regs.de = 0x00d8;
    state->regs.hl = 0x014d;
    state->regs.pc = 0x100;
    state->regs.sp = 0xFFFE;

    state->fetched_data = 0x0;
    state->curr_inst.op_code = bytes->bytes[state->regs.pc];
    state->halt = 0;
    state->memory_dest = 0x0;
    state->step = 1;

    state->interrupt_master_enable = 0;
}

int step_cpu()
{
    
}

void handle_interrupt(cpu_state * state)
{
    if(state->interrupt_master_enable == 1)
    {

    }
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
void call_func(cpu_state * state, instruction ins, struct romBytes * bytes)
{
    switch(ins.op_code)
    {
        case 0xfe:
        cp_d8(state);
        state->regs.pc += ins.length;
        break;

        case 0xf0:
        ldh_a_a8(state);
        state->regs.pc += ins.length;
        break;

        case 0xe0:
        ldh_a8_a(state);
        state->regs.pc += ins.length;
        break;

        case 0xf3:
        di(state);
        state->regs.pc += ins.length;
        break;

        case 0x3e:
        ld_a_d8(state);
        state->regs.pc += ins.length;
        break;

        case 0xd:
        dec_c(state);
        state->regs.pc += ins.length;
        break;

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
        jr_nz_r8(state, bytes);
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

void ldh_a_a8 (cpu_state * state)
{

    //I think this is working correctly, but I believe the location it's reading from is a register so currently it's empty. Will further test later.

    //Set high byte to 0xFF and low byte to desired address.
    uint16_t addr = ((0xFF << 8) | (state->fetched_data & 0x00FF));

    

    state->regs.a = state->address_space[addr];


}

void ldh_a8_a(cpu_state * state)
{

    //Set high byte to 0xFF and low byte to desired address.
    uint16_t addr = ((0xFF << 8) | (state->fetched_data & 0x00FF));

    //printf("Loading to address: %x\n", addr);

    state->address_space[addr] = state->regs.a;
}


void di(cpu_state * state)
{
    state->interrupt_master_enable = 0;
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
    int result = state->regs.d + 1;
    state->regs.d = (unsigned char)result;
    //printf("Result: %uc", state->regs.d);


    //THIS IS BAD
    if(result > 255)
    {
        state->regs.d = 0;
    }

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

void cp_d8(cpu_state * state)
{

    int result = state->regs.a - state->fetched_data;

     if(result < 0)
    {
        //printf("RESULT WAS ZERO");      
        set_flag(0, "z", state);
        
    }
    else if(result == 0)
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

    if(result & (1<<7))
    {
        set_flag(1, "c", state);
    }
    else
    {
        set_flag(0, "c", state);
    }

}

void dec_c(cpu_state * state)
{
    
    int result = state->regs.c - 1;
    

    if(result < 0)
    {
        //printf("RESULT WAS ZERO");      
        set_flag(0, "z", state);
        state->regs.c = 0xff;
    }
    else if(result == 0)
    {
        set_flag(1, "z", state);
        state->regs.c = 0;
    }

    else
    {
        set_flag(0, "z", state);
        state->regs.c -= 1;
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

    int result = state->regs.d - 1;
    

    if(result < 0)
    {
        //printf("RESULT WAS ZERO");      
        set_flag(0, "z", state);
        state->regs.d = 0xff;
    }
    else if(result == 0)
    {
        set_flag(1, "z", state);
        state->regs.d = 0;
    }

    else
    {
        set_flag(0, "z", state);
        state->regs.d -= 1;
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
    state->regs.a = result;

    if(result == 0)
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

void ld_a_d8(cpu_state *state)
{
    state->regs.a = state->fetched_data;
}

void dec_b(cpu_state * state)
{
    //state->regs.b--;

    int result = state->regs.b - 1;
    

    if(result < 0)
    {
        //printf("RESULT WAS ZERO");      
        set_flag(0, "z", state);
        state->regs.b = 0xff;
    }
    else if(result == 0)
    {
        set_flag(1, "z", state);
        state->regs.b = 0;
    }

    else
    {
        set_flag(0, "z", state);
        state->regs.b -= 1;
    }

    set_flag(1, "n", state);

    if(state->regs.b & (1<<3))
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

    int result = state->regs.h - 1;
    

    if(result < 0)
    {
        //printf("RESULT WAS ZERO");      
        set_flag(0, "z", state);
        state->regs.h = 0xff;
    }
    else if(result == 0)
    {
        set_flag(1, "z", state);
        state->regs.h = 0;
    }

    else
    {
        set_flag(0, "z", state);
        state->regs.h -= 1;
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

    int result = state->regs.e - 1;
    

    if(result < 0)
    {
        //printf("RESULT WAS ZERO");      
        set_flag(0, "z", state);
        state->regs.e = 0xff;
    }
    else if(result == 0)
    {
        set_flag(1, "z", state);
        state->regs.e = 0;
    }

    else
    {
        set_flag(0, "z", state);
        state->regs.e -= 1;
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

void jr_nz_r8(cpu_state * state, struct romBytes * bytes)
{

    int toJump = state->fetched_data_8_signed;

    printf("tojump: %d", -(~toJump + 1) + 2);
    
    if(state->regs.z_flag == 0)
    {
        state->regs.pc += -(~toJump + 1) + 2;//
    }
    else
    {
        state->regs.pc += 2;
    }

}