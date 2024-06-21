#include "AffichageSDLS1.h"
#include "topitop.h"



int deplacementenx(float i,int x){
    int r =0;
    if (i>1){
        if (i<2){
            r=333;
        }
        else{
            if (i < 3){
            r=666;
            }
            else {
                if (x < 333){
            r=0;
            }
            else {
                if ( x< 666){
                    r=333;    
                }
                else {
                    if (x < 999){
                        r = 666;
                    }
                }
         }
        }
    }
    }
    return r;
}

int deplacementeny(float j,int y, float i){
    int r =0;
    if (i < 3){
    if (j >1){
        if (j <2 ){
            r = 333;
        }
        else {
            if ( j < 3){
                r = 666;
            }
            }
        }
    }
    else {
                    
        if (y < 333){
            r=0;
        }
        else {
            if ( y< 666){
                r=333;    
            }
            else {
                if (y < 999){
                    r = 666;
                }
            }
        }
                    
    }


    
    return r;
}

rectsdlcouleur * initialisationrectcoulrouge(){
    rectsdlcouleur * rouge = malloc(sizeof(rectsdlcouleur));
    rouge->destination1=malloc(sizeof(SDL_Rect ));
    rouge->destination2=malloc(sizeof(SDL_Rect ));

    rouge->destination1->w  = 200;
    rouge->destination2->w  = 200;
    rouge->destination1->h  = 200;
    rouge->destination2->h  = 200;

    rouge->destination1->x = 1000;
    rouge->destination2->x = 1333;
    rouge->destination1->y = 333;
    rouge->destination2->y = 333;
    rouge->j=1;
    return rouge;
}

rectsdlcouleur * initialisationrectcoulbleu( ){
    rectsdlcouleur * bleu = malloc(sizeof(rectsdlcouleur));
    bleu->destination1=malloc(sizeof(SDL_Rect ));
    bleu->destination2=malloc(sizeof(SDL_Rect ));

    bleu->destination1->w  = 200;
    bleu->destination2->w  = 200;
    bleu->destination1->h  = 200;
    bleu->destination2->h  = 200;

    bleu->destination1->x=1000;
    bleu->destination2->x = 1333;
    bleu->destination1->y=0;
    bleu->destination2->y=0;
    bleu->j=0;
    return bleu;
    
}

SDL_Rect * inirectneutre1(){
    SDL_Rect * destination1 = malloc(sizeof(SDL_Rect ));
    destination1->w = 200;
    destination1->h = 200; 
    destination1->x = 1000;
    destination1->y = 666;
    return destination1;
}
SDL_Rect * inirectneutre2(){
    SDL_Rect * destination1=malloc(sizeof(SDL_Rect ));
    destination1->w = 200;
    destination1->h = 200; 
    destination1->x = 1333;
    destination1->y = 666;
    return destination1;

}

rectsdlneutre * initialisationneutregrand( ){
    rectsdlneutre * grand = malloc(sizeof(rectsdlneutre));
    grand->destination1 = malloc(sizeof(SDL_Rect ));
    grand->destination2 = malloc(sizeof(SDL_Rect ));
    grand->destination3 = malloc(sizeof(SDL_Rect ));
    grand->destination4 = malloc(sizeof(SDL_Rect ));
    grand->destination1 = inirectneutre1();
    grand->destination2 = inirectneutre1();
    grand->destination3 = inirectneutre1();
    grand->destination4 = inirectneutre1();
    return grand;
}

rectsdlneutre * initialisationrectneutremoyen(){
    rectsdlneutre * moyen = malloc(sizeof(rectsdlneutre));
    moyen->destination1 = malloc(sizeof(SDL_Rect  ));
    moyen->destination2 = malloc(sizeof(SDL_Rect  ));
    moyen->destination3 = malloc(sizeof(SDL_Rect  ));
    moyen->destination4 = malloc(sizeof(SDL_Rect  ));
    moyen->destination1 = inirectneutre2();
    moyen->destination2 = inirectneutre2();
    moyen->destination3 = inirectneutre2();
    moyen->destination4 = inirectneutre2();
    return moyen;
    

}







int quelbleucest(rectsdlcouleur * bleu,int x, int y){
    int r=0;
    float a = bleu->destination1->x + bleu->destination1->w;
    float b = bleu->destination2->x + bleu->destination2->w;
    float c = bleu->destination1->y + bleu->destination1->h;
    float d = bleu->destination2->y + bleu->destination2->h;
    if ( ( x < a ) && (x > bleu->destination1->x) ) {
        if ( ( y < c) && (y> bleu->destination1->y) ){
            r=1;
        }
        else{
            if ( ( x < b ) && (x > bleu->destination2->x) ){
                if ( (y < d) && (y> bleu->destination2->y)){
                    r=2;
                }
                else{
                    r=0;
                }
            }
            else{
                r=0;
            }
        }
    }
    else{
        if ( ( x < b ) && (x > bleu->destination2->x) ){
                if ( (y < d) && (y> bleu->destination2->y)){
                    r=2;
                }
                else{
                    r=0;
                }
        }
        else{
            r=0;
        }
    }
    return r;

}








