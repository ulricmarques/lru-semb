/*
 * Este algoritmo foi implementado como trabalho na cadeira de Sistemas Embarcados
 * do curso de Engenharia de Computação do Instituto Federal de Educação, Ciência e 
 * Tecnologia - Campus Fortaleza, ministrada pelo professor Elias Teodoro.
 *
 * Resumo: Implementação do algoritmo Least Recently Used(LRU) para substituição
 * de páginas de memória. O LRU é um algoritmo guloso que se baseia na ideia de que
 * uma página usada recentemente provavelmente será utilizada novamente. Assim, quando 
 * ocorrer uma falta de página, a página que deve ser substituída é aquela que foi
 * referenciada há mais tempo. 
 * 
 * 
 * Autores: Ulric Marques Ferreira e Cláudia Mariana Costa Maia
*/





#include<stdio.h>   //Importação da biblioteca stdio.
#include<stdlib.h>  //Importação da biblioteca stlib.

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

    FILE *file; //Variável que guardará a referência ao arquivo.
    file = fopen("referencias.txt","r"); //abertura do arquivo.
    while(file == NULL){ /* Verifica se houve sucesso na abertura do arquivo e,
                            em caso de falha, tenta abrí-lo novamente. */
            printf("\n\n[!] Arquivo nao localizado, tente novamente.");
            file = fopen("referencias.txt","r");
    }
        
    int i = 0; //Variável contadora. 
    while(!feof(file) && i < num_referencias){ 
        /* Enquanto não chegar ao final do arquivo e o valor atual de "i" 
           for menor que o limite estabelecido pela variável "num_referencias",
           lê o próximo valor do arquivo e o atribui ao índice "i" do vetor de
           referências, incrementando o valor de "i" em seguida. */
        fscanf(file, "%d", &referencias[i]); 
        i++;
    }
    fclose(file); //Fecha o arquivo.
}


/*
    Função:  Preenche as posições do vetor de frames com o valor
             9999, representando o estado inicial onde não há¡
             nenhuma página alocada na memória.
    Entrada: Um vetor representando os frames e a quantidade de
             frames existentes.
    Saída:   O vetor de frames preenchido com o valor 9999.
*/
void inicializa(int frames[], int num_frames){
    int i; //Variável contadora.
    for(i = 0; i < num_frames; i++){
        /* Inicializa o contador "i" com o valor 0, e enquanto ele for menor
           que "num_frames", atribui a  posição "i" do vetor "frames" o valor
           9999, incrementando o contador em seguida. */
        frames[i] = 9999;
    }
}
 

/*
    Função:  Verifica se uma determinada página está alocada em algum 
             frame. Em caso positivo, ocorreu um acerto. Já em caso
             negativo, houve uma falta de página.
    Entrada: Um inteiro representando a página referenciada, um vetor
             representando os frames e a quantidade de frames existentes.
    Saída:   Retorna valor 0 em caso de falta de página ou valor 1 em caso de
             acerto.
*/
int foi_acerto(int referencia, int frames[], int num_frames){
    int i; //Variável contadora.
    int acerto = 0; /*Variável que representa se houve acerto ou falta,
                      inicializada com 0 (falta). */
    for(i = 0; i < num_frames; i++){
        /* Inicializa o contador "i" com o valor 0, e enquanto ele for menor
           que "num_frames", checa se a posição "i" do vetor "frames" contêm
           o valor "referencia". Caso contenha, atribui valor 1 á variável
           contadora e sai do laço. Incrementando o contador ao final. */
        if(frames[i] == referencia){
            acerto = 1;
            break;
        }
    }
    return acerto; //Retorna o valor da variável "acerto".
}

/*
    Função:  Exibe a quantidade de faltas de página ocorridas após a execução
             do algoritmo.
    Entrada: Um inteiro representando a quantidade de faltas ocorridas.
    Saída:   Exibe no terminal a quantidade de faltas.
*/
void mostra_faltas(int cont_faltas){
    printf("\nQuantidade de faltas: %d\n", cont_faltas); 
    /* Exibe no terminal o valor da variável "cont_faltas". */
}


