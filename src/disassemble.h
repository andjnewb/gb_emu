#ifndef DISSASEMBLE_H
#define DISSASEMBLE_H
#include <stdio.h>
#include <stdlib.h>

struct romMetaData
{
    unsigned char * title;
    u_int8_t logo[48];
};

struct romBytes
{
    u_int8_t * bytes;
    int sizeInBytes;
    struct romMetaData metaData;
};


int getSizeInBytes(char * fileName);
struct romBytes getBytes(char * fileName); 
struct romMetaData getMetaData(struct romBytes * bytes);

#endif
