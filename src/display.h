#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "ppu.h"
#include "cpu.h"


typedef struct 
{
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Texture * texture;

    SDL_Event event;

    TTF_Font * font;
    SDL_Color textColor;

    uint8_t framebuff[160 * 144 * 3];//160x144 resolution, 3 bytes per pixel.
    uint8_t framebuff_alpha[160 * 144 * 4];

        
}video_state;



int init_video(video_state * v_state);

int clean_SDL(video_state * v_state);

void draw_frame(video_state * vstate, ppu_state * _ppu_state, cpu_state * _cpu_state);

void copy_bg_from_vram(video_state * vstate, ppu_state * _ppu_state, cpu_state * _cpu_state);

#endif