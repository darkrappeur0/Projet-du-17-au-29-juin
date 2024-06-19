#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <math.h>
SDL_Texture* load(char  *  file_image_name, SDL_Window *window, SDL_Renderer *renderer ){
    SDL_Surface *my_image = NULL;           // Variable de passage
    SDL_Texture* my_texture = NULL;         // La texture

    my_image = IMG_Load(file_image_name);   // Chargement de l'image dans la surface
                                            // image=SDL_LoadBMP(file_image_name); fonction standard de la SDL, 
                                            // uniquement possible si l'image est au format bmp */
    my_texture = SDL_CreateTextureFromSurface(renderer, my_image); // Chargement de l'image de la surface vers la texture
    SDL_FreeSurface(my_image);                                     // la SDL_Surface ne sert que comme élément transitoire 
    return my_texture;
}
void play_with_texture_1_1(SDL_Texture *my_texture, SDL_Window *window,SDL_Renderer *renderer) {
                 SDL_Rect source = {0}, window_dimensions = {0},destination = {0};                    
    SDL_GetWindowSize(window, &window_dimensions.w,&window_dimensions.h);                    
    SDL_QueryTexture(my_texture, NULL, NULL,&source.w, &source.h); 
    destination = window_dimensions;              
    SDL_RenderCopy(renderer, my_texture,&source,&destination);                 
    
}

void anim_manuel(SDL_Texture* my_texture,SDL_Window* window,SDL_Renderer* renderer) {
    SDL_Rect source = {0},window_dimensions = {0},destination = {0},state = {0};                      
    SDL_GetWindowSize(window,&window_dimensions.w,&window_dimensions.h);
    SDL_QueryTexture(my_texture,NULL, NULL,&source.w, &source.h);
    int nb_images = 2;                     
    float zoom = 2;                        
    int offset_x = 32, offset_y = 32;           
    state.x = 0,state.y = 0 ;                           
    state.w = offset_x;                    // Largeur de la vignette
    state.h = offset_y;                    // Hauteur de la vignette
    destination.w = offset_x * zoom;       // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;       // Hauteur du sprite à l'écran
    destination.y =  (window_dimensions.h - destination.h)/2;  
    destination.x=0;                  
    int speed = 9;
    bool run = true;
    int y=0;
    int x=0;
    while(run){
        SDL_Event event;
         while (SDL_PollEvent(&event)){
             switch(event.type){
                 case SDL_QUIT:
                    run = false;
                    printf("fin\n");
                    break;
                 case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_d){
                         SDL_Log("clavier touche d");
                         x = x + speed;
                    }
                    if (event.key.keysym.sym == SDLK_q){
                         SDL_Log("clavier touche q");
                         x = x - speed;
                    }
                     if (event.key.keysym.sym == SDLK_s){
                         SDL_Log("clavier touche s");
                         y = y + speed;   
                    }
                    if (event.key.keysym.sym == SDLK_z){
                         SDL_Log("clavier touche z");
                         y = y - speed;  
                    }
                    destination.x = x;
                    destination.y= y;
                    state.x += offset_x;                 // On passe à la vignette suivante dans l'image
                    state.x %= source.w;
                    SDL_RenderClear(renderer);           // Effacer l'image précédente avant de dessiner la nouvelle
                    SDL_RenderCopy(renderer, my_texture, &state,&destination);  
                    SDL_RenderPresent(renderer);         // Affichage
                    SDL_Delay(80);
                    break;
             }
         }
    }
    SDL_RenderClear(renderer);             // Effacer la fenêtre avant de rendre la main
}

void play_with_texture_5(SDL_Texture *bg_texture,SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer) {
    SDL_Rect source = {0},window_dimensions = {0},destination = {0};                        
    SDL_GetWindowSize(window,&window_dimensions.w, &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL,&source.w, &source.h); 
    int nb_images = 5;                         //  Il y a 8 vignette dans la ligne qui nous intéresse
    int nb_images_animation = 1 * nb_images;    // 
    float zoom = 2;                             // zoom, car ces images sont un peu petites
    int offset_x = 32,                // La largeur d'une vignette de l'image
    offset_y = 32;                // La hauteur d'une vignette de l'image
    SDL_Rect state[6];                         // Tableau qui stocke les vignettes dans le bon ordre pour l'animation

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
    destination.w = offset_x * zoom;            // Largeur du sprite à l'écran
    destination.h = offset_y * zoom;            // Hauteur du sprite à l'écran
    destination.x = 0; // Position en x pour l'affichage du sprite
    destination.y = 0;  // Position en y pour l'affichage du sprite
    int speed = 9;
    bool run = true;
    int y=0;
    int x=0;
    while(run){
        SDL_Event event;
         while (SDL_PollEvent(&event)){
             switch(event.type){
                 case SDL_QUIT:
                    run = false;
                    printf("fin\n");
                    break;
                 case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_d){
                         SDL_Log("clavier touche d");
                         x = x + speed;
                    }
                    if (event.key.keysym.sym == SDLK_q){
                         SDL_Log("clavier touche q");
                         x = x - speed;
                    }
                     if (event.key.keysym.sym == SDLK_s){
                         SDL_Log("clavier touche s");
                         y = y + speed;   
                    }
                    if (event.key.keysym.sym == SDLK_z){
                         SDL_Log("clavier touche z");
                         y = y - speed;  
                    }
                    destination.x = x;
                    destination.y= y;
                    play_with_texture_1_1(bg_texture,window, renderer); 
                    SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
                    i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique 
                    SDL_RenderPresent(renderer);              // Affichage
                    SDL_Delay(80);                          // Pause en ms
             }
         }
    }
    SDL_RenderClear(renderer);                  // Effacer la fenêtre avant de rendre la main
}

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win= SDL_CreateWindow("test1",0,0,200,200,SDL_WINDOW_RESIZABLE);
    SDL_Renderer * render = SDL_CreateRenderer( win, -1,SDL_RENDERER_PRESENTVSYNC);  
    SDL_Texture * l;
    SDL_Texture * l2;
    l = load("sprite.png",win,render);
    l2 = load("fond-bleu.jpg",win,render);
    //anim_manuel(l,win,render);
    play_with_texture_5(l2,l,win,render);
    SDL_DestroyRenderer( render);
    SDL_DestroyWindow(win);
    SDL_Quit();
return 0;
} 