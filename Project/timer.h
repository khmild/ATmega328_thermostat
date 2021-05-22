#ifndef TIMER_LIB
#define TIMER_LIB


/** LIBRARIES */
#include <avr/io.h>
#include <avr/interrupt.h>


/** DEFINITIONS */
#define NOP() asm volatile ("nop")
#define LED (1<<5)


/** VARIABLES */
extern volatile uint16_t timer1overflowCount;


/** FUNCTIONS */
void busyDelay(uint32_t us);
void delay(uint32_t us);
void timerInit(void);
uint32_t getTime(void);

#endif