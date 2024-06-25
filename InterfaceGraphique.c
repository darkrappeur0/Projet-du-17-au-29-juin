#include "InterfaceGraphique.h"

void SetMat(SDL_Texture * bg, SDL_Renderer * renderer, SDL_Window * window){
    SDL_Rect Source = {0}, window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(bg, NULL, NULL, &source.w, &source.h);
    destination = window_dimensions;
    SDL_RenderCopy(renderer, texture, &source, &destination);
}

ItemPaquet * Load_Cards(SDL_Texture * paquet, SDL_Texture * dos, SDL_Renderer * renderer, SDL_Window * window){
    paquet = IMG_LoadTexture(renderer,'./ImagesWizard/FullJeuDuWizard.png');
    dos = IMG_LoadTexture(renderer,'./ImagesWizard/DosCartes.png');
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0}, state[6][9];
    float zoom = 8;
    int deck = 54;
    int offsetx = 16, offsety = 32;
    int i;
    int j;
    ItemPaquet * pileCarte = malloc(sizeof(ItemPaquet));
    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;
    for (i=0;i<6;i++){
        for (j=0;j<9;j++){
            state[i][j].x = i * offsetx;
            state[i][j].y = j * offsety;
            state[i][j].w = offsetx;
            state[i][j].h = offsety;
            pileCarte->Carte->Face = state[i][j];
            pileCarte->Carte->Dos = dos;
            pileCarte->Carte->Objet = NULL;
        }
    }
    
}