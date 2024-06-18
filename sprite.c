#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_render.h>

void animationsprite(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win = SDL_CreateWindow("test1",0,0,1000,1000,SDL_WINDOW_RESIZABLE);
    SDL_Renderer* render = SDL_CreateRenderer( win, -1,SDL_RENDERER_PRESENTVSYNC);
    SDL_Rect* rect = malloc(sizeof(SDL_Rect));
    SDL_Rect* rect2 = malloc(sizeof(SDL_Rect));
    SDL_SetRenderDrawColor( render, 0,  255 , 20 , 0);
    rect->x=0;
    rect->y=700;
    rect->w=1000;
    rect->h=300;
    SDL_RenderDrawRect( render, rect);
    SDL_RenderFillRect( render, rect);
    SDL_SetRenderDrawColor( render, 0,  200 , 255 , 0);
    rect2->x=0;
    rect->y=0;
    rect->w=1000;
    rect->h=700;
    SDL_RenderDrawRect( render, rect);
    SDL_RenderFillRect( render, rect);
    SDL_RenderPresent(render);
    SDL_Delay(3000);

    SDL_DestroyRenderer( render);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
int main(){
    animationsprite();
    return 0;
}