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
SDL_Texture  * texture;
SDL_Event      event;

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

void play_with_texture_1(SDL_Texture *my_texture, SDL_Window *window, SDL_Renderer *renderer){
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
    SDL_RenderPresent(renderer);                  // Affichage
    SDL_Delay(2000);                              // Pause en ms

    SDL_RenderClear(renderer);                    // Effacer la fenêtre
}

void play_with_texture_2(SDL_Texture* my_texture, SDL_Window* window, SDL_Renderer* renderer){
    SDL_Rect 
        source = {0},                      // Rectangle définissant la zone de la texture à récupérer
        window_dimensions = {0},           // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0};                 // Rectangle définissant où la zone_source doit être déposée dans le renderer

    SDL_GetWindowSize(
    window, &window_dimensions.w, &window_dimensions.h);               // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL, &source.w, &source.h);  // Récupération des dimensions de l'image

    float zoom = 1.5;                        // Facteur de zoom à appliquer    
    destination.w = source.w * zoom;         // La destination est un zoom de la source
    destination.h = source.h * zoom;         // La destination est un zoom de la source
    destination.x = (window_dimensions.w - destination.w) /2;     // La destination est au milieu de la largeur de la fenêtre
    destination.y = (window_dimensions.h - destination.h) / 2;  // La destination est au milieu de la hauteur de la fenêtre

    SDL_RenderCopy(renderer, my_texture, &source, &destination);     // Préparation de l'affichage              
    SDL_RenderPresent(renderer);             
    SDL_Delay(1000);                         

    SDL_RenderClear(renderer);               // Effacer la fenêtre
}

void play_with_texture_3(SDL_Texture* my_texture,
               SDL_Window* window,
               SDL_Renderer* renderer) {
    SDL_Rect 
      source = {0},                             // Rectangle définissant la zone de la texture à récupérer
      window_dimensions = {0},                  // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
      destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer
                                
    SDL_GetWindowSize(                      
    window, &window_dimensions.w,               
    &window_dimensions.h);                      // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,         
                     &source.w,                 
             &source.h);                    // Récupération des dimensions de l'image
                                
    /* On décide de déplacer dans la fenêtre         cette image */
    float zoom = 0.25;                              // Facteur de zoom entre l'image source et l'image affichée
                                
    int nb_it = 200;                                // Nombre d'images de l'animation
    destination.w = source.w * zoom;                // On applique le zoom sur la largeur
    destination.h = source.h * zoom;                // On applique le zoom sur la hauteur
    destination.x =                     
    (window_dimensions.w - destination.w) / 2;  // On centre en largeur
    float h = window_dimensions.h - destination.h;  // hauteur du déplacement à effectuer

    for (int i = 0; i < nb_it; ++i) {
      destination.y =
      h * (1 - exp(-5.0 * i / nb_it) / 2 *
               (1 + cos(10.0 * i / nb_it * 2 *
                M_PI)));            // hauteur en fonction du numéro d'image

      SDL_RenderClear(renderer);                    // Effacer l'image précédente

      SDL_SetTextureAlphaMod(my_texture,(1.0-1.0*i/nb_it)*255);      // L'opacité va passer de 255 à 0 au fil de l'animation
      SDL_RenderCopy(renderer, my_texture, &source, &destination);   // Préparation de l'affichage
      SDL_RenderPresent(renderer);                  // Affichage de la nouvelle image
      SDL_Delay(30);                                // Pause en ms
    }                               
    SDL_RenderClear(renderer);                      // Effacer la fenêtre une fois le travail terminé
}

void play_with_texture_4(SDL_Texture* my_texture,
               SDL_Window* window,
               SDL_Renderer* renderer){
    SDL_Rect 
        source = {0},                    // Rectangle définissant la zone totale de la planche
        window_dimensions = {0},         // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
        destination = {0},               // Rectangle définissant où la zone_source doit être déposée dans le renderer
        state = {0};                     // Rectangle de la vignette en cours dans la planche 

    SDL_GetWindowSize(window,              // Récupération des dimensions de la fenêtre
            &window_dimensions.w,
            &window_dimensions.h);
    SDL_QueryTexture(my_texture,           // Récupération des dimensions de l'image
            NULL, NULL,
            &source.w, &source.h);

     /* Mais pourquoi prendre la totalité de l'image, on peut n'en afficher qu'un morceau, et changer de morceau :-) */

    int nb_images = 8;                     // Il y a 8 vignette dans la ligne de l'image qui nous intéresse
    float zoom = 2;                        // zoom, car ces images sont un peu petites
    int offset_x = source.w / nb_images,   // La largeur d'une vignette de l'image, marche car la planche est bien réglée
        offset_y = source.h / 4;           // La hauteur d'une vignette de l'image, marche car la planche est bien réglée
       

    state.x = 0 ;                          // La première vignette est en début de ligne
    state.y = offset_y;                    // On s'intéresse à la 4ème ligne, le bonhomme qui court
    state.w = offset_x;                    // Largeur de la vignette
    state.h = offset_y;                    // Hauteur de la vignette

    destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran

    destination.y =                        // La course se fait en milieu d'écran (en vertical)
       (window_dimensions.h - destination.h) /2;

    int speed = 9;
    for (int x = 0; x < window_dimensions.w - destination.w; x += speed) {
        destination.x = x;                   // Position en x pour l'affichage du sprite
        state.x += offset_x;                 // On passe à la vignette suivante dans l'image
        state.x %= source.w;                 // La vignette qui suit celle de fin de ligne est
                        // celle de début de ligne

    SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
    SDL_RenderCopy(renderer, my_texture, // Préparation de l'affichage
            &state,
            &destination);  
    SDL_RenderPresent(renderer);         // Affichage
    SDL_Delay(80);                       // Pause en ms
    }
    SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
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

    texture = load_texture_from_image("Attack (1).png", window, renderer);
    //play_with_texture_1(texture, window, renderer);
    //play_with_texture_2(texture, window, renderer);
    play_with_texture_3(texture, window, renderer);
    //play_with_texture_4(texture, window, renderer);
    IMG_Quit();
    return 0;
} 
 