#include "cpu.h"
#include "disassemble.h"
#include "stack.h"
#include "interrupt.h"
//CPU FUNCTIONS. Should find a better place for these. Macros are defined in instructions.h. These are mostly used for functions that would pointless to have seperate definition for each version, for example LD A,E and LD E,A.
//Considering that there are well over forty of these variations for the 8 bit registers, you can see why it makes sense to do it this way.

//Arithmetic/Logic
_DEC_REG(b)
_DEC_REG(d)
_DEC_REG(h)
_DEC_REG(c)
_DEC_REG(e)
_DEC_REG(l)
_DEC_REG(a)
_DEC_REG(bc)
_DEC_REG(de)
_DEC_REG(hl)
_DEC_REG(sp)

_OR_REG(a)
_OR_REG(b)
_OR_REG(c)
_OR_REG(d)
_OR_REG(e)
_OR_REG(h)
_OR_REG(l)


//Load/Store
_LD_REG_8_8(a,e)
_LD_REG_8_8(b,b)
_LD_REG_8_8(b,c)
_LD_REG_8_8(b,d)
_LD_REG_8_8(b,e)
_LD_REG_8_8(b,h)
_LD_REG_8_8(b,l)
_LD_REG_8_8(b,a)
_LD_REG_8_8(c,b)
_LD_REG_8_8(c,c)
_LD_REG_8_8(c,d)
_LD_REG_8_8(c,e)
_LD_REG_8_8(c,h)
_LD_REG_8_8(c,l)
_LD_REG_8_8(c,a)
_LD_REG_8_8(d,b)
_LD_REG_8_8(d,c)
_LD_REG_8_8(d,d)
_LD_REG_8_8(d,e)
_LD_REG_8_8(d,h)
_LD_REG_8_8(d,l)
_LD_REG_8_8(d,a)
_LD_REG_8_8(e,b)
_LD_REG_8_8(e,c)
_LD_REG_8_8(e,d)
_LD_REG_8_8(e,e)
_LD_REG_8_8(e,h)
_LD_REG_8_8(e,l)
_LD_REG_8_8(e,a)
_LD_REG_8_8(h,b)
_LD_REG_8_8(h,c)
_LD_REG_8_8(h,d)
_LD_REG_8_8(h,e)
_LD_REG_8_8(h,h)
_LD_REG_8_8(h,l)
_LD_REG_8_8(h,a)
_LD_REG_8_8(l,b)
_LD_REG_8_8(l,c)
_LD_REG_8_8(l,d)
_LD_REG_8_8(l,e)
_LD_REG_8_8(l,h)
_LD_REG_8_8(l,l)
_LD_REG_8_8(l,a)
_LD_REG_8_8(a,b)
_LD_REG_8_8(a,c)
_LD_REG_8_8(a,d)
_LD_REG_8_8(a,h)
_LD_REG_8_8(a,l)
_LD_REG_8_8(a,a)


_LD_REG_d8(a)
_LD_REG_d8(b)
_LD_REG_d8(c)
_LD_REG_d8(d)
_LD_REG_d8(e)
_LD_REG_d8(h)
_LD_REG_d8(l)

_LD_REG16_d16(bc)
_LD_REG16_d16(de)
_LD_REG16_d16(hl)
_LD_REG16_d16(sp)

void init_cpu(cpu_state * state, struct romBytes * bytes)
{
//
    //These initial register values are based on the DMG(original) gameboy.
    state->regs.af = 0x01b0;
    state->regs.bc = 0x0013;
    state->regs.de = 0x00d8;
    state->regs.hl = 0x014d;
    state->regs.pc = 0x017e;
    state->regs.sp = 0xFFFE;

    state->fetched_data = 0x0;
    state->curr_inst.op_code = bytes->bytes[state->regs.pc];
    state->halt = 0;
    state->memory_dest = 0x0;
    state->step = 1;

    state->interrupt_master_enable = 1;
}

int step_cpu()
{
    
}

