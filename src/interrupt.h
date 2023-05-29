#ifndef INTERRUPT_H_
#define INTERRUPT_H_

enum interrupt_enable
{
    VBLANK_E,
    LCD_STAT_E,
    TIMER_E,
    SERIAL_E,
    JOYPAD_E,
};

enum interrupt_flag
{
    VBLANK_F,
    LCD_STAT_F,
    TIMER_F,
    SERIAL_F,
    JOYPAD_F,
};


#endif