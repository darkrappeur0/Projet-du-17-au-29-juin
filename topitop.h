#ifndef TOPITOP_H
#define TOPITOP_H

typedef struct seau_case {
    int pose;
    char * couleur;
}Seau_case;

typedef struct case {
    int x;
    int y;
    seau_case * seau;
    int tour;
    int base;
}Case;

typedef struct joueur {
    char * couleur;
    int nb_chateaux;
}Joueur;

Case ** genere_grille();
Joueur * genere_joueur(char * couleur);
int coup_valide(Joueur * j, Case * case_depart, Case * case_arrivee);
void coup_joueur(Joueur * j, Case * case_depart, Case * case_arrivee, Case ** grid);
int gagnant(Joueur* j);
#endif