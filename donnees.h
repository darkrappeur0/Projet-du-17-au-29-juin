#ifndef DONNEES_H
#define DONNEES_H

struct joueur {
    int id_joueur;
    int * pions;
}joueur;

struct placement {
    joueur * joueur;
    int ** etat;
}placement;

struct arbre_heuristique {
    int heur;
    placement position;
    struct arbre_heuristique * fils;
}arbre_heur;

struct coup {
    int x;
    int y;
    int p;
}coup;

placement * initialisation_placement();
joueur * initialsation_joueur(int i);
placement * applique_coup(placement * p, int x, int y, int pion);
bool est_gagnant(placement * p);
coup * creer_coup(int x, int y, int p);
coup ** genere_coups(placement * p, joueur * j, float (*h)(placement *));

#endif