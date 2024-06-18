#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
 

SDL_Window   * window;
SDL_Window   * window1;
SDL_Window   * window2;
SDL_Window   * window3;
SDL_Window   * window4;
SDL_Window   * window5;
SDL_Event      event;

int            x         = 200;
int            y         = 200;
int            hauteur   = 480;  
int            largeur   = 870; 
int            cote_X    = 100; 


int            running  = 1;


int main(){ 
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        return EXIT_FAILURE; 
    }

    window = SDL_CreateWindow("X.fenêtré", x, y, 
                largeur, hauteur, 
                SDL_WINDOW_RESIZABLE); 
    
    if (window == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    }

    int x_a;
    int y_a;

    while (running){
        while (SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_WINDOWEVENT:
                    switch (event.window.event)  {
                        case SDL_WINDOWEVENT_CLOSE:  
                            printf("appui sur la croix\n");	
                            break;
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            largeur = event.window.data1;
                            hauteur = event.window.data2;
                            printf("Size : %d%d\n", largeur, hauteur);
                        default:
                    }   
                break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_q){
                        SDL_Delay(10);
                        x = x - 5;
                        SDL_SetWindowPosition(window, x, y);
                    } 
                    if(event.key.keysym.sym == SDLK_d){
                        SDL_Delay(10);
                        x = x + 5;
                        SDL_SetWindowPosition(window, x, y);
                    } 
                    if(event.key.keysym.sym == SDLK_r){
                        SDL_Delay(10);
                        printf("Taille réduite ");
                        largeur = largeur - 5;
                        hauteur = hauteur - 5;
                        SDL_SetWindowSize(window, largeur, hauteur); 
                    } 
                    if(event.key.keysym.sym == SDLK_a){
                        SDL_Delay(10);
                        printf("Taille réduite ");
                        largeur = largeur + 5;
                        hauteur = hauteur + 5;
                        SDL_SetWindowSize(window, largeur, hauteur); 
                    } 
                break;
                case SDL_MOUSEBUTTONDOWN:
                    printf("Appui :%d %d\n", event.button.x, event.button.y);
                    x_a = event.button.x;
                    y_a = event.button.y;
                    running = 0;
                break;
                case SDL_QUIT : 
				printf("on quitte\n");    
				running = 0;
            }	
        SDL_Delay(10); 
        } 
    } 

    SDL_DestroyWindow(window);

    window1 = SDL_CreateWindow("X.fenêtré", x_a + (3 * cote_X / 2) , y_a + (3 * cote_X / 2), 
                cote_X, cote_X, 
                SDL_WINDOW_RESIZABLE); 

    SDL_Delay(500);

    window2 = SDL_CreateWindow("X.fenêtré", x_a + (3 * cote_X / 2) - cote_X, y_a + (3 * cote_X / 2) + cote_X, 
                cote_X, cote_X, 
                SDL_WINDOW_RESIZABLE);

    SDL_Delay(500);

    window3 = SDL_CreateWindow("X.fenêtré", x_a + (3 * cote_X / 2) + cote_X, y_a + (3 * cote_X / 2) + cote_X, 
                cote_X, cote_X, 
                SDL_WINDOW_RESIZABLE);

    SDL_Delay(500);

    window4 = SDL_CreateWindow("X.fenêtré", x_a + (3 * cote_X / 2) + cote_X, y_a + (3 * cote_X / 2) - cote_X, 
                cote_X, cote_X, 
                SDL_WINDOW_RESIZABLE);

    SDL_Delay(500);

    window5 = SDL_CreateWindow("X.fenêtré", x_a + (3 * cote_X / 2) - cote_X, y_a  + (3 * cote_X / 2) - cote_X, 
                cote_X, cote_X, 
                SDL_WINDOW_RESIZABLE);


    SDL_Delay(5000);

    SDL_DestroyWindow(window5);
    SDL_Delay(500);

    SDL_DestroyWindow(window4);
    SDL_Delay(500);

    SDL_DestroyWindow(window3);
    SDL_Delay(500);

    SDL_DestroyWindow(window2);
    SDL_Delay(500);

    SDL_DestroyWindow(window1);
    SDL_Delay(500);

    SDL_Quit();
    return 0;
}