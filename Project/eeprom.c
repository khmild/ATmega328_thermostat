#include "eeprom.h"

#define TX_CONFIRM 0x28
#define RX_CONFIRM 0x50 
#define TX_CONF 0x58

uint8_t data_to_save[32] = {0};
uint8_t recieved_eeprom[32] = {0};


/**function for saving up to 32 bytes
	returns 0 if success			*/
uint8_t eeprom_store(uint8_t *data, uint8_t size){
	
	i2c_Start();
	i2c_send_byte(0b10100000); //address and write bite
	i2c_send_byte(0); //goto 00 first word
	i2c_send_byte(0); //second
	
	for (uint8_t i = 0; i < size; i++)
	{
		TWDR=data[i];
		TWCR = (1<<TWINT)|(1<<TWEN);
		while(!(TWCR&(1<<TWINT)));
		if ((TWSR & 0xF8) != TX_CONFIRM)return 1; //error
	}
	
	i2c_Stop();	
	return 0; //success
}


/**function for reading up to 32 bytes
	returns 0 if success			*/
uint8_t eeprom_read(uint8_t *data, uint8_t size){
	
	i2c_Start();
	i2c_send_byte(0b10100000); //address and write bite
	i2c_send_byte(0); //goto 00 first word
	i2c_send_byte(0); //second
	i2c_Start();
	delay(10000); // delay for stability
	i2c_send_byte(0b10100001); //address and read bite
	
	for (uint8_t i = 0; i < size-1; i++)
	{
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);	//receive
		while(!(TWCR & (1<<TWINT)));
		if ((TWSR & 0xF8) != RX_CONFIRM) return 1; //error
		data[i] = TWDR;
	}
	
	TWCR = (1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	if ((TWSR & 0xF8) != TX_CONF) return 1;
	data[size-1] = TWDR;
	
	i2c_Stop();
	return 0; //success
}