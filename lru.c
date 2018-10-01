#include<stdio.h>
#include<stdlib.h>

void le_referencias(int referencias[]){
    FILE *file;
    file = fopen("referencias.txt","r");
    while(file == NULL){ /* Arquivo não encontrado */
            printf("\n\n[!] Arquivo nao localizado, tente novamente.");
            file = fopen("referencias.txt","r");
    }
        
    int i = 0;
    while(!feof(file)){
        fscanf(file, "%d", &referencias[i]);
        i++;
    }
    fclose(file);
    
}

void inicializa(int frames[], int num_frames){
    int i;
    for(i = 0; i < num_frames; i++)
        frames[i] = 9999;
}
 
int foi_acerto(int referencia, int frames[], int num_frames){
    int i;
    int acerto = 0;
    for(i = 0; i < num_frames; i++){
        if(frames[i] == referencia){
            acerto = 1;
            break;
        }
    }
    return acerto;
}

void mostra_paginas(int frames[], int num_frames){
    int i;
    for (i = 0 ; i < num_frames; i++){
        if(frames[i] != 9999)
            printf("%d ", frames[i]);
    }
}
 
void mostra_faltas(int cont_faltas){
    printf("\nQuantidade de faltas: %d\n", cont_faltas);
}
 
int lru(int frames[], int num_frames, int num_referencias, int referencias[],  int cont_faltas){
    int i,j,k;
    int ultimo_acesso[50];

    inicializa(frames, num_frames);

    for(i = 0; i < num_referencias; i++){
        if(!foi_acerto(referencias[i], frames, num_frames)){
            for(j = 0; j < num_frames; j++){
                int frame_atual = frames[j];
                int achou = 0;
                for(k = i-1; k >= 0; k--){
                    if(frame_atual == referencias[k]){
                        ultimo_acesso[j] = k;
                        achou = 1;
                        break;
                    }
                    else
                        achou = 0;
                }
                if(!achou)
                    ultimo_acesso[j] = -9999;
            }

            int menor = 9999;
            int indice_substituido;
            for(j = 0; j < num_frames; j++){
                if(ultimo_acesso[j] < menor){
                    menor = ultimo_acesso[j];
                    indice_substituido = j;
                }
            }

            frames[indice_substituido] = referencias[i];
            cont_faltas++;
        }
    }
    return cont_faltas;
}

int main(){
    int referencias[3000];
    int frames[50];
    int cont_faltas;

    le_referencias(referencias);
	cont_faltas = lru(frames, 4, 3000, referencias, 0);

    mostra_faltas(cont_faltas);
}
