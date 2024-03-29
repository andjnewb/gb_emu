#include "cpu.h"
#include "disassemble.h"
#include "stack.h"
#include "interrupt.h"
//CPU FUNCTIONS. Should find a better place for these. Macros are defined in instructions.h. These are mostly used for functions that would pointless to have seperate definition for each version, for example LD A,E and LD E,A.
//Considering that there are well over forty of these variations for the 8 bit registers, you can see why it makes sense to do it this way.

const instruction cb_instructions[256] =
    {
        {"RLC B", 0x0,       2, NONE, "z00c", "8/0" },
        {"RLC C", 0x1,       2, NONE, "z00c", "8/0"},
        {"RLC D", 0x2,       2, NONE, "z00c", "8/0" },
        {"RLC E", 0x3,       2, NONE, "z00c", "8/0" },
        {"RLC H", 0x4,       2, NONE, "z00c", "8/0" },
        {"RLC L", 0x5,       2, NONE, "z00c", "8/0" },
        {"RLC (HL)", 0x6,    2, NONE, "z00c", "8/0" },
        {"RLC A", 0x7,       2, NONE, "z00c", "8/0" },
        {"RRC B", 0x8,       2, NONE, "z00c", "8/0"},
        {"RRC C", 0x9,       2, NONE, "z00c", "8/0"},
        {"RRC D", 0xa,       2, NONE, "z00c", "8/0"},
        {"RRC E", 0xb,       2, NONE, "z00c", "8/0"},
        {"RRC H", 0xc,       2, NONE, "z00c", "8/0"},
        {"RRC L", 0xd,       2, NONE, "z00c", "8/0"},
        {"RRC (HL)", 0xe,    2, NONE, "z00c", "8/0"},
        {"RRC A", 0xf,       2, NONE, "z00c", "8/0"},
        {"RL B", 0x10,       2, NONE, "z00c", "8/0"},
        {"RL C", 0x11,       2, NONE, "z00c", "8/0"},
        {"RL D", 0x12,       2, NONE, "z00c", "8/0"},
        {"RL E", 0x13,       2, NONE, "z00c", "8/0"},
        {"RL H", 0x14,       2, NONE, "z00c", "8/0"},
        {"RL L", 0x15,       2, NONE, "z00c", "8/0"},
        {"RL (HL)", 0x16,    2, NONE, "z00c", "8/0"},
        {"RL A", 0x17,       2, NONE, "z00c", "8/0"},
        {"RR B", 0x18,       2, NONE, "z00c", "8/0"},
        {"RR C", 0x19,       2, NONE, "z00c", "8/0"},
        {"RR D", 0x1a,       2, NONE, "z00c", "8/0"},
        {"RR E", 0x1b,       2, NONE, "z00c", "8/0"},
        {"RR H", 0x1c,       2, NONE, "z00c", "8/0"},
        {"RR L", 0x1d,       2, NONE, "z00c", "8/0"},
        {"RR (HL)", 0x1e,    2, NONE, "z00c", "8/0"},
        {"RR A", 0x1f,       2, NONE, "z00c", "8/0"},
        {"SLA B", 0x20,      2, NONE, "z00c", "8/0"},
        {"SLA C", 0x21,      2, NONE, "z00c", "8/0"},
        {"SLA D", 0x22,      2, NONE, "z00c", "8/0"},
        {"SLA E", 0x23,      2, NONE, "z00c", "8/0"},
        {"SLA H", 0x24,      2, NONE, "z00c", "8/0"},
        {"SLA L", 0x25,      2, NONE, "z00c", "8/0"},
        {"SLA (HL)", 0x26,   2, NONE, "z00c", "8/0"},
        {"SLA A", 0x27,      2, NONE, "z00c", "8/0"},
        {"SRA B", 0x28,      2, NONE, "z000", "8/0"},
        {"SRA C", 0x29,      2, NONE, "z000", "8/0"},
        {"SRA D", 0x2a,      2, NONE, "z000", "8/0"},
        {"SRA E", 0x2b,      2, NONE, "z000", "8/0"},
        {"SRA H", 0x2c,      2, NONE, "z000", "8/0"},
        {"SRA L", 0x2d,      2, NONE, "z000", "8/0"},
        {"SRA (HL)", 0x2e,   2, NONE, "z000", "8/0"},
        {"SRA A", 0x2f,      2, NONE, "z000", "8/0"},
        {"SWAP B", 0x30,     2, NONE, "z000", "8/0"},
        {"SWAP C", 0x31,     2, NONE, "z000", "8/0"},
        {"SWAP D", 0x32,     2, NONE, "z000", "8/0"},
        {"SWAP E", 0x33,     2, NONE, "z000", "8/0"},
        {"SWAP H", 0x34,     2, NONE, "z000", "8/0"},
        {"SWAP L", 0x35,     2, NONE, "z000", "8/0"},
        {"SWAP (HL)", 0x36,  2, NONE, "z000", "8/0"},
        {"SWAP A", 0x37,     2, NONE, "z000", "8/0"},
        {"SRL B", 0x38,      2, NONE, "z00c", "8/0"},
        {"SRL C", 0x39,      2, NONE, "z00c", "8/0"},
        {"SRL D", 0x3a,      2, NONE, "z00c", "8/0"},
        {"SRL E", 0x3b,      2, NONE, "z00c", "8/0"},
        {"SRL H", 0x3c,      2, NONE, "z00c", "8/0"},
        {"SRL L", 0x3d,      2, NONE, "z00c", "8/0"},
        {"SRL (HL)", 0x3e,   2, NONE, "z00c", "8/0"},
        {"SRL A", 0x3f,      2, NONE, "z00c", "8/0"},
        {"BIT 0,B", 0x40,    2, NONE, "z01-", "8/0"},
        {"BIT 0,C", 0x41,    2, NONE, "z01-", "8/0"},
        {"BIT 0,D", 0x42,    2, NONE, "z01-", "8/0"},
        {"BIT 0,E", 0x43,    2, NONE, "z01-", "8/0"},
        {"BIT 0,H", 0x44,    2, NONE, "z01-", "8/0"},
        {"BIT 0,L", 0x45,    2, NONE, "z01-", "8/0"},
        {"BIT 0,(HL)", 0x46, 2, NONE, "z01-", "8/0"},
        {"BIT 0,A", 0x47,    2, NONE, "z01-", "8/0"},
        {"BIT 1,B", 0x48,    2, NONE, "z01-", "8/0"},
        {"BIT 1,C", 0x49,    2, NONE, "z01-", "8/0"},
        {"BIT 1,D", 0x4a,    2, NONE, "z01-", "8/0"},
        {"BIT 1,E", 0x4b,    2, NONE, "z01-", "8/0"},
        {"BIT 1,H", 0x4c,    2, NONE, "z01-", "8/0"},
        {"BIT 1,L", 0x4d,    2, NONE, "z01-", "8/0"},
        {"BIT 1,(HL)", 0x4e, 2, NONE, "z01-", "8/0"},
        {"BIT 1,A", 0x4f,    2, NONE, "z01-", "8/0"},
        {"BIT 2,B", 0x50,    2, NONE, "z01-", "8/0"},
        {"BIT 2,C", 0x51,    2, NONE, "z01-", "8/0"},
        {"BIT 2,D", 0x52,    2, NONE, "z01-", "8/0"},
        {"BIT 2,E", 0x53,    2, NONE, "z01-", "8/0"},
        {"BIT 2,H", 0x54,    2, NONE, "z01-", "8/0"},
        {"BIT 2,L", 0x55,    2, NONE, "z01-", "8/0"},
        {"BIT 2,(HL)", 0x56, 2, NONE, "z01-", "8/0"},
        {"BIT 2,A", 0x57,    2, NONE, "z01-", "8/0"},
        {"BIT 3,B", 0x58,    2, NONE, "z01-", "8/0"},
        {"BIT 3,C", 0x59,    2, NONE, "z01-", "8/0"},
        {"BIT 3,D", 0x5a,    2, NONE, "z01-", "8/0"},
        {"BIT 3,E", 0x5b,    2, NONE, "z01-", "8/0"},
        {"BIT 3,H", 0x5c,    2, NONE, "z01-", "8/0"},
        {"BIT 3,L", 0x5d,    2, NONE, "z01-", "8/0"},
        {"BIT 3,(HL)", 0x5e, 2, NONE, "z01-", "8/0"},
        {"BIT 3,A", 0x5f,    2, NONE, "z01-", "8/0"},
        {"BIT 4,B", 0x60,    2, NONE, "z01-", "8/0"},
        {"BIT 4,C", 0x61,    2, NONE, "z01-", "8/0"},
        {"BIT 4,D", 0x62,    2, NONE, "z01-", "8/0"},
        {"BIT 4,E", 0x63,    2, NONE, "z01-", "8/0"},
        {"BIT 4,H", 0x64,    2, NONE, "z01-", "8/0"},
        {"BIT 4,L", 0x65,    2, NONE, "z01-", "8/0"},
        {"BIT 4,(HL)", 0x66, 2, NONE, "z01-", "8/0"},
        {"BIT 4,A", 0x67,    2, NONE, "z01-", "8/0"},
        {"BIT 5,B", 0x68,    2, NONE, "z01-", "8/0"},
        {"BIT 5,C", 0x69,    2, NONE, "z01-", "8/0"},
        {"BIT 5,D", 0x6a,    2, NONE, "z01-", "8/0"},
        {"BIT 5,E", 0x6b,    2, NONE, "z01-", "8/0"},
        {"BIT 5,H", 0x6c,    2, NONE, "z01-", "8/0"},
        {"BIT 5,L", 0x6d,    2, NONE, "z01-", "8/0"},
        {"BIT 5,(HL)", 0x6e, 2, NONE, "z01-", "8/0"},
        {"BIT 5,A", 0x6f,    2, NONE, "z01-", "8/0"},
        {"BIT 6,B", 0x70,    2, NONE, "z01-", "8/0"},
        {"BIT 6,C", 0x71,    2, NONE, "z01-", "8/0"},
        {"BIT 6,D", 0x72,    2, NONE, "z01-", "8/0"},
        {"BIT 6,E", 0x73,    2, NONE, "z01-", "8/0"},
        {"BIT 6,H", 0x74,    2, NONE, "z01-", "8/0"},
        {"BIT 6,L", 0x75,    2, NONE, "z01-", "8/0"},
        {"BIT 6,(HL)", 0x76, 2, NONE, "z01-", "8/0"},
        {"BIT 6,A", 0x77,    2, NONE, "z01-", "8/0"},
        {"BIT 7,B", 0x78,    2, NONE, "z01-", "8/0"},
        {"BIT 7,C", 0x79,    2, NONE, "z01-", "8/0"},
        {"BIT 7,D", 0x7a,    2, NONE, "z01-", "8/0"},
        {"BIT 7,E", 0x7b,    2, NONE, "z01-", "8/0"},
        {"BIT 7,H", 0x7c,    2, NONE, "z01-", "8/0"},
        {"BIT 7,L", 0x7d,    2, NONE, "z01-", "8/0"},
        {"BIT 7,(HL)", 0x7e, 2, NONE, "z01-", "8/0"},
        {"BIT 7,A", 0x7f,    2, NONE, "z01-", "8/0"},
        {"RES 0,B", 0x80,    2, NONE, "----", "8/0"},
        {"RES 0,C", 0x81,    2, NONE, "----", "8/0"},
        {"RES 0,D", 0x82,    2, NONE, "----", "8/0"},
        {"RES 0,E", 0x83,    2, NONE, "----", "8/0"},
        {"RES 0,H", 0x84,    2, NONE, "----", "8/0"},
        {"RES 0,L", 0x85,    2, NONE, "----", "8/0"},
        {"RES 0,(HL)", 0x86, 2, NONE, "----", "8/0"},
        {"RES 0,A", 0x87,    2, NONE, "----", "8/0"},
        {"RES 1,B", 0x88,    2, NONE, "----", "8/0"},
        {"RES 1,C", 0x89,    2, NONE, "----", "8/0"},
        {"RES 1,D", 0x8a,    2, NONE, "----", "8/0"},
        {"RES 1,E", 0x8b,    2, NONE, "----", "8/0"},
        {"RES 1,H", 0x8c,    2, NONE, "----", "8/0"},
        {"RES 1,L", 0x8d,    2, NONE, "----", "8/0"},
        {"RES 1,(HL)", 0x8e, 2, NONE, "----", "8/0"},
        {"RES 1,A", 0x8f,    2, NONE, "----", "8/0"},
        {"RES 2,B", 0x90,    2, NONE, "----", "8/0"},
        {"RES 2,C", 0x91,    2, NONE, "----", "8/0"},
        {"RES 2,D", 0x92,    2, NONE, "----", "8/0"},
        {"RES 2,E", 0x93,    2, NONE, "----", "8/0"},
        {"RES 2,H", 0x94,    2, NONE, "----", "8/0"},
        {"RES 2,L", 0x95,    2, NONE, "----", "8/0"},
        {"RES 2,(HL)", 0x96, 2, NONE, "----", "8/0"},
        {"RES 2,A", 0x97,    2, NONE, "----", "8/0"},
        {"RES 3,B", 0x98,    2, NONE, "----", "8/0"},
        {"RES 3,C", 0x99,    2, NONE, "----", "8/0"},
        {"RES 3,D", 0x9a,    2, NONE, "----", "8/0"},
        {"RES 3,E", 0x9b,    2, NONE, "----", "8/0"},
        {"RES 3,H", 0x9c,    2, NONE, "----", "8/0"},
        {"RES 3,L", 0x9d,    2, NONE, "----", "8/0"},
        {"RES 3,(HL)", 0x9e, 2, NONE, "----", "8/0"},
        {"RES 3,A", 0x9f,    2, NONE, "----", "8/0"},
        {"RES 4,B", 0xa0,    2, NONE, "----", "8/0"},
        {"RES 4,C", 0xa1,    2, NONE, "----", "8/0"},
        {"RES 4,D", 0xa2,    2, NONE, "----", "8/0"},
        {"RES 4,E", 0xa3,    2, NONE, "----", "8/0"},
        {"RES 4,H", 0xa4,    2, NONE, "----", "8/0"},
        {"RES 4,L", 0xa5,    2, NONE, "----", "8/0"},
        {"RES 4,(HL)", 0xa6, 2, NONE, "----", "8/0"},
        {"RES 4,A", 0xa7,    2, NONE, "----", "8/0"},
        {"RES 5,B", 0xa8,    2, NONE, "----", "8/0"},
        {"RES 5,C", 0xa9,    2, NONE, "----", "8/0"},
        {"RES 5,D", 0xaa,    2, NONE, "----", "8/0"},
        {"RES 5,E", 0xab,    2, NONE, "----", "8/0"},
        {"RES 5,H", 0xac,    2, NONE, "----", "8/0"},
        {"RES 5,L", 0xad,    2, NONE, "----", "8/0"},
        {"RES 5,(HL)", 0xae, 2, NONE, "----", "8/0"},
        {"RES 5,A", 0xaf,    2, NONE, "----", "8/0"},
        {"RES 6,B", 0xb0,    2, NONE, "----", "8/0"},
        {"RES 6,C", 0xb1,    2, NONE, "----", "8/0"},
        {"RES 6,D", 0xb2,    2, NONE, "----", "8/0"},
        {"RES 6,E", 0xb3,    2, NONE, "----", "8/0"},
        {"RES 6,H", 0xb4,    2, NONE, "----", "8/0"},
        {"RES 6,L", 0xb5,    2, NONE, "----", "8/0"},
        {"RES 6,(HL)", 0xb6, 2, NONE, "----", "8/0"},
        {"RES 6,A", 0xb7,    2, NONE, "----", "8/0"},
        {"RES 7,B", 0xb8,    2, NONE, "----", "8/0"},
        {"RES 7,C", 0xb9,    2, NONE, "----", "8/0"},
        {"RES 7,D", 0xba,    2, NONE, "----", "8/0"},
        {"RES 7,E", 0xbb,    2, NONE, "----", "8/0"},
        {"RES 7,H", 0xbc,    2, NONE, "----", "8/0"},
        {"RES 7,L", 0xbd,    2, NONE, "----", "8/0"},
        {"RES 7,(HL)", 0xbe, 2, NONE, "----", "8/0"},
        {"RES 7,A", 0xbf,    2, NONE, "----", "8/0"},
        {"SET 0,B", 0xc0,    2, NONE, "----", "8/0"},
        {"SET 0,C", 0xc1,    2, NONE, "----", "8/0"},
        {"SET 0,D", 0xc2,    2, NONE, "----", "8/0"},
        {"SET 0,E", 0xc3,    2, NONE, "----", "8/0"},
        {"SET 0,H", 0xc4,    2, NONE, "----", "8/0"},
        {"SET 0,L", 0xc5,    2, NONE, "----", "8/0"},
        {"SET 0,(HL)", 0xc6, 2, NONE, "----", "8/0"},
        {"SET 0,A", 0xc7,    2, NONE, "----", "8/0"},
        {"SET 1,B", 0xc8,    2, NONE, "----", "8/0"},
        {"SET 1,C", 0xc9,    2, NONE, "----", "8/0"},
        {"SET 1,D", 0xca,    2, NONE, "----", "8/0"},
        {"SET 1,E", 0xcb,    2, NONE, "----", "8/0"},
        {"SET 1,H", 0xcc,    2, NONE, "----", "8/0"},
        {"SET 1,L", 0xcd,    2, NONE, "----", "8/0"},
        {"SET 1,(HL)", 0xce, 2, NONE, "----", "8/0"},
        {"SET 1,A", 0xcf,    2, NONE, "----", "8/0"},
        {"SET 2,B", 0xd0,    2, NONE, "----", "8/0"},
        {"SET 2,C", 0xd1,    2, NONE, "----", "8/0"},
        {"SET 2,D", 0xd2,    2, NONE, "----", "8/0"},
        {"SET 2,E", 0xd3,    2, NONE, "----", "8/0"},
        {"SET 2,H", 0xd4,    2, NONE, "----", "8/0"},
        {"SET 2,L", 0xd5,    2, NONE, "----", "8/0"},
        {"SET 2,(HL)", 0xd6, 2, NONE, "----", "8/0"},
        {"SET 2,A", 0xd7,    2, NONE, "----", "8/0"},
        {"SET 3,B", 0xd8,    2, NONE, "----", "8/0"},
        {"SET 3,C", 0xd9,    2, NONE, "----", "8/0"},
        {"SET 3,D", 0xda,    2, NONE, "----", "8/0"},
        {"SET 3,E", 0xdb,    2, NONE, "----", "8/0"},
        {"SET 3,H", 0xdc,    2, NONE, "----", "8/0"},
        {"SET 3,L", 0xdd,    2, NONE, "----", "8/0"},
        {"SET 3,(HL)", 0xde, 2, NONE, "----", "8/0"},
        {"SET 3,A", 0xdf,    2, NONE, "----", "8/0"},
        {"SET 4,B", 0xe0,    2, NONE, "----", "8/0"},
        {"SET 4,C", 0xe1,    2, NONE, "----", "8/0"},
        {"SET 4,D", 0xe2,    2, NONE, "----", "8/0"},
        {"SET 4,E", 0xe3,    2, NONE, "----", "8/0"},
        {"SET 4,H", 0xe4,    2, NONE, "----", "8/0"},
        {"SET 4,L", 0xe5,    2, NONE, "----", "8/0"},
        {"SET 4,(HL)", 0xe6, 2, NONE, "----", "8/0"},
        {"SET 4,A", 0xe7,    2, NONE, "----", "8/0"},
        {"SET 5,B", 0xe8,    2, NONE, "----", "8/0"},
        {"SET 5,C", 0xe9,    2, NONE, "----", "8/0"},
        {"SET 5,D", 0xea,    2, NONE, "----", "8/0"},
        {"SET 5,E", 0xeb,    2, NONE, "----", "8/0"},
        {"SET 5,H", 0xec,    2, NONE, "----", "8/0"},
        {"SET 5,L", 0xed,    2, NONE, "----", "8/0"},
        {"SET 5,(HL)", 0xee, 2, NONE, "----", "8/0"},
        {"SET 5,A", 0xef,    2, NONE, "----", "8/0"},
        {"SET 6,B", 0xf0,    2, NONE, "----", "8/0"},
        {"SET 6,C", 0xf1,    2, NONE, "----", "8/0"},
        {"SET 6,D", 0xf2,    2, NONE, "----", "8/0"},
        {"SET 6,E", 0xf3,    2, NONE, "----", "8/0"},
        {"SET 6,H", 0xf4,    2, NONE, "----", "8/0"},
        {"SET 6,L", 0xf5,    2, NONE, "----", "8/0"},
        {"SET 6,(HL)", 0xf6, 2, NONE, "----", "8/0"},
        {"SET 6,A", 0xf7,    2, NONE, "----", "8/0"},
        {"SET 7,B", 0xf8,    2, NONE, "----", "8/0"},
        {"SET 7,C", 0xf9,    2, NONE, "----", "8/0"},
        {"SET 7,D", 0xfa,    2, NONE, "----", "8/0"},
        {"SET 7,E", 0xfb,    2, NONE, "----", "8/0"},
        {"SET 7,H", 0xfc,    2, NONE, "----", "8/0"},
        {"SET 7,L", 0xfd,    2, NONE, "----", "8/0"},
        {"SET 7,(HL)", 0xfe, 2, NONE, "----", "8/0"},
        {"SET 7,A", 0xff,    2, NONE, "----", "8/0"},
}; 

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
        {"JR C,r8 ", 0x38, 2, r8, "----", "1/0"},
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
        {"CBPREFIX", 0xcb, 2, d8, "----", "1/0"},
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

