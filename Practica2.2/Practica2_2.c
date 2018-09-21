// I/O List
//Inputs************************************************************************

//Outputs***********************************************************************
// LED en RB0

// 1. Sección Directivas pre-proceso
// Incluir librerías
#include <xc.h>  //Esta es la librería principal del compilador
//en ella se encuentran todas las definiciones para el microcontrolador utilizado
#include "confp2.h"
// Definiciones
#define _XTAL_FREQ 32000000
// Macros


// 2. Sección de declaraciones
//   Variables Globales


//   Prototipos de funciones



// 3. Sección de subrutinas
// MAIN: obligatorio para un programa en C
void  main(void) {
    
    //Configuración del Oscilador+
    //OSCCON1bits.NOSC=0b110;
    // OSCCON1bits.NDIV=0b000;
    OSCFRQbits.HFFRQ=0b110; //Selecciona la frecuencia de 32MHz del INTOSC
    //Configuración de puertos
    PORTB =0;    //Limpia puerto B
     PORTA =0;
    ANSELB=0;   //Puerto B como digital
     ANSELA=0; 
    TRISB=0b11110011;
    TRISA=0b00000000;    //RB0-3 Salidas,RB4-7 Entradas
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
   
   
    while(1){
      if (PORTBbits.RB0==0) {
          __delay_ms(200);
          PORTAbits.RA4= PORTAbits.RA4 +1;
          __delay_ms(200);
          }
       if(PORTBbits.RB1 == 0) {
         __delay_ms(200);
          PORTBbits.RB3= PORTBbits.RB3 +1;
          __delay_ms(200);  
       }  
      
      
       
    }
    return;
}