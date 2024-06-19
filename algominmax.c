#include "algominmax.h"





int * genere_coups( struct abr * l,bool max){
    int n=nbdenfant(l);
    int * R =NULL;
    if (n==0){
        R=0;
    }
    else{
        R=malloc(sizeof(int) * n);
        if (max){ //influence le tri des position on trie les j premiers du plus grand au plus petit limité a un petit j
            //on parcours l'entièreté de ses fils
            //on affecte les valeurs dans le tableau R
        }
        else {  // on trie les j premiers du plus petit au plus grand afin de facilité l'algo de cherche coup
                // on parcours l'entièreté de ses fils
                //on affecte les valeurs choisit dans le tableau R
                // R[i]!=val
        }
        
    }



    return R;
    
}


int chosir_coup(struct abr * l,bool max){
    int * R = genere_coups(l,max);
    return R[0];
}

struct abr * applique_coup(struct abr * l, bool max, int i){
    struct abr * f=NULL;
    if (l!=NULL){
        f=l->fils;
        int c= 0;
        while (c==0){
            if (f->v != i){
                //on change le fils
            }
            else{
                c=1;
            }
        }
    }
    return f;
}

int evaluation(){
    int R=0;
    if (l!=NULL){
        if(l->fils==NULL){
            R=l->v;
        }
        else{
            int i =choisir_coup(l,max);
            struct abr * f=applique_coup(l,max,i);
            R=evalutaion(f,max);
        }
    }
    return R;
}