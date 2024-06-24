#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "topitop.h"
#include "min_max_topitop.h"

//constantes

#define MAX_GAGNANT 100
#define MIN_GAGNANT 0

//fonctions liste chaînées:

lst_coup * cree_list(){
    lst_coup * new = malloc(sizeof(lst_coup));
    new->val_coup = NULL;
    new->suiv = NULL;
    return new;
} 

lst_coup * ajoute_list(lst_coup *l, coup *c){
    lst_coup * new = malloc(sizeof(lst_coup));
    new->val_coup = c;
    new->suiv = l;
    return new;
} 

int longueur_l(lst_coup *l){
    if(NULL == l){
        return 0;
    }else{
        return 1 + longueur_l(l->suiv);
    } 
} 

void libere_l(lst_coup *l){
    if(l != NULL){
        lst_coup * temp = l->suiv;
        free(l);
        libere_l(temp);
    } 
} 

// fonctions min_max
// joueur rouge represente max, joueur bleu represente min

position * genere_position() {
    position * p = malloc(sizeof(position));
    p->etat = genere_grille();
    p->j1 = genere_joueur(1);
    p->j2 = genere_joueur(2);
    p->pieces = genere_pieces();
    return p;
}

coup * cree_coup(Joueur * j, int type_action, Case_grid * c_depart, Case_grid * c_arrivee) {
    coup * cp = malloc(sizeof(coup));
    cp->j = j;
    cp->type_action = type_action;
    cp->case_depart = c_depart;
    cp->case_arrivee = c_arrivee;
    return cp;
}

lst_coup* genere_coup(position * p, Joueur * jou) {
    lst_coup * l = cree_list();
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            coup * cp1 = cree_coup(jou, DEPOSE_BASE, NULL, p->etat[i][j]);
            if(coup_valide(cp1->j, p->pieces, cp1->type_action, cp1->case_depart, cp1->case_arrivee)) {
                l = ajoute_list(l, cp1);
            }else {
                free(cp1);
            }
            coup * cp2 = cree_coup(jou, DEPOSE_TOUR, NULL, p->etat[i][j]);
            if(coup_valide(cp2->j, p->pieces, cp2->type_action, cp2->case_depart, cp2->case_arrivee)) {
                l = ajoute_list(l, cp2);
            }else {
                free(cp2);
            }
            coup * cp3 = cree_coup(jou, DEPOSE_SEAU, NULL, p->etat[i][j]);
            if(coup_valide(cp3->j, p->pieces, cp3->type_action, cp3->case_depart, cp3->case_arrivee)) {
                l = ajoute_list(l, cp3);
            }else {
                free(cp3);
            }
            for(int x = 0; x < 3; x++) {
                for(int y = 0; y < 3; y++) {
                    coup * cp4 = cree_coup(jou, DEPLACEMENT, p->etat[i][j], p->etat[x][y]);
                    if(coup_valide(cp4->j, p->pieces, cp4->type_action, cp4->case_depart, cp4->case_arrivee)){
                        l = ajoute_list(l, cp4);
                    }else {
                        free(cp4);
                    }
                }
            }
        }
    }
    return l;
}

//on suppose que le coup est valide

