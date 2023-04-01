#include <stdio.h>
#include <string.h>
#include "disassemble.h"
#include <inttypes.h>
#include <stdint.h>
#include "cpu.h"

int main(int argc, char *argv[])
{
    struct romBytes * r = malloc(sizeof(struct romBytes));
    cpu_state state;

    init_cpu(&state, r);
   
    *r = getBytes("tetris.gb");
    r->metaData = getMetaData(r);

    printf("REGISTERS:\n");
    printf("A: 0x%x ", state.regs.a);
    printf("B: 0x%x ", state.regs.b);
    printf("C: 0x%x ", state.regs.c);
    printf("D: 0x%x ", state.regs.d);
    printf("E: 0x%x ", state.regs.e);
    printf("F: 0x%x ", state.regs.f);
    printf("H: 0x%x ", state.regs.h);
    printf("L: 0x%x ", state.regs.l);
    printf("PC: 0x%x ", state.regs.pc);
    printf("SP: 0x%x ", state.regs.sp);


    
    // //printf("Title = %s", r->metaData.title);
    // FILE * out = fopen( "out.hex", "w");
    // //for(int i = 0; i < 48; i++)
    //     //printf("%x", r->metaData.logo[i]);
    // fwrite(r->bytes, r->sizeInBytes, sizeof(uint8_t), out);
    // //printf("\n");
    // //free(r.bytes);
    // fclose(out);
}
