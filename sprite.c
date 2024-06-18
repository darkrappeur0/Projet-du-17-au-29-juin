#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <math.h>



 void affichagetotal(SDL_Texture * text, SDL_Window *win, SDL_Renderer *render){
    SDL_Rect dest={0};
    SDL_GetWindowSize(win, &(dest.w), &(dest.h));
    SDL_Rect source = {0};
    SDL_QueryTexture(text,NULL,NULL,&(source.w),&(source.h));
    SDL_RenderCopy(render, text, &source, &dest);
    SDL_RenderPresent(render);
    SDL_Delay(3000);
    SDL_RenderClear(render);
}
 void affichagetotal1(SDL_Texture * text, SDL_Window *win, SDL_Renderer *render){
    SDL_Rect dest={0};
    SDL_GetWindowSize(win, &(dest.w), &(dest.h));
    SDL_Rect source = {0};
    SDL_QueryTexture(text,NULL,NULL,&(source.w),&(source.h));
    SDL_RenderCopy(render, text, &source, &dest);
    SDL_RenderClear(render);
}

void affichagelocaliser(SDL_Texture* text,  SDL_Window* win, SDL_Renderer* render){
    SDL_Rect  source= {0};
    SDL_Rect  dest = {0};
    SDL_Rect  dim = {0};
    SDL_GetWindowSize(win, &(dim.w), &(dim.h));
    SDL_QueryTexture(text,NULL,NULL,&(source.w),&(source.h));
    float zoom = 1.5;
    dest.w=source.w*zoom;
    dest.h=source.h*zoom;
    dest.x = (dim.w - dest.w)/2 ;
    dest.y = (dim.h - dest.h )/2 ;
    SDL_RenderCopy(render,text,&source,&dest);
    SDL_RenderPresent(render);             
    SDL_Delay(1000);
    SDL_RenderClear(render);

}
void play_with_texture_3(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer) {
    SDL_Rect 
      source = {0},                             // Rectangle définissant la zone de la texture à récupérer
      window_dimensions = {0},                  // Rectangle définissant la fenêtre, on n'utilisera que largeur et hauteur
      destination = {0};                        // Rectangle définissant où la zone_source doit être déposée dans le renderer
                                
    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);                      // Récupération des dimensions de la fenêtre
    SDL_QueryTexture(my_texture, NULL, NULL,&source.w,&source.h);                    // Récupération des dimensions de l'image
                                
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
               (1 + cos(10.0 * i / nb_it * 2 *3.14)));            // hauteur en fonction du numéro d'image

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
               SDL_Renderer* renderer) {
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
     state.y = 3 * offset_y;                // On s'intéresse à la 4ème ligne, le bonhomme qui court
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
    for (int y = 0; y < source.h ; y += offset_y) {
      for (int x = 0; x < source.w; x += offset_x) {
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
    for (int cpt = 0; cpt < nb_images_animation ; ++cpt) {
      affichagetotal1(bg_texture,         // identique à play_with_texture_1, où on a enlevé l'affichage et la pause
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
    SDL_Window * win= SDL_CreateWindow("test1",0,0,1000,1000,SDL_WINDOW_RESIZABLE);
    SDL_Renderer * render = SDL_CreateRenderer( win, -1,SDL_RENDERER_PRESENTVSYNC);
    SDL_Surface * temp =NULL;
    SDL_Texture * image = NULL;
    temp = IMG_Load("perso_jeu.jpg");
    image = SDL_CreateTextureFromSurface(render, temp);
    temp = IMG_Load("fond-bleu-jpg");
    SDL_Texture * image2 = NULL;
    image2 = SDL_CreateTextureFromSurface(render, temp);
    play_with_texture_4(image,win,render);
    play_with_texture_5(image2,image,win,render);
    IMG_Quit();
    return 0;
}