position* applique_coup(position *p, coup * cp, int jou) {
    position * p_new = genere_position();
    p_new->etat = p->etat;
    p_new->j1 = p->j1;
    p_new->j2 = p->j2;
    p_new->pieces = p->pieces;
    int x1;
    int y1;
    if(cp->type_action == DEPLACEMENT){
        x1 = cp->case_depart->x;
        y1 = cp->case_depart->y;
    }  
    int x2 = cp->case_arrivee->x;
    int y2 = cp->case_arrivee->y;
    switch (cp->type_action){
        case DEPLACEMENT:
            if(p_new->etat[x1][y1]->base == 1){
                p_new->etat[x2][y2]->base = 1;
                p_new->pieces->nb_bases = p_new->pieces->nb_bases - 1;
            }
            if(p_new->etat[x1][y1]->tour == 1){
                p_new->etat[x2][y2]->tour = 1;
                p_new->pieces->nb_tours = p_new->pieces->nb_tours - 1;
            }
            if(p_new->etat[x1][y1]->seau.pose == 1){
                p_new->etat[x2][y2]->seau.pose = 1;
                p_new->etat[x2][y2]->seau.couleur = p_new->etat[x1][y1]->seau.couleur;
                if(jou == p_new->j1->couleur){
                    p_new->j1->nb_seaux = p_new->j1->nb_seaux - 1;
                }else{
                    p_new->j2->nb_seaux = p_new->j2->nb_seaux - 1;
                }
            }
        break;
        case DEPOSE_BASE :
            p->etat[x2][y2]->base = 1;
            p_new->pieces->nb_bases = p_new->pieces->nb_bases - 1;
        break;   
        case DEPOSE_TOUR :
            p->etat[x2][y2]->tour = 1;
            p_new->pieces->nb_bases = p_new->pieces->nb_bases - 1; 
        break;  
        case DEPOSE_SEAU :
            p->etat[x2][y2]->seau.pose = 1;
            p->etat[x2][y2]->seau.couleur = jou;
            if(jou == p_new->j1->couleur) {
                p_new->j1->nb_seaux = p_new->j1->nb_seaux - 1;
            }else {
                p_new->j2->nb_seaux = p_new->j2->nb_seaux - 1;
            }
        break;   
    }
    if(p_new->etat[x2][x2]->base == 1 && p_new->etat[x2][x2]->tour == 1 && p_new->etat[x2][x2]->seau.pose == 1){
        if(jou == p_new->j1->couleur){
            p_new->j1->nb_chateaux = p_new->j1->nb_chateaux + 1;
        }
    } 
    return p_new;
}

int evaluation(int n, position * p, int(*heuristique)(position * p), int jou){
    if(gagnant(p->j1)){
        return MAX_GAGNANT;
    }
    if(gagnant(p->j2)){
        return MIN_GAGNANT;
    }
    if(n == 0){
        return heuristique(p);
    }else {
        lst_coup * l;
        if(jou == p->j1->couleur){
            l = genere_coup(p, p->j1);
        } else{
            l = genere_coup(p, p->j2);
        } 
        if(jou == p->j1->couleur){
            float max = MIN_GAGNANT;
            while(l != NULL){
                int t = 0;
                t= evaluation(n - 1, applique_coup(p, l->val_coup, jou), heuristique, p->j2->couleur);
                if(t >= max){
                    max = t;
                } 
                l = l->suiv;
            } 
            libere_l(l);
            return max;
        }else{
            float min = MAX_GAGNANT;
            while(l != NULL){
                int t=0;
                t = evaluation(n - 1, applique_coup(p, l->val_coup, jou), heuristique, p->j1->couleur);
                if(t <= min){
                    min = t;
                } 
            l = l->suiv;
            } 
            libere_l(l);
            return min;
        }
    }
}

coup * choisir_coup(int n, position * p, int(*eval)(int n, position * p, int( * heuristique)(position * p), int jou), int(*heuristique)(position * p)){
    lst_coup * l = cree_list();
    l = genere_coup(p, p->j1);
    float max = MIN_GAGNANT;
    coup * cp_max = NULL;
    while(l != NULL){
        int t = eval(n, applique_coup(p, l->val_coup, 1), heuristique, 2);
        if(t >= max){
            max = t;
            cp_max = l->val_coup;
        l = l->suiv;
        } 
    }
    libere_l(l);
    return cp_max;  
} 

int heur(position * p){
    int h = (MIN_GAGNANT + MAX_GAGNANT) / 2;
    h = h + p->j1->nb_chateaux * MAX_GAGNANT / 5 - p->j1->nb_chateaux * MAX_GAGNANT / 5;   //avoir un château est très favorable
    h = h + p->j2->nb_seaux * MAX_GAGNANT / 25 - p->j1->nb_seaux * MAX_GAGNANT / 25;       //avoir des seaux posés est légèrement favorable
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            Case_grid * c = p->etat[i][j];
            if(c->seau.pose == 1 && c->tour == 1){
                if(c->seau.couleur == 1){
                    h = h + MAX_GAGNANT / 10;                                              //avoir un seau sur une tour
                } else{                                                                    //est plutôt favorable
                    h = h - MAX_GAGNANT / 10;
                } 
            }   
        }  
    } 
    return h;
} 