int quelrougecest(rectsdlcouleur * bleu,int x, int y){
    int r=0;
    float a = bleu->destination1->x + bleu->destination1->w;
    float b = bleu->destination2->x + bleu->destination2->w;
    float c = bleu->destination1->y + bleu->destination1->h;
    float d = bleu->destination2->y + bleu->destination2->h;
    if ( ( x < a ) && (x > bleu->destination1->x) ) {
        if ( ( y < c) && (y> bleu->destination1->y) ){
            r=3;
        }
        else{
            if ( ( x < b ) && (x > bleu->destination2->x) ){
                if ( (y < d) && (y> bleu->destination2->y)){
                    r=4;
                }
                else{
                    r=0;
                }
            }
            else{
                r=0;
            }
        }
    }
    else{
        if ( ( x < b ) && (x > bleu->destination2->x) ){
                if ( (y < d) && (y> bleu->destination2->y)){
                    r=4;
                }
                else{
                    r=0;
                }
        }
        else{
            r=0;
        }
    }
    return r;

}












int quelmoyencest(rectsdlneutre * moyen, int x, int y){
    int r=0;
    float a = moyen->destination1->x + moyen->destination1->w;
    float b = moyen->destination2->x + moyen->destination2->w;
    float c = moyen->destination3->x + moyen->destination3->w;
    float d = moyen->destination4->x + moyen->destination4->w;

    float e = moyen->destination1->y + moyen->destination1->h;
    float f = moyen->destination2->y + moyen->destination2->h;
    float g = moyen->destination3->y + moyen->destination3->h;
    float h = moyen->destination4->y + moyen->destination4->h;
    if ((x<a) && (x>moyen->destination1->x)){
        if( (y<e) && (y>moyen->destination1->y)){
            r=9;
        }
        else{
            if ((x<b) && (x>moyen->destination2->x)){
                if ( (y<f) && (y>moyen->destination2->y)){
                    r=10;
                }
                else {
                    if ((x<c) && (x>moyen->destination3->x)){
                        if ( (y<g) && (y>moyen->destination3->y)){
                            r=11;
                        }
                        else{
                            if ((x<d) && (x>moyen->destination4->x)){
                                if ( (y<h) && (y>moyen->destination4->y)){
                                    r=12;
                                }
                                else{
                                    r=0;
                                }
                            }
                            else{
                                r=0;
                            }
                        }
                    }
                    else{
                        if ( (x<d) && (x>moyen->destination4->x) ){
                            if ( (y<h) && (y>moyen->destination4->y)){
                                r=12;
                            }
                            else{
                                r=0;
                            }
                        }
                        else{
                            r=0;
                        }
                        
                        
                    }
                }
            }
            else {
                    if ((x<c) && (x>moyen->destination3->x)){
                        if ( (y<g) && (y>moyen->destination3->y)){
                            r=11;
                        }
                        else{
                            if ((x<d) && (x>moyen->destination4->x)){
                                if ( (y<h) && (y>moyen->destination4->y)){
                                    r=12;
                                }
                                else{
                                    r=0;
                                }
                            }
                            else{
                                r=0;
                            }
                        }
                    }
                    else{
                        if ( (x<d) && (x>moyen->destination4->x) ){
                            if ( (y<h) && (y>moyen->destination4->y)){
                                r=12;
                            }
                            else{
                                r=0;
                            }
                        }
                        else{
                            r=0;
                        }
                        
                        
                    }
                }
            
        }

    }
    else{
        if ((x<b) && (x>moyen->destination2->x)){
            if( (y<f) && (y>moyen->destination2->y)){
                r=10;
            }
            else{
                if ((x<c) && (x>moyen->destination3->x)){
                    if ( (y<g) && (y>moyen->destination3->y)){
                        r=11;
                    }
                    else {
                        if ((x<d) && (x>moyen->destination4->x)){
                            if ( (y<h) && (y>moyen->destination4->y)){
                                r=12;
                            }
                            else{
                                r=0;
                            }
                            
                            
                        }
                        else{
                            r=0;
                        }
                    }
                }
                else {
                    if ((x<d) && (x>moyen->destination4->x)){
                        if ( (y<h) && (y>moyen->destination4->y)){
                            r=12;
                        }
                        else{
                            r=0;
                        }
                    }
                    else{
                        r=0;
                    }
                          
                }
                    
            
            }
        }
        else{
            if ((x<c) && (x>moyen->destination3->x)){
                    if ( (y<g) && (y>moyen->destination3->y)){
                        r=11;
                    }
                    else {
                        if ((x<d) && (x>moyen->destination4->x)){
                            if ( (y<h) && (y>moyen->destination4->y)){
                                r=12;
                            }
                            else{
                                r=0;
                            }
                            
                            
                        }
                        else{
                            r=0;
                        }
                    }
            }
            else {       
                if ((x<d) && (x>moyen->destination4->x)){
                    if ( (y<h) && (y>moyen->destination4->y)){
                        r=12;
                    }
                    else{
                        r=0;
                    }
                }
                else{
                    r=0;
                }
            }
        }
                        
    }
    return r;
}







