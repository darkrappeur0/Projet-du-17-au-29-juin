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


void ini_manche_n( joueur * IA, joueur * J2, position * p){
    displaydeck(J2->deck_joueur);
    //joueur * temp1 = p->j1;
    //joueur * temp2 = p->j2;
    p->j1 = IA;
    p->j2 = J2;
}

position * fin_manche_n( position * p, score * scorefin,joueur * IA, joueur * J2){
    //p->id_joueur= (i % 2) + 1;
    p->j1 = IA;
    p->j2 = J2;
    p->sco= scorefin;
    return p;
}

void manche_n( joueur * IA, joueur * J2, int atout,int x, int y, score * sco1){
    
    position * p_théorique =cree_position();
    ini_manche_n(IA,J2, p_théorique);
    displaydeck(IA->deck_joueur);
    IA->nb_de_plis_predit = prediction1plis(IA->deck_joueur->carte,atout,p_théorique->id_joueur); //peut pas car applique coût renvoie 0
    int j = p_théorique->id_joueur;
    while (IA->deck_joueur!=NULL){
        noeud * n_manche =cree_noeud(p_théorique, genere_coup(p_théorique));
        carte * carteIAjouer= malloc(sizeof(carte));
        carte * carteJ2jouer = malloc(sizeof(carte));
        coup * c;
        int couleur = y;
        int num =x;


        carteJ2jouer = traddemandej2(couleur, num); 
        displaycarte(carteJ2jouer);
        J2->deck_joueur= changement_pos_deck(J2->deck_joueur,carteJ2jouer); 
        if (p_théorique->id_joueur == 1){
        c= coup_interet(n_manche->l);
        carteIAjouer = c->carte_jouee;
        IA->deck_joueur = changement_pos_deck(IA->deck_joueur, carteIAjouer); // a garder
        }
        else {
            c= coup_interet(n_manche->l);
            carteIAjouer = c->carte_jouee;
            IA->deck_joueur = changement_pos_deck(IA->deck_joueur, carteIAjouer);
        }

        //on fait un pli:

        plisevalindiv(IA->deck_joueur->carte, J2->deck_joueur->carte,atout, &p_théorique->id_joueur,&IA->nb_de_plis_fait,&J2->nb_de_plis_fait);//modif de p->id_joueur a l'interieur de la fonction
        //supprime_deck(IA->deck_joueur, carteIAjouer );
        //supprime_deck(J2->deck_joueur, carteJ2jouer ); 
        IA->deck_joueur = IA->deck_joueur->next; // A garder
        J2->deck_joueur = J2->deck_joueur->next; // A GARDER
        
        printf("%d\n", IA->nb_de_plis_fait);
        printf("%d\n", J2->nb_de_plis_fait);
        
        displaydeck(J2->deck_joueur);
        // calcul du score
        sco1 = update_score(IA->nb_de_plis_fait,J2->nb_de_plis_fait,IA->nb_de_plis_predit,J2->nb_de_plis_predit,sco1);


        //réactualisation de p_théorique
        IA->nb_de_plis_predit = IA->nb_de_plis_predit - IA->nb_de_plis_fait;
        J2->nb_de_plis_predit = J2->nb_de_plis_predit - J2->nb_de_plis_fait;
        IA->nb_de_plis_fait = 0;
        J2->nb_de_plis_fait = 0;
        fin_manche_n(p_théorique, sco1,IA, J2);

        freenoeud(n_manche);



    }
    p_théorique->id_joueur = ( (j + 1) % 2 ) + 1 ;
}


void initialisationtrad(){
    joueur * IA = creejoueur(1);
    joueur * J2 = creejoueur(2);
    int r =1;
    int i =1;
    int atout =0;
    score * sco1 = creescore();
    while (i<=r){
        atout = update_atout();
        IA->deck_joueur = generedeck(i,NULL);
        J2->deck_joueur=generedeck(i,IA->deck_joueur);
        manche_n( IA, J2,atout,J2->deck_joueur->carte->num,J2->deck_joueur->carte->couleur,sco1 );
        i=i+1;
    }
}


int main(){
    initialisationtrad();
    return 0;
}