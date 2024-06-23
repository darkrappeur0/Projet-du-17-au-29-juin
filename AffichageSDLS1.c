#include "AffichageSDLS1.h"
#include "topitop.h"
#include "min_max_topitop.h"


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



void affichage(SDL_Texture *bg_texture1, SDL_Texture *bg_texture2 ,SDL_Texture *my_texture1 ,SDL_Texture *my_texture2,SDL_Texture *my_texture3,SDL_Texture *my_texture4,SDL_Texture *my_texture5,SDL_Texture *my_texture6,SDL_Window *window,SDL_Renderer *renderer){ 
    SDL_Rect  source1 = {0} ;

    SDL_QueryTexture(my_texture1, NULL, NULL,&source1.w, &source1.h);
    rectsdlcouleur * rouge;
    rectsdlcouleur * bleu;
    rectsdlneutre  * grand;
    rectsdlneutre  * moyen;

    bleu = initialisationrectcoulbleu();
    rouge = initialisationrectcoulrouge();
    grand = initialisationneutregrand();
    moyen = initialisationrectneutremoyen();

    play_with_texture_1_1(bg_texture2,window, renderer); 
    SDL_RenderPresent(renderer);

    bool run = true;
    float y=0;
    float x=0;
    int c=0;
    float j=0;
    float i=0;
    int f=0;
    position * main_pos = genere_position();


    while(run){
        SDL_Event event;
         while (SDL_PollEvent(&event)){
             switch(event.type){
                 case SDL_QUIT:
                    run = false;
                    printf("fin\n");
                    break;
                 case SDL_MOUSEBUTTONDOWN:
                    c=c+1;
                    int d= c % 3;
                    if (d==1){
                        //faire jouer l'IA
                        
                    }
                    else{
                        if (d==2){
                            x=event.button.x;
                            y=event.button.y;
                        SDL_Log(" coordonées du click x=%f , y= %f", x,y);
                        
                        }
                        else{
                            i=event.button.x;
                            j=event.button.y;
                            SDL_Log(" coordonées du click x=%f , y= %f \n",i , j);
                            i=i/333;
                            j=j/333;
                            printf("i=%f , j=%f \n", i ,j);

                            deplacement(bleu,rouge,grand,moyen,x,y,j,i);
                            main_pos->etat = trad( main_pos->etat,moyen,grand, x, y, j, i);       // fonction de trad
                            main_pos->j2= actuj2(main_pos->j2, main_pos->etat , j,  i);        //actuellisation du j2
                        }
                    }
                    
                    play_with_texture_1_1(bg_texture1,window, renderer); 
                    SDL_RenderCopy(renderer,my_texture1, &source1, bleu->destination1);
                    SDL_RenderCopy(renderer,my_texture2, &source1, bleu->destination2);
                    SDL_RenderCopy(renderer,my_texture3, &source1, rouge->destination1); 
                    SDL_RenderCopy(renderer,my_texture4, &source1, rouge->destination2);  
                    SDL_RenderCopy(renderer,my_texture5, &source1, grand->destination1);
                    SDL_RenderCopy(renderer,my_texture5, &source1, grand->destination2);
                    SDL_RenderCopy(renderer,my_texture5, &source1, grand->destination3);
                    SDL_RenderCopy(renderer,my_texture5, &source1, grand->destination4);
                    SDL_RenderCopy(renderer,my_texture6, &source1, moyen->destination1);
                    SDL_RenderCopy(renderer,my_texture6, &source1, moyen->destination2);
                    SDL_RenderCopy(renderer,my_texture6, &source1, moyen->destination3);
                    SDL_RenderCopy(renderer,my_texture6, &source1, moyen->destination4);  
                    SDL_RenderPresent(renderer);              // Affichage
                    SDL_Delay(80);                            // Pause en ms
                    
                    
                    f=gagnant(main_pos->j1); 
                    if (f!=0){      //test si max a gagner
                        printf("j1 a gagner!");
                        break;
                                    
                    }
                    else{           //test si min a gagner
                        f=gagnant(main_pos->j2);
                        if (f!=0){  
                            printf("j2 a gagner");
                            break;
                        }
                    }            
            }
            
        }
    }
    
    SDL_RenderClear(renderer);
}



int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window * win= SDL_CreateWindow("topitop",0,0,2000,1000,SDL_WINDOW_RESIZABLE);
    SDL_Renderer * render = SDL_CreateRenderer( win, -1,SDL_RENDERER_PRESENTVSYNC);  
    SDL_Texture * l = load("ImageSdl/Fond-Topitop.png",render);
    SDL_Texture * l1 = load("ImageSdl/Petite-Piece-bleu.png",render);
    SDL_Texture * l2 = l1;
    SDL_Texture * l3 = load("ImageSdl/Petite-Piece-rouge.png",render);
    SDL_Texture * l4 = l3;
    SDL_Texture * l5 = load("ImageSdl/Tours-grand.png",render);
    SDL_Texture * l6 = load("ImageSdl/Tours-petit.png",render);
    SDL_Texture * l7 = load("ImageSdl/Ecrandemarrage.png",render);


    affichage(l,l7,l1,l2,l3,l4,l5,l6,win,render);
    SDL_DestroyRenderer( render);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}