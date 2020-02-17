#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000
#define RS (1<<4)
#define EN (1<<5)
#define DATA_PORT	PORTB
#define DATA_TRIS	TRISB

uint8_t lcd_init(void);
uint8_t lcd_clear(void);
uint8_t lcd_cmd(uint8_t cmd);
uint8_t lcd_data(uint8_t data);
uint8_t lcd_set_position(uint8_t x, uint8_t y);
uint8_t lcd_print_text(uint8_t x, uint8_t y, uint8_t* text);


