#include "ppu.h"

void init_ppu(cpu_state *_cpu_state, ppu_state *_ppu_state)
{
    _ppu_state->lcd_ly = &_cpu_state->address_space[0xff44];//This is the LY Register.
    _ppu_state->ly_comp = &_cpu_state->address_space[0xff45];//This is the LYC register.

    _ppu_state->lcd_stat = &_cpu_state->address_space[0xff41];

}

void get_lcd_regs(cpu_state *state, int regs[8])
{
    regs[0] = ((state->address_space[0xff40]) >> 0) & 1;
    regs[1] = ((state->address_space[0xff40]) >> 1) & 1;
    regs[2] = ((state->address_space[0xff40]) >> 2) & 1;
    regs[3] = ((state->address_space[0xff40]) >> 3) & 1;
    regs[4] = ((state->address_space[0xff40]) >> 4) & 1;
    regs[5] = ((state->address_space[0xff40]) >> 5) & 1;
    regs[6] = ((state->address_space[0xff40]) >> 6) & 1;
    regs[7] = ((state->address_space[0xff40]) >> 7) & 1;
}

int get_lcd_ly(cpu_state *state)
{
    return state->address_space[0xff44];
}

void ppu_cycle(cpu_state * _cpu_state, ppu_state * _ppu_state)
{
     (*_ppu_state->lcd_ly) += 1;

    // if(*_ppu_state->lcd_ly == *_ppu_state->ly_comp)
    // {
    //     *_ppu_state->lcd_stat = setBit(*_ppu_state->lcd_stat, LY_EQUALS_LYC_FLAG);//Set LYC=LY FLAG
        

    //     if(checkBit(*_ppu_state->lcd_stat, LY_LYC_STAT_SOURCE) == 1)
    //     {
    //         request_interrupt(_cpu_state, LY_EQUALS_LYC_FLAG);
    //     }

    //     (*_ppu_state->lcd_ly)++;
    // }
    // else if(*_ppu_state->lcd_ly > MAX_LY)
    // {
    //     (*_ppu_state->lcd_ly) = 0;
    // }
    // else
    // {
    //     (*_ppu_state->lcd_ly)++;
    // } 


    printf("LCD Status: \n");
    printf("Interrupt sources: LYC=LY STAT:%d Mode 2 OAM STAT:%d Mode 1 VBlank STAT:%d Mode 0 HBlank STAT:%d\n", checkBit(*_ppu_state->lcd_stat, LY_LYC_STAT_SOURCE), checkBit(*_ppu_state->lcd_stat, OAM_STAT_SOURCE), checkBit(*_ppu_state->lcd_stat, V_BLANK_STAT_SOURCE), checkBit(*_ppu_state->lcd_stat, H_BLANK_STAT_SOURCE));
    printf("LY:%d LYC:%d LYC=LY FLAG:%d\n", *_ppu_state->lcd_ly, *_ppu_state->ly_comp, checkBit(*_ppu_state->lcd_stat, LY_EQUALS_LYC_FLAG));
}