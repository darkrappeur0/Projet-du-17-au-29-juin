#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *Canvas = NULL;
    Canvas = SDL_CreateWindow("Wait until the end : What do you see ?",100,0,700,600,SDL_WINDOW_RESIZABLE);
    SDL_Renderer *Renderer = NULL;
    Renderer = SDL_CreateRenderer(Canvas, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect rect;
    int i;
    int n = 10+rand()%90;
    for (i=0;i<n;i++){
        int r = rand()%255;
        int g = rand()%255;
        int b = rand()%255;
        int o = 100+rand()%155;
        int w = 10+rand()%690;
        int h = 10+rand()%590;
        int x = rand()%(700-w);
        int y = rand()%(600-h);
        SDL_SetRenderDrawColor(Renderer,r,g,b,o);
        rect.x = x;
        rect.y = y;
        rect.w = w;
        rect.h = h;
        SDL_RenderFillRect(Renderer, &rect);
        SDL_RenderPresent(Renderer);
        SDL_Delay(500);
    }
    SDL_Delay(5000);
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Canvas);
    SDL_Quit();
    return 0;
}