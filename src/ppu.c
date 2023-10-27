#include "ppu.h"

void init_ppu(cpu_state *_cpu_state, ppu_state *_ppu_state)
{
    _ppu_state->lcd_ly = &_cpu_state->address_space[LY_REG_ADDR];//This is the LY Register.
    _ppu_state->ly_comp = &_cpu_state->address_space[LYC_REG_ADDR];//This is the LYC register.

    //Scrolling registers
    _ppu_state->scx = &_cpu_state->address_space[SCX_REG_ADDR];
    _ppu_state->scy = &_cpu_state->address_space[SCY_REG_ADDR];

    _ppu_state->lcd_stat = &_cpu_state->address_space[0xff41];
    
    _ppu_state->tile_map_loc  = (checkBit(_cpu_state->address_space[LCD_CTL_ADDR], BG_TILE_MAP) == 1) ? 0x9c00 : 0x9800;
    _ppu_state->tile_data_loc  = (checkBit(_cpu_state->address_space[LCD_CTL_ADDR], BG_AND_WINDOW_TILESET) == 1) ? 0x8000 : 0x8800;
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
    //(*_ppu_state->lcd_ly)++;

    if(*_ppu_state->lcd_ly == *_ppu_state->ly_comp)
    {
        *_ppu_state->lcd_stat = setBit(*_ppu_state->lcd_stat, LY_EQUALS_LYC_FLAG);//Set LYC=LY FLAG
       
        if(checkBit(*_ppu_state->lcd_stat, LY_LYC_STAT_SOURCE) == 1)
        {
            request_interrupt(_cpu_state, LCD_STAT_F);
        }
   
        
    
    }
    else
    {
        *_ppu_state->lcd_stat = clearBit(*_ppu_state->lcd_stat, LY_EQUALS_LYC_FLAG);
        
    }



    if(*_ppu_state->lcd_ly > 143)
    {
        //Bit 1-0 of lcd_stat indicate which mode we are in. Here we, want to indicate we are in VBlank with 01.
        *_ppu_state->lcd_stat = clearBit(*_ppu_state->lcd_stat, 1);
        *_ppu_state->lcd_stat = setBit(*_ppu_state->lcd_stat, 0);
        
    }
    else
    {
        
        *_ppu_state->lcd_stat = clearBit(*_ppu_state->lcd_stat, 1);
        *_ppu_state->lcd_stat = clearBit(*_ppu_state->lcd_stat, 0);
        
   
    }
    if(*_ppu_state->lcd_ly > MAX_LY)
    {
        (*_ppu_state->lcd_ly) = 0;
    }


    

    printf("LCD Status: \n");
    printf("Interrupt sources: LYC=LY STAT:%d Mode 2 OAM STAT:%d Mode 1 VBlank STAT:%d Mode 0 HBlank STAT:%d\n", checkBit(*_ppu_state->lcd_stat, LY_LYC_STAT_SOURCE), checkBit(*_ppu_state->lcd_stat, OAM_STAT_SOURCE), checkBit(*_ppu_state->lcd_stat, V_BLANK_STAT_SOURCE), checkBit(*_ppu_state->lcd_stat, H_BLANK_STAT_SOURCE));
    printf("LY:%3d LYC:%3d LYC=LY FLAG:%3d\n", *_ppu_state->lcd_ly, *_ppu_state->ly_comp, checkBit(*_ppu_state->lcd_stat, LY_EQUALS_LYC_FLAG));
   
}