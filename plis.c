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


void displaycarte(carte * carte1){
    if (carte1->couleur == 0){
    printf("allégance: nain \n");
    }
    else{
        if (carte1->couleur == 1){
            printf("allégance: géant \n");
        }
        else{
            if(carte1->couleur == 2){
                printf("allégance: elf \n");
            }
            else{
                if(carte1->couleur == 3){
                printf("allégance: humain \n");
                }
                else{
                    if(carte1->couleur == 4){
                        printf("allégance: zarbi \n");
                    }
                    else{
                        printf("allégance: null \n");
                    }
                }
            }
        }
    }
    printf("voici son rang: %d\n",carte1->num);
}


void displaydeck(deck * deck1){
    int i = 1;
    while(deck1!=NULL){
        printf("voici la %d-ème carte \n",i);
        displaycarte(deck1->carte);
        deck1=deck1->next;
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
        cour1=NULL;
        prec=NULL;
        
    }
    return main;
}




int moyenne1plis( int tab[][14],int n){
    float f=0;
    int i =0;
    int r = 0;
    int j =0;
    while (i<4){
        j=0;
        while (j < 13){
        f= f + tab[i][j];
        j=j+1;
        }
        i=i+1;
    }
    while (i<6){
        j=0;
        while (j<4){
            f=f+ tab[i][j];
            j=j+1;
        }
        i=i+1;
    }
    //printf("avant la moyenne: %f\n", f);
    f= f / n;
    //printf("après la moyenne: %f\n", f);
    if (f > 0.5){
        r= 1;
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
                if (cartejouerj1->couleur == 4){
                    if (cartejouerj2->couleur != 4){
                        r=1;
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
    }
    return r;
}

void displaytab(int tab[][14]){
    int i =0;
    int j =0;
    while (i<4){
        j=0;
        while (j<13){
            printf("valeur a la ligne %d , et colonne %d : %d\n ", i, j, tab[i][j]);
            j=j+1;
        }
        i=i+1;
    }
    while (i<6){
        j=0;
        while(j<4){
            printf("valeur a la ligne %d , et colonne %d : %d\n ", i, j, tab[i][j]);
            j=j+1;
        }
        i=i+1;
    }

}

int update_premierecarte(int r){
    int a = 0;
    if (r == 1){
        a=1;
    }
    else{
        a=2;
    }
    return a;
}


int prediction1plis(carte * cartejouerj1,int atout,int premierecarte){
    int r =0;
    int n = 13 * 3 +20;
    carte * cartejouerj2 = malloc( sizeof(carte));
    int i =0;
    int j =0;
    int tab[6][14] = {0}; 
    while (i<4){
        j=0;
        while (j<13){
            cartejouerj2->couleur = i;
            cartejouerj2->num = j +1;
            if ( (cartejouerj1->couleur == cartejouerj2->couleur) && (cartejouerj1->num == cartejouerj2->num)   ){
                tab[i][j]=0;
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
        j=0;
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
    //displaycarte(cartejouerj1);
    //printf("prediction de r après la moyenne des plis: %d\n", r);
    //printf("voici l'atout : %d\n", atout);
    //displaytab(tab);
    //printf("\n");
    free (cartejouerj2);
    return r;
}




int predictionplistotal(deck * main1,int atout,int premierecarte){
    int r = 0;
    int i = 0;
    int y = 0;
    int n = main1->nb_de_carte;
    while ( i < n){
        printf("\n");
        printf("voici le deck regarder\n");
        displaydeck(main1);
        y = prediction1plis(main1->carte, atout, premierecarte);
        r= r + y;
        //printf("prediction des plis au nombre %d de tours: %d\n", i, r);
        i=i+1;
        premierecarte = update_premierecarte(y);
        main1 = main1->next;
    }
    //printf("prediction de la fonction plis tot: %d\n", r);
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
int update_atout(){
    int r = rand() % 4;
    return r;
}

void pliseval(deck * deckIA, deck * deckj2, int atout, int j, int * nb_plit_j1, int * nb_plit_j2){
    int c=0;
    int d=0;
    int x = 0;
    int i = deckIA->nb_de_carte;
    while ( i!=0 ) {
        x = evalplisj1(deckIA->carte, deckj2->carte,atout, j);
        c = c + x;
        d = d + 1 - x;
        /* printf("\n");
        printf("%d\n",c);
        printf("\n");
        printf("\n");
        printf("%d\n",d);
        printf("\n");
        printf("%d plis gagner par le joueur 1\n",x); */
        deckIA=deckIA->next;
        deckj2=deckj2->next;
        i=i-1;
        j = update_premierecarte(x);
    }
    *nb_plit_j1 = c;
    *nb_plit_j2 = d;
}



void plisevalindiv(carte * cartej1, carte * cartej2, int atout, int * j, int * nb_plit_j1, int * nb_plit_j2){
    int c=0;
    int d=0;
    int x = 0;
    x = evalplisj1(cartej1, cartej2,atout, *j);
    c=x;
    d= 1-x;
    *nb_plit_j1 = c;
    *nb_plit_j2 = d;
    *j = update_premierecarte(x);
}

/* int memecarte(carte * carte1, carte * carte2){
    int r =0;
            if (carte1->couleur == carte2->couleur){
                if (carte1->num == carte2->num){
                    r=1;
                }
            }
    return r;
} */

/* deck * changement_pos_deck(deck * deck2,carte * carte2){
    if (deck2!=NULL){
        if (carte2!=NULL){
            deck * cour = deck2;
            deck * prev = NULL;
            if (deck2->nb_de_carte > 1){
                while ( (cour!=NULL) && (memecarte(cour->carte,carte2) != 1 ) ){
                    prev = cour;
                    cour = cour->next;
                }
                prev->next = cour->next;
                cour->next = deck2;
                deck2 = cour;
            }
            //cour =NULL;
            //prev =NULL;
        }
    }
    return deck2;
} */

/* carte * cartemax(deck * deckIA, int j,int atout){
    carte * cmax= deckIA->carte;
    int n =0;
    deck * temp = deckIA;
    while (temp!=NULL){
        float r = prediction1plis (temp->carte, atout, j);
        if (r>n){
            n=r;
            cmax = temp->carte;
        }
        temp=temp->next; 
    }
    return cmax;

} */

void freedeck(deck * deck1){
    deck * temp = deck1;
    while (temp!=NULL){
        free(temp->carte);
        temp=temp->next;
    }
    temp = deck1;
    while (temp!=NULL){
        deck1=deck1->next;
        free (temp);
        temp=deck1;
    }
}

