#include "wizard_MCTS.h"

#define CST 1.4         //constante pour l'algo UCB
#define TOUR_MAX 24     //nombre de tour maximum dans une partie

//fonctions liste_chaînée:

lst_coup * cree_list_coup(){
    lst_coup * new = malloc(sizeof(lst_coup));
    new->c = NULL;
    new->n_coup = 0;
    new->gain_coup = 0;
    new->suiv = NULL;
    return new;
} 

lst_coup * ajoute_list_coup(lst_coup * l, coup *c){
    lst_coup * new = cree_list_coup();
    new->c = c;
    new->suiv = l;
    return new;
} 

int calcul_n_total(lst_coup *l){
    int n = 0;
    lst_coup * l_temp = l;
    while(l_temp != NULL){
        n = n + l_temp->n_coup;
        l_temp = l_temp->suiv;
    } 
    return n;
} 

lst_noeud * cree_list_noeud(){
    lst_noeud * new = malloc(sizeof(lst_noeud));
    new->n = NULL;
    new->suiv = NULL;
    return new;
} 

lst_noeud * ajoute_list_noeud(lst_noeud *l, noeud * n){ 
    lst_noeud * new = cree_list_noeud();
    new->n = n;
    new->suiv = l;
    return new;
} 

//fonctions initialisation

//fonctions MCTS:

lst_noeud ** cree_liste_noeud_2(int nb_tour_max){
    lst_noeud ** lst_n = malloc(nb_tour_max * sizeof(lst_noeud *));
    return lst_n;
} 

bool compare_position(position *p1, position *p2){
    if(p1 == NULL){
        return p1;
    } 
    return p2;
} 

bool compare_noeud(noeud *n1, noeud *n2){
    return compare_position(n1->p, n2->p);
} 

    // calcul de l'interet d'un coup k, i.e: I(k) = Gn(k) + C * sqrt(ln(n) / nk)

float interet(lst_coup * l, int n_total){
    return (l->gain_coup / l->n_coup) + CST * sqrt(log(n_total) / l->n_coup);
} 

    //obtention du coup possédant le plus grand interet 

coup * coup_interet(lst_coup * l){
    lst_coup * l_temp = l;
    coup * c_max = NULL;
    float interet_max = 0;
    int n_total = calcul_n_total(l);
    bool continu = true;
    while(l_temp != NULL && continu){
        if(l->n_coup == 0){
            continu = false;
        } else{
            float i = interet(l, n_total);
            if(i >= interet_max){
                c_max = l_temp->c;
                interet_max = i;
            } 
            l_temp = l_temp->suiv;
        } 
    } 
    return c_max;
} 

noeud * noeud_appartient(lst_noeud * l, noeud * n){
    lst_noeud * l_temp = l;
    while(l_temp != NULL){
        if(compare_noeud(n, l_temp->n)){
            return l_temp->n;
        } 
        l_temp = l_temp->suiv;
    } 
    return NULL;
}  

noeud * applique_coup(noeud * n, coup * c){
    if(c != NULL){
        return n;
    } 
    return NULL;
} 

//fonction mcts a appeler en boucle avec au départ un lst_n et un n de base:

float mcts(lst_noeud ** lst_n, noeud * n){
    int tour = n->p->tour;
    coup * c = coup_interet(n->l);
    noeud * n_new = applique_coup(n, c);
    if(tour + 1 >= TOUR_MAX ){     // fin de partie forcée
        return 0;   // valeur de fin de partie à ajouter
    } else{
        lst_noeud * l = lst_n[tour + 1];
        n->l->n_coup = n->l->n_coup + 1;
        noeud * n_suiv = noeud_appartient(l, n_new);
        if(n_suiv != NULL){
            n->l->gain_coup = n->l->gain_coup + mcts(lst_n, n_suiv);
        } else{
            lst_n[tour + 1] = ajoute_list_noeud(lst_n[tour + 1], n_new);        //création d'un nouveau noeud non exploré
            return 0; //valeur de la partie aléatoire généré a partir de la position n_new->p
        }  
        return 0; //vraiment 0 ici car lorsque la partie est pas fini; on a pas encore de score final 
    } 
} 

int main(){
    return 0;
} 