_INC_REG(b)
_INC_REG(d)
_INC_REG(h)
_INC_REG(c)
_INC_REG(e)
_INC_REG(l)
_INC_REG(a)


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

_LD_REG16_REG(de,a)
_LD_REG16_REG(bc,a)

_LD_REG_REGA16(d,hl)

_CB_SWAP(b)
_CB_SWAP(c)
_CB_SWAP(d)
_CB_SWAP(e)
_CB_SWAP(h)
_CB_SWAP(l)
_CB_SWAP(a)

_XOR_REG(b)
_XOR_REG(c)
_XOR_REG(d)
_XOR_REG(e)
_XOR_REG(h)
_XOR_REG(l)
_XOR_REG(a)

_AND_REG(b)
_AND_REG(c)
_AND_REG(d)
_AND_REG(e)
_AND_REG(h)
_AND_REG(l)
_AND_REG(a)

_ADD_A_REG(b)
_ADD_A_REG(c)
_ADD_A_REG(d)
_ADD_A_REG(e)
_ADD_A_REG(h)
_ADD_A_REG(l)
_ADD_A_REG(a)

_POP_REG_16(bc)
_POP_REG_16(de)
_POP_REG_16(hl)
_POP_REG_16(af)//This is the weird one. Need to do some bit magic to handle it if it comes up, since I'm not emulating the f register normally.

