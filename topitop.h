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
    Seau_case seau;
    int tour;
    int base;
}Case_grid;

typedef struct joueur {
    char * couleur;
    int nb_chateaux;
    int nb_seaux;
}Joueur;

typedef struct nb_pieces_neutre{
    int nb_tours;
    int nb_bases;
}Nb_pieces_neutre;


Case_grid * genere_case(int i, int j);
Case_grid *** genere_grille();
Joueur * genere_joueur(char * couleur);
Nb_pieces_neutre * genere_pieces();
int check_case_vide(Case_grid * case_verif);
int check_couleur(Case_grid * case_verif, Joueur * j);
int check_deplacement(Joueur * j, Case_grid * case_depart, Case_grid * case_arrivee);
int coup_valide(Joueur * j, Nb_pieces_neutre * pieces, int type_action, Case_grid * case_depart, Case_grid * case_arrivee);
int gagnant(Joueur * j);

#endif