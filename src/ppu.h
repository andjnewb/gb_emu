#ifndef PPU_H_
#define PPU_H_
#include "cpu.h"

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
    LY_LYC_COMPARISON_SIGNAL,
    H_BLANK_CHECK_ENABLE,
    V_BLANK_CHECK_ENABLE,
    OAM_CHECK_ENABLE,
    LY_LYC_CHECK_ENABLE,
};

void get_lcd_regs(cpu_state * state, int regs[8]);
int get_lcd_ly(cpu_state * state);

#endif