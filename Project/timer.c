#include "timer.h"

volatile uint16_t timer1overflowCount = 0;

/**delay using NOP function*/
void busyDelay(uint32_t us){
	
	us -= 2;
	
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	
	
	for (;us != 0; --us)
	{
		NOP();
		NOP();
		NOP();
		NOP();
		NOP();
		NOP();
	}
	
}

/**delay using timer*/ 
void delay(uint32_t us){
	
	us = (us << 1);
	
	uint32_t startTime;
	uint32_t actTime;
	startTime = getTime();
	actTime = getTime();
	
	while ((actTime - startTime) < us)
	{
		actTime = getTime();
	}
	
}

/**initialize timers for getTime function*/
void timerInit(void){
	
	TIMSK1 |= (1<<TOIE1);			//povoleni preruseni pri preteceni
	TIFR1 = (1<<TOV1) | (1<<OCF1A); //vynulovani preteceni a compare
	TCNT1 = 0;						//vynulovani timeru
	TCCR1B = (1<<CS11);				//preddelic 8
	
}

/**get actual time from start*/
uint32_t getTime(void){
	
	uint32_t actualTime;
	
	actualTime = TCNT1 | (((uint32_t)timer1overflowCount) << 16);
	
	return actualTime;
}

ISR(TIMER1_OVF_vect){
	++timer1overflowCount;
}