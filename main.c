#include "InterfaceGraphique.h"


#include "Trad_logi_mcts.h"
int main(){
    score * s =  creescore();
    int i =1;
    score * spartie =  creescore();
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
            spartie = s;
        }
        displayscore(s);
        i=i+1;
        freedeck(coucou);
    }
    free(s);
    return 0;
}