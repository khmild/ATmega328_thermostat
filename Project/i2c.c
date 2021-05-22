#include "i2c.h"

/**setup twi*/
void i2c_init(){
	TWBR = 0x20; //((F_CPU/F_SCL)-16)/(2*4^TWPS);
}

/**send start command*/
void i2c_Start(){
	TWCR = (1<<TWINT)
			|(1<<TWSTA) // start bit
			|(1<<TWEN); // enable i2c

	while(!(TWCR&(1<<TWINT))); // wait until ready
}

/**send stop command*/
void i2c_Stop(){
	TWCR = (1<<TWINT)
			|(1<<TWSTO)	// stop bit
			|(1<<TWEN); // enable i2c
}


/**send data*/
void i2c_send_byte(uint8_t data){
	TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN); //sending
	while (!(TWCR & (1<<TWINT))); //wait until ready
}

/**write data on address*/
void i2c_send_byteAddr(uint8_t data, uint8_t addr){
	i2c_Start();
	i2c_send_byte(addr);
	i2c_send_byte(data);
	i2c_Stop();
}

/**read one byte*/
uint8_t i2c_read_byte(){
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

/**read last byte (without confirmation)*/
uint8_t i2c_read_lastByte(){
	TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}