int quelgrandcest(rectsdlneutre * moyen, int x, int y){
    int r=0;
    float a = moyen->destination1->x + moyen->destination1->w;
    float b = moyen->destination2->x + moyen->destination2->w;
    float c = moyen->destination3->x + moyen->destination3->w;
    float d = moyen->destination4->x + moyen->destination4->w;

    float e = moyen->destination1->y + moyen->destination1->h;
    float f = moyen->destination2->y + moyen->destination2->h;
    float g = moyen->destination3->y + moyen->destination3->h;
    float h = moyen->destination4->y + moyen->destination4->h;
    if ((x<a) && (x>moyen->destination1->x)){
        if( (y<e) && (y>moyen->destination1->y)){
            r=5;
        }
        else{
            if ((x<b) && (x>moyen->destination2->x)){
                if ( (y<f) && (y>moyen->destination2->y)){
                    r=6;
                }
                else {
                    if ((x<c) && (x>moyen->destination3->x)){
                        if ( (y<g) && (y>moyen->destination3->y)){
                            r=7;
                        }
                        else{
                            if ((x<d) && (x>moyen->destination4->x)){
                                if ( (y<h) && (y>moyen->destination4->y)){
                                    r=8;
                                }
                                else{
                                    r=0;
                                }
                            }
                            else{
                                r=0;
                            }
                        }
                    }
                    else{
                        if ( (x<d) && (x>moyen->destination4->x) ){
                            if ( (y<h) && (y>moyen->destination4->y)){
                                r=8;
                            }
                            else{
                                r=0;
                            }
                        }
                        else{
                            r=0;
                        }
                        
                        
                    }
                }
            }
            else {
                    if ((x<c) && (x>moyen->destination3->x)){
                        if ( (y<g) && (y>moyen->destination3->y)){
                            r=7;
                        }
                        else{
                            if ((x<d) && (x>moyen->destination4->x)){
                                if ( (y<h) && (y>moyen->destination4->y)){
                                    r=8;
                                }
                                else{
                                    r=0;
                                }
                            }
                            else{
                                r=0;
                            }
                        }
                    }
                    else{
                        if ( (x<d) && (x>moyen->destination4->x) ){
                            if ( (y<h) && (y>moyen->destination4->y)){
                                r=8;
                            }
                            else{
                                r=0;
                            }
                        }
                        else{
                            r=0;
                        }
                        
                        
                    }
                }
            
        }

    }
    else{
        if ((x<b) && (x>moyen->destination2->x)){
            if( (y<f) && (y>moyen->destination2->y)){
                r=6;
            }
            else{
                if ((x<c) && (x>moyen->destination3->x)){
                    if ( (y<g) && (y>moyen->destination3->y)){
                        r=7;
                    }
                    else {
                        if ((x<d) && (x>moyen->destination4->x)){
                            if ( (y<h) && (y>moyen->destination4->y)){
                                r=8;
                            }
                            else{
                                r=0;
                            }
                            
                            
                        }
                        else{
                            r=0;
                        }
                    }
                }
                else {
                    if ((x<d) && (x>moyen->destination4->x)){
                        if ( (y<h) && (y>moyen->destination4->y)){
                            r=8;
                        }
                        else{
                            r=0;
                        }
                    }
                    else{
                        r=0;
                    }
                          
                }
                    
            
            }
        }
        else{
            if ((x<c) && (x>moyen->destination3->x)){
                    if ( (y<g) && (y>moyen->destination3->y)){
                        r=7;
                    }
                    else {
                        if ((x<d) && (x>moyen->destination4->x)){
                            if ( (y<h) && (y>moyen->destination4->y)){
                                r=8;
                            }
                            else{
                                r=0;
                            }
                            
                            
                        }
                        else{
                            r=0;
                        }
                    }
            }
            else {       
                if ((x<d) && (x>moyen->destination4->x)){
                    if ( (y<h) && (y>moyen->destination4->y)){
                        r=8;
                    }
                    else{
                        r=0;
                    }
                }
                else{
                    r=0;
                }
            }
        }
                        
    }
    return r;
}










