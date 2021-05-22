#include "timer.h"
#include "display.h"
#include "eeprom.h"
#include "i2c.h"
#include "rtc.h"
#include "usart.h"
#include "thermometer.h"
#include "buttons.h"
#include "thermostat_UI.h"

//custom outputs
static FILE display = FDEV_SETUP_STREAM(display_print, NULL, _FDEV_SETUP_WRITE);

void main_screen();

int main(void)
{
	//relays initialization
	DDRC |= REL_COOL|REL_HEAT;
	PORTC |= REL_COOL|REL_HEAT;
	
	//interrupts setup
	DDRD &= ~(1 << DDD2);
	EIMSK |= (1<<INT0);				// enable INT0
	EICRA |= (1<<ISC01)|(1<<ISC00);	//INT0 - rising edge
	
	//timer initialization
	timerInit();
	sei();
	
	//usart initialization
	usart_init(9600);
	
	//i2c initialization
	i2c_init();
	
	//thermometer adc init
	adc_init();
	
	
	//display initialization	
	display_init();
	stdout = &display;
	
	//read eeprom stored settings
	eeprom_read(recieved_eeprom, 11);
	rtc_setTimeAndDate(recieved_eeprom[0],recieved_eeprom[1],
						recieved_eeprom[2],recieved_eeprom[3],recieved_eeprom[4],
						recieved_eeprom[5],recieved_eeprom[6]); 
    hysteresis = recieved_eeprom[7];
	correction = recieved_eeprom[8];
	temp_set = ((int16_t)recieved_eeprom[9] << 8);
	temp_set |= (int16_t)recieved_eeprom[10];
	
	//set generator to 1Hz
	rtc_setGenerator();
	
    while (1) 
    {	
		process_rellays();					// check if need to turn on/off rellays
		if(received_flag) process_uart();	// check uart messages
		
		switch (screen)						
		{
			case 0:
				main_screen();
				break;
			case 1:
				settings1_screen();
				break;
			case 2:
				settings2_screen();
				break;
			case 3:
				settings3_screen();
				break;
			case 4:
				save_screen();
				break;
		}
    }
}



/* refresh mainscreen with 1Hz and return to mainscreen in 5s*/
ISR (INT0_vect){ 
	refresh_screen_flag = 1;
	return_counter++;
	if (return_counter > 5)
	{
		screen = 0;
		return_counter = 0;
	}
}