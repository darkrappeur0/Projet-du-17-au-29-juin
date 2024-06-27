#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Trad_logi_mcts.h"

void SetMat(SDL_Texture * bg, SDL_Renderer * renderer, SDL_Window * window){
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(bg, NULL, NULL, &source.w, &source.h);
    destination = window_dimensions;
    SDL_RenderCopy(renderer, bg, &source, &destination);
}

void DisplayCardfront(SDL_Renderer * renderer, carte * card, SDL_Texture * paquet, int x, int y){
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
    //SDL_Texture * cardbak = NULL;
    //cardbak = IMG_LoadTexture(renderer,"ImagesWizard/DosCarte.png");
    SDL_Texture * cardfron = NULL;
    cardfron = IMG_LoadTexture(renderer, "ImagesWizard/FullJeuDuWizard.png");
    SDL_bool running = SDL_TRUE;
    SDL_Event event;
    deck * deckp = generedeck(1,NULL);
    deck * decko = generedeck(1,NULL);
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
        DisplayCardfront(renderer, deckp->carte, cardfron, 750, 10);
        DisplayCardfront(renderer, decko->carte, cardfron, 750, 490);
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