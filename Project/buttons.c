#include "buttons.h"
uint32_t last_time_pressed = 0;

/**setup ADC*/
void buttons_init(){
	ADMUX &= ~(1 << MUX0);		//AVcc reference, ADC0
}

/**returns ADC value*/
uint16_t read_buttons_val(){
	ADMUX &= ~(1 << MUX0);		//AVcc reference, ADC0
	ADCSRA |= (1 << ADSC);
	while((ADCSRA & (1<<ADSC)));
	return (uint16_t)ADC;
}

/**returns a value depending on pressed button, 0-not pressed*/
uint8_t button_state(){
	delay(1000);
	
	uint16_t but_val = read_buttons_val();
	uint8_t status = 0;
	
	if ((getTime() - last_time_pressed) > 300000)
	{
		if(but_val > 1020)		status = 0;
		else if (but_val > 630) status = 1; //select
		else if (but_val > 400) status = 2; //left
		else if (but_val > 250) status = 3; //down
		else if (but_val > 90)	status = 4; //up
		else					status = 5; //right
		
		last_time_pressed = getTime();
	}
	return status;
}