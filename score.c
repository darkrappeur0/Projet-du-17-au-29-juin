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
        r = 10 + nb_plit_predit*10 - abs(  nb_plit_reel - nb_plit_predit )*10; // a revoir si c'est exactement comme ça 
                                                                          // qu'on update le score
    }
    return r;
}
//                      Facultatif  

// a voir ou passe les précédent  pour vérifier les allocs

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
    free(snouv);
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
    free(p);
    freedeck(deckj2possible);
    return s;
}


void displayscore(score * s){
    printf("score du j1 : %d\n", s->scorej1);
    printf("score du j2 : %d\n", s->scorej2);
    printf("nb de carte jouer: %d\n ", s->nb_de_carte);
}

//on peut potentiellement faire une fonction qui dit le nb de plit par adversaire et qui le prennent en compte
//pour crée leur propre prédition.

// ameliorer l'allocation du tableau ou on stock les données des plis.

