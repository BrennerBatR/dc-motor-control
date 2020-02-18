#include <xc.h>
#include <stdint.h>
#include "lcd.h"
#define  _XTAL_FREQ 4000000
// globais
uint16_t valor = 0;
float	valor_f = 0;


void main(void) {
	// configuração dos periféricos
	//TRISA = TRISA | (1<<0); 
	TRISA	|= (1<<0); // ra0 como entrada
	ANSEL |= (1<<0); // ra0 como entrada analogica
	// ADCON: ADCS = Fosc/8,CHS= AN0, GO = 0, ADON=1
	ADCON0 = 0x00;
	ADCON0 |= 0b01000001;
	//ADCON1: ADFM= right, VCFG1= VSS, VCFG0= VDD
	ADCON1 = 0;
	ADCON1 |= (1<<7); 
	TRISD	= 0;
	TRISC	= 0;
    __delay_ms(20);
    lcd_init();
    lcd_data(0x30);

    lcd_set_position(1,15);
    lcd_data('A');
	
		//config do pwm
   	//ccp1con, intcon, pr2
   	TRISC &= ~(1<<2);
   	T2CON = 0B00000101;	//TRM2CON=1  PRESCALER= 4
   	PR2 = 249;
   	CCP1CON = 0B00001100; //<5:4> os 2 menos significativos do 500 PWM SINGLE OUTPUT ,PWM MODE pag 127
   	CCPR1L = 500 >>2; // pegando os 8 bits mais significativos e armazenando
   	
	
	while(1){
		// loop infinito
		ADCON0 |= (1<<1); // seta go/done (inicia conversão)
		while( ADCON0 & (1<<1));
		valor = (ADRESH<<8) + ADRESL;
		valor = valor*5;
		if (valor > 2000){
			PORTD |= (1<<0); //set RD0
		} else {
			PORTD &= ~(1<<0); //reseta RD0
		}
		__delay_us(5); // delay entre conversões
	}
}