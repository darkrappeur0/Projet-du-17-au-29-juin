#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "interface_graphique_autre.h"

typedef struct ZoneDeJeu{
    carte * cardo;
    SDL_Rect * card;
}ZoneDeJeu;

void SetMat(SDL_Texture * bg, SDL_Renderer * renderer, SDL_Window * window){
    SDL_Rect source = {0}, window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_QueryTexture(bg, NULL, NULL, &source.w, &source.h);
    destination = window_dimensions;
    SDL_RenderCopy(renderer, bg, &source, &destination);
}

SDL_Rect DisplayCardfrontj(SDL_Renderer * renderer, carte * card, SDL_Texture * paquet, int x, int y){
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
    return destination;
}

/*SDL_Rect DisplayCardbackj(SDL_Renderer * renderer, SDL_Texture * dos, int x, int y){
    SDL_Rect source = {0}, destination = {0};
    float zoom = 6;
    SDL_QueryTexture(dos, NULL, NULL, &source.w, &source.h);
    destination.w = source.w * zoom;
    destination.h = source.h * zoom;
    destination.x = x;
    destination.y = y;
    SDL_RenderCopy(renderer, dos, &source, &destination);
    return destination;
}*/

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

ZoneDeJeu * DisplayHandj(SDL_Renderer * renderer, SDL_Window * window, deck * hand, SDL_Texture * face){
    SDL_Rect window_dimensions = {0}, CartesEnMain = {0};
    ZoneDeJeu * mano = malloc(hand->nb_de_carte * sizeof(ZoneDeJeu));
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
        CartesEnMain = DisplayCardfrontj(renderer, haux->carte, face, x, y);
        mano[i].cardo = haux->carte;
        mano[i].card = &CartesEnMain;
        haux = haux->next;
    }
    return mano;
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

int GetPlis(){
    return 0;
}

void DisplayPlisCounter(SDL_Renderer * renderer, TTF_Font * font, int plis, int x, int y){
    SDL_Rect zone;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 140);
    zone.w = 300;
    zone.h = 200;
    zone.x = x;
    zone.y = y;
    SDL_RenderFillRect(renderer, &zone);
    
    SDL_Color color = {0, 0, 0, 255};
    SDL_Surface* text_surface = NULL;
    switch(plis){
        case 0 :
            text_surface = TTF_RenderText_Blended(font, "Plis Pris : 0", color);
            break;
        case 1 :
            text_surface = TTF_RenderText_Blended(font, "Plis Pris : 1", color);
            break;
        case 2 :
            text_surface = TTF_RenderText_Blended(font, "Plis Pris : 2", color);
            break;
        case 3 :
            text_surface = TTF_RenderText_Blended(font, "Plis Pris : 3", color);
            break;
        case 4 :
            text_surface = TTF_RenderText_Blended(font, "Plis Pris : 4", color);
            break;
        case 5 :
            text_surface = TTF_RenderText_Blended(font, "Plis Pris : 5", color);
            break;
        default :
            break;
    }
    SDL_Texture* text_texture = NULL;
    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_FreeSurface(text_surface);
    SDL_Rect pos = {0, 0, 0, 0};
    SDL_QueryTexture(text_texture, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(renderer, text_texture, NULL, &pos);
    SDL_DestroyTexture(text_texture);
}

void AfficheJeu(SDL_Renderer * renderer, SDL_Window * window, SDL_Texture * palette, carte * carteo, carte * cartej){
    SDL_Rect window_dimensions = {0};
    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    int x, yj, yo;
    x = (window_dimensions.w - (6*24))/2;
    yj = window_dimensions.h/2 + 5;
    yo = window_dimensions.h/2 - 37;
    DisplayCardfrontj(renderer, cartej, palette, x, yj);
    DisplayCardfronto(renderer, carteo, palette, x, yo);
}

carte * SelectCarte(ZoneDeJeu * jeu, int manche, int xclick, int yclick){
    carte * selectionnee = NULL;
    int i;
    for (i=0;i<manche;i++){
        if (xclick > jeu[i].card->x && yclick > jeu[i].card->y){
            if ((xclick < jeu[i].card->x + jeu[i].card->w) && (yclick < jeu[i].card->y + jeu[i].card->h)){
                selectionnee = jeu[i].cardo;
            }
        }
    }
    return selectionnee;
}

void PlayGame(SDL_Window * window, SDL_Renderer * renderer, SDL_Texture * bg, SDL_Texture * bak, SDL_Texture * fron, SDL_Texture * atoucarte, TTF_Font * font){
    SDL_bool running = SDL_TRUE;
    SDL_Event event;
    deck * deckp = generedeck(5,NULL);
    deck * decko = generedeck(5,NULL);
    ZoneDeJeu * zone;
    int atout;
    int xc;
    int yc;
    carte * selek = NULL;
    atout = update_atout();
    while (running){
        SDL_RenderClear(renderer);
        SetMat(bg, renderer, window);
        DisplayPlisCounter(renderer, font, 2, 1290, 690);
        DisplayHando(renderer, window, decko, bak);
        zone = DisplayHandj(renderer, window, deckp, fron);
        DisplayAtout(renderer, window, atoucarte, atout);
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT :
                    running = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONDOWN :
                    xc = event.button.x;
                    yc = event.button.y;
                    selek = SelectCarte(zone, 5, xc, yc);
                default :
                    break;
            }
        }
        AfficheJeu(renderer, window, fron, decko->carte, selek);
        SDL_RenderPresent(renderer);
    }
}

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TTF_Font * font = NULL;
    font = TTF_OpenFont("./Silkscreen/sklscr.ttf", 65);
    int z = 25;
    SDL_Window * window = NULL;
    window = SDL_CreateWindow("Jouez au Wizard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, z*64, z*36, 0);
    SDL_Renderer * renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Texture * bakgrond = NULL;
    bakgrond = IMG_LoadTexture(renderer, "ImagesWizard/Tapis.png");
    SDL_Texture * cardbak = NULL;
    cardbak = IMG_LoadTexture(renderer,"ImagesWizard/DosCarte.png");
    SDL_Texture * cardfron = NULL;
    cardfron = IMG_LoadTexture(renderer, "ImagesWizard/FullJeuDuWizard.png");
    SDL_Texture * atoutplank = NULL;
    atoutplank = IMG_LoadTexture(renderer, "ImagesWizard/Atouts.png");
    
    PlayGame(window, renderer, bakgrond, cardbak, cardfron, atoutplank, font);
    
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}