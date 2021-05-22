#ifndef UI_LIB
#define UI_LIB

/** LIBRARIES */
#include <avr/io.h>
#include "timer.h"
#include "display.h"
#include "eeprom.h"
#include "i2c.h"
#include "rtc.h"
#include "usart.h"
#include "thermometer.h"
#include "buttons.h"

/** DEFINES */
#define REL_COOL (1 << DDD2)
#define REL_HEAT (1 << DDD3)

/** VARIABLES */
extern uint8_t screen;
extern uint8_t sec,min,hour,weekday,day,month,year;
extern int16_t temp_set;
extern int16_t temp_act;
extern uint8_t hysteresis;
extern int8_t correction;
extern uint8_t refresh_screen_flag;
extern uint8_t return_counter;

/** FUNCTIONS */
void main_screen();
void settings1_screen();
void settings2_screen();
void settings3_screen();
void save_screen();
void process_rellays();
void process_uart();

#endif