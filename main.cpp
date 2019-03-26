
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>

#include "I2C.h"
#include "lcd1602.h"

int main(void)
{	
	LCD_1602_I2C hi(0x4E);
	hi.print_str("12345");
    while (1) {
		
	}
    

    
}

