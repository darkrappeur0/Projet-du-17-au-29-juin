#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void xfentre(int a){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win;
    int x = 400;
    int y = 100;
    int w = 100;
    int h = 100;
    int i = x;
    int j = y;
    int c = a;
    int r = c/2;
    int mid = c - r + 1; 
    int * tab = malloc(sizeof(int) * c);
    while (c!=0){
        if (c>r){
            x= x + w;
            y= y + h;
            win = SDL_CreateWindow("testavant",x,y,w,h,SDL_WINDOW_RESIZABLE);
            
                if ( c == mid ){
                    i = x + w * (c-r);
                }
        }
        else{
            j= j + w;
            i= i - h;
            win = SDL_CreateWindow("testback",i,j,w,h,SDL_WINDOW_RESIZABLE);
        }
        tab[a - c] = SDL_GetWindowID( win);
        c=c-1;
    }
    SDL_Delay(6000);
    win=NULL;
    c= a;
    while (c!=0){
        SDL_Window* win1 =SDL_GetWindowFromID(tab[a - c]);
        SDL_DestroyWindow(win1);
        c=c-1;
    }
    free(tab);
    SDL_Quit();
    
}
void losange( int a){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win;
    int x = 900;
    int y = 300;
    int w = 100;
    int h = 100;
    int c = a;
    int r = c / 4;
    int q1 = c - r;
    int q2 = c - 2*r;
    int q3 = c - 3*r;
    int * tab = malloc(sizeof(int) * c);
    while (c!=0){
        if (c>=q1){
            x= x - w;
            y= y + h;
            win = SDL_CreateWindow("testq1",x,y,w,h,SDL_WINDOW_RESIZABLE);
        }
        else{
            if (c>=q2){
            x= x + w;
            y= y + h;
            win = SDL_CreateWindow("testq2",x,y,w,h,SDL_WINDOW_RESIZABLE);
            }
            else{
                if (c>=q3){
                    x= x + w;
                    y= y - h;
                    win = SDL_CreateWindow("testq3",x,y,w,h,SDL_WINDOW_RESIZABLE);
                }
                else{
                    x= x - w;
                    y= y - h;
                    win = SDL_CreateWindow("testqf",x,y,w,h,SDL_WINDOW_RESIZABLE);
                }
            }
        }
        tab[a - c] = SDL_GetWindowID( win);
        c=c-1;
        
    }  
    c=a;
    while (c!=0){
        SDL_Window* win1 =SDL_GetWindowFromID(tab[a - c]);
        SDL_DestroyWindow(win1);
        c=c-1;
    }
    free(tab);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void reditman(){
    SDL_Init(SDL_INIT_EVERYTHING);
    int x=500;
    int y =500;
    int w=100;
    int h=100;
    SDL_Window * win=SDL_CreateWindow("testavant",x,y,w,h,SDL_WINDOW_RESIZABLE);
    bool run = true;
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
                         int right = x + 1;
                        
                         SDL_SetWindowPosition(win ,right ,y );
                         x=right;
                     }
                     if (event.key.keysym.sym == SDLK_q){
                         SDL_Log("clavier touche q");
                         int left = x - 1;
                        
                         SDL_SetWindowPosition(win ,left ,y );
                         x=left;

                     }
                     if (event.key.keysym.sym == SDLK_s){
                         SDL_Log("clavier touche s");
                         y = y + 1;
                        
                         SDL_SetWindowPosition(win ,x ,y );
                        
                     }
                     if (event.key.keysym.sym == SDLK_z){
                         SDL_Log("clavier touche z");
                         y = y - 1;
                        
                         SDL_SetWindowPosition(win ,x ,y );
                        
                     }


                     break;
                 case SDL_MOUSEWHEEL:
                 if (event.wheel.y > 0){
                     w = w + 20;
                     h = h + 40;
                     SDL_SetWindowSize(win ,  w ,  h);
                 }
                 if (event.wheel.y<0){
                     w = w - 20;
                     h = h - 40;
                     SDL_SetWindowSize(win ,  w ,  h);
                 }
                     break;
                    
             }
         }
    }
    SDL_DestroyWindow(win);
    SDL_Quit();
}
void reditauto(){
    SDL_Init(SDL_INIT_EVERYTHING);
    int x = 500;
    int y = 500;
    int w =100;
    int h=100;
    SDL_Window * win=SDL_CreateWindow("testavant",x,y,w,h,SDL_WINDOW_RESIZABLE);
    int c=20;
    while (c!=0){
        if (c>10){
        w = w + 10;
        h = h + 20;
        }
        else{
            w=w-10;
            h=h-20;
        }
        SDL_SetWindowSize(win ,  w ,  h);
        c=c-1;
        SDL_Delay(2000);
    }
    c=20;
    while (c!=0){
        if (c>=15){
            x= x+w;
            y=y-h;
        }
        else{
            if(c>=10){
                y=y+h;
            }
            else{
                if (c>=5){
                    x=x-w;
                    y=y-h;
                }
                else{
                    x=x+w;
                    y=y+h -10;
                }
            }
        }
        SDL_SetWindowPosition(win ,x ,y );
        c=c-1;
        SDL_Delay(2000);
    }
    SDL_DestroyWindow(win);
    SDL_Quit();


}
int main(){
    xfentre(10);
    losange(8);
    printf("début du redimentionnement manuel\n");
    reditman();
    printf("fin du redimentionnement manuel\n");
    printf("début du redimentionnement auto\n");
    reditauto();
    printf("fin du redimentionnement auto\n");
    return 0;
}