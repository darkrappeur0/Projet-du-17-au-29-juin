#include "score.h"



score * creescore(){
    score * s = malloc(sizeof(score));
    s->scorej1=0;
    s->scorej2=0;
    s->nb_de_carte=0;
    return s;
}


int reglescore(int nb_plit_reel,int nb_plit_predit){
    int r=0;
    if (nb_plit_reel == nb_plit_predit){
        r= 10 + nb_plit_reel*10;
    }
    else{
        r = 10 + nb_plit_predit*10 - ( nb_plit_reel - nb_plit_predit)*10;
    }
    return r;
}


score * update_score (int nb_plit_j1, int nb_plit_j2, int nb_plit_preditj1, int nb_plit_preditj2, score * sprev ){
    score * s = sprev;
    s->scorej1 = sprev->scorej1 + reglescore(nb_plit_j1,nb_plit_preditj1);
    s->scorej2 = sprev->scorej2 + reglescore(nb_plit_j2,nb_plit_preditj2);
    s->nb_de_carte=sprev->nb_de_carte;
    return s;
}

score * update_score2 (score * snouv, score * sprev ){
    score * s = sprev;
    s->scorej1 = sprev->scorej1 + snouv->scorej1;
    s->scorej2 = sprev->scorej2 + snouv->scorej2;
    s->nb_de_carte=snouv->nb_de_carte;
    return s;
}



score * unepartie(deck * deckIA, int atout, int premierecarte){
    prediction * p = malloc(sizeof(prediction));
    p->nb_plit_preditj1 = predictionplistotal(deckIA,atout,premierecarte);
    deck * deckj2possible = generedeck(deckIA->nb_de_carte, deckIA);
    p->nb_plit_preditj2= predictionplistotal(deckj2possible,atout,premierecarte);
    pliseval(deckIA,deckj2possible, atout, premierecarte, &p->nb_plit_j1, &p->nb_plit_j2);
    score * s = creescore();
    s->nb_de_carte = deckIA->nb_de_carte;
    s = update_score(p->nb_plit_j1,p->nb_plit_j2,p->nb_plit_preditj1,p->nb_plit_preditj2,s);
    return s;
}


void displayscore(score * s){
    printf("score du j1 : %d\n", s->scorej1);
    printf("score du j2 : %d\n", s->scorej2);
    printf("nb de carte jouer: %d\n ", s->nb_de_carte);
}


int main(){
    
    score * s =  creescore();
    score * spartie =  creescore();
    int i =1;
    while (i != 10){
        srand(time(NULL));
        deck * coucou = generedeck(i,NULL);
        spartie->nb_de_carte = i;
        int d = i% 2;
        d=d+1;
        spartie = unepartie(coucou, 1, d);
        if (i == 1){
            s = spartie;
        }
        else{
            s = update_score2(spartie,s);
        }
        displayscore(s);
        i=i+1;
    }
    return 0;
}