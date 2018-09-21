// 0.Sección de documentación 

// main.c

// Dispositivo: PIC16F18877

// Práctica 2.3

// Autores: Gabriel Casarrubias Guerrero

// Fecha: Septiembre 06, 2018



// I/O List

//Inputs************************************************************************



//Outputs***********************************************************************

// Puerto RA4 a LCD
// Puerto RA3 a LCD
// Puerto RA2 a LCD
// Puerto RA1 a LCD


// 1. Sección Directivas pre-proceso

// Incluir librerías

#include <xc.h>  //Esta es la librería principal del compilador

//en ella se encuentran todas las definiciones para el microcontrolador utilizado

#include "confp3.h"
#include <stdio.h>
// Definiciones

#define _XTAL_FREQ 32000000

// Libreria de LCD
#include "flex_lcd.h"
// Macros





// 2. Sección de declaraciones

//   Variables Globales





//   Prototipos de funciones







// 3. Sección de subrutinas

// MAIN: obligatorio para un programa en C

void main(void) {

    unsigned char i, j;
    unsigned char buffer1[16];
    
    //Oscilador frecuencia
    OSCFRQbits.HFFRQ = 0b110;
    //Puertos
    ANSELA = 0; //Puerto A como digital
    ANSELC = 0; //Puerto C como digital
    ANSELD = 0;
    //Inicializacion de la LCD
    Lcd_Init();
    
    d:
    Lcd_Cmd(LCD_CLEAR); //Limpia la LCD
    Lcd_Cmd(LCD_BLINK_CURSOR_ON); //Enciende el cursor por 1 segundo
    __delay_ms(1000);
    int x = 2;         // Inicializamos la variable x en 2 para centrar la palabra

    for(i=0; i<13; i++){
        
        sprintf(buffer1,"Contador = %03d ", i); // %03d Para completar a 3 digitos
        Lcd_Out2(2, 1, buffer1);
        __delay_ms(500);
        Lcd_Out2(1, x, " Mecatronica"); // Imprimimos y corremos la palabra Mecatronica
        __delay_ms(10);
        
        x++;
        
        if(i==12){           // Ciclo para reiniciar el programa cuando la cuenta sea = 12
            i=0;
            Lcd_Out2(1, 1, "                ");
            __delay_ms(100);
            goto d;         // Nos dirigimos a la etiqueta d:
        }
    }
        

//4. Inicia ciclo infinito

    while(1);

    return;

}