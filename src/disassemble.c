#include "disassemble.h"
#include <sys/stat.h>
#include <string.h>
#include <byteswap.h>
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
    u_int8_t * buffer;
    int fileLen = getSizeInBytes(fileName);

    rom.sizeInBytes = fileLen;

    filePtr = fopen(fileName, "rb");

    buffer = (u_int8_t *)malloc(fileLen * sizeof(u_int8_t));
    rom.bytes = (u_int8_t *)malloc(fileLen * sizeof(u_int8_t));
    fread(buffer, fileLen, 1, filePtr);

    rom.bytes = buffer;
    // rom.metaData.title = malloc(16);
    // memcpy(rom.metaData.title, buffer + 0x134, 16);

    memcpy(rom.bytes, buffer, fileLen);
    //printf("%u", buffer[0]);

    fclose(filePtr);

    //free(buffer);

    return rom;

}

struct romMetaData getMetaData(struct romBytes * bytes)
{
    struct romMetaData metaData;

    //Malloc hell
    metaData.title = malloc(16);
    memcpy(metaData.title, bytes->bytes + 0x134, 16);

    for(int i = 0x104; i <= 0x133; i++)
    {
        printf("%x",bytes->bytes[i]);//TODO:Find way to copy this to logo in rom header
    }

    return metaData;
}
