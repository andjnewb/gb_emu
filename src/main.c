#include <stdio.h>
#include <string.h>
#include "disassemble.h"
#include "display.h"
#include <inttypes.h>
#include "instructions.h"
#include "cpu.h"
#include <endian.h>

const instruction instructions[256] =
    {
        {"NOP", 0x0, 1, NONE, "----", "4/0"},
        {"LD BC,d16", 0x1, 3, d16, "----", "12/0"},
        {"LD (BC),A", 0x2, 1, NONE, "----", "8/0"},
        {"INC BC", 0x3, 1, NONE, "----", "8/0"},
        {"INC B", 0x4, 1, NONE, "z0h-", "4/0"},
        {"DEC B", 0x5, 1, NONE, "z1h-", "4/0"},
        {"LD B,d8", 0x6, 2, d8, "----", "8/0"},
        {"RLCA", 0x7, 1, NONE, "000c", "4/0"},
        {"LD (a16),SP", 0x8, 3, a16, "----", "20/0"},
        {"ADD HL,BC", 0x9, 1, NONE, "-0hc", "8/0"},
        {"LD A,(BC)", 0xa, 1, NONE, "----", "8/0"},
        {"DEC BC", 0xb, 1, NONE, "----", "8/0"},
        {"INC C", 0xc, 1, NONE, "z0h-", "4/0"},
        {"DEC C", 0xd, 1, NONE, "z1h-", "4/0"},
        {"LD C,d8", 0xe, 2, d8, "----", "8/0"},
        {"RRCA", 0xf, 1, NONE, "000c", "4/0"},
        {"STOP 0", 0x10, 2, NONE, "----", "4/0"},
        {"LD DE,d16", 0x11, 3, d16, "----", "12/0"},
        {"LD (DE), A", 0x12, 1, NONE, "----", "8/0"},
        {"INC DE", 0x13, 1, NONE, "----", "8/0"},
        {"INC D", 0x14, 1, NONE, "z0h-", "4/0"},
        {"DEC D", 0x15, 1, NONE, "z1h-", "4/0"},
        {"LD D,d8", 0x16, 2, d8, "----", "8/0"},
        {"RLA", 0x17, 1, NONE, "000c", "4/0"},
        {"JR r8", 0x18, 2, r8, "----", "12/0"},
        {"ADD HL,DE", 0x19, 1, NONE, "-0hc", "8/0"},
        {"LD A,(DE)", 0x1a, 1, NONE, "----", "8/0"},
        {"DEC DE", 0x1b, 1, NONE, "----", "8/0"},
        {"INC E", 0x1c, 1, NONE, "z0h-", "4/0"},
        {"DEC E", 0x1d, 1, NONE, "z1h-", "4/0"},
        {"LD E, d8", 0x1e, 2, d8, "----", "8/0"},
        {"RRA", 0x1f, 1, NONE, "000c", "4/0"},
        {"JR NZ,r8", 0x20, 2, r8, "----", "12/8"},
        {"LD HL,d16", 0x21, 3, d16, "----", "12/0"},
        {"LD (HL+),A", 0x22, 1, NONE, "----", "8/0"},
        {"INC HL", 0x23, 1, NONE, "----", "8/0"},
        {"INC H", 0x24, 1, NONE, "z0h-", "4/0"},
        {"DEC H", 0x25, 1, NONE, "z1h-", "4/0"},
        {"LD H,d8", 0x26, 2, d8, "----", "8/0"},
        {"DAA", 0x27, 1, NONE, "z-0c", "4/0"},
        {"JR Z,r8", 0x28, 2, r8, "----", "12/8"},
        {"ADD HL,HL", 0x29, 1, NONE, "-0hc", "8/0"},
        {"LD A,(HL+)", 0x2a, 1, NONE, "----", "8/0"},
        {"DEC HL", 0x2b, 1, NONE, "----", "8/0"},
        {"INC L", 0x2c, 1, NONE, "z0h-", "4/0"},
        {"DEC L", 0x2d, 1, NONE, "z1h-", "4/0"},
        {"LD L,d8", 0x2e, 2, d8, "----", "8/0"},
        {"CPL", 0x2f, 1, NONE, "-11-", "4/0"},
        {"JR NC,r8", 0x30, 2, r8, "----", "12/8"},
        {"LD SP,d16", 0x31, 3, d16, "----", "12/0"},
        {"LD (HL-),A", 0x32, 1, NONE, "----", "8/0"},
        {"INC SP", 0x33, 1, NONE, "----", "8/0"},
        {"INC (HL)", 0x34, 1, NONE, "z0h-", "12/0"},
        {"DEC (HL)", 0x35, 1, NONE, "z1h-", "12/0"},
        {"LD (HL),d8", 0x36, 2, d8, "----", "12/0"},
        {"SCF", 0x37, 1, NONE, "-001", "4/0"},
        {"JR Z,r8 ", 0x38, 2, r8, "----", "1/0"},
        {"ADD HL,SP ", 0x39, 1, NONE, "-0hc", "1/0"},
        {"LD A,(HL-) ", 0x3a, 1, NONE, "----", "1/0"},
        {"DEC SP", 0x3b, 1, NONE, "----", "1/0"},
        {"INC A", 0x3c, 1, NONE, "z0h-", "1/0"},
        {"DEC A", 0x3d, 1, NONE, "z1h-", "1/0"},
        {"LD A,d8", 0x3e, 2, d8, "----", "1/0"},
        {"CCF", 0x3f, 1, NONE, "000c", "1/0"},
        {"LD B,B", 0x40, 1, NONE, "----", "1/0"},
        {"LD B,C", 0x41, 1, NONE, "----", "1/0"},
        {"LD B,D", 0x42, 1, NONE, "----", "1/0"},
        {"LD B,E", 0x43, 1, NONE, "----", "1/0"},
        {"LD B,H", 0x44, 1, NONE, "----", "1/0"},
        {"LD B,L", 0x45, 1, NONE, "----", "1/0"},
        {"LD B,(HL)", 0x46, 1, NONE, "----", "1/0"},
        {"LD B,A", 0x47, 1, NONE, "----", "1/0"},
        {"LD C,B", 0x48, 1, NONE, "----", "1/0"},
        {"LD C,C", 0x49, 1, NONE, "----", "1/0"},
        {"LD C,D", 0x4a, 1, NONE, "----", "1/0"},
        {"LD C,E", 0x4b, 1, NONE, "----", "1/0"},
        {"LD C,H", 0x4c, 1, NONE, "----", "1/0"},
        {"LD C,L", 0x4d, 1, NONE, "----", "1/0"},
        {"LD C,(HL)", 0x4e, 1, NONE, "----", "1/0"},
        {"LD C,A", 0x4f, 1, NONE, "----", "1/0"},
        {"LD D,B", 0x50, 1, NONE, "----", "1/0"},
        {"LD D,C", 0x51, 1, NONE, "----", "1/0"},
        {"LD D,D", 0x52, 1, NONE, "----", "1/0"},
        {"LD D,E", 0x53, 1, NONE, "----", "1/0"},
        {"LD D,H", 0x54, 1, NONE, "----", "1/0"},
        {"LD D,L", 0x55, 1, NONE, "----", "1/0"},
        {"LD D,(HL)", 0x56, 1, NONE, "----", "1/0"},
        {"LD D,A", 0x57, 1, NONE, "----", "1/0"},
        {"LD E,B", 0x58, 1, NONE, "----", "1/0"},
        {"LD E,C", 0x59, 1, NONE, "----", "1/0"},
        {"LD E,D", 0x5a, 1, NONE, "----", "1/0"},
        {"LD E,E", 0x5b, 1, NONE, "----", "1/0"},
        {"LD E,H", 0x5c, 1, NONE, "----", "1/0"},
        {"LD E,L", 0x5d, 1, NONE, "----", "1/0"},
        {"LD E,(HL)", 0x5e, 1, NONE, "----", "1/0"},
        {"LD E,A", 0x5f, 1, NONE, "----", "1/0"},
        {"LD H,B", 0x60, 1, NONE, "----", "1/0"},
        {"LD H,C", 0x61, 1, NONE, "----", "1/0"},
        {"LD H,D", 0x62, 1, NONE, "----", "1/0"},
        {"LD H,E", 0x63, 1, NONE, "----", "1/0"},
        {"LD H,H", 0x64, 1, NONE, "----", "1/0"},
        {"LD H,L", 0x65, 1, NONE, "----", "1/0"},
        {"LD H,(HL)", 0x66, 1, NONE, "----", "1/0"},
        {"LD H,A", 0x67, 1, NONE, "----", "1/0"},
        {"LD L,B", 0x68, 1, NONE, "----", "1/0"},
        {"LD L,C", 0x69, 1, NONE, "----", "1/0"},
        {"LD L,D", 0x6a, 1, NONE, "----", "1/0"},
        {"LD L,E", 0x6b, 1, NONE, "----", "1/0"},
        {"LD L,H", 0x6c, 1, NONE, "----", "1/0"},
        {"LD L,L", 0x6d, 1, NONE, "----", "1/0"},
        {"LD L,(HL)", 0x6e, 1, NONE, "----", "1/0"},
        {"LD L,A", 0x6f, 1, NONE, "----", "1/0"},
        {"LD (HL),B", 0x70, 1, NONE, "----", "1/0"},
        {"LD (HL),C", 0x71, 1, NONE, "----", "1/0"},
        {"LD (HL),D", 0x72, 1, NONE, "----", "1/0"},
        {"LD (HL),E", 0x73, 1, NONE, "----", "1/0"},
        {"LD (HL),H", 0x74, 1, NONE, "----", "1/0"},
        {"LD (HL),L", 0x75, 1, NONE, "----", "1/0"},
        {"HALT", 0x76, 1, NONE, "----", "1/0"},
        {"LD (HL),A", 0x77, 1, NONE, "----", "1/0"},
        {"LD A,B", 0x78, 1, NONE, "----", "1/0"},
        {"LD A,C", 0x79, 1, NONE, "----", "1/0"},
        {"LD A,D", 0x7a, 1, NONE, "----", "1/0"},
        {"LD A,E", 0x7b, 1, NONE, "----", "1/0"},
        {"LD A,H", 0x7c, 1, NONE, "----", "1/0"},
        {"LD A,L", 0x7d, 1, NONE, "----", "1/0"},
        {"LD A,(HL)", 0x7e, 1, NONE, "----", "1/0"},
        {"LD A,A", 0x7f, 1, NONE, "----", "1/0"},
        {"ADD A,B", 0x80, 1, NONE, "z0hc", "1/0"},
        {"ADD A,C", 0x81, 1, NONE, "z0hc", "1/0"},
        {"ADD A,D", 0x82, 1, NONE, "z0hc", "1/0"},
        {"ADD A,E", 0x83, 1, NONE, "z0hc", "1/0"},
        {"ADD A,H", 0x84, 1, NONE, "z0hc", "1/0"},
        {"ADD A,L", 0x85, 1, NONE, "z0hc", "1/0"},
        {"ADD A,(HL", 0x86, 1, NONE, "z0hc", "1/0"},
        {"ADD A,A", 0x87, 1, NONE, "z0hc", "1/0"},
        {"ADC A,B", 0x88, 1, NONE, "z0hc", "1/0"},
        {"ADC A,C", 0x89, 1, NONE, "z0hc", "1/0"},
        {"ADC A,D", 0x8a, 1, NONE, "z0hc", "1/0"},
        {"ADC A,E", 0x8b, 1, NONE, "z0hc", "1/0"},
        {"ADC A,H", 0x8c, 1, NONE, "z0hc", "1/0"},
        {"ADC A,L", 0x8d, 1, NONE, "z0hc", "1/0"},
        {"ADC A,(HL", 0x8e, 1, NONE, "z0hc", "1/0"},
        {"ADC A,A", 0x8f, 1, NONE, "z0hc", "1/0"},
        {"SUB B", 0x90, 1, NONE, "z1hc", "1/0"},
        {"SUB C", 0x91, 1, NONE, "z1hc", "1/0"},
        {"SUB D", 0x92, 1, NONE, "z1hc", "1/0"},
        {"SUB E", 0x93, 1, NONE, "z1hc", "1/0"},
        {"SUB H", 0x94, 1, NONE, "z1hc", "1/0"},
        {"SUB L", 0x95, 1, NONE, "z1hc", "1/0"},
        {"SUB (HL)", 0x96, 1, NONE, "z1hc", "1/0"},
        {"SUB A", 0x97, 1, NONE, "z1hc", "1/0"},
        {"SBC A,B", 0x98, 1, NONE, "z1hc", "1/0"},
        {"SBC A,C", 0x99, 1, NONE, "z1hc", "1/0"},
        {"SBC A,D", 0x9a, 1, NONE, "z1hc", "1/0"},
        {"SBC A,E", 0x9b, 1, NONE, "z1hc", "1/0"},
        {"SBC A,H", 0x9c, 1, NONE, "z1hc", "1/0"},
        {"SBC A,L", 0x9d, 1, NONE, "z1hc", "1/0"},
        {"SBC A,(HL)", 0x9e, 1, NONE, "z1hc", "1/0"},
        {"SBC A,A", 0x9f, 1, NONE, "z1hc", "1/0"},
        {"AND B", 0xa0, 1, NONE, "z010", "1/0"},
        {"AND C", 0xa1, 1, NONE, "z010", "1/0"},
        {"AND D", 0xa2, 1, NONE, "z010", "1/0"},
        {"AND E", 0xa3, 1, NONE, "z010", "1/0"},
        {"AND H", 0xa4, 1, NONE, "z010", "1/0"},
        {"AND L", 0xa5, 1, NONE, "z010", "1/0"},
        {"AND (HL)", 0xa6, 1, NONE, "z010", "1/0"},
        {"AND A", 0xa7, 1, NONE, "z010", "1/0"},
        {"XOR B", 0xa8, 1, NONE, "z010", "1/0"},
        {"XOR C", 0xa9, 1, NONE, "z000", "1/0"},
        {"XOR D", 0xaa, 1, NONE, "z000", "1/0"},
        {"XOR E", 0xab, 1, NONE, "z000", "1/0"},
        {"XOR H", 0xac, 1, NONE, "z000", "1/0"},
        {"XOR L", 0xad, 1, NONE, "z000", "1/0"},
        {"XOR (HL", 0xae, 1, NONE, "z000", "1/0"},
        {"XOR A", 0xaf, 1, NONE, "z000", "1/0"},
        {"OR B", 0xb0, 1, NONE, "z000", "1/0"},
        {"OR C", 0xb1, 1, NONE, "z000", "1/0"},
        {"OR D", 0xb2, 1, NONE, "z000", "1/0"},
        {"OR E", 0xb3, 1, NONE, "z000", "1/0"},
        {"OR H", 0xb4, 1, NONE, "z000", "1/0"},
        {"OR L", 0xb5, 1, NONE, "z000", "1/0"},
        {"OR (HL)", 0xb6, 1, NONE, "z000", "1/0"},
        {"OR A", 0xb7, 1, NONE, "z000", "1/0"},
        {"CP B", 0xb8, 1, NONE, "z000", "1/0"},
        {"CP C", 0xb9, 1, NONE, "z1hc", "1/0"},
        {"CP D", 0xba, 1, NONE, "z1hc", "1/0"},
        {"CP E", 0xbb, 1, NONE, "z1hc", "1/0"},
        {"CP H", 0xbc, 1, NONE, "z1hc", "1/0"},
        {"CP L", 0xbd, 1, NONE, "z1hc", "1/0"},
        {"CP (HL)", 0xbe, 1, NONE, "z1hc", "1/0"},
        {"CP A", 0xbf, 1, NONE, "z1hc", "1/0"},
        {"RET NZ", 0xc0, 1, NONE, "z1hc", "1/0"},
        {"POP BC", 0xc1, 1, NONE, "----", "1/0"},
        {"JP NZ,A16", 0xc2, 3, a16, "----", "1/0"},
        {"JP A16", 0xc3, 3, a16, "----", "1/0"},
        {"CALL NZ,A16", 0xc4, 3, a16, "----", "1/0"},
        {"PUSH BC", 0xc5, 1, NONE, "----", "1/0"},
        {"ADD A,D8", 0xc6, 2, d8, "z0hc", "1/0"},
        {"RST 00H", 0xc7, 1, NONE, "----", "1/0"},
        {"RET Z", 0xc8, 1, NONE, "----", "1/0"},
        {"RET", 0xc9, 1, NONE, "----", "1/0"},
        {"JP Z,A16", 0xca, 3, a16, "----", "1/0"},
        {"CBPREFIX", 0xcb, 2, NONE, "----", "1/0"},
        {"CALL Z,A16", 0xcc, 3, a16, "----", "1/0"},
        {"CALL A16", 0xcd, 3, a16, "----", "1/0"},
        {"ADC A,D8", 0xce, 2, d8, "z0hc", "1/0"},
        {"RST 08H", 0xcf, 1, NONE, "----", "1/0"},
        {"RET NC", 0xd0, 1, NONE, "----", "1/0"},
        {"POP DE", 0xd1, 1, NONE, "----", "1/0"},
        {"JP NC,A16", 0xd2, 3, a16, "----", "1/0"},
        {"UNDEFINED", 0xd3, 1, NONE, "----", "1/0"},
        {"CALL NC,A16", 0xd4, 3, a16, "----", "1/0"},
        {"PUSH DE", 0xd5, 1, NONE, "----", "1/0"},
        {"SUB D8", 0xd6, 2, d8, "z1hc", "1/0"},
        {"RST 10H", 0xd7, 1, NONE, "----", "1/0"},
        {"RET C", 0xd8, 1, NONE, "----", "1/0"},
        {"RETI", 0xd9, 1, NONE, "----", "1/0"},
        {"JP C,A16", 0xda, 3, a16, "----", "1/0"},
        {"UNDEFINED", 0xdb, 1, NONE, "----", "1/0"},
        {"CALL C,a16", 0xdc, 3, a16, "----", "1/0"},
        {"UNDEFINED", 0xdd, 1, NONE, "----", "1/0"},
        {"SBC A,D8", 0xde, 2, d8, "z1hc", "1/0"},
        {"RST 18H", 0xdf, 1, NONE, "----", "1/0"},
        {"LDH (A8),A", 0xe0, 2, a8, "----", "1/0"},
        {"POP HL", 0xe1, 1, NONE, "----", "1/0"},
        {"LD (C),A", 0xe2, 2, NONE, "----", "1/0"},
        {"UNDEFINED", 0xe3, 1, NONE, "----", "1/0"},
        {"UNDEFINED", 0xe4, 1, NONE, "----", "1/0"},
        {"PUSH HL", 0xe5, 1, NONE, "----", "1/0"},
        {"AND D8", 0xe6, 2, d8, "z010", "1/0"},
        {"RST 20H", 0xe7, 1, NONE, "----", "1/0"},
        {"ADD SP,R8", 0xe8, 2, r8, "00hc", "1/0"},
        {"JP (HL)", 0xe9, 1, NONE, "----", "1/0"},
        {"LD (A16),A", 0xea, 3, a16, "----", "1/0"},
        {"UNDEFINED", 0xeb, 1, NONE, "----", "1/0"},
        {"UNDEFINED", 0xec, 1, NONE, "----", "1/0"},
        {"UNDEFINED", 0xed, 1, NONE, "----", "1/0"},
        {"XOR D8", 0xee, 2, d8, "z000", "1/0"},
        {"RST 28H", 0xef, 1, NONE, "----", "1/0"},
        {"LDH A,A8", 0xf0, 2, a8, "----", "1/0"},
        {"POP AF", 0xf1, 1, NONE, "znhc", "1/0"},
        {"LD A,(C)", 0xf2, 2, NONE, "----", "1/0"},
        {"DI", 0xf3, 1, NONE, "----", "1/0"},
        {"UNDEFINED", 0xf4, 1, NONE, "----", "1/0"},
        {"PUSH AF", 0xf5, 1, NONE, "----", "1/0"},
        {"OR D8", 0xf6, 2, d8, "z000", "1/0"},
        {"RST 30H", 0xf7, 1, NONE, "----", "1/0"},
        {"LD HL,SP+R8", 0xf8, 2, r8, "00hc", "1/0"},
        {"LD SP,HL", 0xf9, 1, NONE, "----", "1/0"},
        {"LD A,(A16)", 0xfa, 3, a16, "----", "1/0"},
        {"EI", 0xfb, 1, NONE, "----", "1/0"},
        {"UNDEFINED", 0xfc, 1, NONE, "----", "1/0"},
        {"UNDEFINED", 0xfd, 1, NONE, "----", "1/0"},
        {"CP D8", 0xfe, 2, d8, "z1hc", "1/0"},
        {"RST 38H", 0xff, 1, NONE, "----", "1/0"},
};
int main(int argc, char *argv[])
{

    video_state v_state;

    if (init_video(&v_state) != 1)
    {
        printf("Error intializing video. Exiting....\n");
        exit(0);
    }

    struct romBytes *r = malloc(sizeof(struct romBytes));
    //

    *r = getBytes("tetris.gb");
    r->metaData = getMetaData(r);

    uint8_t ins = r->bytes[0x100];

    FILE *out = fopen("tetris.asm", "w");

    cpu_state state;
    init_cpu(&state, r);
    state.regs.pc = 0x100;
    state.step = 0;

    int delay = 0;

    while (state.halt != 1)
    {
        while (SDL_PollEvent(&v_state.event) == 1)
        {
            if (v_state.event.type == SDL_QUIT)
            {
                state.halt = 1;
            }

            if (v_state.event.type == SDL_KEYDOWN)
            {
                if (v_state.event.key.keysym.sym == SDLK_SPACE)
                {
                    if (state.step == 1)
                    {
                        state.step = 0;
                    }
                    else
                    {
                        state.step = 1;
                    }
                }

                if (v_state.event.key.keysym.sym == SDLK_s)
                {
                    delay += 10;
                }

                if (v_state.event.key.keysym.sym == SDLK_f)
                {
                    delay -= 10;
                }

                if (delay < 0)
                {
                    delay = 0;
                }
            }
        }

        SDL_Delay(delay);

        if (state.step == 1)
        {

            continue;
        }

        char text_state[512];

        sprintf(text_state, "PC: 0x%x\nA:%x B:%x C:%x D:%x E:%x H:%x L:%x \nFlags: %d%d%d%d\nStack Pointer: %x\nFetched Data: %x \nHalted: %d\nCycle: %d\nInterrupts Enabled: %s\n",
                state.regs.pc,
                state.regs.a, state.regs.b, state.regs.c, state.regs.d, state.regs.e, state.regs.h, state.regs.l,
                state.regs.z_flag, state.regs.n_flag, state.regs.h_flag, state.regs.c_flag,
                state.regs.sp,
                state.fetched_data,
                state.halt,
                state.cycles,
                state.interrupt_master_enable == 1 ? "Yes" : "No");

        // get_text_and_rect(v_state.renderer, 0, 0, text_state, v_state.font, &v_state.tex1, v_state.rect1, &v_state);

        char toAppend[256];

        system("clear");
        printf("\nPC: 0x%x\n", state.regs.pc);
        printf("A:%x B:%x C:%x D:%x E:%x H:%x L:%x \n", state.regs.a, state.regs.b, state.regs.c, state.regs.d, state.regs.e, state.regs.h, state.regs.l);
        printf("Flags: %d%d%d%d\n", state.regs.z_flag, state.regs.n_flag, state.regs.h_flag, state.regs.c_flag);
        printf("Stack Pointer: %x\n", state.regs.sp);
        printf("Fetched Data: %x \n", state.fetched_data);
        printf("Halted: %d\n", state.halt);
        printf("Cycle: %d\n\n", state.cycles);
        printf("Interrupts Enabled: %s\n", state.interrupt_master_enable == 1 ? "Yes" : "No");

        state.curr_inst = instructions[r->bytes[state.regs.pc]];
        printf("0x%x : 0x%x %s %x \n", state.regs.pc, state.curr_inst.op_code, state.curr_inst.mnmemonic, state.fetched_data);

        // SDL_SetRenderDrawColor(v_state.renderer, 0, 0, 0, 0);
        // SDL_RenderClear(v_state.renderer);

        // /* Use TTF textures. */
        // SDL_RenderCopy(v_state.renderer, v_state.tex1, NULL, v_state.rect1);
        // SDL_RenderCopy(v_state.renderer, v_state.tex2, NULL, v_state.rect2);

        // SDL_RenderPresent(v_state.renderer);

        state.address_space[0xFF44] = 148; // Register HACK, remove later.

        switch (instructions[r->bytes[state.regs.pc]].d_type)
        {
        case a16:
            uint8_t d1 = r->bytes[state.regs.pc + 1];
            uint8_t d2 = r->bytes[state.regs.pc + 2];

            uint16_t toConvert = (d2 << 8) | d1;

            state.fetched_data = toConvert;

            break;
        case d8:
            state.fetched_data = r->bytes[state.regs.pc + 1];

            break;
        case d16:
            uint8_t d3 = r->bytes[state.regs.pc + 1];
            uint8_t d4 = r->bytes[state.regs.pc + 2];

            uint16_t toConvert1 = (d4 << 8) | d3;

            state.fetched_data = toConvert1;
            break;

        case a8:
            state.fetched_data = r->bytes[state.regs.pc + 1];
            break;

        case r8:
            state.fetched_data_8_signed = r->bytes[state.regs.pc + 1];
            // state.regs.pc += r->bytes[state.regs.pc + 1];

            break;

        case NONE:
            state.fetched_data = 0x0;

            break;

        default:
            // exit(0);
            break;
        }
        // fprintf(out, "0x%x : 0x%x %s %x \n", state.regs.pc,  state.curr_inst.op_code, state.curr_inst.mnmemonic ,state.fetched_data);
        // printf("Current instruction: 0x%x: %s %x\n", state.curr_inst.op_code, state.curr_inst.mnmemonic, (state.curr_inst.length > 1) ? state.fetched_data : 0);
        // printf("Cycle from Current: %d/%d\n", get_instruction_cycles(state.curr_inst, 1), get_instruction_cycles(state.curr_inst, 0));

        if(state.regs.pc == 0x237)
        {
             printf("0xcffe: %x\n", state.address_space[0xcffe]);
             printf("0xcffd: %x\n", state.address_space[0xcffd]);
             printf("0xcfff: %x\n", state.address_space[0xcfff]);
            exit(0);
           
        }



        call_func(&state, instructions[r->bytes[state.regs.pc]], r);




        if (state.interrupt_master_enable == 1)
        {
            handle_interrupt(&state);
        }


        // if(state.cycles > 10)
        // {
        //     clean_SDL(&v_state);
        //     exit(0);

        // }

        state.step = 0;
    }
    ////
    printf("Disassembly written to: %s\n", "tetris.asm");
    // printf("Title = %s", r->metaData.title);
        
    fwrite(state.address_space, 0xffff, sizeof(uint8_t), out);
        
    //free(r.bytes);
    fclose(out);

    return clean_SDL(&v_state);
}
