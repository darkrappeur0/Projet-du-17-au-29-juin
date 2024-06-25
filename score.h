#include "plis.h"
#include <math.h>
typedef struct score {
    int scorej1;
    int scorej2;
    int nb_de_carte;
}score;






score * creescore();
joueur * creejoueur(int i);
int reglescore(int nb_plit_reel,int nb_plit_predit);
score * update_score (int nb_plit_j1, int nb_plit_j2, int nb_plit_preditj1, int nb_plit_preditj2, score * sprev );
score * update_score2 (score * snouv, score * sprev );
score * unepartie(deck * deckIA, int atout, int premierecarte, int * predijoueur);
void displayscore(score * s);
void testlogique();