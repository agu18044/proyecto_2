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
char value;
char dato;
char localidad;
char lec1;
char lec2; 
char lec3;
char lec4; 
char lec5;
char lec_pwm1;
char lec_pwm2;

// Funciones
void setup(void);
void bitb1(void);  //funciones para el bitbanging
void bitb2(void);
void bitb3(void);

// Interrupciones
void __interrupt() isr(void){
    
    if(PIR1bits.ADIF == 1){
        if(ADCON0bits.CHS == 0){
            CCPR1L = (ADRESH >> 1) + 124;
        }    
        else if(ADCON0bits.CHS == 1){ 
            CCPR2L = (ADRESH >> 1) + 124;
        }
        else if (ADCON0bits.CHS == 2){
               value = ADRESH;
            if (value <= 85){
                bitb1();
                 }
           if ((value <= 170)&&(value >= 86)){
                bitb2();
                 }
            if (value >= 171){
                bitb3();
                 }
        }   
           PIR1bits.ADIF = 0; 
    }
    
    if (RBIF == 1){  // Bandera de puerto b
        if (PORTBbits.RB1 == 0)   //revisa PB1
        {
            PORTDbits.RD0 = 0;    
            PORTDbits.RD4 = 1;
            PORTDbits.RD5 = 1;
        }
        else if (PORTBbits.RB1 == 1) 
        {
            PORTDbits.RD0 = 1;
            PORTDbits.RD4 = 0;
            PORTDbits.RD5 = 0;
        }
        if (PORTBbits.RB2 == 0)  //revisa PB2
        {
            PORTDbits.RD1 = 0;     
            PORTDbits.RD6 = 1;
            PORTDbits.RD7 = 1;
        }
        else if (PORTBbits.RB2 == 1)
        {
            PORTDbits.RD1 = 1;
            PORTDbits.RD6 = 0;
            PORTDbits.RD7 = 0;
        } 
        INTCONbits.RBIF = 0;     // Se limpia la bandera
        
    }
    
    if (RCIF == 1) {
        if (RCREG == 'w'){ 
            bitb2();
            __delay_ms(500);
            printf("\r Avanzando \r");
        }
        if (RCREG == ''){ 
        }
        if (RCREG == ''){ 
        }
        if (RCREG == ''){ 
        }
        else{ 
            NULL;//seguridad para que el usuario no ponga otras opciones  //seguridad para que el usuario no ponga otras opciones  
        }  
    } 
        
    }



// Ciclo Principal
void main (void){
    setup();
    ADCON0bits.GO = 1;                      // Bit para que comience la conversion
    PORTDbits.RD1 = 1;
    printf("\r Presione w para avanzar \r");
    
    while(1){
        if (ADCON0bits.GO == 0){
            if(ADCON0bits.CHS == 0){
                ADCON0bits.CHS =1;
            }
            else if (ADCON0bits.CHS == 1){
                ADCON0bits.CHS = 2;
            }
            else
                ADCON0bits.CHS = 0;
            __delay_us(50);
            ADCON0bits.GO = 1;
        }        
    }
}

void putch(char data){   //funcion de stdio.h
    while(TXIF == 0);
    TXREG = data;        //value que se muestra
    return;
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
    //SALIDAS PORTC
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 1;
    //SALIDAS PORTD
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
    //INTR CLK
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;   //8 MHz
    OSCCONbits.SCS = 1;
    //INT PULLUP PORTB
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0b00011110;
    IOCBbits.IOCB1 = 1;
    IOCBbits.IOCB2 = 1;   
    IOCBbits.IOCB3 = 1;
    IOCBbits.IOCB4 = 1;
    //ADC
    ADCON1bits.ADFM = 0;       // Justificado a la izquierda
    ADCON1bits.VCFG0 = 0;      // Vref en VSS y VDD 
    ADCON1bits.VCFG1 = 0;   
    ADCON0bits.ADCS = 0b10;    //oscilador FOSC/32
    ADCON0bits.ADON = 1;       
    ADCON0bits.CHS = 0;        // Canal 0
    __delay_us(50); 
    //PWM
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
    //TMR2
    PIR1bits.TMR2IF = 0;       //apaga la bandera
    T2CONbits.T2CKPS = 0b11;   //prescaler 1:16
    T2CONbits.TMR2ON = 1;   
    while(PIR1bits.TMR2IF == 0);    
    PIR1bits.TMR2IF = 0;
    TRISCbits.TRISC2 = 0;          
    TRISCbits.TRISC1 = 0;
    //UART
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    BAUDCTLbits.BRG16 = 1;
    
    SPBRG = 210;
    SPBRGH = 0;
    
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
    
    TXSTAbits.TXEN = 1;
    
    PIR1bits.RCIF = 0; //bandera RX
    PIR1bits.TXIF = 0; //bandera TX
    //INT
    INTCONbits.GIE = 1;   //globales
    INTCONbits.PEIE = 1;  //perifericos
    PIE1bits.ADIE = 1;        
    PIR1bits.ADIF = 0;      
    INTCONbits.RBIF = 1;
    INTCONbits.RBIE = 1;       
}

void bitb1 (void){
        PORTCbits.RC0 = 1;
        __delay_ms(1);
        PORTCbits.RC0 = 0;
        __delay_ms(19);
    }
    
void bitb2 (void){
        PORTCbits.RC0 = 1;
        __delay_ms(1.5);
        PORTCbits.RC0 = 0;
        __delay_ms(18.5);
    }

void bitb3 (void){
        PORTCbits.RC0 = 1;
        __delay_ms(2);
        PORTCbits.RC0 = 0;
        __delay_ms(18);
    }

