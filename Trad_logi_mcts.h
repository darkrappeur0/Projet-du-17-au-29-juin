#include "wizard_MCTS.h"

carte * traddemandej2( int couleur, int num);

void freejoueur(joueur * j);
void freepos(position * p);
void freecoup(coup * c);
void freelistcoup(lst_coup * l);
void freenoeud(noeud * n);

void ini_manche_n( joueur * IA, joueur * J2, position * p);
position * fin_manche_n( position * p, score * scorefin,joueur * IA, joueur * J2);
void manche_n(int i,lst_noeud ** l_n, joueur * IA, joueur * J2, int atout,int x, int y, score * sco1, int z);

void initialisationtrad(int x);