void handle_interrupt(cpu_state * state)
{

    //If the interrupt has been requested and is enabled, handle it.
    if(checkBit(state->address_space[INTERRUPT_FLAG_REGISTER], VBLANK_F))
    {
        if(checkBit(state->address_space[INTERRUPT_ENABLE_REGISTER], VBLANK_E))
        {
            printf("VBLANK INTERRUPT...\n");
            state->address_space[INTERRUPT_FLAG_REGISTER] = setBit(state->address_space[INTERRUPT_FLAG_REGISTER], VBLANK_F);

            state->fetched_data = VBLANK_JUMP_VECTOR;//My call doesn't take in a parameter, it just uses the cpu state's fetched data. So this lil hack allows us to just use it for now.
            call_a16(state);

            state->interrupt_master_enable = 0;//Disable all interrupt handling until ei or reti renables it.

        }
    }
}


int get_instruction_cycles(instruction ins, int actionTaken)
{
    // int taken;
    // int noTaken;
    // char * token;

    // token = strtok(ins.cycles, "/");
    // taken = atoi(token);

    // token = strtok(NULL, "/");
    // noTaken = atoi(token);

    // // printf("Taken: %d Not Taken: %d", taken, noTaken);

    // if( actionTaken == 1)
    // {
    //     return taken;
    // }
    // else
    // {
    //     return noTaken;
    // }
    // free(token);
    return 0;
}

