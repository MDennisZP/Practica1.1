// 0.Secci�n de documentaci�n 

// main.c

// Dispositivo: PIC16F18877

// Pr�ctica 2.1 

// Autores: Gabriel Casarrubias Guerrero

// Fecha: Septiembre 03, 2018



// I/O List

//Inputs************************************************************************



//Outputs***********************************************************************

// LED en RA0



// 1. Secci�n Directivas pre-proceso

// Incluir librer�as

#include <xc.h>  //Esta es la librer�a principal del compilador

//en ella se encuentran todas las definiciones para el microcontrolador utilizado

#include "confp2.h"

// Definiciones

#define _XTAL_FREQ 32000000

// Macros





// 2. Secci�n de declaraciones

//   Variables Globales





//   Prototipos de funciones







// 3. Secci�n de subrutinas

// MAIN: obligatorio para un programa en C

void main(void) {

    

    //Configuraci�n del Oscilador

    //OSCCON1bits.NOSC=0b110;
    // OSCCON1bits.NDIV=0b000;
     OSCFRQbits.HFFRQ = 0b110; // HFINT 32MHz

    //Configuraci�n de puertos

    PORTA=0;    //Limpia puerto A

    TRISA=0;    //Puerto A como salidas

    ANSELA=0;   //Puerto A como digital

 

//4. Inicia ciclo infinito

    while(1){

        LATAbits.LATA0=~LATAbits.LATA0;  //Toggle bits RA0

        __delay_ms(500);                //Espera medio segundo

    }

    return;

}