int quelcouleurcest(rectsdlcouleur * bleu, rectsdlcouleur * rouge,int x, int y){
    int r=0;
    r=quelbleucest(bleu,x,y);
    if (r==0){
        r=quelrougecest(rouge,x,y);
    }
    return r;
}










int quelneutrecest(rectsdlneutre * grand, rectsdlneutre * moyen, int x, int y){
    int r=0;
    r=quelmoyencest(moyen,x,y);
    if (r==0){
        r=quelgrandcest(grand,x,y);
    }
    return r;
}










int queltypecest(rectsdlcouleur * bleu, rectsdlcouleur * rouge,rectsdlneutre * grand, rectsdlneutre * moyen, int x, int y){
    int r=0;
    r=quelcouleurcest(bleu,rouge,x, y);
    if (r==0){
        r=quelneutrecest(grand, moyen, x, y);
    }
    return r;
}










void deplacementmoyen(rectsdlneutre * moyen, int x, int y, float j, float i, int r){
    if (r==9){
        moyen->destination1->x=deplacementenx(i,x);
        moyen->destination1->y=deplacementeny(j,y,i) + 50;
        
    }
    else{
        if (r==10){
            moyen->destination2->x=deplacementenx(i,x);
            moyen->destination2->y=deplacementeny(j,y,i) + 50;
        }
        else{
            if (r==11){
                moyen->destination3->x=deplacementenx(i,x);
                moyen->destination3->y=deplacementeny(j,y,i) +50;
            }
            else{
                if (r==12){
                    moyen->destination4->x=deplacementenx(i,x);
                    moyen->destination4->y=deplacementeny(j,y,i) +50;
                }
            }

        }
            
    }
}





void deplacementgrand(rectsdlneutre * grand, rectsdlneutre * moyen, int x, int y, float j, float i, int r){
    if (r==5){
        grand->destination1->x=deplacementenx(i,x);
        grand->destination1->y=deplacementeny(j,y,i) + 100;
    }
    else{
        if (r==6){
            grand->destination2->x=deplacementenx(i,x);
            grand->destination2->y=deplacementeny(j,y,i) + 100;
        }
        else{
            if (r==7){
                grand->destination3->x=deplacementenx(i,x);
                grand->destination3->y=deplacementeny(j,y,i) + 100;
            }
            else{
                if (r==8){
                    grand->destination4->x=deplacementenx(i,x);
                    grand->destination4->y=deplacementeny(j,y,i) + 100;
                }
                else{
                    deplacementmoyen(moyen,x,y,j,i,r);
                }
            }
        }
    }
}


void deplacementrouge(rectsdlcouleur * rouge,rectsdlneutre * grand, rectsdlneutre * moyen, int x, int y, float j, float i, int r){
                if (r==3){
                    rouge->destination1->x = deplacementenx(i,x) +5;
                    rouge->destination1->y = deplacementeny(j,y,i) +2;
                }
                else{
                    if (r==4){
                        rouge->destination2->x = deplacementenx(i,x) +5;
                        rouge->destination2->y = deplacementeny(j,y,i) +2;
                    }
                    else {
                         deplacementgrand(grand,moyen,x,y,j,i,r);
                            }
                        }
                    
                

            
}


void deplacement(rectsdlcouleur * bleu, rectsdlcouleur * rouge,rectsdlneutre * grand, rectsdlneutre * moyen, int x, int y, float j, float i ){
    int r=0;
    r=queltypecest(bleu,rouge,grand,moyen,x,y);
    if (r!=0){
        if (r==1){
            bleu->destination1->x = deplacementenx(i,x) +5;
            bleu->destination1->y = deplacementeny(j,y,i) +2;
        }
        else{
            if (r==2){
                bleu->destination2->x = deplacementenx(i,x) +5;
                bleu->destination2->y = deplacementeny(j,y,i) +2;
            }
            else{
                deplacementrouge(rouge,grand,moyen,x,y,j,i,r);
            }
            
        }
    }
    
    
}




Case_grid *** trad(){
    Case_grid *** lol = genere_grille() ;

    return lol;
}


Joueur * actuj2(){
    Joueur * j = genere_joueur("bleu");
    return j;
}