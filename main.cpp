
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#define ADD 0x4E
void i2c_init(){
	TWBR = 0x20; //vibor chastoti
}
void i2c_start(){
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
void i2c_stop(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void i2c_sendbyte(unsigned char byte){
	TWDR = byte;
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
unsigned char I2C_ReadByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}
unsigned char I2C_ReadLastByte(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));//ожидание установки бита TWIN
	return TWDR;//читаем регистр данных
}
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
	str_out("ti kak");
    while (1) 
    {
	
    }
}

