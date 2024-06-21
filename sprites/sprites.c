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
SDL_Texture  * texture_fw;

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
    SDL_RenderPresent(renderer);                  // Affichage
    SDL_Delay(2000);                              // Pause en ms
    SDL_RenderClear(renderer);                    // Effacer la fenêtre
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

    void play_with_texture_5(SDL_Texture *bg_texture,
                 SDL_Texture *my_texture,
                 SDL_Window *window,
                 SDL_Renderer *renderer) {
    SDL_Rect
      source = {0},                             // Rectangle définissant la zone de la texture à récupérer
      window_dimensions = {0},                  // Rectangle définissant la fenêtre, on  n'utilisera que largeur et hauteur
      destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(window,                   // Récupération des dimensions de la fenêtre
              &window_dimensions.w, 
              &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL,    // Récupération des dimensions de l'image
             &source.w, &source.h); 

    int nb_images = 40;                         //  Il y a 8 vignette dans la ligne qui nous intéresse
    int nb_images_animation = 1 * nb_images;    // 
    float zoom = 2;                             // zoom, car ces images sont un peu petites
    int offset_x = source.w / 4,                // La largeur d'une vignette de l'image
    offset_y = source.h / 5;                // La hauteur d'une vignette de l'image
    SDL_Rect state[40];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

    /* construction des différents rectangles autour de chacune des vignettes de la planche */
    int i = 0;                                   
    for (int y = 0; y < source.h ; y += offset_y){
        for (int x = 0; x < source.w; x += offset_x){
            state[i].x = x;
            state[i].y = y;
            state[i].w = offset_x;
            state[i].h = offset_y;
            ++i;
        }
    }
                                                // ivaut 20 en sortie de boucle
    state[15]  = state[14]                      // on fabrique des images 14 et 15 en reprenant la 13  
              = state[13];                      // donc state[13 à 15] ont la même image, le monstre ne bouge pas   

    for(; i< nb_images ; ++i){                  // reprise du début de l'animation en sens inverse  
      state[i] = state[39-i];                   // 20 == 19 ; 21 == 18 ; ... 39 == 0  
    }

    destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
    destination.x = window_dimensions.w * 0.75; // Position en x pour l'affichage du sprite
    destination.y = window_dimensions.h * 0.7;  // Position en y pour l'affichage du sprite

    i = 0;
    for (int cpt = 0; cpt < nb_images_amination ; ++cpt) {
        charge_bg(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
                window, renderer); 
        SDL_RenderCopy(renderer,                  // Préparation de l'affichage
            my_texture, &state[i], &destination);
        i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique 
        SDL_RenderPresent(renderer);              // Affichage
        SDL_Delay(100);                           // Pause en ms
    }
    SDL_RenderClear(renderer);                  // Effacer la fenêtre avant de rendre la main
}


int main(){
    window = SDL_CreateWindow("X.fenêtré", x, y, 
                largeur, hauteur, 
                SDL_WINDOW_RESIZABLE); 
    
    if (window == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); 

    if (renderer == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    texture_fw = load_texture_from_image("Attack (1).png", window, renderer);
    texture_bg = load_texture_from_image("Attack (1).png", window, renderer);
    return 0;
} 