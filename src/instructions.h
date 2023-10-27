#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_
#include <inttypes.h>
#include "disassemble.h"

//FIXME: Do I need to set the zero flag when result wraps around???
#define _INC_REG16(register)\
    void _INC_##register(cpu_state * state)\
    {\
        int result = state->regs.register + 1;\
        \
        if(result > 0xffff)\
        {\
            state->regs.register = 0x0;\
        }\
        else\
        {\
            state->regs.register++;\
        }\
    }\

#define _LD_REG_VALUE_AT_ADDR_IN_HL(register)\
    void _LD_##register##_AT_HL(cpu_state * state)\
    {\
        state->regs.register = state->address_space[state->regs.hl];\
        state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\

#define _ADD_REG16_REG16(register1,register2) \
    void _ADD_##register1##_##register2(cpu_state * state) \
    {\
      int result = state->regs.register1 + state->regs.register2;\
        \
      if(result > 0xffff)\
        {\
            state->regs.register1 = 0x0;\
        }\
            \
      else\
        {\
            state->regs.register1 = result;\
        }\
            \
      set_flag(0, "n", state);\
      \
      \
      if(state->regs.register1 & (1<<11))\
        {\
            set_flag(1, "h", state);\
        }\
      else\
        {\
            set_flag(0, "h", state);\
        }\
\
      if(state->regs.register1 & (1<<15))\
      {\
        set_flag(1, "c", state);\
      }\
      else\
      {\
        set_flag(1, "c", state);\
      }\
\
    state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\


#define _POP_REG_16(register)\
    void _POP_##register(cpu_state * state)\
    {\
        if(state->curr_inst.op_code == 0xf1)\
        {\
            uint8_t temp;\
            \
            state->regs.register = 0;\
            state->regs.a = stack_pop(state);\
            temp = stack_pop(state);\
            state->regs.z_flag =  1 ? checkBit(temp,3) == 1 : 0;\
            state->regs.n_flag =  1 ? checkBit(temp,2) == 1 : 0;\
            state->regs.h_flag =  1 ? checkBit(temp,1) == 1 : 0;\
            state->regs.c_flag =  1 ? checkBit(temp,0) == 1 : 0;\
        }\
        else\
        {\
            state->regs.register = stack_pop_16(state);\
        }\
    }\

#define _PUSH_REG_16(register)\
    void _PUSH_##register(cpu_state * state)\
    {\
        if(state->curr_inst.op_code == 0xf5)\
        {\
            uint8_t temp;\
            \
            stack_push(state->regs.a,state);\
\
            temp = setBit(temp, 3) ? state->regs.z_flag == 1 : clearBit(temp, 3);\
            temp = setBit(temp, 2) ? state->regs.n_flag == 1 : clearBit(temp, 2);\
            temp = setBit(temp, 1) ? state->regs.h_flag == 1 : clearBit(temp, 1);\
            temp = setBit(temp, 0) ? state->regs.c_flag == 1 : clearBit(temp, 0);\
            \
            stack_push(temp,state);\
\
        }\
        else\
        {\
            stack_push16(state->regs.register, state);\
        }\
    }\

#define _ADD_A_REG(register) \
    void _ADD_A_## register(cpu_state * state) \
    {\
      int result = state->regs.a + state->regs.register;\
        \
      if(result > 255)\
        {\
            set_flag(1, "z", state);\
            state->regs.register = 0x0;\
        }\
      else\
        {\
            set_flag(0, "z", state);\
            state->regs.register = result;\
        }\
        \
      set_flag(0, "n", state);\
      \
      \
      if(state->regs.register & (1<<3))\
        {\
            set_flag(1, "h", state);\
        }\
      else\
        {\
            set_flag(0, "h", state);\
        }\
      if(state->regs.register & (1<<7))\
        {\
            set_flag(1, "c", state);\
        }\
      else\
        {\
            set_flag(0, "c", state);\
        }\
    state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\


#define _AND_REG(reg)\
    void _AND_##reg(cpu_state * state)\
    {\
        uint8_t result = state->regs.a & state->regs.reg;\
        state->regs.a = result;\
\
        if(result == 0)\
        {\
            set_flag(1, "z", state);\
        }\
        else\
        {\
            set_flag(0, "z", state);\
        }\
       state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\

#define _XOR_REG(reg)\
    void _XOR_##reg(cpu_state * state)\
    {\
        uint8_t result = state->regs.a ^ state->regs.reg;\
        state->regs.a = result;\
\
        if(result == 0)\
        {\
            set_flag(1, "z", state);\
        }\
        else\
        {\
            set_flag(0, "z", state);\
        }\
\
        set_flag(0,"n",state);\
        set_flag(0,"h",state);\
        set_flag(0,"c",state);\
\
       state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\

#define _CB_SWAP(reg)\
    void _SWAP_##reg(cpu_state * state)\
    {\
        uint8_t val = state->regs.reg;\
        state->regs.reg = ((val & 0x0f) << 4 | (val & 0xf0) >> 4);\
    }\

#define _OR_REG(reg)\
    void _OR_##reg (cpu_state * state)\
    {\
        uint8_t result = state->regs.a | state->regs.reg;\
        \
        state->regs.a = result;\
        \
        if(result == 0)\
        {\
            set_flag(1, "z", state);\
        }\
        else\
        {\
            set_flag(0, "z", state);\
        }\
        \
        state->regs.n_flag = 0;\
        state->regs.h_flag = 0;\
        state->regs.c_flag = 0;\
    }\

#define _LD_REG_d8(reg)\
    void _LD_##reg## _d8(cpu_state * state)\
    {\
        state->regs.reg = state->fetched_data;\
        state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\

#define _LD_REG_8_8(reg1, reg2)\
    void _LD_##reg1##_##reg2(cpu_state * state)\
    {\
        state->regs.reg1 = state->regs.reg2;\
        state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\

#define _LD_REG16_d16(register_16)\
    void _LD_##register_16##_d16(cpu_state * state)\
    {\
        state->regs.register_16 = state->fetched_data;\
        state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\

#define _LD_REG16_REG(reg16, reg8)\
    void _LD_##reg16##_##reg8(cpu_state * state)\
    {\
        state->regs.reg16 = state->regs.reg8;\
        state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\


#define _DEC_REG(register) \
    void _DEC_ ## register(cpu_state * state) \
    {\
      int result = state->regs.register - 1;\
        \
      if(result < 0)\
        {\
            set_flag(0, "z", state);\
            state->regs.register = 0xff;\
        }\
      else if(result == 0)\
        {\
            set_flag(1, "z", state);\
            state->regs.register = 0;\
        }\
        \
      else\
        {\
            set_flag(0, "z", state);\
            state->regs.register -= 1;\
        }\
        \
      set_flag(1, "n", state);\
      \
      \
      if(state->regs.register & (1<<3))\
        {\
            set_flag(1, "h", state);\
        }\
      else\
        {\
            set_flag(0, "h", state);\
        }\
    state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\
//NOT TESTED. PROBABLY NEEDS WORK.
#define _INC_REG(register) \
    void _INC_ ## register(cpu_state * state) \
    {\
      int result = state->regs.register + 1;\
        \
      if(result > 255)\
        {\
            set_flag(1, "z", state);\
            state->regs.register = 0x0;\
        }\
      else\
        {\
            set_flag(0, "z", state);\
            state->regs.register += 1;\
        }\
        \
      set_flag(1, "n", state);\
      \
      \
      if(state->regs.register & (1<<3))\
        {\
            set_flag(1, "h", state);\
        }\
      else\
        {\
            set_flag(0, "h", state);\
        }\
    state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\

#define _LD_REG_REGA16(register1, register2)\
    void _LD_##register1##_## register2(cpu_state * state)\
    {\
        state->regs.register1 = state->address_space[state->regs.register2];\
        state->cycles += get_instruction_cycles(state->curr_inst, 1);\
    }\



enum data_type
{
    NONE, //Instruction is not followed by data or an address.
    d8,   //Instruction is followed by immediate 8 bit data
    d16,  //Instruction is followed by immediate 16bit data. Don't forget to shift the bits!
    a8,  //Instruction is followed by 8 bit unsigned data. Added to $FF00 in certain instructions.
    a16, //Instruction is followed by 16bit address
    r8  //Instruction is followed by 8 bit signed data, which is added to the program counter.
};

typedef struct instruction
{
    char mnmemonic[16];
    uint8_t op_code;
    int length;
    int d_type;
    char flags[4];
    char cycles[4];
    
} instruction;




#endif