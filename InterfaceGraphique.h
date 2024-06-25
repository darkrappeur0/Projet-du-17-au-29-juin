#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef INTERFACEGRAPHIQUE_H
#define INTERFACEGRAPHIQUE_H

typedef struct ItemCarte {
    SDL_Rect * Face;
    SDL_Texture * Dos;
    carte * Objet;
}ItemCarte;

typedef struct ItemPaquet ItemPaquet;

struct ItemPaquet {
    ItemCarte * Carte;
    ItemPaquet * NextCarte;
};