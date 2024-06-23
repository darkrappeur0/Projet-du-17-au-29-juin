#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "topitop.h"

typedef struct position {
    Joueur * j1;
    Joueur * j2;
    Case_grid *** etat;
    Nb_pieces_neutre * pieces;
}position;

typedef struct coup{
    Joueur * j;
    int type_action;
    Case_grid * case_depart;
    Case_grid * case_arrivee;
}coup;

//struct liste chaînée

typedef struct lst_coup lst_coup;
struct lst_coup{
    coup * val_coup;
    lst_coup * suiv;
};

//prototypes fonctions listes chaînées

int longueur_l(lst_coup * l);
void libere_l(lst_coup * l);

//prototypes des fonctions min_max:

//initialisation

position * genere_position();
coup * cree_coup(Joueur * j, int type_action, Case_grid * c_depart, Case_grid * c_arrivee);

//algorithme

lst_coup* genere_coup(position * p, Joueur * jou);
position* applique_coup(position *p, coup * cp, int jou);
int evaluation(int n, position * p, int(*heuristique)(position * p), int jou);
coup * choisir_coup(int n, position * p, int(eval)(int n, position * p, int(*heuristique)(position * p),  int jou), int(* heuristique)(position * p) );
int heur(position * p);

