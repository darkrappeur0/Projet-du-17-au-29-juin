#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Trad_logi_mcts.h"

#ifndef INTERFACEGRAPHIQUE_H
#define INTERFACEGRAPHIQUE_H

typedef struct ItemCarte {
    SDL_Rect * Face;
    SDL_Texture * Dos;
//    carte * Objet;
}ItemCarte;

void SetMat(SDL_Texture * bg, SDL_Renderer * renderer, SDL_Window * window);
ItemCarte ** Load_Cards(SDL_Texture * dos, SDL_Renderer * renderer);

#endif