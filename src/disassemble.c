#include "disassemble.h"
#include <sys/stat.h>
#include <string.h>
int getSizeInBytes(char * fileName)
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        printf("Cannot open source file.\n");
        exit(1);
    }
 
    struct stat st;
    int fd = fileno(fp);    // get file descriptor
    fstat(fd, &st);
    fclose(fp);

    return (int) st.st_size;//Should change this but it doesn't like off_t as return type.
}

struct romBytes getBytes(char * fileName)
{
    struct romBytes rom;

    FILE *filePtr;
    unsigned char * buffer;
    int fileLen = getSizeInBytes(fileName);

    rom.sizeInBytes = fileLen;

    filePtr = fopen(fileName, "rb");

    buffer = (unsigned char *)malloc(fileLen * sizeof(unsigned char));
    rom.bytes = (unsigned char *)malloc(fileLen * sizeof(unsigned char));
    fread(buffer, fileLen, 1, filePtr);

    //rom.bytes = buffer;
    
    for(int i = 0; i < fileLen; i+8)
    {
        buffer[i] = __ntohl(buffer[i]);//TODO, FIX
    }

    memcpy(rom.bytes, buffer, fileLen);
    //printf("%u", buffer[0]);

    fclose(filePtr);

    free(buffer);

    return rom;

}