#include "InterfaceGraphique.c" 

carte * donne_carte_n(deck * d, int n){
    deck * d_temp = d;
    while(d_temp != NULL){
        if(n == 0){
            return d_temp->carte;
        } 
        n--;
        d_temp = d_temp->next;
    } 
    return NULL;
} 

//x_click ; y_click : coordonnées du click
//x_premiere_carte ; x_derniere_carte : coordonnées du début de la premiere/derniere carte en main
//x_carte ; y_carte : taille de la carte
//d : deck du joueur

carte * interface_to_carte(int x_click, int y_click, int x_premiere_carte,int x_derniere_carte,int x_carte, int y_carte, deck * d){
    if(y_click < 10 || y_click > y_carte + 10){
        return NULL;
    } 
    if(x_click > x_premiere_carte){
        int x_act = x_premiere_carte;
        int i = 0;
        while(x_act < x_click && x_act < x_derniere_carte + x_carte){
            if(x_click < x_act){
                return donne_carte_n(d, i);
            } 
            i++;
            x_act = x_act + x_carte;
        } 
    } 
    return NULL;
} 