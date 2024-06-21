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

void deplacement(rectsdlcouleur * bleu, rectsdlcouleur * rouge,rectsdlneutre * grand, rectsdlneutre * moyen, int x, int y, float j, float i );
void deplacementrouge(rectsdlcouleur * rouge,rectsdlneutre * grand, rectsdlneutre * moyen, int x, int y, float j, float i, int r);
void deplacementgrand(rectsdlneutre * grand, rectsdlneutre * moyen, int x, int y, float j, float i, int r);
void deplacementmoyen(rectsdlneutre * moyen, int x, int y, float j, float i, int r);
int queltypecest(rectsdlcouleur * bleu, rectsdlcouleur * rouge,rectsdlneutre * grand, rectsdlneutre * moyen, int x, int y);
int quelneutrecest(rectsdlneutre * grand, rectsdlneutre * moyen, int x, int y);
int quelcouleurcest(rectsdlcouleur * bleu, rectsdlcouleur * rouge,int x, int y);
int quelgrandcest(rectsdlneutre * moyen, int x, int y);
int quelmoyencest(rectsdlneutre * moyen, int x, int y);
int quelrougecest(rectsdlcouleur * bleu,int x, int y);
int quelbleucest(rectsdlcouleur * bleu,int x, int y);
rectsdlneutre * initialisationrectneutremoyen();
rectsdlneutre * initialisationneutregrand( );
SDL_Rect * inirectneutre2();
SDL_Rect * inirectneutre1();
rectsdlcouleur * initialisationrectcoulbleu( );
rectsdlcouleur * initialisationrectcoulrouge();
int deplacementeny(float j,int y, float i);
int deplacementenx(float i,int x);
