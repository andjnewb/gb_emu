0x100 : 0 NOP 0 
0x101 : c3 JP A16 150 
0x150 : c3 JP A16 20c 
0x20c : af XOR A 0 
0x20d : 21 LD HL,d16 ffffdfff 
0x210 : e LD C,d8 10 
0x212 : 6 LD B,d8 0 
0x214 : 32 LD (HL-),A 0 
0x215 : 5 DEC B 0 
0x216 : 20 JR NZ,r8 fc 
0x312 : 1d DEC E 0 
0x313 : 16 LD D,d8 1f 
0x315 : 1f RRA 0 
0x316 : 1f RRA 0 
0x317 : 25 DEC H 0 
0x319 : b0 OR B 0 
0x31a : 14 INC D 0 
