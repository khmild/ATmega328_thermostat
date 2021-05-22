#ifndef EEPROM_LIB
#define EEPROM_LIB

/** LIBRARIES */
#include <avr/io.h>
#include "i2c.h"
#include "timer.h"

/** DEFINES */


/** VARIABLES */
uint8_t data_to_save[32];
uint8_t recieved_eeprom[32];

/** FUNCTIONS */
uint8_t eeprom_store(uint8_t *data, uint8_t size);
uint8_t eeprom_read(uint8_t *data, uint8_t size);

#endif