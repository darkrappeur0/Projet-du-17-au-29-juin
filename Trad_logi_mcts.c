#include "Trad_logi_mcts.h"
#include <string.h>

// on peut voir les cartes comme des machines a sous
// chaque carte dispose d'une espèrance plus ou moins bonne théoriquement -> selon des facteurs de la manche ( aka atout + le joueur qui commence)
// on choisit au début celle qui a la plus haute
// puis une fois jouée on modif son espérance
// on supprime cette machine des machines jouable
// on change ou pas l'espérance des autres carte avec celle qui a été déjà jouer en face si cela impacte fortement notre choix
// on regarde sur les machines restante et on répète jusqu'à ce qu'il n'y ait plus de machines
// puis on sort le score fait avec nos plis
// on affecte les nouvelles espérance au global
// et on retire des cartes pour le prochains tour
// et on recommence.

carte * traddemandej2( int couleur, int num){
    carte * cartejoueur = generecarte();
    cartejoueur->couleur = couleur;
    cartejoueur->num = num;
    return cartejoueur;
    
}

void freejoueur(joueur * j){
    freedeck(j->deck_joueur);
    free(j);
}


void freepos(position * p){
    free(p->carte_placee);
    freejoueur(p->j1);
    freejoueur(p->j2);
    free(p->sco);
    free(p);
}
void freecoup(coup * c){
    free(c->carte_placee);
    free(c->carte_jouee);
}
void freelistcoup(lst_coup * l){
    if (l!=NULL){
    freecoup(l->c);
    l=l->suiv;
    free(l);
    }
}
void freenoeud(noeud * n){
    freepos(n->p);
    freelistcoup(n->l);
}



void ini_manche_n( joueur * IA, joueur * J2, position * p,int atout,int z){
    displaydeck(J2->deck_joueur);
    //joueur * temp1 = p->j1;
    //joueur * temp2 = p->j2;
    p->j1 = IA;
    p->j2 = J2;
    p->sco = creescore();
    p->atout = atout;
    p->id_joueur = z;
    p->carte_placee=NULL;

}

position * fin_manche_n( position * p, score * scorefin,joueur * IA, joueur * J2){
    //p->id_joueur= (i % 2) + 1;
    p->j1 = IA;
    p->j2 = J2;
    p->sco= scorefin;
    return p;
}

void partie_de_manche_n(int i ,lst_noeud ** l_n, joueur * IA, joueur * J2, int atout,int x, int y, score * sco1, int z){
    printf("au début de la manche %d\n",i);
    position * p_théorique =cree_position(i);
    ini_manche_n(IA,J2, p_théorique,atout,z);


    printf("voici le deck du joueur IA\n");
    displaydeck(IA->deck_joueur);
    printf("\n");
    score * scotemp = creescore();
    
    
    int j = p_théorique->id_joueur;
        IA->nb_de_plis_predit = prediction1plis(IA->deck_joueur->carte,atout,p_théorique->id_joueur); //peut pas car applique coût renvoie 0
        J2->nb_de_plis_predit = prediction1plis(J2->deck_joueur->carte,atout,p_théorique->id_joueur);
        
        carte * carteIAjouer= malloc(sizeof(carte));
        carte * carteJ2jouer = malloc(sizeof(carte));
        noeud * n_manche ;
        coup * c;
        int couleur = y;
        int num =x;


        carteJ2jouer = traddemandej2(couleur, num); 
        if (p_théorique->id_joueur == 1){
            n_manche =cree_noeud(p_théorique, genere_coup(p_théorique));
            n_manche->p->carte_placee = NULL;
            noeud * n_try = noeud_appartient(l_n[i - 1], n_manche->p);
            if(n_try != NULL){
                c = coup_interet(n_try->l);
            } else{
                c= coup_interet(n_manche->l);
            } 

            if(c != NULL){
            carteIAjouer = c->carte_jouee;
            } else{
                carteIAjouer = n_manche->l->c->carte_jouee;
            } 
        }
        else {
            n_manche =cree_noeud(p_théorique, genere_coup(p_théorique));
            n_manche->p->carte_placee = carteJ2jouer;
            noeud * n_try = noeud_appartient(l_n[i - 1], n_manche->p);
            if(n_try != NULL){
                c = coup_interet(n_try->l);
            } else{
                c= coup_interet(n_manche->l);
            } 
            carteIAjouer = c->carte_jouee; 
        }

        //on fait un pli:

        plisevalindiv(carteIAjouer, carteJ2jouer ,atout, &p_théorique->id_joueur,&IA->nb_de_plis_fait,&J2->nb_de_plis_fait);//modif de p->id_joueur a l'interieur de la fonction

        IA->deck_joueur = IA->deck_joueur->next; // A garder
        J2->deck_joueur = J2->deck_joueur->next; // A GARDER

        
        // calcul du score

        sco1 = update_score(IA->nb_de_plis_fait,J2->nb_de_plis_fait,IA->nb_de_plis_predit,J2->nb_de_plis_predit,scotemp);

        //réactualisation de p_théorique
        IA->nb_de_plis_predit = IA->nb_de_plis_predit - IA->nb_de_plis_fait;
        J2->nb_de_plis_predit = J2->nb_de_plis_predit - J2->nb_de_plis_fait;
        IA->nb_de_plis_fait = 0;
        J2->nb_de_plis_fait = 0;
        fin_manche_n(p_théorique, scotemp,IA, J2);

        //freenoeud(n_manche);



    
    p_théorique->id_joueur = ( (j + 1) % 2 ) + 1 ;
    update_score2(sco1,scotemp);
    
}



