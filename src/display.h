#ifndef DISPLAY_H_
#define DISPLAY_H_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



typedef struct 
{
    SDL_Window * window;
    SDL_Renderer * renderer;


    SDL_Event event;

    TTF_Font * font;
    SDL_Texture * tex1;
    SDL_Texture * tex2;
    SDL_Rect * rect1;
    SDL_Rect * rect2;

    SDL_Color textColor;
    
}video_state;



int init_video(video_state * v_state);
void get_text_and_rect(SDL_Renderer * renderer, int x, int y, char * text, TTF_Font * font, SDL_Texture ** texture, SDL_Rect * rect, video_state * state);
int clean_SDL(video_state * v_state);



#endif