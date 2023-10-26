#ifndef CPU_H
#define CPU_H
#include <inttypes.h>
#include "instructions.h"
#include "disassemble.h"
#include "interrupt.h"
#include "util.h"
#include <byteswap.h>
#include <string.h>

#define INTERRUPT_ENABLE_REGISTER 0xffff
#define INTERRUPT_FLAG_REGISTER 0xff0f
#define VBLANK_JUMP_VECTOR 0x40

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

    uint16_t fetched_data;//Data fetched by current instruction.
	int8_t fetched_data_8_signed;
    uint16_t memory_dest;//Instructions may or may not interact with this. Only trust it's value if the current instruction interacts with it.
    instruction curr_inst;

	int cycles;

    uint8_t address_space[0xffff];

    int halt;//If this is true, no instructions will execute.
    int step;//If we are in stepping mode, only execute one instruction and wait.

	int interrupt_master_enable;

}cpu_state;

void init_cpu(cpu_state * state, struct romBytes * bytes);
int step_cpu();
int decode_instruction(cpu_state * state, struct romBytes * r);
void set_flag(int toSet, char flag[2], cpu_state * state);
void call_func(cpu_state * state, instruction ins, struct romBytes * bytes);
void call_cb_func(cpu_state * state, instruction ins);
void handle_interrupt(cpu_state * state);
int get_instruction_cycles(instruction ins, int actionTaken);
void request_interrupt(cpu_state * state, int interrupt);
void fetch_instruction(cpu_state * state, struct romBytes * r);

//CPU INSTRUCTIONS

//JUMPS
void jp_nocond(cpu_state * state);//Jumps to the address in the operand.
void jp_hl_addr(cpu_state * state);//Jump to the address stored in the HL register.
void jr_nz_r8(cpu_state * state, struct romBytes * bytes);//Jump if the zero flag is not set.
void jr_nc_r8(cpu_state * state);//Jump if the carry flag is not set.
void jr_z_r8(cpu_state * state);//Jump if the zero flag is set.
void jr_c_r8(cpu_state * state);//Jump if the carry flag is set.
void call_a16(cpu_state * state);//Call function at address. Push pc onto the stack.
void ret(cpu_state * state);//Return from function. Pop address to return to of the stack.
void jr_r8(cpu_state * state);

//Logical/Arithmetic
// void xor_a(cpu_state * state);
void rra(cpu_state * state);
void inc_d(cpu_state * state);
void and_d8(cpu_state * state);

//Comparison
void cp_d8(cpu_state * state);

//Load/Store
//void ld_hl_d16(cpu_state * state);
// void ld_c_d8(cpu_state * state);
// void ld_b_d8(cpu_state * state);
// void ld_d_d8(cpu_state * state);
void ld_hl_decrement_a(cpu_state * state);
//void ld_a_e(cpu_state * state);
//void ld_a_d8(cpu_state * state);
void ldh_a8_a(cpu_state * state);
void ldh_a_a8 (cpu_state * state);
void ldh_c_a(cpu_state * state);
void ld_hl_d8(cpu_state * state);
void ld_a16_a(cpu_state * state);
void ld_hl_increment_a(cpu_state * state);
void ld_data_at_addr_de_a(cpu_state * state);
void ld_data_at_addr_bc_a(cpu_state * state);
void ld_a16_SP(cpu_state * state);


//MISC
void di(cpu_state * state);
void rst(cpu_state * state);
void cpl(cpu_state * state);

#endif
