#include <stdio.h>
#include <SDL2/SDL.h>

void display_xwin (int n){
    int i = n;
    int x = 0;
    int y = 0;
    int xi = x;
    int yi = y;
    int height = 50;
    int width = 50;
    int halv = (i/2)+1;
    SDL_Window *xwindow = NULL;
    while (i!=0){
        if (i>=halv){
            x = xi + width * (n - i);
            y = yi + height * (n - i);
            xwindow = SDL_CreateWindow("Xfenetre_maindiag",x,y,width,height,0);
        }
        else {
            x = xi + width * (i-1);
            y = yi + height * (n/2 - i);
            xwindow = SDL_CreateWindow("Xfenetre_counterdiag",x,y,width,height,0);
        }
        i-=1;
    }
    SDL_Delay(2500);
    SDL_DestroyWindow(xwindow);
}

void display_fourwin(){
    int x = 1200;
    int y = 0;
    int xi = x;
    int yi = y;
    int height = 100;
    int width = 100;
    SDL_Window *xwindow = NULL;
    int i;
    for (i=0;i<6;i++){
        x = xi;
        y = yi + height * i;
        xwindow = SDL_CreateWindow("4fenetre_column",x,y,width,height,0);
    }
    for (i=0;i<4;i++){
        x = (xi-2*width) + width * i;
        y = yi+4*height;
        xwindow = SDL_CreateWindow("4fenetre_row",x,y,width,height/2,0);
    }
    for (i=1;i<4;i++){
        x = (xi-2*width) + width/2 * i;
        y = yi - height*(i-4);
        xwindow = SDL_CreateWindow("4fenetre_diagbar",x,y,width/2,height,0);
        
    }
    SDL_Delay(2500);
    SDL_DestroyWindow(xwindow);
}

void Explosioooon(){
    int width = 300;
    int height = 300;
    int x = 700;
    int y = 700;
    int bwidth = width;
    int bheight = height;
    int bx = x;
    int by = y;
    SDL_Window *explowindow = NULL;
    explowindow = SDL_CreateWindow("Click this like your life depends on it !",bx,by,bwidth,bheight,SDL_WINDOW_RESIZABLE);
    int decompte = 15;
    int run = 1;
    while (decompte != 0 && run != 0){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT :
                    run = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN :
                    width += 20;
                    height += 20;
                    SDL_SetWindowSize(explowindow,width,height);
                    decompte -= 1;
                    break;
                default:
                    break;
            }
        }
    }
    if (run != 0){
        SDL_DestroyWindow(explowindow);
        explowindow = SDL_CreateWindow("Whoooosh",bx,by,bwidth,bheight,SDL_WINDOW_RESIZABLE);
        int i;
        for (i=0;i<33;i++){
            x -= 20;
            y -= 20;
            SDL_SetWindowPosition(explowindow,x,y);
            SDL_Delay(1);
        }
    }
    SDL_DestroyWindow(explowindow);
}

int main(int argc, char **argv){
    (void)argc;
    (void)argv;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    display_xwin(30);
    display_fourwin();
    Explosioooon();
    SDL_Quit();
    return 0;
}