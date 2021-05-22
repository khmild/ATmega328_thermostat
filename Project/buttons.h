#ifndef BUTTONS_LIB
#define BUTTONS_LIB

/** LIBRARIES */
#include <avr/io.h>
#include "timer.h"

/** DEFINES */


/** VARIABLES */


/** FUNCTIONS */
void buttons_init();
uint16_t read_buttons_val();
uint8_t button_state();

#endif