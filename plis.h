#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef struct carte {
    int couleur;
    int num;
}carte;

typedef struct deck{
    int nb_de_carte;
    carte * carte;
    struct deck * next; 
}deck;

typedef struct joueur{
    int joueur;
    int nb_de_carte;
    int nb_de_plis_predit;
    int nb_de_plis_fait;
    deck * deck_joueur;
}joueur;


typedef struct prediction{
    int nb_plit_j1;
    int nb_plit_j2;
    int nb_plit_preditj1;
    int nb_plit_preditj2;
}prediction;





int membre (carte * x, deck * deck1);
carte * generecarte();
carte * generecartesansdoublons(deck * deck1, deck * deck2);
void displaycarte(carte * carte);
void displaydeck(deck * deck);
deck * generedeck(int nbdecarte, deck * deck1);
int moyenne1plis( int tab[][14],int n);
int evalplisj1( carte * cartejouerj1, carte * cartejouerj2, int atout,int premierecarte);
int update_premierecarte(int r);
int prediction1plis(carte * cartejouerj1,int atout,int premierecarte);
int predictionplistotal(deck * main1,int atout,int premierecarte);
void plispredic(deck * main, int atout, int premierecarte, prediction * plispredi, int j );
void pliseval(deck * deckIA, deck * deckj2, int atout, int j, int * nb_plit_j1, int * nb_plit_j2);
void freedeck(deck * deck1);