#include<stdio.h>
#include<stdlib.h>

/*
    Função:  Lê um arquivo no formato .txt contendo elementos inteiros
             que representam acessos a páginas de memória, e guarda esses valores
             em um vetor "referencias" passado como parâmetro, até a quantidade
             limite representada por "num_referencias".   
    Entrada: Um vetor representando as referências e a quantidade limite 
             de valores a serem lidos.       
    Saída:   O vetor de referências preenchido.
*/
void le_referencias(int referencias[], int num_referencias){
    
    FILE *file;
    file = fopen("referencias.txt","r");
    while(file == NULL){ /* Arquivo não encontrado */
            printf("\n\n[!] Arquivo nao localizado, tente novamente.");
            file = fopen("referencias.txt","r");
    }
        
    int i = 0;
    while(!feof(file) && i < num_referencias){
        fscanf(file, "%d", &referencias[i]);
        i++;
    }
    fclose(file);
    
}


/*
    Função:  Preenche as posições do vetor de frames com o valor
             9999, representando o estado inicial onde não há
             nenhuma página alocada na memória.
    Entrada: Um vetor representando os frames e a quantidade de
             frames existentes.
    Saída:   O vetor de frames preenchido com o valor 9999.
*/
void inicializa(int frames[], int num_frames){
    int i;
    for(i = 0; i < num_frames; i++)
        frames[i] = 9999;
}
 

/*
    Função:  Verifica se uma determinada paǵina está alocada em algum 
             frame. Em caso positivo, ocorreu um acerto. Já em caso
             negativo, houve uma falta de página.
    Entrada: Um inteiro representando a página referenciada, um vetor
             representando os frames e a quantidade de frames existentes.
    Saída:   Retorna valor 0 em caso de falta de página ou valor 1 em caso de
             acerto.
*/
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

/*
    Função:  Exibe a quantidade de faltas de página ocorridas após a execução
             do algoritmo.
    Entrada: Um inteiro representando a quantidade de faltas ocorridas.
    Saída:   Exibe no terminal a quantidade de faltas.
*/
void mostra_faltas(int cont_faltas){
    printf("\nQuantidade de faltas: %d\n", cont_faltas);
}


/*
    Função:  Simula a substituição de páginas de memória utilizando o algoritmo
             Least Recently Used.
    Entrada: Um vetor representando os frames, a quantidade de frames existentes,
             a quantidade de referências que serão analisadase  um vetor contendo
             as referências (onde cada página é representada por um inteiro).
    Saída:   Retorna a quantidade de faltas de página ocorridas.
*/
int lru(int frames[], int num_frames, int num_referencias, int referencias[]){
    int i,j,k;
    int ultimo_acesso[50];
    int cont_faltas = 0;
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

/*
    Função:  Ponto de entrada. Declara e inicializa as variáveis necessárias,
             executando o algoritmo uma única vez. 
    Entrada: Nada.
    Saída:   Ao final da execução, a quantidade de faltas de página ocorridas
             é exibida no terminal.
*/
int main(){
    int referencias[3000];
    int frames[50];
    int cont_faltas;

    le_referencias(referencias, 3000);
	cont_faltas = lru(frames, 4, 3000, referencias);

    mostra_faltas(cont_faltas);
}
