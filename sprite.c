#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>

#include <SDL2/SDL_render.h>

SDL_Texture * load(char  *  file_image_name, SDL_Window *win, SDL_Renderer * render){
    SDL_Renderer * temp =NULL;
    SDL_Texture * final = NULL;
    temp = IMG_Load(file_image_name);
    final = SDL_CreateTextureFromSurface(render, temp);
    SDL_FreeSurface(temp);
    return final;
}

 void affichage(SDL_Texture * text, SDL_Window *win, SDL_Renderer *render){
    int  win_w;
    int  win_h;
    SDL_Rect * source= malloc(sizeof(SDL_Rect));
    SDL_GetWindowSize(win, &win_w, &win_h);
    source->w=win_w;
    source->h=win_h;
    int text_w;
    int text_h;
    SDL_Rect * dest = malloc(sizeof(SDL_Rect));
    SDL_QueryTexture(text,NULL,NULL,&text_w,&text_h);
    dest->w=text_w;
    dest->h=text_h;
    SDL_RenderCopy(render, text, source, text);
    SDL_RenderPresent(render);
    SDL_Delay(3000);
    SDL_RenderClear(render);
}

int main(){

    
    return 0;
}