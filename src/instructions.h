#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_
#include <inttypes.h>
#include "disassemble.h"

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