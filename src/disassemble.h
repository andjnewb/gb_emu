#ifndef DISSASEMBLE_H
#define DISSASEMBLE_H
#include <stdio.h>
#include <stdlib.h>

struct romMetaData
{
    int title;

};

struct romBytes
{
    unsigned char * bytes;
    int sizeInBytes;
    struct romMetaData metaData;
};


int getSizeInBytes(char * fileName);
struct romBytes getBytes(char * fileName); //Will perform endianess conversion

#endif
