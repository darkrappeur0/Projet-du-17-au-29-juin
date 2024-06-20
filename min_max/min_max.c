#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "min_max.h"

//constantes

float max_gagnant;
float min_gagnant;

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

nb_pieces * init_pieces(){
    nb_pieces * pie = malloc(sizeof(nb_pieces));
    pie->b = 2;
    pie->r = 2;
    pie->l = 4;
    pie->s = 4; 
    return pie;
} 

cases * init_cases(){
    cases * ca = malloc(sizeof(cases));
    ca->b = false;
    ca->r = false;
    ca->s = false;
    ca->l = false; 
    return ca;
} 

placement * init_placement(){
    placement * p = malloc(sizeof(placement));
    p->joueur = 1;
    p->etat = malloc(3 * sizeof(cases **));
    for(int i = 0; i < 3; i++){
        p->etat[i] = malloc(3 *sizeof(cases *));
        for(int j = 0; j < 3; j++){
            p->etat[i][j] = init_cases();  
        } 
    } 
    p->restant = init_pieces();
    return p;
} 

coup * creer_coup(co * av, co * ap, char piece){
    coup * c = malloc(sizeof(coup));
    c->avant = av;
    c->apres = ap;
    c->piece = piece;
    return c;
} 

bool est_vide(cases * c){
     return c->b == false && 
    c->r == false && 
    c->s == false && 
    c->l == false;
} 

//On considere que le coup est jouable

placement * applique_coup(placement * p, coup * c){
    placement * p_new = init_placement();
    p_new->joueur = (-1) * p->joueur;
    p_new->etat = p->etat;
    p_new->restant->b = p->restant->b;
    p_new->restant->r = p->restant->r;
    p_new->restant->s = p->restant->s;
    p_new->restant->l = p->restant->l;
    if(c->avant != NULL){
        if(c->piece == 'b'){
            p_new->etat[c->avant->x][c->avant->y]->b = false; 
        } 
        if(c->piece == 'r'){
            p_new->etat[c->avant->x][c->avant->y]->r = false; 
        } 
        if(c->piece == 's'){
            p_new->etat[c->avant->x][c->avant->y]->s = false; 
        } 
        if(c->piece == 'l'){
            p_new->etat[c->avant->x][c->avant->y]->l = false; 
        } 
    }   
    if(c->piece == 'b'){
        p_new->etat[c->apres->x][c->apres->y]->b = true; 
        p_new->restant->b = p_new->restant->b - 1;
    } 
    if(c->piece == 'r'){
        p_new->etat[c->apres->x][c->apres->y]->r = true;
        p_new->restant->r = p_new->restant->r - 1; 
    } 
    if(c->piece == 's'){
        p_new->etat[c->apres->x][c->apres->y]->s = true; 
        p_new->restant->s = p_new->restant->s - 1;
    } 
    if(c->piece == 'l'){
        p_new->etat[c->apres->x][c->apres->y]->l = true; 
        p_new->restant->l = p_new->restant->l - 1;
    }  
    return p_new;   
} 


lst_coup* genere_coups(placement * p){   //pas terminé, en attente de la partie logique de jeu
    lst_coup * l_placement = cree_list();
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            co * coordo = malloc(sizeof(co));
            if(est_vide(p->etat[i][j])){
                if(p->restant->b != 0 && p->joueur == 1){
                    coup * c = creer_coup(NULL, coordo, 'b');
                }
                if(p->restant->r != 0 && p->joueur == (-1)){
                    coup * c = creer_coup(NULL, coordo, 'r');
                } 
                if(p->restant->s != 0){
                    coup * c = creer_coup(NULL, coordo, 's');
                } 
                if(p->restant->l != 0){
                    coup * c = creer_coup(NULL, coordo, 'l');
                }  
            }else{
                if(p->joueur == 1){
                    if(!est_vide(p->etat[i][j])){
                        if(i-1 >= 0){
                            
                        }   
                    } 
                } 
            } 
        } 
    } 
    return l_placement;
} 

float evaluation(placement *p){
    if(est_gagnant(p)){
        if(p->joueur == 1){
            return max_gagnant;
        } 
        else{
            return min_gagnant;
        } 
    } 
    else{
        lst_coup * l = genere_coups(p);
        if(p->joueur == 1){
            float max = min_gagnant;
            while(l != NULL){
                float t = evaluation(applique_coup(p, l->val_coup));
                if(t >= max){
                    max = t;
                } 
                l = l->suiv;
            } 
            libere_l(l);
            return max;
        }else{
            float min = max_gagnant;
            while(l != NULL){
                float t = evaluation(applique_coup(p, l->val_coup));
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

float evaluation_n(placement *p,float(*h)(placement * p), int n){
    if(est_gagnant(p)){
        if(p->joueur == 1){
            return max_gagnant;
        } 
        else{
            return min_gagnant;
        } 
    } 
    if(n == 0){
        return h(p);
    } else{
        lst_coup * l = genere_coups(p);
        if(p->joueur == 1){
            float max = min_gagnant;
            while(l != NULL){
                float t = evaluation_n(applique_coup(p, l->val_coup), h, n - 1);
                if(t >= max){
                    max = t;
                } 
                l = l->suiv;
            } 
            libere_l(l);
            return max;
        }else{
            float min = max_gagnant;
            while(l != NULL){
                float t = evaluation_n(applique_coup(p, l->val_coup), h, n - 1);
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



coup * choisir_coup(placement * p, float(*eval)(placement *p)){
    lst_coup * l = genere_coups(p);
    float max = min_gagnant;
    coup * c_max = NULL;
    while(l != NULL){
        float t = eval(applique_coup(p, l->val_coup));
        if(t >= max){
            max = t;
            c_max = l->val_coup;
        } 
        l = l->suiv;
    } 
    libere_l(l);
    return c_max;  
} 

coup * choisir_coup_n(placement * p, float(*eval_n)(placement * p, float(*h)(placement * p), int n),float(*h)(placement * p), int n){
    lst_coup * l = genere_coups(p);
    float max = min_gagnant;
    coup * c_max = NULL;
    while(l != NULL){
        float t = eval_n(applique_coup(p, l->val_coup), h, n);
        if(t >= max){
            max = t;
            c_max = l->val_coup;
        } 
        l = l->suiv;
    } 
    libere_l(l);
    return c_max;  
} 


int main(){
    placement * p = init_placement();
    int n = 4;      // nombre de couche d'arbre parcouru 
    while(!est_gagnant(p)){
        if(p->joueur == 1){
            coup * a_jouer = choisir_coup_n(p, evaluation_n, heuristique, n);
            p = applique_coup(p, a_jouer);
        } 
        else{
            coup * a_jouer = NULL;      // coup de l'utilisateur à demander
            p = applique_coup(p, a_jouer);
        } 
    } 
    return 1;
} 