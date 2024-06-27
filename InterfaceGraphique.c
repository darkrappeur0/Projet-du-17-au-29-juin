#include "InterfaceGraphique.h"

void SetMat(SDL_Texture * bg, SDL_Renderer * renderer, SDL_Window * window){
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(bg, NULL, NULL, &source.w, &source.h);
    destination = window_dimensions;
    SDL_RenderCopy(renderer, bg, &source, &destination);
}

ItemCarte ** LoadCards(SDL_Texture * dos){
    SDL_Rect sourced = {0}, state[5][13];
    float zoom = 8;
    int offsetx = 16, offsety = 32;
    int i;
    int j;
    ItemCarte ** pileCarte = malloc(5 * sizeof(ItemCarte*));
    SDL_QueryTexture(dos, NULL, NULL, &sourced.w, &sourced.h);
    for (i=0;i<5;i++){
        pileCarte[i] = malloc(13 * sizeof(ItemCarte));  
    }
    for (i=0;i<5;i++){
        if (i<4){
            for (j=0;j<13;j++){
                state[i][j].x = i * offsetx;
                state[i][j].y = j * offsety;
                state[i][j].w = offsetx * zoom;
                state[i][j].h = offsety * zoom;
                pileCarte[i][j].Face = &state[i][j];
                pileCarte[i][j].Dos = &sourced;
            }
        }
        else if (i == 4){
            for (j=0;j<2;j++){
                state[i][j].x = i * offsetx;
                state[i][j].y = j * offsety;
                state[i][j].w = offsetx * zoom;
                state[i][j].h = offsety * zoom;
                pileCarte[i][j].Face = &state[i][j];
                pileCarte[i][j].Dos = &sourced;
            }
        }
    }
    return pileCarte;
}

void DisplayHands(SDL_Renderer * renderer, SDL_Window * window, SDL_Texture * dos, ItemCarte ** paquet, deck * opponenthand, deck * playerhand){
    SDL_Rect sourcef = {0}, sourced = {0}, window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_Texture * face = NULL;
    face = IMG_LoadTexture(renderer, "ImagesWizard/FullJeuDuWizard.png");
    SDL_QueryTexture(face, NULL, NULL, &sourcef.w, &sourcef.h);
    SDL_QueryTexture(dos, NULL, NULL, &sourced.w, &sourced.h);
    int i;
    if (opponenthand->nb_de_carte == playerhand->nb_de_carte){
        for (i=0;i<opponenthand->nb_de_carte;i++){
            //main du joueur
            destination.w = paquet[playerhand[i].carte->couleur][playerhand[i].carte->num].Face->w;
            destination.h = paquet[playerhand[i].carte->couleur][playerhand[i].carte->num].Face->h;
            destination.x = (window_dimensions.w - i * paquet[playerhand[i].carte->couleur][playerhand[i].carte->num].Face->w)/2;
            destination.y = window_dimensions.h - (10 + paquet[playerhand[i].carte->couleur][playerhand[i].carte->num].Face->h);
            SDL_RenderCopy(renderer, face, &sourcef, &destination);
        }
        for (i=0;i<opponenthand->nb_de_carte;i++){
            //main du joueur
            destination.w = paquet[opponenthand[i].carte->couleur][opponenthand[i].carte->num].Dos->w;
            destination.h = paquet[opponenthand[i].carte->couleur][opponenthand[i].carte->num].Dos->h;
            destination.x = (window_dimensions.w - i * paquet[opponenthand[i].carte->couleur][opponenthand[i].carte->num].Dos->w)/2;
            destination.y = 10 + paquet[opponenthand[i].carte->couleur][opponenthand[i].carte->num].Dos->h;
            SDL_RenderCopy(renderer, dos, &sourced, &destination);
        }
    }
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
    SDL_bool running = SDL_TRUE;
    SDL_Event event;
    deck * deckp = generedeck(1,NULL);
    deck * decko = generedeck(1,NULL);
    ItemCarte ** pack = LoadCards(cardbak);
    while (running){
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT :
                    running = SDL_FALSE;
                    break;
                default :
                    SDL_RenderClear(renderer);
                    SetMat(bakgrond, renderer, window);
                    DisplayHands(renderer, window, cardbak, pack, decko, deckp);
                    SDL_RenderPresent(renderer);
                    break;
            }
        }
    }
    free(pack);
    pack = NULL;
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