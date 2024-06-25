#include <stdlib.h>
#include <stdio.h>


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
}joueur;


typedef struct prediction{
    int nb_plit_j1;
    int nb_plit_j2;
    int nb_plit_preditj1;
    int nb_plit_preditj2;
}prediction;






carte * generecarte();
carte * generecartesansdoublons(deck * deck);
void displaycarte(carte * carte);
void displaydeck(deck * deck);
deck * generedeck(int nbdecarte);
int moyenne1plis( int tab[][14],int n);
int evalplis( carte * cartejouerj1, carte * cartejouerj2, int atout,int premierecarte);
int prediction1plis(carte * cartejouerj1,int atout,int premierecarte);
int predictionplistotal(deck * main1,int atout,int premierecarte);
void plispredic(deck * main, int atout, int premierecarte, prediction * plispredi, int j );
