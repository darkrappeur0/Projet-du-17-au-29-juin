#ifndef DONNEES_H
#define DONNEES_H
#include <stdlib.h>


//structures:

typedef struct nb_pieces{
    int b;
    int r;
    int s;
    int l;
}nb_pieces;

typedef struct cases{
    bool b;
    bool r;
    bool s;  
    bool l;
}cases;

typedef struct placement {
    int joueur;
    cases *** etat;
    nb_pieces * restant;
}placement;

typedef struct coordonnees{
    int x;
    int y;
}co;

typedef struct coup{
    char piece;
    co * avant;
    co * apres;
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



//prototypes des fonctions:

nb_pieces * init_pieces();
cases * init_cases();
placement * init_placement();
coup * creer_coup(co * av, co * ap, char p);
bool est_gagnant(placement * p);
placement * applique_coup(placement * p, coup * c);
lst_coup* genere_coups(placement * p);
float heuristique(placement * p);
float evaluation(placement *p);
coup * choisir_coup(placement * p, float(*eval)(placement * p));
float evaluation_n(placement *p, float(*h)(placement * p), int n);
coup * choisir_coup_n(placement * p, float(*eval_n)(placement * p, float(*h)(placement * p), int n),float(*h)(placement * p), int n);

#endif