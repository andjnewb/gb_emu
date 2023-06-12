#ifndef PPU_H_
#define PPU_H_

#define MAX_LY 153

#include "cpu.h"
#include "util.h"



enum LCDC
{
    BG_ENABLED,//Background enabled
    SPRITES_ENABLED,
    SPRITE_SIZE,//0 = 8x8, 1 = 8x16
    BG_TILE_MAP,//0 = 0x9800 - 0x9bff, 1 = 0x9c00, 0x9fff
    BG_AND_WINDOW_TILESET,  // 0=8800h-97FFh, 1=8000h-8FFFh
    WINDOW_ENABLE,
    WINDOW_TILE_MAP, //0=9800h-9BFFh, 1=9C00h-9FFFh
    LCD_POWER
};

enum LCD_STAT
{
    SCREEN_MODE_1,
    SCREEN_MODE_2,
    LY_EQUALS_LYC_FLAG,
    H_BLANK_STAT_SOURCE,
    V_BLANK_STAT_SOURCE,
    OAM_STAT_SOURCE,
    LY_LYC_STAT_SOURCE,
};

typedef struct 
{
    uint8_t * lcd_ly;
    uint8_t * ly_comp;
    uint8_t * lcd_stat;
    uint8_t * lcd_ctl;

    uint8_t * enabled;
    uint8_t in_vblank;
}ppu_state;


void init_ppu(cpu_state * _cpu_state, ppu_state * _ppu_state);
void get_lcd_regs(cpu_state * state, int regs[8]);
int get_lcd_ly(cpu_state * state);
void ppu_cycle(cpu_state * _cpu_state, ppu_state * _ppu_state);
#endif