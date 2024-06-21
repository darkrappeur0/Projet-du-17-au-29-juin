#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void BackGround (SDL_Texture *Texture, SDL_Window *Window, SDL_Renderer *Renderer){
    SDL_Rect Source = {0}, Window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(Window, &Window_dimensions.w, &Window_dimensions.h);
    SDL_QueryTexture(Texture, NULL, NULL, &Source.w, &Source.h);
    destination = Window_dimensions;
    SDL_RenderCopy(Renderer, Texture, &Source, &destination);
}

void animation(SDL_Texture *Background, SDL_Texture *Texture, SDL_Window *Window, SDL_Renderer *Renderer, int xspeed, int yspeed){
    SDL_Rect Source ={0}, Window_dimensions = {0}, destination = {0};
    SDL_GetWindowSize(Window,&Window_dimensions.w, &Window_dimensions.h);
    SDL_QueryTexture(Texture, NULL, NULL,&Source.w, &Source.h);
    float zoom = 8;
    int offset_x = 8, offset_y = 8;
    SDL_Rect state[4];
    //Rectangles pour vignettes
    int i = 0;
    int x;
    int y;
    for (y = 0;y<Source.h;y+=offset_y){
        for (x=0;x<Source.w;x+=offset_x){
            state[i].x = x;
            state[i].y = y;
            state[i].w = offset_x;
            state[i].h = offset_y;
            i++;
        }
    }
    destination.w = offset_x * zoom;
    destination.h = offset_y * zoom;
    destination.x = 0;
    destination.y = 250;
    i = 0;
    if (xspeed < 0 || yspeed >0){
        SDL_Rect destinationMirroir ={0};
        destinationMirroir.x = destination.x+destination.w;
        destinationMirroir.y = destination.y;
        destinationMirroir.w = -destination.w;
        destinationMirroir.h = destination.h;

        x = x + xspeed;
        y = y + yspeed;
        destinationMirroir.x = x;
        destinationMirroir.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopy(Renderer,Texture, &state[i], &destinationMirroir);
        i += 1; 
        SDL_RenderPresent(Renderer);
        SDL_Delay(300);
        
        x = x + xspeed;
        y = y + yspeed;
        destinationMirroir.x = x;
        destinationMirroir.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopy(Renderer,Texture, &state[i], &destinationMirroir);
        i += 1; 
        SDL_RenderPresent(Renderer);
        SDL_Delay(300);

        x = x + xspeed;
        y = y + yspeed;
        destinationMirroir.x = x;
        destinationMirroir.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopy(Renderer,Texture, &state[i], &destinationMirroir);
        i += 1; 
        SDL_RenderPresent(Renderer);
        SDL_Delay(300);
    }
    else {
        x = x + xspeed;
        y = y + yspeed;
        destination.x = x;
        destination.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopy(Renderer,Texture, &state[i], &destination);
        i += 1; 
        SDL_RenderPresent(Renderer);
        SDL_Delay(300);

        x = x + xspeed;
        y = y + yspeed;
        destination.x = x;
        destination.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopy(Renderer,Texture, &state[i], &destination);
        i += 1; 
        SDL_RenderPresent(Renderer);
        SDL_Delay(300);

        x = x + xspeed;
        y = y + yspeed;
        destination.x = x;
        destination.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopy(Renderer,Texture, &state[i], &destination);
        i += 1; 
        SDL_RenderPresent(Renderer);
        SDL_Delay(300);
    }

}

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * Win= SDL_CreateWindow("test1",0,0,500,500,SDL_WINDOW_RESIZABLE);
    SDL_Renderer * Renderer = SDL_CreateRenderer(Win, -1,SDL_RENDERER_PRESENTVSYNC);  
    SDL_Texture * sp_st;
    SDL_Texture * sp_mo;
    SDL_Texture * bg;
    sp_st = IMG_LoadTexture(Renderer, "Slime_Still(1).png");
    sp_mo = IMG_LoadTexture(Renderer, "Slime_Advancing(1).png");
    bg = IMG_LoadTexture(Renderer, "Flowery_Floor.png");
    SDL_bool running = SDL_TRUE;
    while (running){
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT :
                    running = SDL_FALSE;
                    break;
                case SDL_KEYDOWN :
                    switch (event.key.keysym.sym){
                        case SDLK_UP :
                            animation(bg, sp_mo, Win, Renderer, 0, -10);
                            break;
                        case SDLK_RIGHT :
                            animation(bg, sp_mo, Win, Renderer, 10, 0);
                            break;
                        case SDLK_DOWN :
                            animation(bg, sp_mo, Win, Renderer, 0, 10);
                            break;
                        case SDLK_LEFT :
                            animation(bg, sp_mo, Win, Renderer, -10, 0);
                            break;
                        default :
                            break;
                    }
                    break;
                default :
                    animation(bg, sp_st, Win, Renderer, 0, 0);
                    break;
            }
        }
    }
    
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Win);
    SDL_Quit();
    return 0;
}