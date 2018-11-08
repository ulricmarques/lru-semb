/*
 * Este algoritmo foi implementado como trabalho na cadeira de Sistemas Embarcados
 * do curso de Engenharia de Computa��o do Instituto Federal de Educa��o, Ci�ncia e 
 * Tecnologia - Campus Fortaleza, ministrada pelo professor Elias Teodoro.
 *
 * Resumo: Implementa��o do algoritmo Least Recently Used(LRU) para substitui��o
 * de p�ginas de mem�ria. O LRU � um algoritmo guloso que se baseia na ideia de que
 * uma p�gina usada recentemente provavelmente ser� utilizada novamente. Assim, quando 
 * ocorrer uma falta de p�gina, a p�gina que deve ser substitu�da � aquela que foi
 * referenciada h� mais tempo. 
 * 
 * 
 * Autores: Ulric Marques Ferreira e Cl�udia Mariana Costa Maia
*/





#include<stdio.h>   //Importa��o da biblioteca stdio.
#include<stdlib.h>  //Importa��o da biblioteca stlib.
#include <time.h>

/*
    Fun��o:  L� um arquivo no formato .txt contendo elementos inteiros
             que representam acessos a p�ginas de mem�ria, e guarda esses valores
             em um vetor "referencias" passado como par�metro, at� a quantidade
             limite representada por "num_referencias".   
    Entrada: Um vetor representando as refer�ncias e a quantidade limite 
             de valores a serem lidos.       
    Sa�da:   O vetor de refer�ncias preenchido.
*/
void le_referencias(int referencias[], int num_referencias){

    FILE *file; //Vari�vel que guardar� a refer�ncia ao arquivo.
    file = fopen("referencias.txt","r"); //abertura do arquivo.
    while(file == NULL){ /* Verifica se houve sucesso na abertura do arquivo e,
                            em caso de falha, tenta abr�-lo novamente. */
            printf("\n\n[!] Arquivo nao localizado, tente novamente.");
            file = fopen("referencias.txt","r");
    }
        
    int i = 0; //Vari�vel contadora. 
    while(!feof(file) && i < num_referencias){ 
        /* Enquanto n�o chegar ao final do arquivo e o valor atual de "i" 
           for menor que o limite estabelecido pela vari�vel "num_referencias",
           l� o pr�ximo valor do arquivo e o atribui ao �ndice "i" do vetor de
           refer�ncias, incrementando o valor de "i" em seguida. */
        fscanf(file, "%d", &referencias[i]); 
        i++;
    }
    fclose(file); //Fecha o arquivo.

}


/*
    Fun��o:  Preenche as posi��es do vetor de frames com o valor
             9999, representando o estado inicial onde n�o h�
             nenhuma p�gina alocada na mem�ria.
    Entrada: Um vetor representando os frames e a quantidade de
             frames existentes.
    Sa�da:   O vetor de frames preenchido com o valor 9999.
*/
void inicializa(int frames[], int num_frames){
    int i; //Vari�vel contadora.
    for(i = 0; i < num_frames; i++){
        /* Inicializa o contador "i" com o valor 0, e enquanto ele for menor
           que "num_frames", atribui a� posi��o "i" do vetor "frames" o valor
           9999, incrementando o contador em seguida. */
        frames[i] = 9999;
    }
}
 

/*
    Fun��o:  Verifica se uma determinada p�gina est� alocada em algum 
             frame. Em caso positivo, ocorreu um acerto. J� em caso
             negativo, houve uma falta de p�gina.
    Entrada: Um inteiro representando a p�gina referenciada, um vetor
             representando os frames e a quantidade de frames existentes.
    Sa�da:   Retorna valor 0 em caso de falta de p�gina ou valor 1 em caso de
             acerto.
*/
int foi_acerto(int referencia, int frames[], int num_frames){
    int i; //Vari�vel contadora.
    int acerto = 0; /*Vari�vel que representa se houve acerto ou falta,
                      inicializada com 0 (falta). */
    for(i = 0; i < num_frames; i++){
        /* Inicializa o contador "i" com o valor 0, e enquanto ele for menor
           que "num_frames", checa se a posi��o "i" do vetor "frames" cont�m
           o valor "referencia". Caso contenha, atribui valor 1 � vari�vel
           contadora e sai do la�o. Incrementando o contador ao final. */
        if(frames[i] == referencia){
            acerto = 1;
            break;
        }
    }
    return acerto; //Retorna o valor da vari�vel "acerto".
}

/*
    Fun��o:  Exibe a quantidade de faltas de p�gina ocorridas ap�s a execu��o
             do algoritmo.
    Entrada: Um inteiro representando a quantidade de faltas ocorridas.
    Sa�da:   Exibe no terminal a quantidade de faltas.
*/
void mostra_faltas(int cont_faltas){
    printf("\nQuantidade de faltas: %d\n", cont_faltas); 
    /* Exibe no terminal o valor da vari�vel "cont_faltas". */
}


