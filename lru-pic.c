/* 
 * Arquivo:   main.c
 * Autores: Ulric Marques e Cláudia Mariana
 *
 * Criado em 14 de Novembro, 2018, 16:20
 */

// Production -> Set Configuration Bits;
// PIC16F18875 Configuration Bit Settings
// 'C' source line config statements

// CONFIG1
#pragma config FEXTOSC = OFF    // External Oscillator mode selection bits (Oscillator not enabled)
#pragma config RSTOSC = HFINT32 // Power-up default value for COSC bits (HFINTOSC with OSCFRQ= 32 MHz and CDIV = 1:1)
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN = ON       // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (FSCM timer enabled)

// CONFIG2
#pragma config MCLRE = ON       // Master Clear Enable bit (MCLR pin is Master Clear function)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config LPBOREN = OFF    // Low-Power BOR enable bit (ULPBOR disabled)
#pragma config BOREN = ON       // Brown-out reset enable bits (Brown-out Reset Enabled, SBOREN bit is ignored)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices)
#pragma config ZCD = OFF        // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = ON     // Peripheral Pin Select one-way control (The PPSLOCK bit can be cleared and set only once in software)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)

// CONFIG3
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF       // WDT operating mode (WDT Disabled, SWDTEN is ignored)
#pragma config WDTCWS = WDTCWS_7// WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = SC      // WDT input clock selector (Software Control)

// CONFIG4
#pragma config WRT = OFF        // UserNVM self-write protection bits (Write protection off)
#pragma config SCANE = available// Scanner Enable bit (Scanner module is available for use)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (Low Voltage programming enabled. MCLR/Vpp pin function is MCLR.)

// CONFIG5
#pragma config CP = OFF         // UserNVM Program memory code protection bit (Program Memory code protection disabled)
#pragma config CPD = OFF        // DataNVM code protection bit (Data EEPROM code protection disabled)

// CONFIG

#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>              //Importação da biblioteca do compilador XC8.
#include<stdio.h>            //Importação da biblioteca stdio.
#include<stdlib.h>           //Importação da biblioteca stlib.
#include "referencias.h"     //Importação do header que contém o vetor com as referências.


#define _XTAL_FREQ 32000000
#define F_CPU 32000000/64//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)//cálculo do taxa de transmissão serial para Uart

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
 
*/


/*
    Função:  Preenche as posições do vetor de frames com o valor
             9999, representando o estado inicial onde não há
             nenhuma página alocada na memória.
    Entrada: Um vetor representando os frames e a quantidade de
             frames existentes.
    Saída:   O vetor de frames preenchido com o valor 9999.
*/
void inicializa(int frames[], int num_frames){
    int i; //Variável contadora.
    for(i = 0; i < num_frames; i++){
        /* Inicializa o contador "i" com o valor 0, e enquanto ele for menor
           que "num_frames", atribui à posição "i" do vetor "frames" o valor
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
           que "num_frames", checa se a posição "i" do vetor "frames" contém
           o valor "referencia". Caso contenha, atribui valor 1 à variável
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
    int ultimo_acesso[12]; /* Declaração do vetor de frames, de tamanho máximo 12,
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
           									o valor "frame_atual". Caso contenha, atribui valor "k" à posição "j" do vetor
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
											"índice_substituido" recebe o valor "j".
											Incrementando o contador ao final. */
                if(ultimo_acesso[j] < menor){
                    menor = ultimo_acesso[j];
                    indice_substituido = j;
                }
            }

            frames[indice_substituido] = referencias[i];/* Substitui a página contida no vetor "frames" na posição "indice_substituido"
														pela referência atual.*/
            cont_faltas++; /*Incrementa contador de faltas. */
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
        int frames[12];        //Declaração do vetor de frames, de tamanho máximo 12.
        int cont_faltas;       //Variável que guardará a quantidade de faltas de página.

        cont_faltas = lru(frames, 4, 3000, referencias); /* Chamada da função de simulação, 
                                                        armazenando seu resultado na variável
                                                        "cont_faltas". */
         
    }
    

}
