#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <inttypes.h>

typedef enum 
{
    INS_NOP, //No Operation
    INS_LD, //Load operation
    INS_INC, //Increment
    INS_DEC, //Decrement
    INS_RLCA,
    INS_ADD,
    INS_RRCA,
    INS_STOP,
    INS_RLA,
    INS_RRA,
    INS_JR,
    INS_JP,
    INS_DAA,
    INS_CPL,
    INS_SCF,
    INS_CCF,
    INS_HALT,
    INS_ADC,
    INS_SUB,
    INS_SBC,
    INS_AND,
    INS_XOR,
    INS_OR,
    INS_CP,
    INS_RET,
    INS_POP,
    INS_CALL,
    INS_PUSH,
    INS_RST,
    INS_CB,
    INS_LDH,
    INS_DI,
    INS_EI,
}INS_TYPE;

typedef enum
{
    ADDR_IMPL, //Implied addressing mode, as in implied by opcode
    ADDR_R_D16,//Direct 16 bit value into register
    ADDR_R_R,//Register to register
    ADDR_MR_R,//Register to memory location
    ADDR_R,//Register
    ADDR_R_D8,//Direct 8 bit value to register
    ADDR_R_MR,//Memory location to register
    ADDR_R_HLI,//HL register, indirect, to Register
    ADDR_R_HLD,//HL register, direct, to Register
    ADDR_R_A8,//8 bit address to register 
    ADDR_A8_R,//Register value to 8 bit address
    ADDR_HL_SPR,//Stack pointer to HL register
    ADDR_D8,//8 bit direct value
    ADDR_D16,//16 bit direct value
    ADDR_D16_R,//Register and direct 16 bit value
    ADDR_MR_D8,//Direct 8 bit value to memory register
    ADDR_MR,//Memory register
    ADDR_A16_R,// Register to 16 bit address
    ADDR_R_A16,//16 bit address to register

}ADDR_MODE;

typedef struct
{
    ADDR_MODE addr_mode;
    INS_TYPE inst_type;
    uint8_t op_code;
    uint8_t op1;
    uint8_t op2;
    uint8_t cond;
}instruction;

instruction instructions[0x100] = 
{
    [0x00] = {INS_NOP, ADDR_IMPL},
};
#endif