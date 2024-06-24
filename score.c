#include "score.h"



score * creescore(){
    score * s = malloc(sizeof(score));
    s->scorej1=0;
    s->scorej2=0;
    s->nb_de_carte=0;
    return s;
}


int reglescore(int nb_plit_reel,int nb_plit_predit){
    r=0;
    if (nb_plit_reel == nb_plit_predit){
        r= 10 + nb_plit_reel*10;
    }
    else{
        r = 10 + nb_plit_predit*10 - nb_plit_reel*10;
    }
    return r;
}


score * update_score (int nb_plit_j1, int nb_plit_j2, int nb_plit_preditj1, int nb_plit_preditj2, score * sprev ){
    score * s = sprev;
    s->scorej1 = reglescore(nb_plit_j1,nb_plit_preditj1);
    s->scorej2 = reglescore(nb_plit_j2,nb_plit_preditj2);
    s->nb_de_carte=s->nb_de_carte + 1;
    return s;
}