_PUSH_REG_16(bc)
_PUSH_REG_16(de)
_PUSH_REG_16(hl)
_PUSH_REG_16(af)

_ADD_REG16_REG16(hl,de)
_ADD_REG16_REG16(hl,hl)
_ADD_REG16_REG16(hl,sp)
_ADD_REG16_REG16(hl,bc)

_LD_REG_VALUE_AT_ADDR_IN_HL(c)
_LD_REG_VALUE_AT_ADDR_IN_HL(e)
_LD_REG_VALUE_AT_ADDR_IN_HL(l)
_LD_REG_VALUE_AT_ADDR_IN_HL(a)
_LD_REG_VALUE_AT_ADDR_IN_HL(b)
_LD_REG_VALUE_AT_ADDR_IN_HL(d)
_LD_REG_VALUE_AT_ADDR_IN_HL(h)

_INC_REG16(bc)
_INC_REG16(de)
_INC_REG16(hl)
_INC_REG16(sp)

void init_cpu(cpu_state * state, struct romBytes * bytes)
{
//
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

void fetch_instruction(cpu_state *state, struct romBytes *r)
{
        state->curr_inst = instructions[state->address_space[state->regs.pc]];
        

        switch (instructions[state->address_space[state->regs.pc]].d_type)
        {
        case a16:

            uint8_t d1 = r->bytes[state->regs.pc + 1];
            uint8_t d2 = r->bytes[state->regs.pc + 2];

            uint16_t toConvert = (d2 << 8) | d1;

            state->fetched_data = toConvert;

            break;
        case d8:

            state->fetched_data = r->bytes[state->regs.pc + 1];

            break;
        case d16:

            uint8_t d3 = r->bytes[state->regs.pc + 1];
            uint8_t d4 = r->bytes[state->regs.pc + 2];

            uint16_t toConvert1 = (d4 << 8) | d3;

            state->fetched_data = toConvert1;
            break;

        case a8:

            state->fetched_data = r->bytes[state->regs.pc + 1];
            break;

        case r8:

            state->fetched_data_8_signed = (int8_t)r->bytes[state->regs.pc + 1];
            // state.regs.pc += r->bytes[state.regs.pc + 1];

            break;

        case NONE:

            state->fetched_data = 0x0;

            break;

        default:

            // exit(0);
            break;
        }

        //printf("0x%x : 0x%x %s %x \n", state->regs.pc, state->curr_inst.op_code, state->curr_inst.mnmemonic, state->fetched_data);
}

void call_func(cpu_state * state, instruction ins, struct romBytes * bytes)
{
    switch(ins.op_code)
    {
    case 0xff:
    case 0xef:
    case 0xdf:
    case 0xcf:
    case 0xf7:
    case 0xe7:
    case 0xd7:
    case 0x3:
        _INC_bc(state);
        state->regs.pc += ins.length;
        break;

    case 0xc5:
        _PUSH_bc(state);
        state->regs.pc += ins.length;
        break;
    case 0xc7:
        rst(state);
        break;
    case 0x3c:
        _INC_a(state);
        state->regs.pc += ins.length;
        break;

    case 0x77:
        _LD_a_AT_HL(state);
        state->regs.pc += ins.length;
        break;

    case 0xf1:
        _POP_af(state);
        state->regs.pc += ins.length;
        break;

    case 0xf5:
        _PUSH_af(state);
        state->regs.pc += ins.length;
        break;

    case 0xe5:
        _PUSH_hl(state);
        state->regs.pc += ins.length;
        break;

    case 0x18:
        jr_r8(state);
        break;

    case 0x7c:
        _LD_a_h(state);
        state->regs.pc += ins.length;
        break;

    case 0x7d:
        _LD_a_l(state);
        state->regs.pc += ins.length;
        break;

    case 0xc1:
        _POP_bc(state);
        state->regs.pc += ins.length;
        break;

    case 0x8:
        ld_a16_SP(state);
        state->regs.pc += ins.length;
        break;
    case 0xe9:
        jp_hl_addr(state);
        break;

    case 0xd5:
        _PUSH_de(state);
        state->regs.pc += ins.length;
        break;
    
    case 0x23:
        _INC_hl(state);
        state->regs.pc += ins.length;
        break;

    case 0x5e:
        _LD_h_AT_HL(state);
        state->regs.pc += ins.length;
        break;
        
    case 0x19:
        _ADD_hl_de(state);
        state->regs.pc += ins.length;
        break;

    case 0x5f:
        _LD_e_a(state);
        state->regs.pc += ins.length;
        break;

    case 0xe1:
        _POP_hl(state);
        state->regs.pc += ins.length;
        break;

    case 0x87:
        _ADD_A_a(state);
        state->regs.pc += ins.length;
        break;

    case 0x79:
            _LD_a_c(state);
            state->regs.pc += ins.length;
            break;

    case 0xa1:
            _AND_c(state);
            state->regs.pc += ins.length;
            break;
    case 0xa9:
            _XOR_c(state);
            state->regs.pc += ins.length;
            break;

    case 0x4f:
            _LD_c_a(state);
            state->regs.pc += ins.length;
            break;

    case 0xcb:

            call_cb_func(state,cb_instructions[state->fetched_data]);
            break;

    case 0xe6:
            and_d8(state);
            state->regs.pc += ins.length;
            break;

    case 0x2f:
            cpl(state);
            state->regs.pc += ins.length;
            break;
    
    case 0xfb:
            state->interrupt_master_enable = 1;
            state->regs.pc += ins.length;
            break;

    case 0x61:
            _LD_h_c(state);
            state->regs.pc += ins.length;
            break;
    case 0x02:
            ld_data_at_addr_bc_a(state);
            state->regs.pc += ins.length;
            break;

    case 0x56:
            _LD_d_hl(state);
            state->regs.pc += ins.length;
            break;

    case 0x4b:
            _LD_c_e(state);
            state->regs.pc += ins.length;
            break;

    case 0x40:
            _LD_b_b(state);
            state->regs.pc += ins.length;
            break;

    case 0x38:
            jr_c_r8(state);
            
            break;

    case 0x30:
            jr_nc_r8(state);
            
            break;

    case 0x28:
            jr_z_r8(state);
            break;

    case 0x1c:
            _INC_e(state);
            state->regs.pc += ins.length;
            break;

    case 0x12:
            ld_data_at_addr_de_a(state);
            state->regs.pc += ins.length;
            break;

    case 0x11:
            _LD_de_d16(state);
            state->regs.pc += ins.length;
            break;

    case 0x47:
            _LD_b_a(state);
            state->regs.pc += ins.length;
            break;

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
            _XOR_a(state);
            state->regs.pc += ins.length;
            break;

    case 0x0:
            state->regs.pc += ins.length;
            break;

    default:
            printf("Non implemented instruction at 0x%x: 0x%x %s\n", state->regs.pc, ins.op_code, ins.mnmemonic);
            state->halt = 1; //
            break;
    }

    if(state->regs.pc > 0xffff)
    {
        //PC somehow ended up outside of our address space. die.
        state->halt = 1;
    }
}

void call_cb_func(cpu_state *state, instruction ins)
{

    switch(ins.op_code)
    {
        case 0x37:
        _SWAP_a(state);
        break;


        default:
            printf("Non implemented CB instruction at 0x%x: 0x%x %s\n", state->regs.pc, ins.op_code, ins.mnmemonic);
            state->halt = 1; //
            break;
        
    }

    state->regs.pc += ins.length;//This will always be two. Fisrt byte is cb prefix, second byte is op-code.
}

void ld_data_at_addr_de_a(cpu_state * state)
{
    state->address_space[state->regs.de] = state->regs.a;
}

void ld_data_at_addr_bc_a(cpu_state *state)
{
    state->address_space[state->regs.bc] = state->regs.a;
}

void ld_a16_SP(cpu_state *state)
{
    state->regs.sp = state->fetched_data;
    state->cycles += get_instruction_cycles(state->curr_inst, 1);
}

void ret(cpu_state * state)
{
    state->regs.pc = stack_pop_16(state);
}

void jr_r8(cpu_state *state)
{   
    //This seems hackish but it isn't. The CPU of the gameboy increments the PC by two before this jump, since two is the length of the instruction.
    state->regs.pc += state->curr_inst.length;
    state->regs.pc += state->fetched_data_8_signed;
}

void call_a16(cpu_state * state)
{

    state->regs.pc += 3;

    //printf("pc:%2x \n",state->regs.pc);

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

    if(addr == 0xff01)
    {
        FILE *out = fopen("test.txt", "a");
        fprintf(out, "%x\n", state->regs.a);
        fclose(out);
    }
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

void rst(cpu_state *state)
{
    uint8_t addr;
    switch(state->curr_inst.op_code)
    {
        case 0xFF:
        addr = 0x38;
        break;

        case 0xef:
        addr = 0x28;
        break;

        case 0xdf:
        addr = 0x18;
        break;

        case 0xcf:
        addr = 0x08;
        break;

        case 0xc7:
        addr = 0x0;
        break;

        case 0xd7:
        addr = 0x10;
        break;

        case 0xe7:
        addr = 0x20;
        break;

        case 0xf7:
        addr = 0x30;
        break;

        default:break;
    }

    stack_push16(state->regs.pc, state);

    state->regs.pc = addr;

}

void cpl(cpu_state *state)
{
    state->regs.a = ~(state->regs.a);

    set_flag(1, "n", state);
    set_flag(1, "h", state);
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

void and_d8(cpu_state *state)
{
    uint8_t result = state->regs.a & state->fetched_data;

    state->regs.a = result;

    if(result == 0)
    {
        set_flag(1, "z", state);
    }
    else
    {
        set_flag(0, "z", state);
    }

    set_flag(0, "n", state);
    set_flag(1, "h", state);
    set_flag(0, "c", state);
}

void cp_d8(cpu_state * state)
{

    int result = state->regs.a - state->fetched_data;
    uint8_t umm = state->fetched_data;

    if( result == 0){state->regs.z_flag = 1;}
    else{state->regs.z_flag = 0;}

    state->regs.n_flag = 1;

    if((umm & 0xF) > (result & 0xF)){state->regs.h_flag = 1;}
    else{state->regs.h_flag = 0;}

    if((umm & 0xFF) > (result & 0xFF)){state->regs.c_flag = 1;}
    else{state->regs.c_flag = 0;}


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

void jp_hl_addr(cpu_state *state)
{
    state->regs.pc = state->regs.hl;
    state->cycles += get_instruction_cycles(state->curr_inst, 1);

}

// void xor_a(cpu_state * state)
// {
//     //This is effectively a NOP

//     uint8_t result = state->regs.a ^ state->regs.a;
//     state->regs.a = result;

//     if(result == 0)
//     {
//         set_flag(1, "z", state);
//     }
//     else
//     {
//         set_flag(0, "z", state);
//     }

//     set_flag(0,"n",state);
//     set_flag(0,"h",state);
//     set_flag(0,"c",state);

//     state->cycles += get_instruction_cycles(state->curr_inst, 1);
// }


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
        state->regs.pc += state->curr_inst.length;
        state->regs.pc += toJump;//
        state->cycles += get_instruction_cycles(state->curr_inst, 1);
    }
    else
    {
        state->regs.pc += 2;
        state->cycles += get_instruction_cycles(state->curr_inst, 0);
    }

}

void jr_nc_r8(cpu_state *state)
{
    int toJump = state->fetched_data_8_signed;

    //printf("tojump: %d", -(~toJump + 1) + 2);
    
    if(state->regs.c_flag == 0)
    {
        state->regs.pc += state->curr_inst.length;
        state->regs.pc += toJump;//
        state->cycles += get_instruction_cycles(state->curr_inst, 1);
    }
    else
    {
        state->regs.pc += 2;
        state->cycles += get_instruction_cycles(state->curr_inst, 0);
    }
}

void jr_z_r8(cpu_state *state)
{
    int toJump = state->fetched_data_8_signed;

    //printf("tojump: %d", -(~toJump + 1) + 2);
    
    if(state->regs.z_flag == 1)
    {
        state->regs.pc += state->curr_inst.length;
        state->regs.pc += toJump;//
        state->cycles += get_instruction_cycles(state->curr_inst, 1);
    }
    else
    {
        state->regs.pc += 2;
        state->cycles += get_instruction_cycles(state->curr_inst, 0);
    }
}

void jr_c_r8(cpu_state *state)
{

    int toJump = state->fetched_data_8_signed;

    if(state->regs.c_flag == 1)
    {
        state->regs.pc += state->curr_inst.length;
        state->regs.pc += toJump;//
        state->cycles += get_instruction_cycles(state->curr_inst, 1);
    }
    else
    {
        state->regs.pc += 2;
        state->cycles += get_instruction_cycles(state->curr_inst, 0);
    }
}
