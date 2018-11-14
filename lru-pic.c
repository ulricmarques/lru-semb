/* 
 * File:   main.c
 * Author: elias
 *
 * Created on October 19, 2018, 3:48 PM
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

#include <xc.h>
#include<stdio.h>   //Importa��o da biblioteca stdio.
#include<stdlib.h>  //Importa��o da biblioteca stlib.
#include "referencias.h"


#define _XTAL_FREQ 32000000
#define F_CPU 32000000/64//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)//calculo do taxa de transmissão serial para Uart

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
    int ultimo_acesso[12]; /* Declara��o do vetor de frames, de tamanho m�ximo 12,
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


int main(void){
    

    while(1){
        //int referencias[3000]; //Declar��o do vetor de refer�ncias, de tamanho m�ximo 3000.
        int frames[12];        //Declara��o do vetor de frames, de tamanho m�ximo 12.
        int cont_faltas;       //Vari�vel que guardar� a quantidade de faltas de p�gina.

        cont_faltas = lru(frames, 4, 3000, referencias); /* Chamada da fun��o de simula��o, 
                                                        armazenando seu resultado na vari�vel
                                                        "cont_faltas". */
         
    }
    
    
    
}
