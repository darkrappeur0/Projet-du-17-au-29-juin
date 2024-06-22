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

void animation(SDL_Texture *Background, SDL_Texture *Texture, SDL_Window *Window, SDL_Renderer *Renderer, int current_x, int current_y, int xspeed, int yspeed){
    SDL_Rect Source = {0},/* Window_dimensions = {0},*/ destination = {0};
//    SDL_GetWindowSize(Window,&Window_dimensions.w, &Window_dimensions.h);
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
    destination.x = current_x;
    destination.y = current_y;
    i = 0;
    x = current_x;
    y = current_y;
    if (xspeed < 0 || yspeed >0){

        SDL_RenderClear(Renderer);
        x = x + xspeed;
        y = y + yspeed;
        destination.x = x;
        destination.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopyEx(Renderer,Texture, &state[i], &destination, 0, NULL, 1);
        i += 1; 
        SDL_RenderPresent(Renderer);
        SDL_Delay(50);
        
        SDL_RenderClear(Renderer);
        x = x + xspeed;
        y = y + yspeed;
        destination.x = x;
        destination.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopyEx(Renderer,Texture, &state[i], &destination, 0, NULL, 1);
        i += 1; 
        SDL_RenderPresent(Renderer);
        SDL_Delay(50);

        SDL_RenderClear(Renderer);
        x = x + xspeed;
        y = y + yspeed;
        destination.x = x;
        destination.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopyEx(Renderer,Texture, &state[i], &destination, 0, NULL, 1);
        SDL_RenderPresent(Renderer);
        SDL_Delay(50);
    }
    else {

        SDL_RenderClear(Renderer);
        x = x + xspeed;
        y = y + yspeed;
        destination.x = x;
        destination.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopy(Renderer,Texture, &state[i], &destination);
        i += 1; 
        SDL_RenderPresent(Renderer);
        SDL_Delay(50);

        SDL_RenderClear(Renderer);
        x = x + xspeed;
        y = y + yspeed;
        destination.x = x;
        destination.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopy(Renderer,Texture, &state[i], &destination);
        i += 1; 
        SDL_RenderPresent(Renderer);
        SDL_Delay(50);

        SDL_RenderClear(Renderer);
        x = x + xspeed;
        y = y + yspeed;
        destination.x = x;
        destination.y = y;
        BackGround(Background,Window, Renderer); 
        SDL_RenderCopy(Renderer,Texture, &state[i], &destination);
        SDL_RenderPresent(Renderer);
        SDL_Delay(50);
    }

}

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * Win= SDL_CreateWindow("Strolling_Slime",0,0,500,500,SDL_WINDOW_RESIZABLE);
    SDL_Renderer * Renderer = SDL_CreateRenderer(Win, -1,SDL_RENDERER_PRESENTVSYNC);  
    SDL_Texture * sp_st = IMG_LoadTexture(Renderer, "Slime_Still(1).png");
    SDL_Texture * sp_mo = IMG_LoadTexture(Renderer, "Slime_Advancing(1).png");
    SDL_Texture * bg = IMG_LoadTexture(Renderer, "Flowery_Floor.png");
    SDL_Rect Pos = {0}, window_dimension = {0};
    int x = 300;
    int y = 300;
    int base_spd = 20;
//    const Uint8* keystates;
    SDL_Event event;
    SDL_bool running = SDL_TRUE;
    SDL_GetWindowSize(Win, &window_dimension.w, &window_dimension.h);
    while (running){
/*        keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_ESCAPE]){
            running = SDL_FALSE;
            printf("so long\n");
        }
        else if (keystates[SDL_SCANCODE_UP]){
            animation(bg, sp_mo, Win, Renderer, x, y, 0, -base_spd);
            SDL_QueryTexture(sp_mo, NULL, NULL, &Pos.w, &Pos.h);
            x = window_dimension.w - Pos.w;
            y = window_dimension.h - Pos.h;
            printf("haut\n");
        }
        else if (keystates[SDL_SCANCODE_RIGHT]){
            animation(bg, sp_mo, Win, Renderer, x, y, base_spd, 0);
            SDL_QueryTexture(sp_mo, NULL, NULL, &Pos.w, &Pos.h);
            x = window_dimension.w - Pos.w;
            y = window_dimension.h - Pos.h;
            printf("droite\n");
        }
        else if (keystates[SDL_SCANCODE_DOWN]){
            animation(bg, sp_mo, Win, Renderer, x, y, 0, base_spd);
            SDL_QueryTexture(sp_mo, NULL, NULL, &Pos.w, &Pos.h);
            x = window_dimension.w - Pos.w;
            y = window_dimension.h - Pos.h;
            printf("bas\n");
        }
        else if (keystates[SDL_SCANCODE_LEFT]){
            animation(bg, sp_mo, Win, Renderer, x, y, -base_spd, 0);
            SDL_QueryTexture(sp_mo, NULL, NULL, &Pos.w, &Pos.h);
            x = window_dimension.w - Pos.w;
            y = window_dimension.h - Pos.h;
            printf("gauche\n");
        }
        else {
            animation(bg, sp_st, Win, Renderer, x, y, 0, 0);
            SDL_QueryTexture(sp_st, NULL, NULL, &Pos.w, &Pos.h);
            x = window_dimension.w - Pos.w;
            y = window_dimension.h - Pos.h;
            printf("pas bouger\n");
        }
    }*/
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT :
                    running = SDL_FALSE;
                    printf("so long");
                    break;
                case SDL_KEYDOWN :
                    switch (event.key.keysym.sym){
                        case SDLK_UP :
                            animation(bg, sp_mo, Win, Renderer, x, y, 0, -base_spd);
                            SDL_QueryTexture(sp_mo, NULL, NULL, &Pos.w, &Pos.h);
                            y = y - (3 * base_spd);
                            printf("haut\n");
                            break;
                        case SDLK_RIGHT :
                            animation(bg, sp_mo, Win, Renderer, x, y, base_spd, 0);
                            SDL_QueryTexture(sp_mo, NULL, NULL, &Pos.w, &Pos.h);
                            x = x + (3 * base_spd);
                            printf("droite\n");
                            break;
                        case SDLK_DOWN :
                            animation(bg, sp_mo, Win, Renderer, x, y, 0, base_spd);
                            SDL_QueryTexture(sp_mo, NULL, NULL, &Pos.w, &Pos.h);
                            y = y + (3 * base_spd);
                            printf("bas\n");
                            break;
                        case SDLK_LEFT :
                            animation(bg, sp_mo, Win, Renderer, x, y, -base_spd, 0);
                            SDL_QueryTexture(sp_mo, NULL, NULL, &Pos.w, &Pos.h);
                            x = x - (3 * base_spd);
                            printf("gauche\n");
                            break;
                        default :
                            animation(bg, sp_st, Win, Renderer, x, y, 0, 0);
                            printf("pas bouger\n");
                            break;
                    }
                    break;
               default :
                    animation(bg, sp_st, Win, Renderer, x, y, 0, 0);
                    printf("pas bouger\n");
                    break;
            }
            SDL_FlushEvents(0x101,0xFFFF);
        }
        animation(bg, sp_st, Win, Renderer, x, y, 0, 0);
        printf("pas bouger\n");
    }
    
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Win);
    SDL_Quit();
    return 0;
}