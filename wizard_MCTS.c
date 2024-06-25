#include "wizard_MCTS.h"
#include <math.h>
#include <stdlib.h>

#define CST 1.4         //constante pour l'algo UCB
#define TOUR_MAX 5      //nombre de tour maximum dans une partie

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

position * cree_position(){
    position * p = malloc(sizeof(position));
    p->id_joueur = 1;
    p->j1 = creejoueur(1);
    p->j2 = creejoueur(2);
    p->sco = creescore();
    p->carte_placee = NULL;
    return p;
} 

coup * cree_coup(carte * c_jouee, carte * c_placee, int id){
    coup * c = malloc(sizeof(coup));
    c->carte_jouee = c_jouee;
    c->carte_placee = c_placee;
    c->id_joueur = id;
    return c;
} 

noeud * cree_noeud(position * p, lst_coup * l){
    noeud * n = malloc(sizeof(noeud));
    n->p = p;
    n->l = l;
    return n;
} 

lst_noeud ** cree_liste_noeud_2(int nb_tour_max){
    lst_noeud ** lst_n = malloc(nb_tour_max * sizeof(lst_noeud *));
    return lst_n;
} 

//fonctions MCTS:

bool compare_deck(deck *d1, deck *d2){          //pour comparer 2 positions
    if(d1->nb_de_carte != d2->nb_de_carte){
        return false;
    } else{
        deck * d1_temp = d1;
        deck * d2_temp = d2;
        while(d1_temp != NULL && d2_temp != NULL){
            if(d1_temp->carte != d2_temp->carte){
                return false;
            } 
        } 
        return true;
    } 
}  

bool compare_joueur(joueur *j1, joueur *j2,bool est_IA){    //pour comparer 2 positions
    return (compare_deck(j1->deck_joueur, j2->deck_joueur) || !est_IA) &&
           j1->nb_de_plis_fait == j2->nb_de_plis_fait                         &&
           j1->nb_de_plis_predit == j2->nb_de_plis_predit;       
} 

bool compare_score(score *s1, score *s2){       //pour comparer 2 positions
    return (s1->scorej1 == s2->scorej1 && s1->scorej2 == s2->scorej2 && s1->nb_de_carte == s2->nb_de_carte);
} 

bool compare_position(position * p1, position * p2){
    if(p1->id_joueur == p2->id_joueur){
        if((p1->carte_placee != NULL && p2->carte_placee == NULL) || (p2->carte_placee != NULL && p1->carte_placee == NULL) ){
            return false;
        } 
        if(p1->id_joueur == 1){
            return compare_joueur(p1->j1, p2->j1, true)  &&
                   compare_joueur(p1->j2, p2->j2, false) &&
                   compare_score(p1->sco, p2->sco);
        }  
        return compare_joueur(p1->j1, p2->j1, false)  &&
               compare_joueur(p1->j2, p2->j2, true) &&
               compare_score(p1->sco, p2->sco);
    }  
    return false;
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
        if(l_temp->n_coup == 0){
            c_max = l_temp->c;
            continu = false;
        } else{
            float i = interet(l_temp, n_total);
            if(i >= interet_max){
                c_max = l_temp->c;
                interet_max = i;
            } 
            l_temp = l_temp->suiv;
        } 
    } 
    return c_max;
} 

noeud * noeud_appartient(lst_noeud * l, position * p){
    lst_noeud * l_temp = l;
    while(l_temp != NULL){
        if(compare_position(p, l_temp->n->p)){
            return l_temp->n;
        } 
        l_temp = l_temp->suiv;
    } 
    return NULL;
}  

/*position * applique_coup(position * p, coup * c){
    position * p_new = cree_position();

    //à completer

    return p_new;
} */

/* lst_coup * genere_coup(position * p){
    lst_coup * l = cree_list_coup();

    //à completer

    return l;
} */

//fonction mcts a appeler en boucle avec au départ un lst_n et un n de base:

float mcts(lst_noeud ** lst_n, noeud * n){
    int tour = n->p->sco->nb_de_carte;
    coup * c = coup_interet(n->l);
    position * p_new = applique_coup(n->p, c);
    if(tour + 1 >= TOUR_MAX ){     // fin de partie forcée
        return 0;   // valeur de fin de partie à ajouter
    } else{
        lst_noeud * l = lst_n[tour + 1];
        n->l->n_coup = n->l->n_coup + 1;
        noeud * n_suiv = noeud_appartient(l, p_new);
        if(n_suiv != NULL){
            n->l->gain_coup = n->l->gain_coup + mcts(lst_n, n_suiv);
        } else{
            lst_n[tour + 1] = ajoute_list_noeud(lst_n[tour + 1], cree_noeud(p_new, genere_coup(p_new)));        //création d'un nouveau noeud non exploré
            return 0; //valeur de la partie aléatoire généré a partir de la position p_new
        }  
        return 0; //vraiment 0 ici car lorsque la partie est pas fini; on a pas encore de score final 
    } 
} 
 

void oldmain(){
    int nombre_appel_mcts = 100;
    lst_noeud ** lst_n = cree_liste_noeud_2(TOUR_MAX);
    position * p_base = cree_position();
    noeud * n_base = cree_noeud(p_base, genere_coup(p_base));
    for(int i = 0; i <nombre_appel_mcts; i++){
        mcts(lst_n, n_base);
    } 
}
