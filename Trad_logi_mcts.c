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

carte * traddemandej2(char * couleur, int num){
    carte * cartejoueur = generecarte();
    if ( (strcmp("nain",couleur) == 0) | (strcmp("Nain", couleur) == 0) ){
        cartejoueur->couleur = 0;
    }
    else{
        if ( (strcmp("géant",couleur) == 0) | (strcmp("Géant", couleur) == 0) ){
            cartejoueur->couleur = 1;
        }
        else{
            if ( (strcmp("elf",couleur) == 0) | (strcmp("Elf", couleur) == 0) ){
                cartejoueur->couleur = 2;
            }
            else{
                if ( (strcmp("humain",couleur) == 0) | (strcmp("Humain", couleur) == 0) ){
                    cartejoueur->couleur = 3;
                }
                else{
                    if ( (strcmp("zarbi",couleur) == 0) | (strcmp("Zarbi", couleur) == 0) ){
                        cartejoueur->couleur = 4;
                    }
                    else{
                        if ( (strcmp("null",couleur) == 0) | (strcmp("Null", couleur) == 0) ){
                            cartejoueur->couleur = 5;
                        }
                        else{
                            printf("veuillez l'écrire sous la forme : nain ou Nain, géant ou Géant, elfe ou Elfe, humain ou Humain, zarbi ou Zarbi, null ou Null");
                        }
                    }
                }
            }
        }
    }
    cartejoueur->num = num;
    return cartejoueur;
    
}


void ini_manche_n(int i, joueur * IA, joueur * J2, position * p){
    IA->deck_joueur = generedeck(i,NULL);
    J2->deck_joueur=generedeck(i,IA->deck_joueur);
    displaydeck(J2->deck_joueur);
    //joueur * temp1 = p->j1;
    //joueur * temp2 = p->j2;
    p->j1 = IA;
    p->j2 = J2;
}

position * fin_manche_n(int i, position * p, score * scorefin,joueur * IA, joueur * J2){
    p->id_joueur= (i % 2) + 1;
    p->j1 = IA;
    p->j2 = J2;
    p->sco= scorefin;
    return p;
}

void manche_n(int i, joueur * IA, joueur * J2, int atout){
    
    position * p_théorique =cree_position();
    ini_manche_n(i,IA,J2, p_théorique);
    displaydeck(IA->deck_joueur);
    //noeud * n_manche =cree_noeud(p_théorique, genere_coup(p_théorique));
    //mcts( n,n_manche);
    int j = p_théorique->id_joueur;
    while (IA->deck_joueur!=NULL){
        carte * carteIAjouer;
        carte * carteJ2jouer;
        char * couleur = malloc(sizeof(char));
        int num =0;
        // scanf pour couleur
        // scanf pour num



        printf("quel type de carte voulez vous jouer?\n");
        scanf("%s\n", couleur);
        printf("quel est son numéro?\n");
        scanf("%d\n",&num);
        printf("combien de plis vos supposer faire?");
        scanf("%d\n",&J2->nb_de_plis_predit);



        carteJ2jouer = traddemandej2(couleur, num); 
        J2->deck_joueur= changement_pos_deck(J2->deck_joueur,carteJ2jouer); 
            

        carteIAjouer =  IA->deck_joueur->carte;   //cartemax(IA->deck_joueur, atout, p_théorique->id_joueur); // a changer 


        IA->deck_joueur = changement_pos_deck(IA->deck_joueur, carteIAjouer); // a garder

        IA->nb_de_plis_predit = prediction1plis(IA->deck_joueur->carte,atout,p_théorique->id_joueur); // a changer

        //on fait un pli:

        plisevalindiv(IA->deck_joueur->carte, J2->deck_joueur->carte,atout, &p_théorique->id_joueur,&IA->nb_de_plis_fait,&J2->nb_de_plis_fait);//modif de p->id_joueur a l'interieur de la fonction
        IA->deck_joueur = IA->deck_joueur->next; // A garder
        J2->deck_joueur = J2->deck_joueur->next; // A GARDER
        
        printf("%d\n", IA->nb_de_plis_fait);
        printf("%d\n", J2->nb_de_plis_fait);
        
        displaydeck(J2->deck_joueur);
        score * sco1 = creescore();
        sco1 = update_score(IA->nb_de_plis_fait,J2->nb_de_plis_fait,IA->nb_de_plis_predit,J2->nb_de_plis_predit,sco1);


        printf("\n");
        displayscore(sco1);
        printf("\n");
        //supprime_deck (IA->deck_joueur, carteIAjouer );
        //supprime_deck (J2->deck_joueur, carteJ2jouer );   
    }
    p_théorique->id_joueur = ( (j + 1) % 2 ) + 1 ;
}


void initialisationtrad(){
    joueur * IA = creejoueur(1);
    joueur * J2 = creejoueur(2);
    int r =1;

    //lst_noeud ** n = cree_liste_noeud_2(r);
    int i =1;
    int atout =0;
    while (i<=r){
        atout = update_atout();
        manche_n(i, IA, J2,atout );
        i=i+1;
    }
}

int main(){
    initialisationtrad();
    return 0;
}