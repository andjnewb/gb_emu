#include <stdio.h>
#include <string.h>
#include "disassemble.h"
#include <inttypes.h>

int main(int argc, char *argv[])
{
    struct romBytes r;
    
   
    r = getBytes("tetris.gb");
    

    
    printf("Bytes = ");
    FILE * out = fopen( "out.hex", "w");
    for(int i = 0; i < r.sizeInBytes; i++)
        printf("0x%x", r.bytes[i]);
    fwrite(r.bytes, r.sizeInBytes, sizeof(unsigned char), out);
    //printf("\n");
    //free(r.bytes);
    fclose(out);
}
