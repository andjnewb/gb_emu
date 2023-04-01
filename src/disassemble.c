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
    uint16_t * buffer;
    int fileLen = getSizeInBytes(fileName);

    rom.sizeInBytes = fileLen;

    filePtr = fopen(fileName, "rb");

    buffer = (uint16_t *)malloc(fileLen * sizeof(uint16_t));
    rom.bytes = (uint16_t *)malloc(fileLen * sizeof(uint16_t));
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

    //Memcpy hell
    metaData.title = malloc(16);//TODO:Remove magic numbers
    memcpy(metaData.title, bytes->bytes + 0x134, 16);
    memcpy(metaData.logo, bytes->bytes + 0x104, 48);
    memcpy(metaData.mf_code, bytes->bytes + 0x13F, 3);
    memcpy(metaData.new_licensee_code, bytes->bytes + 0x144, 2);
    memcpy(metaData.global_checksum, bytes->bytes + 0x14E, 2);
    
    
    metaData.cgb_flag = bytes->bytes[0x143];
    metaData.sgb_flag = bytes->bytes[0x146];
    metaData.cart_type = bytes->bytes[0x147];
    metaData.rom_size = bytes->bytes[0x148];
    metaData.ram_size = bytes->bytes[0x149];
    metaData.dest_code = bytes->bytes[0x14A];
    metaData.old_license_code = bytes->bytes[0x14B];
    metaData.game_version = bytes->bytes[0x14C];
    metaData.header_checksum = bytes->bytes[0x14D];

    //printf("Title:%s\nManufacturer Code:%x\nNew Licensee Code:%s\nGlobal Checksum:%s\nCGB Flag:%x\n SGB Flag:%x\n Cart Type:%x\nROM Size(From Header):%x\nRAM Size:%x\nDestination Code:%x\nOld Licensee Code:%x\nGame Version:%x\nHead Checksum:%x\n",metaData.title, metaData.mf_code, metaData.new_licensee_code, metaData.global_checksum, metaData.cgb_flag, metaData.sgb_flag, metaData.cart_type, metaData.rom_size, metaData.ram_size, metaData.dest_code,metaData.old_license_code, metaData.game_version, metaData.header_checksum);
    printf("Title:%s\n", metaData.title);
    printf("ROM Size:%dKiB\n", 32 * (1 << metaData.rom_size));
    printf("RAM Size(See Table For KiB Value):%x\n", metaData.ram_size);
    printf("New Licensee Code(See Table):%s\n", metaData.new_licensee_code);
    printf("Old Licensee Code(Use New Licensee if 0x33)(See Table):0x%x\n", metaData.old_license_code);
    printf("Cart Type(See Table):%x\n", metaData.cart_type);


    return metaData;
}

uint8_t rom_fetch_op_at(uint16_t addr, struct romBytes * bytes)
{
    bytes->bytes[addr];
}
