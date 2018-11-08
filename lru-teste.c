#include<stdio.h>
#include<stdlib.h>
#include "./referencias.h"

int num_referencias = 3000;
int num_frames = 4;
//int referencias[3000];
int frames[4];
int acerto = 0;
int i, j, k;
int cont_faltas = 0;

void mostra_referencias(){
	printf("Referencias: ");
    for (k = 0; k < num_referencias; k++){
    	printf("%d ", referencias[k]);
    }
    printf("\n");
}

void inicializa(){
    cont_faltas = 0;
    for(i = 0; i < num_frames; i++)
        frames[i] = 9999;
}
 
int foi_acerto(int referencia){
    acerto = 0;
    for(j = 0; j < num_frames; j++){
        if(frames[j] == referencia){
            acerto = 1;
            break;
        }
    }
    return acerto;
}
 
void mostra_paginas(){
    for (k =0 ; k < num_frames; k++){
        if(frames[k] != 9999)
            printf(" %d", frames[k]);
    }
}
 
void mostra_faltas(){
    printf("\nQuantidade de faltas: %d\n", cont_faltas);
}
 
void least_recently_used(){
    inicializa();
    int lru[4];
    for(i = 0; i < num_referencias; i++){
        //printf("\nPara %d :",referencias[i]);
        if(foi_acerto(referencias[i]) == 0){
            for(j = 0; j < num_frames; j++){
                int frame_atual = frames[j];
                int achou = 0;
                for(k = i-1; k >= 0; k--){
                    if(frame_atual == referencias[k]){
                        lru[j] = k;
                        achou = 1;
                        break;
                    }
                    else
                        achou = 0;
                }
                if(!achou)
                    lru[j] = -9999;
            }
            int menor = 9999;
            int indice_substituido;
            for(j = 0; j < num_frames; j++){
                if(lru[j] < menor){
                    menor = lru[j];
                    indice_substituido = j;
                }
            }
            frames[indice_substituido] = referencias[i];
            cont_faltas++;
 
            //mostra_paginas();
        }
    }
    mostra_faltas();
}

int main(){
    mostra_referencias();
    least_recently_used();
}
