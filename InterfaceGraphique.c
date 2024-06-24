#include <stdio.h>
#include <stdlib.h>
#include "InterfaceGraphique.h"

SDL_Rect *  Load_Cards(SDL_Texture * paquet, SDL_Renderer * renderer){
    paquet = IMG_LoadTexture(renderer,'./ImagesWizard/FullJeuDuWizard.png');
    SDL_Rect source = {0}, dimensions_window = {0}, destination = {0};
    
}