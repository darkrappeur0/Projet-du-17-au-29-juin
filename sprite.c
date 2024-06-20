#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <math.h>
SDL_Texture* load(char  *  file_image_name, SDL_Renderer *renderer ){
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



void play_with_texture_5(SDL_Texture *bg_texture,SDL_Texture *my_texture,SDL_Window *window,SDL_Renderer *renderer) {
    SDL_Rect source = {0},window_dimensions = {0},destination = {0};                        
    SDL_GetWindowSize(window,&window_dimensions.w, &window_dimensions.h); 
    SDL_QueryTexture(my_texture, NULL, NULL,&source.w, &source.h); 
    int nb_images = 5;                         //  Il y a 8 vignette dans la ligne qui nous intéresse 
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
    destination.y = 250;  // Position en y pour l'affichage du sprite
    int speed = 9;
    int y=250;
    int x=0;
    i =0; 
    play_with_texture_1_1(bg_texture,window, renderer); 
    SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
    i=i+1;                    // Passage à l'image suivante, le modulo car l'animation est cyclique 
    SDL_RenderPresent(renderer);
    int c=0;
    int h=0;
    
    while (c<20){
        x = x+speed;
        destination.x = x;
        play_with_texture_1_1(bg_texture,window, renderer); 
        SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
        i = (i + 1) % nb_images; 
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        c=c+1;
    }
    c=0;
    while (h<3){
    while (c<5){
        x = x+speed;
        y=y-speed;
        destination.x = x;
        destination.y= y;
        play_with_texture_1_1(bg_texture,window, renderer); 
        SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
        i = (i + 1) % nb_images; 
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        c=c+1;
    }
    c=0;
    while (c<5){
        x = x+speed/3;
        destination.x = x;
        play_with_texture_1_1(bg_texture,window, renderer); 
        SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
        i = (i + 1) % nb_images; 
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        c=c+1;
    }
    c=0;
    while (c<5){
        x = x+speed;
        y=y+speed;
        destination.x = x;
        destination.y= y;
        play_with_texture_1_1(bg_texture,window, renderer); 
        SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
        i = (i + 1) % nb_images; 
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        c=c+1;
    }
    c=0;
    while (c<5){
        y=y+speed/3;
        destination.y= y;
        play_with_texture_1_1(bg_texture,window, renderer); 
        SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
        i = (i + 1) % nb_images; 
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        c=c+1;
    }
    c=0;
    while (c<5){
        x = x-speed;
        y=y+speed;
        destination.x = x;
        destination.y= y;
        play_with_texture_1_1(bg_texture,window, renderer); 
        SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
        i = (i + 1) % nb_images; 
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        c=c+1;
    }
    c=0;
    while (c<5){
        x = x-speed/3;
        destination.x = x;
        play_with_texture_1_1(bg_texture,window, renderer); 
        SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
        i = (i + 1) % nb_images; 
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        c=c+1;
    }
    c=0;
    while (c<5){
        x = x-speed;
        y=y-speed;
        destination.x = x;
        destination.y= y;
        play_with_texture_1_1(bg_texture,window, renderer); 
        SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
        i = (i + 1) % nb_images; 
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        c=c+1;
    }
    c=0;
    while (c<5){
        y = y-speed/3;
        destination.y = y;
        play_with_texture_1_1(bg_texture,window, renderer); 
        SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
        i = (i + 1) % nb_images; 
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
        c=c+1;
    }
    c=0;
    
    

    h=h+1;
    }
    

    play_with_texture_1_1(bg_texture,window, renderer); 
    SDL_RenderCopy(renderer,my_texture, &state[i], &destination);
    i = (i + 1) % nb_images;                  // Passage à l'image suivante, le modulo car l'animation est cyclique 
    SDL_RenderPresent(renderer);              // Affichage
    SDL_Delay(80);                          // Pause en ms
             
         
    
    SDL_RenderClear(renderer);                  // Effacer la fenêtre avant de rendre la main
}

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win= SDL_CreateWindow("test1",0,0,500,500,SDL_WINDOW_RESIZABLE);
    SDL_Renderer * render = SDL_CreateRenderer( win, -1,SDL_RENDERER_PRESENTVSYNC);  
    SDL_Texture * l;
    SDL_Texture * l2;
    l = load("sprite.png",render);
    l2 = load("Fond-Topitop.png",render);
    
    play_with_texture_5(l2,l,win,render);
    SDL_DestroyRenderer( render);
    SDL_DestroyWindow(win);
    SDL_Quit();
return 0;
} 