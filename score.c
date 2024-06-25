#include "score.h"



score * creescore(){
    score * s = malloc(sizeof(score));
    s->scorej1=0;
    s->scorej2=0;
    s->nb_de_carte=0;
    return s;
}
joueur * creejoueur(int i){
    joueur * j = malloc(sizeof(joueur));
    j->joueur=i;
    j->nb_de_carte=0;
    j->nb_de_plis_predit=0;
    j->nb_de_plis_fait=0;
    return j;
}


int reglescore(int nb_plit_reel,int nb_plit_predit){
    int r=0;
    /* printf ("nombre de plit fait: %d\n", nb_plit_reel);
    printf ("nombre de plit supposer: %d\n", nb_plit_predit); */
    if (nb_plit_reel == nb_plit_predit){
        r= 10 + nb_plit_reel*10;
        
    }
    else{
        r = 10 + nb_plit_predit*10 - abs(nb_plit_reel - nb_plit_predit )*10; // a revoir si c'est exactement comme ça 
                                    // qu'on update le score
    }
    /* printf("nb de plis reel:%d dans la fonction regle score\n  ", nb_plit_reel);
    printf("nb de plis predit:%d dans la fonction regle score\n  ", nb_plit_predit);
    printf("le resultat du score: %d\n", r); */
    return r;
}
//                      Facultatif  

// a voir ou passe les précédent  pour vérifier les allocs

score * update_score (int nb_plit_j1, int nb_plit_j2, int nb_plit_preditj1, int nb_plit_preditj2, score * sprev ){
    score * s = sprev;
    //printf("score du précédent pli du joueur1:%d \n",sprev->scorej1 );
    s->scorej1 = sprev->scorej1 + reglescore(nb_plit_j1,nb_plit_preditj1);
    //printf("score du précédent pli du joueur2:%d \n",sprev->scorej2 );
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



score * unepartie(deck * deckIA, int atout, int premierecarte,int * predijoueur){
    prediction * p = malloc(sizeof(prediction));
    p->nb_plit_preditj1 = predictionplistotal(deckIA,atout,premierecarte);
    
    deck * deckj2possible = generedeck(deckIA->nb_de_carte, deckIA);
    /* printf("deck du joueur 1: \n");
    displaydeck(deckIA);
    printf("deck du joueur 2:\n");
    displaydeck(deckj2possible);
    printf("\n"); */
    p->nb_plit_preditj2= predictionplistotal(deckj2possible,atout,premierecarte);
    /* printf("nb de plis predit pour le joueur 1: %d\n", p->nb_plit_preditj1);
    printf("nb de plis predit pour le joueur 2: %d\n", p->nb_plit_preditj2); */
    pliseval(deckIA,deckj2possible, atout, premierecarte, &p->nb_plit_j1, &p->nb_plit_j2);
    
    /* printf("\n");
    printf("\n");
    printf("nombre de pli réaliser par le j1 : %d", p->nb_plit_j1);
    printf("\n");
    printf("\n");

    printf("\n");
    printf("\n");
    printf("nombre de pli réaliser par le j2 : %d", p->nb_plit_j2);
    printf("\n");
    printf("\n"); */






    score * s = creescore();
    s->nb_de_carte = deckIA->nb_de_carte;
    s = update_score(   p->nb_plit_j1,      p->nb_plit_j2,   p->nb_plit_preditj1,   p->nb_plit_preditj2,   s);
    *predijoueur = p->nb_plit_preditj1;

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


void testlogique(){
    int r = 0;
    score * s =  creescore();
    int i =1;
    score * spartie =  creescore();
    joueur * IA = creejoueur(i);
    int d =0;
    while (i != 20){ 
        srand(time(NULL));
        IA->nb_de_carte=i;
        IA->deck_joueur = generedeck(i,NULL);
        spartie->nb_de_carte = i;
        d = i% 2;
        r = update_atout();
        spartie = unepartie(IA->deck_joueur, r, d,&IA->nb_de_plis_predit);
        printf("nbdeplispredit: %d\n", IA->nb_de_plis_predit);
        if (i == 1){
            s = spartie;
        }
        else{
            s = update_score2(spartie,s);
            spartie = s;
        }
        displayscore(s);
        i=i+1;
        free(IA->deck_joueur);
    }
    
    free(IA);
    free(s);
}
