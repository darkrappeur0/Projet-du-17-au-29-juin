#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <math.h>

typedef struct  rectsdlcouleur {
    SDL_Rect * destination1;
    SDL_Rect * destination2;
    int j;
}rectsdlcouleur;

typedef struct  rectsdlneutre {
    SDL_Rect * destination1;
    SDL_Rect * destination2;
    SDL_Rect * destination3;
    SDL_Rect * destination4;
    int j;
}rectsdlneutre;