#ifndef CPU_H
#define CPU_H
#include <inttypes.h>
#include "instructions.h"
#include "disassemble.h"
#include <byteswap.h>
typedef struct 
{
    //8 bit registers. Can also be addressed in 16 bit pairs.
    struct {
		union {
			struct {
				unsigned char f;
				unsigned char a;
			};
			unsigned short af;
		};
	};
	
	struct {
		union {
			struct {
				unsigned char c;
				unsigned char b;
			};
			unsigned short bc;
		};
	};
	
	struct {
		union {
			struct {
				unsigned char e;
				unsigned char d;
			};
			unsigned short de;
		};
	};
	
	struct {
		union {
			struct {
				unsigned char l;
				unsigned char h;
			};
			unsigned short hl;
		};
	};

    //16 bit registers. 
    uint16_t pc;
    uint16_t sp;

    //Flags register
    uint8_t z_flag;
    uint8_t n_flag;
    uint8_t c_flag;
    uint8_t h_flag;

}registers;

typedef struct 
{
    registers regs;//Current state of CPU registers.

    int16_t fetched_data;//Data fetched by current instruction.
    uint16_t memory_dest;//Instructions may or may not interact with this. Only trust it's value if the current instruction interacts with it.
    instruction curr_inst;

    uint8_t address_space[0xffff];

    int halt;//If this is true, no instructions will execute.
    int step;//If we are in stepping mode, only execute one instruction and wait.

}cpu_state;

void init_cpu(cpu_state * state, struct romBytes * bytes);
int step_cpu();
int decode_instruction(cpu_state * state, struct romBytes * bytes);
void set_flag(int toSet, char flag[2], cpu_state * state);
void call_func(cpu_state * state, instruction ins);

//CPU INSTRUCTIONS

//JUMPS
void jp_nocond(cpu_state * state);
void jr_nz_r8(cpu_state * state);

//Logical/Arithmetic
void xor_a(cpu_state * state);
void dec_b(cpu_state * state);
void dec_e(cpu_state * state);
void dec_h(cpu_state * state);
void rra(cpu_state * state);
void or_b(cpu_state * state);
void inc_d(cpu_state * state);
void dec_d(cpu_state * state);

//Load/Store
void ld_hl_d16(cpu_state * state);
void ld_c_d8(cpu_state * state);
void ld_b_d8(cpu_state * state);
void ld_d_d8(cpu_state * state);
void ld_hl_decrement_a(cpu_state * state);
void ld_a_e(cpu_state * state);

#endif
