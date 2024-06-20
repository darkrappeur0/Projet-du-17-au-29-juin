#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_render.h>

void denmark(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win = SDL_CreateWindow("test1",0,0,1000,1000,SDL_WINDOW_RESIZABLE);
    SDL_Renderer* render = SDL_CreateRenderer( win, -1,SDL_RENDERER_PRESENTVSYNC);
    printf("drapeau dannois\n");
    SDL_Delay(2000);
    SDL_SetRenderDrawColor( render, 255,  255 , 255 , 0);
    SDL_Rect * rect =malloc(sizeof(SDL_Rect)); 
    SDL_Rect * rect2 = malloc(sizeof(SDL_Rect));
    int i = 0;
    while (i<1001){
    rect->x=0;
    rect->y=470;
    rect->w=i;
    rect->h=30;
    SDL_RenderDrawRect( render, rect);
    SDL_RenderFillRect( render, rect);
    rect2->x=270;
    rect2->y=0;
    rect2->w=30;
    rect2->h=i;
    SDL_RenderDrawRect( render, rect2);
    SDL_RenderFillRect( render, rect2);
    SDL_RenderPresent(render);
    i=i+2;
    }
    SDL_Delay(2000);
    SDL_SetRenderDrawColor( render, 255,  0 , 0 , 0);
    
    i=0;
    int g=0;
    while ((i<271) && (g<471) ){
        rect->x=0;
        rect->y=0;
        rect->w=i;
        rect->h=g;
        SDL_RenderDrawRect( render, rect);
        SDL_RenderFillRect( render, rect);
        SDL_RenderPresent(render);
        i=i+27;
        g=g+47;
        SDL_Delay(200);
    }
    
    SDL_Delay(1000);
    i=0;
    g=0;
    while ( (i<271) &&(g<501)){
    rect->x=0;
    rect->y=500;
    rect->w=i;
    rect->h=g;
    SDL_RenderDrawRect( render, rect);
    SDL_RenderFillRect( render, rect);
    SDL_RenderPresent(render);
    i=i+27;
    g=g+50;
    SDL_Delay(200);
    }
    SDL_Delay(1000);
    i=0;
    g=0;
    while ( (i<701) && (g < 471)){
    rect->x=300;
    rect->y=0;
    rect->w=i;
    rect->h=g;
    SDL_RenderDrawRect( render, rect);
    SDL_RenderFillRect( render, rect);
    SDL_RenderPresent(render);
    i=i+70;
    g=g+47;
    SDL_Delay(200);
    }
    SDL_Delay(1000);
    i=0;
    g=0;
    while ( (i<701) && (g<501)){
    rect->x=300;
    rect->y=500;
    rect->w=i;
    rect->h=g;
    SDL_RenderDrawRect( render, rect);
    SDL_RenderFillRect( render, rect);
    SDL_RenderPresent(render);
    i=i+70;
    g=g+50;
    SDL_Delay(200);
    }
    SDL_Delay(1000);
    SDL_RenderClear(render); 
    SDL_DestroyRenderer( render);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void scotland(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win = SDL_CreateWindow("test1",0,0,1000,1000,SDL_WINDOW_RESIZABLE);
    SDL_Renderer* render = SDL_CreateRenderer( win, -1,SDL_RENDERER_PRESENTVSYNC);
    SDL_Rect* rect = malloc(sizeof(SDL_Rect));
    printf("drapeau de l'Écosse\n");
    SDL_SetRenderDrawColor( render, 0,  0 , 255 , 0);
    rect->x=0;
    rect->y=0;
    rect->w=1000;
    rect->h=1000;
    SDL_RenderDrawRect( render, rect);
    SDL_RenderFillRect( render, rect);
    SDL_RenderPresent(render);
    int c = 30;
    int i = 0;
    SDL_SetRenderDrawColor( render, 255,  255 , 255 , 0);
    SDL_RenderDrawLine(render, 0 , 0 , 1000 , 1000);
    SDL_Delay(1000);
    while (c!=0){
        i= 1000 - c;
        SDL_RenderDrawLine(render, c , 0 , 1000 , i);
        SDL_RenderDrawLine(render, 0 , c, i , 1000);
        SDL_RenderPresent(render);
        c=c-1;
    }
    SDL_Delay(1000);
    c=30;
    i=0;
    SDL_RenderDrawLine(render, 0 , 1000 , 1000 , 0);
    while (c!=0){
        i= 1000 - c;
        
        SDL_RenderDrawLine(render,0 , i, i , 0);
        SDL_RenderDrawLine(render,0 ,1000 + c, 1000 + c , 0);
        SDL_RenderPresent(render);
        c=c-1;
    }
    SDL_Delay(2000);
    free (rect);
    SDL_DestroyRenderer( render);
    SDL_DestroyWindow(win);
    SDL_Quit();
}


int main(){
    denmark();
    scotland();
    return 0;
}