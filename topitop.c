#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "topitop.h"

/*Pas d'utilistation de booléens on utilise des entiers où false=0 et true=tout le reste*/

int nb_tours = 4;
int nb_bases = 4;

Case_grid * genere_case(int i, int j){
    Case_grid * c = malloc(sizeof(Case_grid));
    c->x = i;
    c->y = j;
    c->seau.pose = 0;
    c->seau.couleur = NULL;
    c->tour = 0;
    c->base = 0;
}

Case_grid *** genere_grille(){
    Case_grid *** grille = malloc(3*sizeof(Case**));
    int i;
    int j;
    for (i=0;i<3;i++){
        grille[i] = malloc(3*sizeof(Case*));
        for (j=0;i<3;i++){
            grille[i][j] = genere_case(j,i);
        }
    }
    return grille;
}

Joueur * genere_joueur(char * couleur){
    Joueur * joueur = malloc(sizeof(Joueur));
    joueur->couleur = couleur;
    joueur->nb_chateaux = 0;
    return joueur;
}

int check_case_vide(Case_grid * case_verif){
    int vide = 0;
    if (case_verif->base == 0 && case_verif->tour == 0 && case_verif->seau.pose == 0){
        vide = 1;
    }
    return vide;
}

int check_couleur(Case_grid * case_verif, Joueur * j){
    int verif = 0;
    if (case_verif->seau.pose !=0){
        if (case_verif->seau.couleur == j->couleur){
            verif = 1;
        }
    }
    else {
        verif = 1;
    }
    return verif;
}

int check_deplacement(Joueur * j, Case_grid * case_depart, Case_grid * case_arrivee){
    int deplacement = 0;
    if (check_case_vide(case_depart)!= 0 && check_couleur(case_depart) != 0 && check_couleur(case_arrive) != 0){
        if (check_case_vide(case_arrivee)){
            deplacement = 1;
        }
        else if (case_depart->seau.pose != 0){
            if (case_depart->tour == 0 && case_arrivee->seau.pose == 0 && case_arrivee->tour != 0){
            deplacement = 1;
            }
            else if (case_depart->tour != 0 && case_arrivee->seau.pose == 0 && case_arrivee->tour == 0){
            deplacement = 1;
            } 
        }
        else {
            if (case_depart->base != 0){
                if (case_depart->tour == 0 && case_arrivee->base == 0 && case_arrivee->tour !=0){
                    deplacement = 1;
                }
                else if (case_depart->tour != 0 && case_arrivee->base == 0 && case_arrivee->tour == 0){
                    deplacement = 1;
                }
            }
            else {
                if (case_arrivee->tour == 0){
                    deplacement = 1;
            }
        }
    }
}

int coup_valide(Joueur * j, int type_action, Case_grid * case_depart, Case_grid * case_arrivee){
    int valide = 0;
    if (joueur != NULL){                                                          //On teste si on a pas fait n'importe quoi
        if (case_arrivee != NULL){                                                //Pareil
            switch (type_action){
                case DEPLACEMENT :
                    if (abs((case_arrivee->x)-(case_depart->x)) <= 1 && abs((case_arrivee->y)-(case_depart->y)) <= 1){
                        valide = check_deplacement(case_depart, case_arrivee);
                    }
                    break;
                case DEPOSE_SEAU :
                    if (j->nb_seaux > 0){
                        valide = check_case_vide(case_arrivee);
                    }
                    break;
                case DEPOSE_TOUR :
                    if (nb_tours > 0){
                        valide = check_case_vide(case_arrivee);
                    }
                    break;
                case DEPOSE_BASE :
                    if (nb_bases > 0){
                        valide = check_case_vide(case_arrivee);
                    }
                    break;
            }
        }
    }
    return valide;
}

void coup_joueur(Joueur * j, Case_grid * case_depart, Case_grid * case_arrivee, Case_grid *** grid){
    //Si le coup est valide -> application des éléments non nuls de case_depart à case_arrivee
}
int gagnant(Joueur * j){
    int gagne = 0;
    if (j->nb_châteaux == 2){
        gagne = 1;
    }
    return gagne;
}