#ifndef TOPITOP_H
#define TOPITOP_H

#define DEPLACEMENT 0
#define DEPOSE_SEAU 1
#define DEPOSE_TOUR 2
#define DEPOSE_BASE 3

typedef struct seau_case {
    int pose;
    char * couleur;
}Seau_case;

typedef struct case_grid {
    int x;
    int y;
    seau_case seau;
    int tour;
    int base;
}Case_grid;

typedef struct joueur {
    char * couleur;
    int nb_chateaux;
    int nb_seaux;
}Joueur;

Case_grid *** genere_grille();
Joueur * genere_joueur(char * couleur);
int coup_valide(Joueur * j, int type_action, Case_grid * case_depart, Case_grid * case_arrivee);
void coup_joueur(Joueur * j, Case_grid * case_depart, Case_grid * case_arrivee, Case_grid *** grid);
int gagnant(Joueur * j);

#endif