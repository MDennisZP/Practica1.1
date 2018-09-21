/*
 * File:   Practica2_6.c
 * Author: pcs
 *
 * Created on 8 de septiembre de 2018, 12:31 AM
 */


#include <xc.h>
#include "confp26.h"
#define _XTAL_FREQ 32000000
#include "flex_lcd.h"
#include <stdio.h>

void main(void) {
    int adc=0;
    int adc1 = 0;
    
    float volt,temp;  //,temp para temperatura
    unsigned char buffer1[16];
    
    //Oscilador
    OSCFRQbits.HFFRQ = 0b110;
    
    //Puertos
    //ANSELE = 0;
    ANSELA = 0;
    ANSELC = 0;
    ANSELDbits.ANSD5 = 1;
    TRISDbits.TRISD5 = 1;
    ANSELDbits.ANSD6 = 1;
    TRISDbits.TRISD6 = 1;
    
    //Configurar el convertidor
    ADCON0bits.ADON = 1;  //ADC on
    ADCON0bits.ADCS = 1; //FCR
    ADREFbits.ADNREF = 0; //Vref menos es vss =GND
    ADREFbits.ADPREF = 0b00; //Vref+ sera VDD
    ADCON0bits.ADFRM = 1; //Justificacion derecha
    
    
    //Inicializar la LCD
    Lcd_Init();
    Lcd_Cmd(LCD_CLEAR);
    Lcd_Cmd(LCD_CURSOR_OFF);
    __delay_ms(100);
    
    //Ciclo infinito
    while(1){
        ADPCH = 0b011110;  // Canal AND5
        __delay_ms(20);
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
        adc = ADRESH;
        adc = adc << 8;
        adc = adc + ADRESL;
        
        //volt = 5.0*adc/1023.0;
        temp = adc*100.0*0.00488;
        sprintf(buffer1, "temp= %0.2f",temp);
        Lcd_Out2(1,1,buffer1);
        __delay_ms(2);
        Lcd_Out(1,12, "°C");
        __delay_ms(300);
        
        ADPCH = 0b011101;  // Canal AND5
        __delay_ms(20);
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
        adc1 = ADRESH;
        adc1 = adc1 << 8;
        adc1 = adc1 + ADRESL;
        
        volt = 5.0*adc1/1023.0;
        sprintf(buffer1, "volt= %0.2f",volt);
        Lcd_Out2(2,1,buffer1);
        __delay_ms(300);
        
    }
        return;
}
