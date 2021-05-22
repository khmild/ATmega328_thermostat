#ifndef USART_LIB
#define USART_LIB

/** LIBRARIES */
#include <avr/io.h>
#include <avr/interrupt.h>

/** DEFINES */
#define F_CPU 16000000

/** VARIABLES */
extern volatile uint8_t message[20];
extern volatile uint8_t received_flag;

/** FUNCTIONS */
uint8_t usart_receive(void);
void usart_transmit(uint8_t data);
void usart_init(uint16_t baud);
void usart_receiveStr();

#endif