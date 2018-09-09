#include<stdio.h>
#include<stdlib.h>

int num_paginas,num_frames;
int referencias[20];
int paginas[50];
int acerto=0;
int i,j,k;
int cont_faltas=0;

void gera_referencias(){
	num_frames = 4;
	num_paginas = 20;
	time_t t;
	srand((unsigned) time(&t));
	int i;
	for(i=0; i<20; i++){
		referencias[i] = rand() % 10;
	}	
}

void mostra_referencias(){
	printf("Referencias: ");
    for (k=0; k<num_paginas; k++){
    	printf("%d ",referencias[k]);
    }
    printf("\n");
}
 
void recebe_dados(){
    printf("\nDigite a quantidade de referencias:");
    scanf("%d",&num_paginas);
    printf("\nDigite a sequencia de referencias:");
    for(i=0; i<num_paginas; i++)
        scanf("%d",&referencias[i]);
    printf("\nDigite a quantidade de frames:");
    scanf("%d",&num_frames);
}
 
void inicializa(){
    cont_faltas=0;
    for(i=0; i<num_frames; i++)
        paginas[i]=9999;
}
 
int foi_acerto(int referencia){
    acerto=0;
    for(j=0; j<num_frames; j++){
        if(paginas[j]==referencia){
            acerto=1;
            break;
        }
    }
    return acerto;
}
 
int pega_indice_acerto(int referencia){
    int indice_acerto;
    for(k=0; k<num_frames; k++)
    {
        if(paginas[k]==referencia)
        {
            indice_acerto=k;
            break;
        }
    }
    return indice_acerto;
}
 
void mostra_paginas(){
    for (k=0; k<num_frames; k++){
        if(paginas[k]!=9999)
            printf(" %d",paginas[k]);
    }
}
 
void mostra_faltas(){
    printf("\nQuantidade de faltas: %d", cont_faltas);
}
 
void lru(){
    inicializa();
    int menos_recentemente_usados[50];
    for(i=0; i<num_paginas; i++){
        //printf("\nPara %d :",referencias[i]);
        if(foi_acerto(referencias[i])==0){
            for(j=0; j<num_frames; j++){
                int pagina_atual=paginas[j];
                int achou=0;
                for(k=i-1; k>=0; k--){
                    if(pagina_atual==referencias[k]){
                        menos_recentemente_usados[j]=k;
                        achou=1;
                        break;
                    }
                    else
                        achou=0;
                }
                if(!achou)
                    menos_recentemente_usados[j]=-9999;
            }
            int menor=9999;
            int indice_substituido;
            for(j=0; j<num_frames; j++){
                if(menos_recentemente_usados[j]<menor){
                    menor=menos_recentemente_usados[j];
                    indice_substituido=j;
                }
            }
            paginas[indice_substituido]=referencias[i];
            cont_faltas++;
 
            //mostra_paginas();
        }
        else{
            //printf("Acerto!");
        }
    }
    mostra_faltas();
}

int main(){
    //recebe_dados();
    gera_referencias();
    mostra_referencias();
    
	lru();
}
