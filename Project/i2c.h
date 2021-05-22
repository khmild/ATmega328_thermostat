#ifndef I2C_LIB
#define I2C_LIB

/** LIBRARIES */
#include <avr/io.h>

/** DEFINES */
#ifndef F_CPU
	#define F_CPU 16000000
#endif


/** VARIABLES */


/** FUNCTIONS */
void i2c_init();
void i2c_Start();
void i2c_Stop();
void i2c_send_byte(uint8_t data);
void i2c_send_byteAddr(uint8_t data, uint8_t addr);
uint8_t i2c_read_byte();
uint8_t i2c_read_lastByte();

#endif