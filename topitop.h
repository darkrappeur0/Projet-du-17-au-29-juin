#ifndef TOPITOP_H
#define TOPITOP_H

typedef struct seau_case {
    int pose;
    char * couleur;
}Seau_case;

typedef struct case_grid {
    int x;
    int y;
    seau_case * seau;
    int tour;
    int base;
}Case_grid;

typedef struct joueur {
    char * couleur;
    int nb_chateaux;
}Joueur;

Case_grid *** genere_grille();
Joueur * genere_joueur(char * couleur);
int coup_valide(Joueur * j, Case_grid * case_depart, Case_grid * case_arrivee);
void coup_joueur(Joueur * j, Case_grid * case_depart, Case_grid * case_arrivee, Case_grid *** grid);
int gagnant(Joueur* j);

#endif