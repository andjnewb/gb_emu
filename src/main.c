#include <stdio.h>
#include <string.h>
#include "disassemble.h"

int main(int argc, char *argv[])
{
    struct romBytes r;
    
   
    r = getBytes("tetris.gb");

    printf("Bytes = ");
    for(int i = 0; i < r.sizeInBytes; i++)
        printf("%u ", r.bytes[i]);
    printf("\n");
    //free(r.bytes);
}
