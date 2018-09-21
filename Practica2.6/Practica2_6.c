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
    int adc1 =0;
    int adc2 =0;
    int adc3 =0;
    
    float histeresis,sensor,referencia,x ,volt,volt1,y,z,a,b,c;  //,temp para temperatura
    
    unsigned char buffer1[16];
    
    //Oscilador
    OSCFRQbits.HFFRQ = 0b110;
    
    //Puertos
    //ANSELE = 0;
    ANSELA = 0;
    ANSELC = 0;
    ANSELDbits.ANSD5 = 1; //sensor
    TRISDbits.TRISD5 = 1;
    ANSELDbits.ANSD6 = 1;//potenciometro histeresis
    TRISDbits.TRISD6 = 1;
    ANSELDbits.ANSD7 = 1;//potenciometro medio
    TRISDbits.TRISD7 = 1;
    ANSELDbits.ANSD4 = 0;//rele foco
    TRISDbits.TRISD4 = 0;
    ANSELDbits.ANSD2 = 0;//rele ventilador
    TRISDbits.TRISD2 = 0;
    
    
    
    //Configurar el convertidor
    ADCON0bits.ADON = 1;  //ADC on //
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
        R:
       
        ADPCH = 0b011110;  // Canal AND5
        __delay_ms(20);
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
        adc1 = ADRESH;
        adc1 = adc1 << 8;
        adc1 = adc1 + ADRESL;
        
 
        volt = 5.0*adc1/1023.0;
        sensor = volt*100.0;
        sprintf(buffer1, "s= %0.2f",sensor);
        Lcd_Out2(1,1,buffer1);
        __delay_ms(2);
        Lcd_Out(1,10, "°C");
        __delay_ms(300);
        
        
        
       
        
        ADPCH = 0b011111;  // Canal AND5
        __delay_ms(20);
        ADCON0bits.GO = 1;
        while(ADCON0bits.GO);
        adc3 = ADRESH;
        adc3 = adc3 << 8;
        adc3 = adc3 + ADRESL;
        
        volt1=5.0*adc3/1023.0;
        referencia= volt1*100.0;
        sprintf(buffer1, "R= %0.2f",referencia);
        Lcd_Out2(2,8,buffer1);
        __delay_ms(300);
       
        
        x = 5.0*6.147540/1023;//valor de 3°c
        y = x*100;
        
        z = 5.0*51.22950/1023;//limite inferior 25°c
        a = z*100.0;
        
        b = 5.0*163.9344/1023;//limite inferior 80°c
        c = b*100.0;
        
        
       
        
        
         if (referencia < a || referencia > c ){
             sprintf(buffer1, "ERROR");
        Lcd_Out2(2,1,buffer1);
        __delay_ms(300);
         }else{
             sprintf(buffer1, "      ");
        Lcd_Out2(2,1,buffer1);
         }
        
        
    
       
        if (sensor > (referencia + y)){
      
            LATDbits.LATD2 = 1;
            LATDbits.LATD4=0; //
            
        }
        
        A:
        __delay_ms(300);
        if (sensor < (referencia - y)){
             //
           LATDbits.LATD2 = 0;
           LATDbits.LATD4 = 1;
           
            
        }
           
        
        
    }
        return;
}
