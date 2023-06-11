#include "ppu.h"

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
    _ppu_state->lcd_ly++;
    _cpu_state->address_space[0xff44] = _ppu_state->lcd_ly;

    _ppu_state->ly_comp = _cpu_state->address_space[0xff45];

    if(_ppu_state->lcd_ly == _ppu_state->ly_comp)
    {
        _cpu_state->address_space[0xff41] = setBit(_cpu_state->address_space[0xff41], 2);//Set LYC=LY FLAG
        

        if(checkBit(_cpu_state->address_space[0xff41], ))
        {
            
        }
    } 
}