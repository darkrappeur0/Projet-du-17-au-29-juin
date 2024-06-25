#include "InterfaceGraphique.h"
#include "Trad_logi_mcts.h"


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



int main(){
    
    return 0;
}