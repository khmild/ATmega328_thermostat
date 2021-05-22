#include "usart.h"

volatile uint8_t message[20];
volatile uint8_t received_flag = 0;

void usart_init(uint16_t baud){
	uint16_t ubrr;
	ubrr = F_CPU/16/baud-1;
	
	//Baud rate settings:
	UBRR0H = (uint8_t)(ubrr>>8);
	UBRR0L = (uint8_t)ubrr;
	
	//Enabling RX and TX
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	
	//Frame format:
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00); //8bit, 1stop bit
}

void usart_transmit(uint8_t data){
	// wait until usart is ready for new data
	while ( !( UCSR0A & (1<<UDRE0)) );
	//send the data
	UDR0 = data;
}

uint8_t usart_receive(void){
	//wait for receiving to finish
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}

void usart_receiveStr(){

	uint8_t i = 0;

	while (i < 19) {
		uint8_t c;
		while ( !(UCSR0A & (1<<RXC0)) );
		c = UDR0;
		if (c == '\n') break;
		message[i] = c;
		i++;
	}
	
	message[i] = '\0';

}

ISR(USART_RX_vect){
	received_flag = 1;
	uint8_t i = 0;
	
	while (i < 19) {
		uint8_t c;
		while ( !(UCSR0A & (1<<RXC0)) );
		c = UDR0;
		if (c == '\n') break;
		message[i] = c;
		i++;
	}
}