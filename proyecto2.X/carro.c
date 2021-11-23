/*
 * Proyecto 2 - Carrito
 * Diego Aguilar, 18044
 * 
 
 
 */


#pragma config FOSC = INTRC_NOCLKOUT        // Oscillator Selection bits (LP oscillator: Low-power crystal on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF          // Code Protection bit (Program memory code protection is enabled)
#pragma config CPD = OFF         // Data Code Protection bit (Data memory code protection is enabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF       // Flash Program Memory Self Write Enable bits (0000h to 0FFFh write protected, 1000h to 1FFFh may be modified by EECON control)


#define _XTAL_FREQ 8000000
#include <stdint.h>
#include <stdio.h>
#include <xc.h>

// Variables


// Funciones
void setup(void);

// Interrupciones


// Ciclo Principal
void main (void){
    setup();
    while(1){
    
    }
}


// Set up
void setup(void){
    ANSEL = 0b00000111;
    ANSELH = 0;
    //
    TRISA = 0x0F;
    //
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;
    TRISBbits.TRISB4 = 1;
    //
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    //
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;
    //
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    //
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;   //8 MHz
    OSCCONbits.SCS = 1;
    //
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0b00011110;
    IOCBbits.IOCB1 = 1;
    IOCBbits.IOCB2 = 1;   
    IOCBbits.IOCB3 = 1;
    IOCBbits.IOCB4 = 1;
    //
    ADCON1bits.ADFM = 0;       // Justificado a la izquierda
    ADCON1bits.VCFG0 = 0;      // Vref en VSS y VDD 
    ADCON1bits.VCFG1 = 0;   
    ADCON0bits.ADCS = 0b10;    //oscilador FOSC/32
    ADCON0bits.ADON = 1;       
    ADCON0bits.CHS = 0;        // Canal 0
    __delay_us(50); 
    //
    TRISCbits.TRISC2 = 1;           // CCP como input
    TRISCbits.TRISC1 = 1; 
    PR2 = 249;                      // Periodo
    CCP1CONbits.P1M = 0;            // Modo de PWM
    CCP1CONbits.CCP1M = 0b1100;
    CCPR1L = 0x0f;                  // duty cycle
    CCP2CONbits.CCP2M = 0b1100;
    CCPR2L = 0x0f;
    
    CCP1CONbits.DC1B = 0;
    CCP2CONbits.DC2B0 = 0;
    CCP2CONbits.DC2B1 = 0;
    //
    PIR1bits.TMR2IF = 0;       //apaga la bandera
    T2CONbits.T2CKPS = 0b11;   //prescaler 1:16
    T2CONbits.TMR2ON = 1;   
    while(PIR1bits.TMR2IF == 0);    
    PIR1bits.TMR2IF = 0;
    TRISCbits.TRISC2 = 0;          
    TRISCbits.TRISC1 = 0;
    //
    INTCONbits.GIE = 1;   //globales
    INTCONbits.PEIE = 1;  //perifericos
    PIE1bits.ADIE = 1;        
    PIR1bits.ADIF = 0;      
    INTCONbits.RBIF = 1;
    INTCONbits.RBIE = 1;
    //
    
    
    
    
}

