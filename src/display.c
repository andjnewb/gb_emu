#include "display.h"

int init_video(video_state * v_state)
{

    v_state->textColor.a = 0;
    v_state->textColor.r = 255;
    v_state->textColor.g = 255;
    v_state->textColor.b = 255;

    v_state->rect1 = malloc(sizeof(SDL_Rect));//
    v_state->rect2 = malloc(sizeof(SDL_Rect));

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf("Error Intializing SDL...");
        return 0;
    }

    SDL_CreateWindowAndRenderer(640, 480, 0, &v_state->window, &v_state->renderer);


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

void get_text_and_rect(SDL_Renderer * renderer, int x, int y, char * text, TTF_Font * font, SDL_Texture * texture, SDL_Rect * rect, video_state * state)
{
    int text_width;
    int text_height;
    SDL_Surface *  tSurface;
    
    tSurface = TTF_RenderText_Solid_Wrapped(font, text, state->textColor, 0);
    texture = SDL_CreateTextureFromSurface(renderer, tSurface);

    text_width = tSurface->w;
    text_height = tSurface->h;

    //SDL_FreeSurface(tSurface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;

    SDL_FreeSurface(tSurface);
    
}

int clean_SDL(video_state * v_state)
{
    SDL_DestroyTexture(v_state->tex1);
    SDL_DestroyTexture(v_state->tex2);

    TTF_Quit();

    SDL_DestroyRenderer(v_state->renderer);
    SDL_DestroyWindow(v_state->window);

    SDL_Quit();

    return EXIT_SUCCESS;
}