/*
    Função:  Simula a substituição de páginas de memória utilizando o algoritmo
             Least Recently Used.
    Entrada: Um vetor representando os frames, a quantidade de frames existentes,
             a quantidade de referências que serão analisadas e  um vetor contendo
             as referências (onde cada página é representada por um inteiro).
    Saída:   Retorna a quantidade de faltas de página ocorridas.
*/
int lru(int frames[], int num_frames, int num_referencias, int referencias[]){
    int i,j,k; /* Variáveis contadoras. */
    int ultimo_acesso[50]; /* Declaração do vetor de frames, de tamanho máximo 50,
                              que guardará o último índice... */
    int cont_faltas = 0;   /* Contador de faltas de página. */
    inicializa(frames, num_frames); /* Chamada da função para atribuir aos frames
                                       existentes o valor 9999, simbolizando o
                                       estado inicial da memória. */

    for(i = 0; i < num_referencias; i++){
        /* Inicializa o contador "i" com o valor 0, e enquanto ele for menor
           que "num_frames", checa se o valor contido na posição "i" do vetor
           "referencias" está contido no vetor "frames". Caso não esteja,
           executa o código contido no if abaixo. Incrementa o contador ao final. */
        if(!foi_acerto(referencias[i], frames, num_frames)){
            for(j = 0; j < num_frames; j++){
                int frame_atual = frames[j];/* Declara uma variável auxiliar que guarda o
											valor contido numa posição do vetor de frames */
                int achou = 0; 				/* Variável que representa se a página foi encontrada no vetor de referências,
                      						inicializada com 0 (não encontrada). */
                for(k = i-1; k >= 0; k--){  /* Inicializa o contador "k" com o valor da referência anterior a atual, e enquanto ele for maior
           									ou igual a 0, checa se a posição "k" do vetor "referencias" contém
           									o valor "frame_atual". Caso contenha, atribui valor "k" á  posição "j" do vetor
											"ultimo_acesso" e valor 1 a variável "achou", saindo do laço em seguida.
											Decrementando o contador ao final. */
                    if(frame_atual == referencias[k]){
                        ultimo_acesso[j] = k;
                        achou = 1;
                        break;
                    }
            	}
                if(!achou)  /* Caso a variável "achou" tenha valor 0, atribui o
							valor -9999 na posição "j" do vetor "ultimo_acesso".*/
                    ultimo_acesso[j] = -9999;
            }

            int menor = 9999;	/* Declara uma variável que guardará o menor índice do vetor de "referencias"
								que contenha a página menos recente do vetor de frames*/
            int indice_substituido; /* Declara uma variável que guardará o índice da página
									menos recentemente usada, ou seja, aquela que será substituída*/
            for(j = 0; j < num_frames; j++){/* Inicializa o contador "j" com o valor 0, e enquanto ele for menor
           									que "num_frames", checa se a posição "j" do vetor "ultimo_acesso" contém
           									um valor menor que o da variável "menor". Caso contenha, o valor da variável "menor"
											se torna o valor contido na posição "j" do vetor "ultimo_acesso" e a variável
											"indice_substituido" recebe o valor "j".
											Incrementando o contador ao final. */
                if(ultimo_acesso[j] < menor){
                    menor = ultimo_acesso[j];
                    indice_substituido = j;
                }
            }

            frames[indice_substituido] = referencias[i];/* Substitui o a página contida no vetor frame na posição "indice_substituido"
														pela referência atual.*/
            cont_faltas++; /*Incremanta contador de faltas. */
        }
    }
    return cont_faltas; /* Retorna a quantidade de faltas de página ocorridas */
}

/*
    Função:  Ponto de entrada. Declara e inicializa as variáveis necessárias,
             executando o algoritmo uma única vez. 
    Entrada: Nada.
    Saída:   Ao final da execução, a quantidade de faltas de página ocorridas
             é exibida no terminal.
*/
int main(){
    int referencias[3000]; //Declarção do vetor de referências, de tamanho máximo 3000.
    int frames[50];        //Declaração do vetor de frames, de tamanho máximo 50.
    int cont_faltas;       //Variável que guardará a quantidade de faltas de página.

    le_referencias(referencias, 3000); /*Chamada da função para ler um arquivo .txt e
                                         guardar os valores contidos nele no vetor de
                                         referências. */

	cont_faltas = lru(frames, 4, 3000, referencias); /* Chamada da função de simulação, 
                                                        armazenando seu resultado na variável
                                                        "cont_faltas". */

    mostra_faltas(cont_faltas); /* Chamada da função para exibir no terminal
                                   a quantidade de faltas ocorridas. */
}
