#include "display.h"

int init_video(video_state * v_state)
{

    v_state->textColor.a = 0;
    v_state->textColor.r = 255;
    v_state->textColor.g = 255;
    v_state->textColor.b = 255;


    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf("Error Intializing SDL...");
        return 0;
    }

    //SDL_CreateWindowAndRenderer(640, 480, 0, &v_state->window, &v_state->renderer);
    v_state->window = SDL_CreateWindow("Penis",0,0,640,480,0);
    v_state->renderer = SDL_CreateRenderer(v_state->window, -1, 0);

    if(&v_state->window == NULL)
    {
        printf("Window was NULL...\n");
        return 0;
    }

    if(&v_state->renderer == NULL)
    {
        printf("Renderer was NULL....\n");
        return 0;
    }

    if(TTF_Init() == -1)
    {
        printf("Error initializing TTF.\n");
        return 0;
    }

    v_state->font = TTF_OpenFont("ProFontIIx.ttf", 24);

    if(v_state->font == NULL)
    {
        printf("Error loading font file.\n");
        return 0;
    }
    

    return 1;

}



int clean_SDL(video_state * v_state)
{

    TTF_Quit();

    SDL_DestroyRenderer(v_state->renderer);
    SDL_DestroyWindow(v_state->window);

    SDL_Quit();

    return EXIT_SUCCESS;
}