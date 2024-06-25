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
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window * window = SDL_CreateWindow("Jouez au Wizard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64, 36, SDL_WINDOW_MAXIMIZED);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture * bakgrond = IMG_LoadTexture(renderer, "./ImagesWizard/Tapis.png");
    SetMat(bakgrond, renderer, window);
    SDL_RenderPresent(renderer);
    SDL_Delay(10000);
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}