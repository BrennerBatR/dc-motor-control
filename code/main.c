#include <xc.h>
#include <stdint.h>
#define  _XTAL_FREQ 4000000
// globais
uint16_t valor = 0;


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
	
	while(1){
		// loop infinito
		ADCON0 |= (1<<1); // seta go/done (inicia conversão)
		while( ADCON0 & (1<<1));
		valor = (ADRESH<<8) + ADRESL;
		TRISC = ADRESL;
		TRISD = ADRESH;

		
	
	}
}