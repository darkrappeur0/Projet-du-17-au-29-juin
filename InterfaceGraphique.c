#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "interface_graphique_autre.h"

void SetMat(SDL_Texture * bg, SDL_Renderer * renderer, SDL_Window * window){
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(bg, NULL, NULL, &source.w, &source.h);
    destination = window_dimensions;
    SDL_RenderCopy(renderer, bg, &source, &destination);
}

void DisplayCardfrontj(SDL_Renderer * renderer, carte * card, SDL_Texture * paquet, int x, int y){
    SDL_Rect state = {0}, destination = {0};
    float zoom = 6;
    int offsetx = 24, offsety = 32;
    if (card->couleur < 4){
        state.x = card->num * offsetx;
        state.y = card->couleur * offsety;
        state.w = offsetx;
        state.h = offsety;
    }
    else if (card->couleur == 4){
        state.x = 0;
        state.y = 4 * offsetx;
        state.w = offsetx;
        state.h = offsety;
    }
    else if (card->couleur > 4){
        state.x = offsetx;
        state.y = 4 * offsety;
        state.w = offsetx;
        state.h = offsety;
    }
    destination.w = offsetx * zoom;
    destination.h = offsety * zoom;
    destination.x = x;
    destination.y = y;
    SDL_RenderCopy(renderer, paquet, &state, &destination);
}

void DisplayCardbackj(SDL_Renderer * renderer, SDL_Texture * dos, int x, int y){
    SDL_Rect source = {0}, destination = {0};
    float zoom = 6;
    SDL_QueryTexture(dos, NULL, NULL, &source.w, &source.h);
    destination.w = source.w * zoom;
    destination.h = source.h * zoom;
    destination.x = x;
    destination.y = y;
    SDL_RenderCopy(renderer, dos, &source, &destination);
}

void DisplayCardfronto(SDL_Renderer * renderer, carte * card, SDL_Texture * paquet, int x, int y){
    SDL_Rect state = {0}, destination = {0};
    float zoom = 6;
    int offsetx = 24, offsety = 32;
    if (card->couleur < 4){
        state.x = card->num * offsetx;
        state.y = card->couleur * offsety;
        state.w = offsetx;
        state.h = offsety;
    }
    else if (card->couleur == 4){
        state.x = 0;
        state.y = 4 * offsetx;
        state.w = offsetx;
        state.h = offsety;
    }
    else if (card->couleur > 4){
        state.x = offsetx;
        state.y = 4 * offsety;
        state.w = offsetx;
        state.h = offsety;
    }
    destination.w = offsetx * zoom;
    destination.h = offsety * zoom;
    destination.x = x;
    destination.y = y;
    SDL_RenderCopyEx(renderer, paquet, &state, &destination, 180, NULL, 0);
}

void DisplayCardbacko(SDL_Renderer * renderer, SDL_Texture * dos, int x, int y){
    SDL_Rect source = {0}, destination = {0};
    float zoom = 6;
    SDL_QueryTexture(dos, NULL, NULL, &source.w, &source.h);
    destination.w = source.w * zoom;
    destination.h = source.h * zoom;
    destination.x = x;
    destination.y = y;
    SDL_RenderCopyEx(renderer, dos, &source, &destination, 180, NULL, 0);
}

void DisplayHandj(SDL_Renderer * renderer, SDL_Window * window, deck * hand, SDL_Texture * face){
    SDL_Rect window_dimensions = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    deck * haux = hand;
    int x;
    int y;
    int i;
    for (i=0;i<hand->nb_de_carte;i++){
        if (i<(hand->nb_de_carte/2)){
            x = (window_dimensions.w/2) - (6*24)*(i+1);
            y = window_dimensions.h - 10 -(6*32);
        }
        else {
            x = (window_dimensions.w/2) + (6*24)*(i-(hand->nb_de_carte/2));
            y = window_dimensions.h - 10 -(6*32);
        }
        DisplayCardfrontj(renderer, haux->carte, face, x, y);
        haux = haux->next;
    }
}

void DisplayHando(SDL_Renderer * renderer, SDL_Window * window, deck * hand, SDL_Texture * dos){
    SDL_Rect window_dimensions = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    deck * haux = hand;
    int x;
    int y;
    int i;
    for (i=0;i<hand->nb_de_carte;i++){
        if (i<(hand->nb_de_carte/2)){
            x = (window_dimensions.w/2) - (6*24)*(i+1);
            y = 10;
        }
        else {
            x = (window_dimensions.w/2) + (6*24)*(i-(hand->nb_de_carte/2));
            y = 10;
        }
        DisplayCardbacko(renderer, dos, x, y);
        haux = haux->next;
    }
}

void DisplayAtout(SDL_Renderer * renderer, SDL_Window * window, SDL_Texture * palette, int coulatout){
    SDL_Rect window_dimensions = {0}, destination = {0}, source = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    float zoom = 12;
    int offsetx = 14, offsety = 15;
    int x;
    int y;
    source.x = coulatout * offsetx;
    source.y = 0;
    source.w = offsetx;
    source.h = offsety;
    destination.w = source.w * zoom;
    destination.h = source.h * zoom;
    x = window_dimensions.w/8;
    y = (window_dimensions.h-destination.h)/2;
    destination.x = x;
    destination.y = y;
    SDL_RenderCopy(renderer, palette, &source, &destination);
}

void PlayCarte(carte * jeu, deck * hand, ){

}

void SelectCarte(){
    
}

void PlaySDL(){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    int z = 25;
    SDL_Window * window = NULL;
    window = SDL_CreateWindow("Jouez au Wizard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, z*64, z*36, 0);
    SDL_Renderer * renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture * bakgrond = NULL;
    bakgrond = IMG_LoadTexture(renderer, "ImagesWizard/Tapis.png");
    SDL_Texture * cardbak = NULL;
    cardbak = IMG_LoadTexture(renderer,"ImagesWizard/DosCarte.png");
    SDL_Texture * cardfron = NULL;
    cardfron = IMG_LoadTexture(renderer, "ImagesWizard/FullJeuDuWizard.png");
    SDL_Texture * atoutplank = NULL;
    atoutplank = IMG_LoadTexture(renderer, "ImagesWizard/Atouts.png");
    SDL_bool running = SDL_TRUE;
    SDL_Event event;
    deck * deckp = generedeck(5,NULL);
    deck * decko = generedeck(5,NULL);
    int atout;
    atout = update_atout();
    while (running){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT :
                    running = SDL_FALSE;
                    break;
                default :
                    break;
            }
        }
        SDL_RenderClear(renderer);
        SetMat(bakgrond, renderer, window);
        DisplayHando(renderer, window, decko, cardbak);
        DisplayHandj(renderer, window, deckp, cardfron);
        DisplayAtout(renderer, window, atoutplank, atout);
        SDL_RenderPresent(renderer);
    }
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

int main(){
    PlaySDL();
    return 0;
}