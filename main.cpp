
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include "I2C.cpp"
#define ADD 0x4E

/*class LCD_1602_I2C{
public:
	LCD_1602_I2C(unsigned char i2c_add){
		
	}
private:

	};*/

/////////////////////////////////////////////////
void byte_out(unsigned char data,unsigned char add){
	add &= 0xFE; //poslednii bit vsegda nol'
	i2c_start();
	i2c_sendbyte(add);
	i2c_sendbyte(data);
	i2c_stop();
}
void send_command(unsigned char com){
	com |=0x04;  //E on
	byte_out(com,ADD);
	com &= 0xFB; // E off
	byte_out(com,ADD);
}
void init_1602(void){
	_delay_ms(15); //pausa posle podachi naprajeniya
	send_command(0x30);     //Perehod v chetireh bitnii rejim
	_delay_ms(4); //zaderjka dlya vipolneniya komandi
	send_command(0x30);     //Perehod v chetireh bitnii rejim
	_delay_us(100);
	send_command(0x20);     //Perehod v chetireh bitnii rejim
	_delay_ms(40);
	send_command(0x20); //ustanovka parametrov
	send_command(0x80); //ustanovka parametro
	_delay_us(40);
	send_command(0x00);
	send_command(0x80);
	_delay_us(40);
	send_command(0x00); //ochishaem ekran
	send_command(0x10); //ochishaem ekran
	_delay_ms(2);
	send_command(0x00);
	send_command(0x60);
	_delay_us(40);
	send_command(0x00);
	send_command(0xC0);
	_delay_us(40);

}
void char_out(unsigned char data){
	unsigned char data_h = ((data & 0xF0) + 0x09);//berem pol byte verhnee i dobavlyaem komandu
	unsigned char data_l = (((data<<4)& 0xF0) + 0x09); //berem pol byte nijnee i dobavlyaem komandu
	
 //peredaem starshie biti
	data_h |= 0x04; //E on
	byte_out(data_h,ADD);
	data_h &= 0xF9; //E off
	byte_out(data_h,ADD);
	
//peredaem mladshie biti
	data_l |= 0x04; //E on
	byte_out(data_l,ADD);
	data_l &= 0xF9; //E off
	byte_out(data_l,ADD);
}
void str_out(char *str)
{
	while((*str) != '\0')
	{
		char_out(*str);
		str++;
	}
}
int main(void)
{	
	
	i2c_init();
	init_1602();
	str_out("aasfa");
    while (1) 
    {
	
    }
}

