#include <stdbool.h>
#include <string.h>
 
#include "score.h"


typedef struct lst_coup lst_coup;
typedef struct lst_noeud lst_noeud;

//structures MCTS:

typedef struct position{
    int id_joueur;
    joueur * j1;
    joueur * j2;
    score * sco;    //tour dispo dans nb_cartes
}position; 

typedef struct coup{
    int id_joueur;
    carte * carte_placee;
    carte * carte_jouee;
}coup; 

typedef struct noeud{
    position * p;
    lst_coup * l;
} noeud;

//structures listes:

struct lst_coup{
    coup * c;
    int n_coup;
    float gain_coup;
    lst_coup * suiv;
};

struct lst_noeud{
    noeud * n;
    lst_noeud * suiv;
};

//prototype listes:

    //1) lst_coup:
lst_coup * cree_list_coup();
lst_coup * ajoute_list_coup(lst_coup *l, coup * c);
int calcul_n_total(lst_coup * l);
    //2) lst_noeud:
lst_noeud * cree_list_noeud();
lst_noeud * ajoute_list_noeud(lst_noeud *l, noeud * n);

//prototype MCTS:

position * cree_position();
coup * cree_coup();
noeud * cree_noeud(position * p, lst_coup * l);
lst_noeud ** cree_liste_noeud_2(int nb_tour_max);

bool compare_deck(deck * d1, deck * d2);
bool compare_joueur(joueur * j1, joueur * j2);
bool compare_score(score * s1, score * s2);
bool compare_position(position * p1, position * p2);
bool compare_noeud(noeud * n1, noeud * n2);

lst_coup * genere_coup(position * p);
noeud * applique_coup(noeud * n, coup * c);

float interet(lst_coup * l, int n_total);
coup * coup_interet(lst_coup * l);




float mcts(lst_noeud ** lst_n, noeud * n);

 
