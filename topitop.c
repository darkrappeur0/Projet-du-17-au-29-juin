#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "topitop.h"

/*Pas d'utilistation de booléens on utilise des entiers où false=0 et true=tout le reste*/

Case_grid * genere_case(int i, int j){
    Case_grid * c = malloc(sizeof(Case_grid));
    c->x = i;
    c->y = j;
    c->seau->pose = 0;
    c->seau->couleur = NULL;
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

int conflit(Case_grid * case_depart, Case_grid * case_arrivee){
    int resolu = 0;
    
}

int coup_valide(Joueur * j, Case_grid * case_depart, Case_grid * case_arrivee){
    int valide = 0;
    if (joueur != NULL){                                                          //On teste si on a pas fait n'importe quoi
        if (case_arrivee != NULL){                                                //Pareil
            if (case_depart != NULL){                                             //Cas on veut déplacer une pièce
                float module_arr = sqrt(case_arrivee->x**2+case_arrivee->y**2);
                float module_dep = sqrt(case_depart->x**2+case_depart->y**2);
                if (module_arr <= module_dep+1){                                 //On teste si on vise bien une case adjacente
                   // if (case_arrivee)
                }
            }
            else {

            }
        }
    }
    return valide;
}

void coup_joueur(Joueur * j, Case_grid * case_depart, Case_grid * case_arrivee, Case_grid *** grid){
    int i;
    int j;
    for (i=0;i<3;i++){
        for (j=0;j<3;j++){

        }
    }
}