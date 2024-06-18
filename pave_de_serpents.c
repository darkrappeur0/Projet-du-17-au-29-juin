#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Renderer * renderer;
SDL_Window   * window;
SDL_Event      event;

int            x_f       = 550;
int            y_f       = 300;
int            hauteur   = 480;  
int            largeur   = 870;  
int            c         = 10;

int            running  = 1;

int * liste_fibonacci(int n){
    int * l = malloc(n * sizeof(int));
    l[0] = 0;
    l[1] = 1;

    for(int i = 2; i < n; i++){
        l[i] = l[i - 1] + l[i - 2];   
    }   
    return l;
} 


void dessiner_carre(int x, int y, int c, int r, int g, int b) {
   /* dessine un carré de centre (x, y) ce côté c*/
   SDL_Rect rect;

   /* dessiner en blanc */
   SDL_SetRenderDrawColor(renderer, r, g, b, 255);
   rect.x = x; 
   rect.y = y;
   rect.w = rect.h = c;
   SDL_RenderFillRect(renderer, &rect );

   /* afficher le renderer dans la fenetre */
   SDL_RenderPresent(renderer);
}   

int main(){ 
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        return EXIT_FAILURE; 
    }

    window = SDL_CreateWindow("pave_fibbo", x_f, y_f, 
                largeur, hauteur, 
                SDL_WINDOW_RESIZABLE); 

    if (window == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); 

    if (renderer == 0) {
     fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    int n = 9;
    int * lf = liste_fibonacci(n);

    dessiner_carre(x_f, y_f, c * lf[1], 255, 255, 255);
    x_f = x_f + c * lf[1];
    SDL_Delay(5000 / lf[1]);
    dessiner_carre(x_f, y_f, c * lf[2], 240, 240, 240);
    x_f = x_f - c * lf[1];
    y_f = y_f - c * lf[3];
    SDL_Delay(5000 / lf[2]);
    dessiner_carre(x_f, y_f, c * lf[3], 225, 225, 225);
    x_f = x_f - c * lf[4]; 
    SDL_Delay(5000 / lf[3]);
    dessiner_carre(x_f, y_f, c * lf[4], 210, 210, 210);
    y_f = y_f + c * lf[4];
    SDL_Delay(5000 / lf[4]);
    dessiner_carre(x_f, y_f, c * lf[5], 195, 195, 195);
    x_f = x_f + c * lf[5];
    y_f = y_f - c * lf[4]; 
    SDL_Delay(5000 / lf[5]);
    dessiner_carre(x_f, y_f, c * lf[6], 180, 180, 180); 
    x_f = x_f - c * lf[5];
    y_f = y_f - c * lf[7]; 
    SDL_Delay(5000 / lf[6]);
    dessiner_carre(x_f, y_f, c * lf[7], 165, 165, 165);  
    x_f = x_f - c * lf[8]; 
    SDL_Delay(5000 / lf[7]);
    dessiner_carre(x_f, y_f, c * lf[8], 140, 140, 140);

    free(lf);
    SDL_Delay(5000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
