#include <stdio.h>
#include <string.h>
#include "disassemble.h"
#include <inttypes.h>

int main(int argc, char *argv[])
{
    struct romBytes * r = malloc(sizeof(struct romBytes));
    
   
    *r = getBytes("tetris.gb");
    r->metaData = getMetaData(r);

    
    //printf("Title = %s", r->metaData.title);
    //FILE * out = fopen( "out.hex", "w");
    //for(int i = 0; i < 48; i++)
        //printf("%x", r->metaData.logo[i]);
    //fwrite(r->bytes, r->sizeInBytes, sizeof(unsigned char), out);
    //printf("\n");
    //free(r.bytes);
    //fclose(out);
}