void request_interrupt(cpu_state *state, int interrupt)
{
    switch(interrupt)
    {
        case VBLANK_F:
        state->address_space[INTERRUPT_FLAG_REGISTER] = setBit(state->address_space[INTERRUPT_FLAG_REGISTER], VBLANK_F);
        break;

        case LCD_STAT_F:
        state->address_space[INTERRUPT_FLAG_REGISTER] = setBit(state->address_space[INTERRUPT_FLAG_REGISTER], LCD_STAT_F);
        break;

        case TIMER_F:
        state->address_space[INTERRUPT_FLAG_REGISTER] = setBit(state->address_space[INTERRUPT_FLAG_REGISTER], TIMER_F);
        break;

        case SERIAL_F:
        state->address_space[INTERRUPT_FLAG_REGISTER] = setBit(state->address_space[INTERRUPT_FLAG_REGISTER], SERIAL_F);
        break;

        case JOYPAD_F:
        state->address_space[INTERRUPT_FLAG_REGISTER] = setBit(state->address_space[INTERRUPT_FLAG_REGISTER], JOYPAD_F);
        break;
        
        default:break;
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

        case 0xc9:
        ret(state);
        break;

        case 0xb1:
        _OR_c(state);
        state->regs.pc += ins.length;
        break;

        case 0x78:
        _LD_a_b(state);
        state->regs.pc += ins.length;
        break;

        case 0xb:
        _DEC_bc(state);
        state->regs.pc += ins.length;
        break;

        case 0x1:
        _LD_bc_d16(state);
        state->regs.pc += ins.length;
        break;

        case 0xcd:
        call_a16(state);
        break;

        case 0xe2:
        ldh_c_a(state);
        state->regs.pc += ins.length;
        break;

        case 0x2a:
        ld_hl_increment_a(state);
        state->regs.pc += ins.length;
        break;

        case 0x31:
        _LD_sp_d16(state);
        state->regs.pc += ins.length;
        break;

        case 0xea:
        ld_a16_a(state);
        state->regs.pc += ins.length;
        break;

        case 0x36:
        ld_hl_d8(state);
        state->regs.pc += ins.length;
        break;

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
        _LD_a_d8(state);
        state->regs.pc += ins.length;
        break;

        case 0xd:
        _DEC_c(state);
        state->regs.pc += ins.length;
        break;

        case 0x15:
        _DEC_d(state);
        state->regs.pc += ins.length;
        break;

        case 0x7b:
        _LD_a_e(state);
        state->regs.pc += ins.length;
        break;

        case 0x14:
        inc_d(state);
        state->regs.pc += ins.length;
        break;

        case 0xb0:
        _OR_b(state);
        state->regs.pc += ins.length;
        break;

        case 0x25:
        _DEC_h(state);
        state->regs.pc += ins.length;

        case 0x1f:
        rra(state);
        state->regs.pc += ins.length;
        break;

        case 0x16:
        _LD_d_d8(state);
        state->regs.pc += ins.length;
        break;

        case 0x1d:
        _DEC_e(state);
        state->regs.pc += ins.length;
        break;

        case 0x20:
        jr_nz_r8(state, bytes);
        break;

        case 0x5:
        _DEC_b(state);
        state->regs.pc += ins.length;
        break;

        case 0x32:
        ld_hl_decrement_a(state);
        state->regs.pc += ins.length;

        break;

        case 0x6:
        _LD_b_d8(state);
        state->regs.pc += ins.length;
        break;

        case 0xc3:
        jp_nocond(state);
        break;

        case 0xe:
        _LD_c_d8(state);
        state->regs.pc += ins.length;
        break;


        case 0x21:
        _LD_hl_d16(state);
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

void ret(cpu_state * state)
{
    state->regs.pc = stack_pop_16(state);
}

void call_a16(cpu_state * state)
{
    stack_push16(state->regs.pc, state);
    state->regs.pc = state->fetched_data;
}

void ld_hl_increment_a(cpu_state * state)
{
    state->address_space[state->regs.hl] = state->regs.a;
    state->regs.hl++;
    state->cycles += get_instruction_cycles(state->curr_inst, 1);
}

void ld_a16_a(cpu_state * state)
{
    state->address_space[state->fetched_data] = state->regs.a;
    state->cycles += get_instruction_cycles(state->curr_inst, 1);
}

void ld_hl_d8(cpu_state * state)
{
    state->regs.hl = state->fetched_data;
    state->cycles += get_instruction_cycles(state->curr_inst, 1);
}

void ldh_a_a8 (cpu_state * state)
{

    //I think this is working correctly, but I believe the location it's reading from is a register so currently it's empty. Will further test later.

    //Set high byte to 0xFF and low byte to desired address.
    uint16_t addr = ((0xFF << 8) | (state->fetched_data & 0x00FF));

    

    state->regs.a = state->address_space[addr];

    state->cycles += get_instruction_cycles(state->curr_inst, 1);
}

void ldh_a8_a(cpu_state * state)
{

    //Set high byte to 0xFF and low byte to desired address.
    uint16_t addr = ((0xFF << 8) | (state->fetched_data & 0x00FF));

    //printf("Loading to address: %x\n", addr);

    state->address_space[addr] = state->regs.a;

    state->cycles += get_instruction_cycles(state->curr_inst, 1);
}

void ldh_c_a(cpu_state * state)
{
    uint16_t addr = ((0xFF << 8) | (state->regs.c & 0x00FF));

    state->address_space[addr] = state->regs.a;

    state->cycles += get_instruction_cycles(state->curr_inst, 1);
}


void di(cpu_state * state)
{
    state->interrupt_master_enable = 0;
    state->cycles += get_instruction_cycles(state->curr_inst, 1);
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

    state->cycles += get_instruction_cycles(state->curr_inst, 1);

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

    state->cycles += get_instruction_cycles(state->curr_inst, 1);

}

void rra(cpu_state * state)
{
    state->regs.c_flag = (state->regs.a >> 0) & 1;

    state->regs.a = (state->regs.a >> 1)|(state -> regs.a << (8 - 1));

    state->regs.z_flag = 0;
    state->regs.n_flag = 0;
    state->regs.h_flag = 0;

    state->cycles += get_instruction_cycles(state->curr_inst, 1);

}


void jp_nocond(cpu_state * state)
{
    state->regs.pc = state->fetched_data;
    state->cycles += get_instruction_cycles(state->curr_inst, 1);
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

    state->cycles += get_instruction_cycles(state->curr_inst, 1);
}


void ld_hl_decrement_a(cpu_state * state)
{

    state->address_space[state->regs.hl] = state->regs.a;
    state->regs.hl--;
    state->cycles += get_instruction_cycles(state->curr_inst, 1);
}


void jr_nz_r8(cpu_state * state, struct romBytes * bytes)
{

    int toJump = state->fetched_data_8_signed;

    //printf("tojump: %d", -(~toJump + 1) + 2);
    
    if(state->regs.z_flag == 0)
    {
        state->regs.pc += -(~toJump + 1) + 2;//
        state->cycles += get_instruction_cycles(state->curr_inst, 1);
    }
    else
    {
        state->regs.pc += 2;
        state->cycles += get_instruction_cycles(state->curr_inst, 0);
    }

}