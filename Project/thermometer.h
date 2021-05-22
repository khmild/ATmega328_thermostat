#ifndef THERMO_LIB
#define THERMO_LIB

/** LIBRARIES */
#include <avr/io.h>
#include <math.h>

/** FUNCTIONS */
void adc_init();
uint16_t adc_read();
float calculate_temp(uint16_t adc_val);

#endif