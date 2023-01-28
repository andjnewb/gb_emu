#ifndef DISSASEMBLE_H
#define DISSASEMBLE_H
#include <stdio.h>
#include <stdlib.h>

struct romMetaData
{
    unsigned char * title;
    u_int8_t logo[0x2F];
    u_int8_t mf_code[3];
    u_int8_t cgb_flag;
    u_int8_t new_licensee_code[2];
    u_int8_t sgb_flag;//supre gameboy flag
    u_int8_t cart_type;
    u_int8_t rom_size;//Size as reported by the cartridge metaData byte
    u_int8_t ram_size;//Additional ram provided by cartridge
    u_int8_t dest_code;//Japan 0x0 Rest of world 0x01
    u_int8_t old_license_code;//A value of 0x33 means the new licensee code should be used instead
    u_int8_t game_version;
    u_int8_t header_checksum;
    u_int8_t global_checksum[2];

};

struct romBytes
{
    u_int8_t * bytes;//Should change this, confusing
    int sizeInBytes;//Size as measured by read
    struct romMetaData metaData;
};


int getSizeInBytes(char * fileName);//Get size in bytes of fileName
struct romBytes getBytes(char * fileName); //Get bytes from file
struct romMetaData getMetaData(struct romBytes * bytes);//Used for loading meta data into romByte struct

#endif