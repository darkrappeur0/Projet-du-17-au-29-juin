#include <stdio.h>
#include <stdlib.h>
#include "InterfaceGraphique.h"

void SetMat(SDL_Texture * bg, SDL_Renderer * renderer, SDL_Window * window){
    SDL_Rect Source = {0}, window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(bg, NULL, NULL, &source.w, &source.h);
    destination = window_dimensions;
    SDL_RenderCopy(renderer, texture, &source, &destination);
}

SDL_Rect *  Load_Cards(SDL_Texture * paquet, SDL_Renderer * renderer, SDL_Window * window){
    paquet = IMG_LoadTexture(renderer,'./ImagesWizard/FullJeuDuWizard.png');
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};
    float zoom = 8;
    int deck = 54;
    
}