#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include "topitop.h"

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

void deplacement(rectsdlcouleur * bleu, rectsdlcouleur * rouge,rectsdlneutre * grand, rectsdlneutre * moyen, float x, float y, float j, float i );
void deplacementrouge(rectsdlcouleur * rouge,rectsdlneutre * grand, rectsdlneutre * moyen, float x, float y, float j, float i, int r);
void deplacementgrand(rectsdlneutre * grand, rectsdlneutre * moyen, float x, float y, float j, float i, int r);
void deplacementmoyen(rectsdlneutre * moyen, float x, float y, float j, float i, int r);
int queltypecest(rectsdlcouleur * bleu, rectsdlcouleur * rouge,rectsdlneutre * grand, rectsdlneutre * moyen, float x, float y);
int quelneutrecest(rectsdlneutre * grand, rectsdlneutre * moyen, float x, float y);
int quelcouleurcest(rectsdlcouleur * bleu, rectsdlcouleur * rouge,float x, float y);
int quelgrandcest(rectsdlneutre * moyen, float x, float y);
int quelmoyencest(rectsdlneutre * moyen, float x, float y);
int quelrougecest(rectsdlcouleur * bleu,float x, float y);
int quelbleucest(rectsdlcouleur * bleu,float x, float y);
rectsdlneutre * initialisationrectneutremoyen();
rectsdlneutre * initialisationneutregrand( );
SDL_Rect * inirectneutre2();
SDL_Rect * inirectneutre1();
rectsdlcouleur * initialisationrectcoulbleu( );
rectsdlcouleur * initialisationrectcoulrouge();
int deplacementeny(float j,float y, float i);
int deplacementenx(float i,float x);
Joueur * actuj2(Joueur * j2,Case_grid *** etat,float j, float i);
Case_grid *** trad(Case_grid *** etat,rectsdlneutre * moyen,rectsdlneutre * grand,float x, float y, float j, float i);
