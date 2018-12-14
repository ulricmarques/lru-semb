/* 
 * Arquivo: main.c
 * 
 * Entrada: Um vetor de inteiros representando uma lista de referências
 *          de memória, na formatação definida no arquivo "referencias.h".
 *   
 * Saída:   A quantidade de faltas de página ocorridas após a aplicação do
 *          algoritmo Least Recently Used(LRU) sobre a lista de referências
 *          de memória recebida.
 *  
 * Plataforma Alvo : PIC16F18875 (Microchip)
 * Compilador : XC8 (Microchip)
 * IDE :  MPLABX (Microchip)
 * Autores: Ulric Marques e Cláudia Mariana
 *
 * Adaptado de www.programming9.com, com código original disponível em:
 * <www.programming9.com/programs/c-programs/285-page-replacement-programs-in-c>.
 * 
 * Criado em 14 de Novembro, 2018, 16:20
 * 
 *  Copyright (C) 2018 Cláudia Mariana <claudiamarianacmaia@gmail.com>
 *  Copyright (C) 2018 Ulric Marques  <ulricmf@gmail.com>
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * 
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
 * Modo de uso: Para uso do algoritmo altere o valor do parâmetro "num_frames" da função 
 *              "lru" de acordo com a quantidade de frames desejada(entre 1 e 12).
 *              Caso deseje alterar a lista das referências de memória, modifique os valores
 *              do vetor "referencias" no arquivo "referencias.h", e altere o parâmetro
 *              "num_referencias" da função "lru" de acordo com a quantidade de elementos
 *              da lista. 
 * 
*/

#include <xc.h>              //Importação da biblioteca do compilador XC8.
#include<stdio.h>            //Importação da biblioteca stdio.
#include<stdlib.h>           //Importação da biblioteca stlib.
#include "referencias.h"     //Importação do header que contém o vetor com as referências.
#include "config.h"          /*Importação do header que contém as configurações dos 
                                registradores do PIC 16F18875. */

void inicializa(int frames[], int num_frames){
    /*
    Função:  Preenche as posições do vetor de frames com o valor
             9999, representando o estado inicial onde não há
             nenhuma página alocada na memória.
    Entrada: Um vetor representando os frames e a quantidade de
             frames existentes.
    Saída:   O vetor de frames preenchido com o valor 9999.
    */
    
    int i; //Variável contadora.
    for(i = 0; i < num_frames; i++){
        /* Inicializa o contador "i" com o valor 0, e enquanto ele for menor
           que "num_frames", atribui à posição "i" do vetor "frames" o valor
           9999, incrementando o contador em seguida. */
        frames[i] = -1;
    }
}

int procuraLRU(int ultimo_acesso[], int num_frames){
    int menor = ultimo_acesso[0], posicao = 0;
    int i;
    for(i = 1; i < num_frames; i++){
        if(ultimo_acesso[i] < menor){
            menor = ultimo_acesso[i];
            posicao = i;
        }
    }
    return posicao;
}

int lru(int frames[], int num_frames, int num_referencias, int referencias[]){
    /*
    Função:  Simula a substituição de páginas de memória utilizando o algoritmo
             Least Recently Used.
    Entrada: Um vetor representando os frames, a quantidade de frames existentes,
             a quantidade de referências que serão analisadas e  um vetor contendo
             as referências (onde cada página é representada por um inteiro).
    Saída:   Retorna a quantidade de faltas de página ocorridas.
    */
    
    int i,j; /* Variáveis contadoras. */
    int ultimo_acesso[12]; /* Declaração do vetor de frames, de tamanho máximo 12,
                              que guardará o último índice... */

    int cont_tempo = 0;
    int indice_substituido;
    int foi_acerto, existe_frame_disponivel;

    int cont_faltas = 0;   /* Contador de faltas de página. */
    inicializa(frames, num_frames); /* Chamada da função para atribuir aos frames
                                       existentes o valor 9999, simbolizando o
                                       estado inicial da memória. */

    for(i = 0; i < num_referencias; i++){
        /* Inicializa o contador "i" com o valor 0, e enquanto ele for menor
           que "num_frames", checa se o valor contido na posição "i" do vetor
           "referencias" está contido no vetor "frames". Caso não esteja,
           executa o código contido no if abaixo. Incrementa o contador ao final. */
        
        foi_acerto = 0;
        existe_frame_disponivel = 0;
        
        for(j = 0; j < num_frames; j++){
            if(frames[j] == referencias[i]){
                cont_tempo++;
                ultimo_acesso[j] = cont_tempo;
                foi_acerto = 1;
                existe_frame_disponivel = 1;
                break;
            }
        }
        
        if(foi_acerto == 0){
            for(j = 0; j < num_frames; j++){
                if(frames[j] == -1){
                    cont_tempo++;
                    cont_faltas++;
                    frames[j] = referencias[i];
                    ultimo_acesso[j] = cont_tempo;
                    existe_frame_disponivel = 1;
                    break;
                }
            }   
        }
        
        if(existe_frame_disponivel == 0){
            indice_substituido = procuraLRU(ultimo_acesso, num_frames);
            cont_tempo++;
            cont_faltas++;
            frames[indice_substituido] = referencias[i];
            ultimo_acesso[indice_substituido] = cont_tempo;
        }
    }
    return cont_faltas; /* Retorna a quantidade de faltas de página ocorridas */
}

/*
    Função:  Ponto de entrada. Declara e inicializa as variáveis necessárias,
             executando o algoritmo em loop infinito. 
    Entrada: Nada.
    Saída:   Ao final de cada iteração, a quantidade de faltas de página ocorridas
             é caculada e armazenada na variável "cont_faltas".
*/
int main(void){
    

    while(1){
        int frames[50];        //Declaração do vetor de frames, de tamanho máximo 12.
        int cont_faltas_4;     /* Variável que guardará a quantidade de faltas de página
                                ocorridas com 4 frames disponíveis. */

        cont_faltas_4 = lru(frames, 4, 3000, referencias);  /* Chamada da função de simulação
                                                        com parâmetro "num_frames" igual a 4, 
                                                        armazenando seu resultado na variável
                                                        "cont_faltas_4". */
        
         
    }
    

}
