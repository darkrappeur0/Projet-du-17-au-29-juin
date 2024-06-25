#include "plis.h"


int membre (carte * x, deck * deck1){
    if (deck1 == NULL){
        return 0;
    }
    else{
        if ( (x->couleur == deck1->carte->couleur) && (x->num == deck1->carte->num) ){
            return 1;
        }
        else{
            return membre( x, deck1->next);
        }
    }
}

carte * generecarte(){
    carte * carte1 = malloc(sizeof(carte));
    int i = rand () % 6;
    int j = 0;
    if (i >=4){
        j= rand() % 4;
        j=j+1;
    }
    else{
        j = rand() % 13;
        j=j+1;
    }
    carte1->couleur = i;
    carte1->num = j;
    return carte1;
}


carte * generecartesansdoublons(deck * deck1,deck * deck2){
    carte * carte1 = NULL;
    int i = 1;
    if (deck1 == NULL){
        carte1 = generecarte();
    }
    else{
        carte1 = generecarte();
        while (i!=0){
            if ( membre (carte1, deck1) ) {
                carte * temp1; 
                temp1 = carte1;
                carte1 = NULL;
                carte1 = generecarte();
                free(temp1);
                
            }
            else{
                if (membre (carte1, deck2)){
                    carte * temp1; 
                    temp1 = carte1;
                    carte1 = NULL;
                    carte1 = generecarte();
                    free(temp1);
                }
                else{
                    i=0;
                }
            }
        }
    }
    return carte1;
}


void displaycarte(carte * carte){
    if (carte->couleur == 0){
    printf("voici son allégance: humain \n");
    }
    else{
        if (carte->couleur == 1){
            printf("allégance: nain \n");
        }
        else{
            if(carte->couleur == 2){
                printf("allégance: elf \n");
            }
            else{
                if(carte->couleur == 3){
                printf("allégance: géant \n");
                }
                else{
                    if(carte->couleur == 4){
                        printf("allégance: zarbi \n");
                    }
                    else{
                        printf("allégance: null \n");
                    }
                }
            }
        }
    }
    printf("voici son rang: %d\n",carte->num);
}


void displaydeck(deck * deck){
    int i = 1;
    while(deck!=NULL){
        printf("voici la %d-ème carte \n",i);
        displaycarte(deck->carte);
        deck=deck->next;
        i=i+1;
    }
}



deck * generedeck(int nbdecarte,deck * deck1){
    deck * main =NULL;
    int r = nbdecarte;
    if (nbdecarte !=0){
        main = malloc(sizeof(deck));
        deck * cour1 = NULL;
        deck * prec  = main;
        while (r!=0){
            if (r==nbdecarte){
                main->nb_de_carte=r;
                main->carte = generecartesansdoublons(NULL, deck1);
                main->next=NULL;
            }
            else{
                cour1=malloc(sizeof(deck));
                cour1->nb_de_carte=r;
                cour1->carte = generecartesansdoublons(main, deck1);
                cour1->next=NULL;
                prec->next=cour1;
                cour1=NULL;
                prec=prec->next;
            }
            r=r-1;
        }
        
    }
    return main;
}




int moyenne1plis( int tab[][14],int n){
    float f=0;
    int i =0;
    int r = 0;
    int j =0;
    while (i<5){
        while (j < 13){
        f= f + tab[i][j];
        j=j+1;
        }
        i=i+1;
    }
    f= f / n;
    r=f;
    int g = f-r;
    if (g > 0.5){
        r= r +1;
    }
    return r;
}

int evalplisj1( carte * cartejouerj1, carte * cartejouerj2, int atout,int premierecarte){
    int r=0;
    if (cartejouerj1->couleur == cartejouerj2->couleur){
        if(cartejouerj1->num > cartejouerj2->num){
            r=1;
        }
        else{
            r=0;
        }
    }
    else{
        if( cartejouerj1->couleur == atout){
            if (cartejouerj2->couleur !=4){

            r=1;
            }
            else{
                r=0;
            }
        }
        else{
            if( cartejouerj2->couleur == atout){
                if (cartejouerj1->couleur !=4){
                    r=0;
                }
                else{
                    r=1;
                }
            }
            else{
                if (premierecarte == 1){
                    r=1;
                }
                else{
                    r=0;
                }
            }
        }
    }
    return r;
}

int evalplisj2( carte * cartejouerj1, carte * cartejouerj2, int atout,int premierecarte){
    int r=0;
    if (cartejouerj2->couleur == cartejouerj1->couleur){
        if(cartejouerj2->num > cartejouerj1->num){
            r=1;
        }
        else{
            r=0;
        }
    }
    else{
        if( cartejouerj2->couleur == atout){
            if (cartejouerj1->couleur !=4){

            r=1;
            }
            else{
                r=0;
            }
        }
        else{
            if( cartejouerj1->couleur == atout){
                if (cartejouerj2->couleur !=4){
                    r=0;
                }
                else{
                    r=1;
                }
            }
            else{
                if (premierecarte == 2){
                    r=1;
                }
                else{
                    r=0;
                }
            }
        }
    }
    return r;
}


int prediction1plis(carte * cartejouerj1,int atout,int premierecarte){
    int r =0;
    int n = 13 * 3 +20;
    carte * cartejouerj2 = malloc( sizeof(cartejouerj2));
    int i =0;
    int j =0;
    int tab[6][14] = {0}; 
    while (i<4){
        while (j<13){
            cartejouerj2->couleur = i;
            cartejouerj2->num = j +1;
            if ( (cartejouerj1->couleur == cartejouerj2->couleur) && (cartejouerj1->num == cartejouerj2->num)   ){
                j=j+1;
            }
            else{
                tab[i][j] = evalplisj1(cartejouerj1,cartejouerj2, atout, premierecarte);
                j=j+1;
            }
        }
        i=i+1;
    }
    j=0;
    while (i < 6){
        while (j<4){
            cartejouerj2->couleur = i;
            cartejouerj2->num = j +1;
            if ( (cartejouerj1->couleur == cartejouerj2->couleur) && (cartejouerj1->num == cartejouerj2->num)   ){
                j=j+1;
            }
            else{
                tab[i][j] = evalplisj1(cartejouerj1,cartejouerj2, atout, premierecarte);
                j=j+1;
            }
        }
        i=i+1;
    }
    r=moyenne1plis(tab,n);
    return r;
}




int predictionplistotal(deck * main1,int atout,int premierecarte){
    int r = 0;
    int i = 0;
    int n = main1->nb_de_carte;
    while ( i < n){
        r= r + prediction1plis(main1->carte, atout, premierecarte);
        i=i+1;
        main1 = main1->next;
    }
    return r;
}


void plispredic(deck * main, int atout, int premierecarte, prediction * plispredi, int j ){
    if (j == 1){
        plispredi->nb_plit_preditj1= predictionplistotal( main,atout,premierecarte);
    }
    else{
        plispredi->nb_plit_preditj2 = predictionplistotal(main, atout, premierecarte);
    }
    
}

void pliseval(deck * deckIA, deck * deckj2, int atout, int j, int * nb_plit_j1, int * nb_plit_j2){
    int c=0;
    int d=0;
    int i = deckIA->nb_de_carte * 2;
    while ( i!=0 ) {
        c = c + evalplisj1(deckIA->carte, deckj2->carte,atout, j);
        d = d + evalplisj2(deckIA->carte,deckj2->carte, atout, j);
    }
    *nb_plit_j1 = c;
    *nb_plit_j2 = d;
}


