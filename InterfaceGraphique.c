#include "InterfaceGraphique.h"

void SetMat(SDL_Texture * bg, SDL_Renderer * renderer, SDL_Window * window){
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(bg, NULL, NULL, &source.w, &source.h);
    destination = window_dimensions;
    SDL_RenderCopy(renderer, bg, &source, &destination);
}

ItemCarte ** Load_Cards(SDL_Texture * dos, SDL_Renderer * renderer){
    dos = IMG_LoadTexture(renderer,"ImagesWizard/DosCartes.png");
    SDL_Rect state[6][9];
    float zoom = 8;
    int offsetx = 16, offsety = 32;
    int i;
    int j;
    ItemCarte ** pileCarte = malloc(6 * sizeof(ItemCarte));
    for (i=0;i<6;i++){
        pileCarte[i] = malloc(9 * sizeof(ItemCarte*));
        for (j=0;j<9;j++){
            state[i][j].x = i * offsetx;
            state[i][j].y = j * offsety;
            state[i][j].w = offsetx * zoom;
            state[i][j].h = offsety * zoom;
            pileCarte[i][j].Face = &state[i][j];
            pileCarte[i][j].Dos = dos;
            pileCarte[i][j].Objet = NULL;
        }
    }
    return pileCarte;
}

void initialisationSDL(){
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
}
int main(){
    initialisationSDL();
    return 0;
}