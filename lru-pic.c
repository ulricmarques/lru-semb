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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "referencias.h"

#define _XTAL_FREQ 32000000
#define F_CPU 32000000/64//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)//calculo do taxa de transmissão serial para Uart

int num_referencias,num_frames;
//char referencias[900];
int frames[4];
int acerto=0;
int i,j,k;
int cont_faltas=0;

/*
void gera_referencias(){
	num_frames = 4;
	num_referencias = 3000;
	int i;
	for(i=0; i<num_referencias; i++){
		referencias[i] = i;
	}	
}*/

 
void inicializa(){
    cont_faltas=0;
    for(i=0; i<num_frames; i++)
        frames[i]=9999;
}
 
int foi_acerto(int referencia){
    acerto=0;
    for(j=0; j<num_frames; j++){
        if(frames[j]==referencia){
            acerto=1;
            break;
        }
    }
    return acerto;
}
 


 
int lru(){
    inicializa();
    int menos_recentemente_usados[4];
    for(i=0; i<num_referencias; i++){
        //printf("\nPara %d :",referencias[i]);
        if(foi_acerto(referencias[i])==0){
            for(j=0; j<num_frames; j++){
                int pagina_atual=frames[j];
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
            frames[indice_substituido]=referencias[i];
            cont_faltas++;
 
            //mostra_paginas();
        }
        else{
            //printf("Acerto!");
        }
    }
    return cont_faltas;
}

int main(void) {
        TRISA = 0x0F;

//    LATAbits.LATA4 = 0;
//    LATAbits.LATA5 = 1;
//    LATAbits.LATA6 = 1;            
//    LATAbits.LATA7 = 0;
//    while (1);
    
    while (1) {
       
        cont_faltas = lru(); /* Chamada da fun??o de simula??o, 
                                                        armazenando seu resultado na vari?vel
                                                        "cont_faltas". */

      //LATA = 0x90;
       LATAbits.LATA4 = 1;
       LATAbits.LATA5 = 1;
       LATAbits.LATA6 = 1;            
       LATAbits.LATA7 = 1;
       __delay_ms(500);
       LATAbits.LATA4 = 1;
       LATAbits.LATA5 = 0;
       LATAbits.LATA6 = 0;            
       LATAbits.LATA7 = 1;
       __delay_ms(500);
    
      
    }
    

}
