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
    if(l->c == NULL){
        l->c = c;
        return l;
    } else{
        lst_coup * new = cree_list_coup();
        new->c = c;
        new->suiv = l;
        return new;      
    } 
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
    if(l->n == NULL){
        l->n = n;
        return l;
    } 
    else{
        lst_noeud * new = cree_list_noeud();
        new->n = n;
        new->suiv = l;
        return new;
    } 
} 

//fonctions initialisation

position * cree_position(int y){
    position * p = malloc(sizeof(position));
    p->id_joueur = 1;
    p->atout = update_atout();
    p->j1 = creejoueur(1,y);
    p->j2 = creejoueur(2,y);
    p->sco = creescore();
    p->carte_placee = NULL;
    return p;
} 

coup * cree_coup(carte * c_jouee, carte * c_placee, int id){
    coup * c = malloc(sizeof(coup));
    c->carte_jouee = malloc(sizeof(carte));
    c->carte_jouee = c_jouee;
    c->carte_placee = malloc(sizeof(carte));
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
bool appartient_deck(carte* c, deck * d){
    deck * d_temp = d;
    while(d_temp != NULL && c != NULL){
        if(d_temp->carte->couleur == c->couleur && d_temp->carte->num == c->num){
            return true;
        } 
        d_temp = d_temp->next;
    } 
    return false;
} 

bool compare_deck(deck *d1, deck *d2){          //pour comparer 2 positions
    if(d1->nb_de_carte != d2->nb_de_carte){
        return false;
    } else{
        deck * d1_temp = d1;
        while(d1_temp != NULL){
            if(!appartient_deck(d1_temp->carte, d2)){
                return false;
            } 
            d1_temp = d1_temp->next;
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

bool compare_position(position * p1, position * p2){        //compare que ce qui est connu par notre IA
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
    if(p == NULL){
        return NULL;
    } 
    lst_noeud * l_temp = l;
    while(l_temp != NULL){
        if(compare_position(p, l_temp->n->p)){
            return l_temp->n;
        } 
        l_temp = l_temp->suiv;
    } 
    return NULL;
}  

int len_deck(deck * d){
    if(d == NULL){
        return 0;
    } 
    else{
        return 1 + len_deck(d->next);
    }  
} 

deck * copie_deck(deck *d){ 
    deck * d_copie =  NULL;
    if(d != NULL){
        deck * d_temp = d;
        d_copie = generedeck(len_deck(d), NULL);
        while(d_temp != NULL){
            d_copie->carte = d_temp->carte;
            d_copie->next = d_temp->next;
            d_temp = d_temp->next;
        } 
    } 
    return d_copie;
} 

void supprime_deck(deck * d, carte * c){
    if(d != NULL && c != NULL ){
        deck * d_temp = d;
        deck * d_avant = NULL;
        while(d_temp->carte->couleur != c->couleur || d_temp->carte->num != c->num){
            d_avant = d_temp;
            d_temp = d_temp->next;
        }
        if (d_avant!=NULL){ 
            d_avant->next = d_temp->next;
            d_temp->next = NULL;
            freedeck(d_temp);
        }
        
    } 
} 


position * applique_coup(position * p, coup * c){  //à completer(voir commentaires)
    position * p_new = cree_position(p->sco->nb_de_carte); 
    p_new->atout = p->atout;
    p_new->j1->deck_joueur = copie_deck(p->j1->deck_joueur);
    p_new->j1->deck_joueur = copie_deck(p->j1->deck_joueur);

    if(p->carte_placee == NULL){
        p_new->id_joueur = 2 / c->id_joueur; 
        p->carte_placee = c->carte_jouee;
    }
    else{ 
        int a_gagne = evalplisj1(c->carte_jouee, c->carte_placee, p->atout, 2);
        p_new->carte_placee = NULL;
        if(c->id_joueur == 1 && a_gagne == 1){
            (p_new->j1->nb_de_plis_fait)++;
            p_new->id_joueur = 1;
        } else{
            (p_new->j2->nb_de_plis_fait)++;
            p_new->id_joueur = 2;
        } 
        if(c->id_joueur == 2 && a_gagne == 1){
            (p_new->j2->nb_de_plis_fait)++;
            p_new->id_joueur = 2;
        } else{
            (p_new->j1->nb_de_plis_fait)++;
            p_new->id_joueur = 1;
        } 
    } 
    if(c->id_joueur == 1){
        supprime_deck(p_new->j1->deck_joueur, c->carte_jouee);
        (p_new->j1->nb_de_carte)--;
    } else{
        supprime_deck(p_new->j2->deck_joueur, c->carte_jouee);
        (p_new->j2->nb_de_carte)--;
    } 
    if(p_new->j1->nb_de_carte == 0 && p_new->j2->nb_de_carte ==0){  //cas de fin de manche
        p_new->sco = update_score(p_new->j1->nb_de_plis_fait, p_new->j2->nb_de_plis_fait, p_new->j1->nb_de_plis_predit, p_new->j2->nb_de_plis_predit, p_new->sco);
        p_new->sco->nb_de_carte++;
        p_new->j1->nb_de_carte = p_new->sco->nb_de_carte;
        p_new->j2->nb_de_carte = p_new->sco->nb_de_carte;
        p_new->carte_placee = NULL;
        p_new->atout = update_atout();
        p_new->j1->deck_joueur = generedeck(p_new->j1->nb_de_carte, NULL);
        p_new->j2->deck_joueur = generedeck(p_new->j2->nb_de_carte, p_new->j1->deck_joueur);
        p_new->j1->nb_de_plis_fait = 0;
        p_new->j2->nb_de_plis_fait = 0;
        p_new->j1->nb_de_plis_predit = predictionplistotal(p_new->j1->deck_joueur, p_new->atout, p_new->id_joueur);      //mettre la prediction et pas 0
        p_new->j2->nb_de_plis_predit = predictionplistotal(p_new->j2->deck_joueur, p_new->atout, 2 / p_new->id_joueur);      //mettre la prediction et pas 0
    } 
    return p_new;
}


bool couleur_demande(carte * c_placee, deck * d){
    if(c_placee == NULL){
        return false;
    } 
    deck * d_temp = d;
    int couleur = c_placee ->couleur;
    if(couleur >= 4){
        return false;
    }  
    while(d_temp != NULL){
        if(d_temp->carte->couleur == couleur){
            return true;
        } 
        d_temp = d_temp->next;
    } 
    return false;
}


lst_coup * genere_coup(position * p){
    lst_coup * l = cree_list_coup();
    if(p->id_joueur == 1){
        if(p->carte_placee == NULL){
            deck * d = p->j1->deck_joueur;
            while(d != NULL){
                l = ajoute_list_coup(l, cree_coup(d->carte,NULL, 1));
                d = d->next;
            } 
        } else{
            deck * d = p->j1->deck_joueur;
            if(couleur_demande(p->carte_placee, d)){
                int couleur = p->carte_placee->couleur;
                while(d != NULL){
                    if(d->carte->couleur == couleur){
                        l = ajoute_list_coup(l, cree_coup(d->carte, p->carte_placee, 1));
                    } 
                    d = d->next; 
                } 
            } else{
                while(d != NULL){
                    l = ajoute_list_coup(l, cree_coup(d->carte,p->carte_placee,  1));
                    d = d->next;               
                } 
            }          
        } 
    } else{
        if(p->carte_placee == NULL){
            deck * d = p->j2->deck_joueur;
            while(d != NULL){
                l = ajoute_list_coup(l, cree_coup(d->carte,NULL,  2));
                d = d->next;
            } 
        } else{
            deck * d = p->j2->deck_joueur;
            if(couleur_demande(p->carte_placee, d)){
                int couleur = p->carte_placee->couleur;
                while(d != NULL){
                    if(d->carte->couleur == couleur){
                        l = ajoute_list_coup(l, cree_coup(d->carte,p->carte_placee,  2));
                    } 
                    d = d->next; 
                } 
            } else{
                while(d != NULL){
                    l = ajoute_list_coup(l, cree_coup(d->carte,p->carte_placee, 2));
                    d = d->next;               
                } 
            }          
        }
    } 
    return l;
} 


//fonction mcts a appeler en boucle avec au départ un lst_n et un n de base:

float mcts(lst_noeud ** lst_n, noeud * n){
    int tour = n->p->sco->nb_de_carte;
    if(tour + 1 >= TOUR_MAX ){     // fin de partie forcée
        if(n->p->sco->scorej1 > n->p->sco->scorej2){
            return 1;
        } else{
            return 0;
        } 
    } else{
        coup * c = coup_interet(n->l);
        position * p_new = applique_coup(n->p, c);
        lst_noeud * l = lst_n[tour - 1];
        n->l->n_coup = n->l->n_coup + 1;
        noeud * n_suiv = noeud_appartient(l, p_new);
        if(n_suiv != NULL){
            n->l->gain_coup = n->l->gain_coup + mcts(lst_n, n_suiv);
        } else{
            lst_n[tour - 1] = ajoute_list_noeud(lst_n[tour - 1], cree_noeud(p_new, genere_coup(p_new)));  
            score * s_fin = partie(p_new->j1, TOUR_MAX, p_new->sco);    //à changer
            if(s_fin->scorej1 > s_fin->scorej2){
                return 1;
            } else{
                return 0;
            }       
        }  
        return 0; //vraiment 0 ici car lorsque la partie est pas fini; on a pas encore de score final 
    } 
} 
 

lst_noeud ** utilisation_MCTS(int x){
    lst_noeud ** lst_n = cree_liste_noeud_2(TOUR_MAX);
    position * p_base;
    noeud * n_base;
    deck * d_IA;
    deck * d;
    for(int i = 0; i < x; i++){
        d_IA = generedeck(1, NULL);
        d = generedeck(1, d_IA);
        p_base = cree_position(1);
        p_base->j1->deck_joueur = d_IA;
        p_base->j2->deck_joueur = d;
        p_base->sco->nb_de_carte = 1;
        n_base = cree_noeud(p_base, genere_coup(p_base));
        float poubelle = mcts(lst_n, n_base);         //on a pas besoin de la valeur de retour de MCTS ici
        (void) poubelle;
    } 
    return lst_n;
}


coup * utilise_resultat(lst_noeud ** l_n, noeud * n){
    int tour = n->p->sco->nb_de_carte;
    coup * c_opti = NULL;
    noeud * n_lst = noeud_appartient(l_n[tour - 1], n->p);
    if(n_lst != NULL){
        c_opti = coup_interet(n_lst->l);
    } 
    return c_opti;
} 