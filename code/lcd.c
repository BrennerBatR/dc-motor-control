#include "lcd.h"
uint8_t pos = 0;
uint8_t lcd_init(void)
{
	__delay_ms(40);
	DATA_TRIS = 0x00;
	ANSELH = 0x00;
	lcd_cmd(0x02);
	lcd_cmd(0x02);
	lcd_cmd(0x08);
	lcd_cmd(0x00);
	lcd_cmd(0x0C);
	lcd_cmd(0x00);
	lcd_cmd(0x06);

	return 0;
}

uint8_t lcd_clear(void);

uint8_t lcd_cmd(uint8_t cmd)
{
	DATA_PORT = cmd;
	DATA_PORT &= ~RS;
	DATA_PORT |= EN;
	__delay_ms(2);
	DATA_PORT &= ~EN;
	__delay_ms(2);
	return 0;
	
	
}
uint8_t lcd_data(uint8_t data)
{
	uint8_t high_nibble;
	uint8_t low_nibble;
	
	high_nibble = data >> 4;
	high_nibble &= 0x0F;
	
	low_nibble = data & 0x0F;
	DATA_PORT = high_nibble;
	DATA_PORT |= RS;
	DATA_PORT |= EN;
	__delay_ms(2);
	DATA_PORT &= ~EN;
	__delay_ms(2);
	
	DATA_PORT = low_nibble;
	DATA_PORT |= RS;
	DATA_PORT |= EN;
	__delay_ms(2);
	DATA_PORT &= ~EN;
	__delay_ms(2);
	
	return 0;
	
}
uint8_t lcd_set_position(uint8_t x, uint8_t y)
{
	uint8_t pos = 0;
	if ( x == 0 ){
		pos = y;
		pos |= (1<<7);
		lcd_cmd((pos>>4)&0x0F);
		lcd_cmd(pos & 0x0F);
	} else {
		pos = y;
		pos | = (0xC0);
		lcd_cmd((pos>>4)&0x0F);
		lcd_cmd(pos & 0x0F);
	}
	return 0;
	
}

uint8_t lcd_print_text(uint8_t x, uint8_t y, uint8_t* text);


uint8_t lcd_tensao(uint16_t tensao){
	uint16_t milhar = tensao/1000;
	uint16_t centena = (tensao%1000);
	centena = centena/100;
	uint8_t dezena = (tensao%100);
	dezena = dezena/10;
	
	uint8_t unidade = (tensao%10);
	
	lcd_set_position(1,0);
    lcd_data(milhar+0x30);
    
    lcd_set_position(1,1);
    lcd_data('.');
    
    lcd_set_position(1,2);
    lcd_data(centena +0x30);
    
    lcd_set_position(1,3);
    lcd_data(dezena+0x30);
    
    lcd_set_position(1,4);
    lcd_data(unidade+0x30);
    
    lcd_set_position(1,5);
    lcd_data('V');
    
    
    return 0;
	
	
	
		
}