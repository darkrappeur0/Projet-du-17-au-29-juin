#include <SDL2/SDL_video.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

SDL_Renderer * renderer;
SDL_Window   * window;

SDL_Texture  * texture_bg;
SDL_Texture  * nuage_bg;
SDL_Texture  * oiseau_bg;

SDL_Texture  * texture_fw1;
SDL_Texture  * texture_fw2;
SDL_Texture  * texture_fw3;
SDL_Texture  * texture_fw4;

int            x         = 100;
int            y         = 100;
int            hauteur   = 480;  
int            largeur   = 870;

SDL_Texture* load_texture_from_image(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    if (my_image == NULL){
        return NULL;
    } 
   
    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    if (my_texture == NULL){
        return NULL;
    } 

    return my_texture;
}

void charge_bg(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer){
    SDL_Rect 
        source = {0},                         // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
    window, &window_dimensions.w,
    &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
             &source.w, &source.h);       // Récupération des dimensions de l'image

    destination = window_dimensions;              // On fixe les dimensions de l'affichage à  celles de la fenêtre

    /* On veut afficher la texture de façon à ce que l'image occupe la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
           &source,
           &destination);                 // Création de l'élément à afficher
}

void charge_bg_h(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer, int p){
    SDL_Rect 
        source = {0},                         // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},              // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                    // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
    window, &window_dimensions.w,
    &window_dimensions.h);                    // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,
             &source.w, &source.h);       // Récupération des dimensions de l'image

    destination = window_dimensions;             // On fixe les dimensions de l'affichage à  celles de la fenêtre
    destination.h = window_dimensions.h * p / 100; 
    /* On veut afficher la texture de façon à ce que l'image occupe p% de la totalité de la fenêtre */

    SDL_RenderCopy(renderer, my_texture,
           &source,
           &destination);                 // Création de l'élément à afficher
} 

void loop_charge_fg(SDL_Texture *my_texture[] , SDL_Window *window, SDL_Renderer *renderer, int i, int y_perso){
    SDL_Rect 
        source = {0},                      // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
    window, &window_dimensions.w, &window_dimensions.h);               // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture[i % 3], NULL, NULL, &source.w, &source.h);  // Récupération des dimensions de l'image

    float zoom = 1;                        // Facteur de zoom à appliquer    
    destination.w = source.w * zoom;         // La destination est un zoom de la source
    destination.h = source.h * zoom;         // La destination est un zoom de la source
    destination.x = 25 * i % largeur;     // La destination est au milieu de la largeur de la fenêtre
    destination.y = y_perso;  // La destination est au milieu de la hauteur de la fenêtre

    SDL_RenderCopy(renderer, my_texture[i % 3], &source, &destination);
} 

void loop_charge_bg(SDL_Texture * my_texture , SDL_Window *window, SDL_Renderer *renderer, int v, int y_paysage, int x_depart, float z){
    SDL_Rect 
        source = {0},                      // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
    window, &window_dimensions.w, &window_dimensions.h);               // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);  // Récupération des dimensions de l'image

    float zoom = z;                        // Facteur de zoom à appliquer    
    destination.w = source.w * zoom;         // La destination est un zoom de la source
    destination.h = source.h * zoom;         // La destination est un zoom de la source
    destination.x = largeur - (x_depart + v) % (largeur + x + 10);     // La destination est au milieu de la largeur de la fenêtre
    destination.y = y_paysage;  // La destination est au milieu de la hauteur de la fenêtre

    SDL_RenderCopy(renderer, my_texture, &source, &destination);
} 



int main(){
    window = SDL_CreateWindow("sprites", x, y, 
                largeur, hauteur, 
                SDL_WINDOW_RESIZABLE); 
    
    if (window == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); 

    if (renderer == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    texture_bg = load_texture_from_image("sol.jpg", window, renderer);
    texture_fw1 = load_texture_from_image("perso1.png", window, renderer);
    texture_fw2 = load_texture_from_image("perso2.png", window, renderer);
    texture_fw3 = load_texture_from_image("perso3.png", window, renderer);
    texture_fw4 = load_texture_from_image("perso4.png", window, renderer);
    oiseau_bg = load_texture_from_image("oiseau.png", window, renderer);
    nuage_bg = load_texture_from_image("nuage.png", window, renderer);

    SDL_Texture * l[4];
    l[0] = texture_fw1;
    l[1] = texture_fw2;
    l[2] = texture_fw3;
    l[3] = texture_fw4;

    //charge_bg_h(texture_bg2, window, renderer, 30);

    for(int i = 0; i < 40; i++){
        charge_bg(texture_bg, window, renderer);
        loop_charge_bg(nuage_bg, window, renderer, 8 * i, 182, 100, 1.4);
        loop_charge_bg(nuage_bg, window, renderer, 8 * i, 181, 400, 1.4);
        loop_charge_bg(nuage_bg, window, renderer, 8 * i, 184, 700, 1.4);
        loop_charge_bg(oiseau_bg, window, renderer, 40 * i, 100, 200,0.9);
        loop_charge_bg(oiseau_bg, window, renderer, 40 * i, 70, 480, 0.9);
        loop_charge_bg(oiseau_bg, window, renderer, 40 * i, 100, 705, 0.9);
        loop_charge_bg(oiseau_bg, window, renderer, 40 * i, 70, 950, 0.9);
        loop_charge_fg(l, window, renderer, i, 235);
        SDL_RenderPresent(renderer);
        SDL_Delay(200); 
        SDL_RenderClear(renderer);
    } 


    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture_bg);
    SDL_DestroyTexture(texture_fw1);
    SDL_DestroyTexture(texture_fw2);
    SDL_DestroyTexture(texture_fw3);
    SDL_DestroyTexture(texture_fw4);
    IMG_Quit();
    return 0;
} 