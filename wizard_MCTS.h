#include <stdbool.h>
#include <string.h>
 
#include "score.h"


typedef struct lst_coup lst_coup;
typedef struct lst_noeud lst_noeud;

//structures MCTS:

typedef struct position{
    int id_joueur;
    int atout;
    carte * carte_placee;
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

//fonction d'affichage:
void displayjoueur(joueur * j1);
void displaypos(position * p);
void displaycoup(coup * c);
void displaylstcoup(lst_coup * l);
void displaynoeud(noeud * n);


//prototype listes:

    //1) lst_coup:
lst_coup * cree_list_coup();
lst_coup * ajoute_list_coup(lst_coup *l, coup * c);
int calcul_n_total(lst_coup * l);
    //2) lst_noeud:
lst_noeud * cree_list_noeud();
lst_noeud * ajoute_list_noeud(lst_noeud *l, noeud * n);

//prototype MCTS:

position * cree_position(int y);
coup * cree_coup();
noeud * cree_noeud(position * p, lst_coup * l);
lst_noeud ** cree_liste_noeud_2(int nb_tour_max);


bool appartient_deck(carte* c, deck * d);
bool compare_deck(deck * d1, deck * d2);
bool compare_joueur(joueur * j1, joueur * j2, bool est_IA);
bool compare_score(score * s1, score * s2);
bool compare_position(position * p1, position * p2);
bool couleur_demande(carte * c_placee, deck * d);

noeud * noeud_appartient(lst_noeud * l, position * p);
void supprime_deck(deck * d, carte * c);

deck *copie_deck(deck * d);
lst_coup * genere_coup(position * p);
position * applique_coup(position * p, coup * c);

float interet(lst_coup * l, int n_total);
coup * coup_interet(lst_coup * l);




float mcts(lst_noeud ** lst_n, noeud * n);
lst_noeud ** utilisation_MCTS(int x);

coup * utilise_resultat(lst_noeud ** l_n, noeud * n);

 