/*
    Fun��o:  Simula a substitui��o de p�ginas de mem�ria utilizando o algoritmo
             Least Recently Used.
    Entrada: Um vetor representando os frames, a quantidade de frames existentes,
             a quantidade de refer�ncias que ser�o analisadas e  um vetor contendo
             as refer�ncias (onde cada p�gina � representada por um inteiro).
    Sa�da:   Retorna a quantidade de faltas de p�gina ocorridas.
*/
int lru(int frames[], int num_frames, int num_referencias, int referencias[]){
    int i,j,k; /* Vari�veis contadoras. */
    int ultimo_acesso[50]; /* Declara��o do vetor de frames, de tamanho m�ximo 50,
                              que guardar� o �ltimo �ndice... */
    int cont_faltas = 0;   /* Contador de faltas de p�gina. */
    inicializa(frames, num_frames); /* Chamada da fun��o para atribuir aos frames
                                       existentes o valor 9999, simbolizando o
                                       estado inicial da mem�ria. */

    for(i = 0; i < num_referencias; i++){
        /* Inicializa o contador "i" com o valor 0, e enquanto ele for menor
           que "num_frames", checa se o valor contido na posi��o "i" do vetor
           "referencias" est� contido no vetor "frames". Caso n�o esteja,
           executa o c�digo contido no if abaixo. Incrementa o contador ao final. */
        if(!foi_acerto(referencias[i], frames, num_frames)){
            for(j = 0; j < num_frames; j++){
                int frame_atual = frames[j];/* Declara uma vari�vel auxiliar que guarda o
											valor contido numa posi��o do vetor de frames */
                int achou = 0; 				/* Vari�vel que representa se a p�gina foi encontrada no vetor de refer�ncias,
                      						inicializada com 0 (n�o encontrada). */
                for(k = i-1; k >= 0; k--){  /* Inicializa o contador "k" com o valor da refer�ncia anterior a atual, e enquanto ele for maior
           									ou igual a 0, checa se a posi��o "k" do vetor "referencias" cont�m
           									o valor "frame_atual". Caso contenha, atribui valor "k" � posi��o "j" do vetor
											"ultimo_acesso" e valor 1 a vari�vel "achou", saindo do la�o em seguida.
											Decrementando o contador ao final. */
                    if(frame_atual == referencias[k]){
                        ultimo_acesso[j] = k;
                        achou = 1;
                        break;
                    }
            	}
                if(!achou)  /* Caso a vari�vel "achou" tenha valor 0, atribui o
							valor -9999 na posi��o "j" do vetor "ultimo_acesso".*/
                    ultimo_acesso[j] = -9999;
            }

            int menor = 9999;	/* Declara uma vari�vel que guardar� o menor �ndice do vetor de "referencias"
								que contenha a p�gina menos recente do vetor de frames*/
            int indice_substituido; /* Declara uma vari�vel que guardar� o �ndice da p�gina
									menos recentemente usada, ou seja, aquela que ser� substitu�da*/
            for(j = 0; j < num_frames; j++){/* Inicializa o contador "j" com o valor 0, e enquanto ele for menor
           									que "num_frames", checa se a posi��o "j" do vetor "ultimo_acesso" cont�m
           									um valor menor que o da vari�vel "menor". Caso contenha, o valor da vari�vel "menor"
											se torna o valor contido na posi��o "j" do vetor "ultimo_acesso" e a vari�vel
											"indice_substituido" recebe o valor "j".
											Incrementando o contador ao final. */
                if(ultimo_acesso[j] < menor){
                    menor = ultimo_acesso[j];
                    indice_substituido = j;
                }
            }

            frames[indice_substituido] = referencias[i];/* Substitui o a p�gina contida no vetor frame na posi��o "indice_substituido"
														pela refer�ncia atual.*/
            cont_faltas++; /*Incremanta contador de faltas. */
        }
    }
    return cont_faltas; /* Retorna a quantidade de faltas de p�gina ocorridas */
}

/*
    Fun��o:  Ponto de entrada. Declara e inicializa as vari�veis necess�rias,
             executando o algoritmo uma �nica vez. 
    Entrada: Nada.
    Sa�da:   Ao final da execu��o, a quantidade de faltas de p�gina ocorridas
             � exibida no terminal.
*/


int main(){
    

    clock_t start, end;
    double cpu_time_used;

    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    int referencias[3000]; //Declar��o do vetor de refer�ncias, de tamanho m�ximo 3000.
    int frames[50];        //Declara��o do vetor de frames, de tamanho m�ximo 50.
    int cont_faltas;       //Vari�vel que guardar� a quantidade de faltas de p�gina.

    le_referencias(referencias, 3000); /*Chamada da fun��o para ler um arquivo .txt e
                                         guardar os valores contidos nele no vetor de
                                         refer�ncias. */

    start = clock();
	cont_faltas = lru(frames, 4, 3000, referencias); /* Chamada da fun��o de simula��o, 
                                                        armazenando seu resultado na vari�vel
                                                        "cont_faltas". */
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de CPU usado: %lf\n", cpu_time_used);
    mostra_faltas(cont_faltas); /* Chamada da fun��o para exibir no terminal
                                   a quantidade de faltas ocorridas. */
}
