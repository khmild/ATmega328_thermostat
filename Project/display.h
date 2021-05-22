/******************************************************************************/
/*                      HOW TO USE DISPLAY LIBRARY:                           */
/* First you need to set ports and pins which are used for display connection */
/* ports and pins can be configured here									  */
/*  - LCD_PORT - port used for lcd pins connection (default PORTD)			  */
/*  - E_PORT - port used for E pin connection (default PORTB)				  */
/*  - RS_PORT - port used for RS pin connection (default PORTB)				  */
/*  - LCD_PINS - pin used for lcd pins connection (default 4, 5, 6, 7)		  */
/*  - E_PIN - pin used for E pins connection (default 1)					  */
/*  - RS_PIN - pin used for RS pins connection (default 0)					  */
/******************************************************************************/


#ifndef DISPLAY_LIB
#define DISPLAY_LIB

/** LIBRARIES */
#include <avr/io.h>
#include <stdio.h>
#include "timer.h"


//** CONNECTION SETTINGS */
#define LCD_PORT PORTD
#define LCD_PINS (1 << DDD7)|(1 << DDD6)|(1 << DDD5)|(1 << DDD4)
#define LCD_DDR DDRD

#define E_PORT PORTB
#define E_PIN (1 << DDB1)
#define E_DDR DDRB

#define RS_PORT PORTB
#define RS_PIN (1 << DDB0)
#define RS_DDR DDRB

/** VARIABLES */



/** FUNCTIONS */
void display_init();
void display_print(uint8_t data);
void display_cursor(uint8_t state);
void display_cursor_blink(uint8_t state);
void display_clear();
void set_pos(uint8_t x, uint8_t y);
void cursor_move_dir(uint8_t dir);
void display_shift(uint8_t state);
void display_scroll_left();
void display_scroll_right();

#endif