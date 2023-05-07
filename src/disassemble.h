#ifndef DISSASEMBLE_H
#define DISSASEMBLE_H
#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"
struct romMetaData
{
    unsigned char * title;
    uint8_t logo[0x2F];
    uint8_t mf_code[3];
    uint8_t cgb_flag;
    uint8_t new_licensee_code[2];
    uint8_t sgb_flag;//supre gameboy flag
    uint8_t cart_type;
    uint8_t rom_size;//Size as reported by the cartridge metaData byte
    uint8_t ram_size;//Additional ram provided by cartridge
    uint8_t dest_code;//Japan 0x0 Rest of world 0x01
    uint8_t old_license_code;//A value of 0x33 means the new licensee code should be used instead
    uint8_t game_version;
    uint8_t header_checksum;
    uint8_t global_checksum[2];

};
 struct romBytes
{
    uint8_t * bytes;//Should change this, confusing
    int sizeInBytes;//Size as measured by read
    struct romMetaData metaData;
};


int getSizeInBytes(char * fileName);//Get size in bytes of fileName
struct romBytes getBytes(char * fileName); //Get bytes from file
struct romMetaData getMetaData(struct romBytes * bytes);//Used for loading meta data into romByte struct


#endif