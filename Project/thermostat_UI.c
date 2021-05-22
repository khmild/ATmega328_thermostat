#include "thermostat_UI.h"

uint8_t screen = 0;
uint8_t time_set_selector = 0;

uint8_t refresh_screen_flag = 0;
uint8_t return_counter = 0;

uint8_t sec,min,hour,weekday,day,month,year;
int16_t temp_set = 0;
int16_t temp_act = 0;

uint8_t hysteresis = 5;
int8_t correction = 0;

/************************************************************************/
/*                          MAIN SCREEN                                 */
/************************************************************************/
void main_screen(){
	display_cursor(0);
	
	rtc_readTimeAndDate(&hour, &min, &sec, &weekday, &day, &month, &year);
	temp_act = (int16_t)(10*calculate_temp(adc_read()))+(int16_t)correction;
	uint8_t buttons_val = button_state();
	
	if (refresh_screen_flag)
	{
		delay(1000);
		set_pos(0,0);
		delay(1000);
		
		printf("Temp:");
		if (temp_act < 0)
		{
			printf("-");
			printf("%d.%d",-temp_act/10, -temp_act%10);
			delay(1000);
		}
		else
		{
			printf("%d.%d",temp_act/10, temp_act%10);
			delay(1000);
		}
		printf("/");
		if (temp_set < 0)
		{
			printf("-");
			printf("%d.%d  ",-temp_set/10, -temp_set%10);
			delay(1000);
		}
		else
		{
			printf("%d.%d  ",temp_set/10, temp_set%10);
			delay(1000);
		}
		
		delay(1000);
		set_pos(0,1);
		delay(1000);
		printf("%02d:%02d  %02d/%02d/%02d ", hour, min, day, month, year);
		
		refresh_screen_flag = 0;
	}
	
	switch (buttons_val)
	{
		case 0:
			break;
		case 1:		//select button
			screen++;
			display_clear();
			return_counter = 0;
			break;
		case 2:		//left button
			break;
		case 3:		//down button
			temp_set--;
			refresh_screen_flag = 1;
			break;
		case 4:		//up button
			temp_set++;
			refresh_screen_flag = 1;
			break;
		case 5:		//right button
			break;
	}
}


/************************************************************************/
/*                   HYSTERESIS SETTINGS SCREEN                         */
/************************************************************************/
void settings1_screen(){
	
	delay(250000);
	
	display_cursor(0);
	uint8_t buttons_val = button_state();
	
	delay(1000);
	set_pos(0,0);
	delay(1000);
	printf("Hysteresis");
	
	delay(1000);
	set_pos(6,1);
	delay(1000);
	printf("%d.%d ", hysteresis/10, hysteresis%10);
	
	switch (buttons_val)
	{
		case 0:
			break;
		case 1:		//select button
			display_clear();
			return_counter = 0;
			screen++;
			break;
		case 2:		//left button
			break;
		case 3:		//down button
			hysteresis--;
			return_counter = 0;
			break;
		case 4:		//up button
			hysteresis++;
			return_counter = 0;
			break;
		case 5:		//right button
			break;
	}
}


/************************************************************************/
/*                   TEMPERATURE CORRECTION SCREEN                      */
/************************************************************************/
void settings2_screen(){
	
	delay(250000);
	
	display_cursor(0);
	uint8_t buttons_val = button_state();
	
	delay(1000);
	set_pos(0,0);
	delay(1000);
	printf("Temp calibration");
	
	delay(1000);
	set_pos(6,1);
	delay(1000);
	if (correction < 0)
	{
		printf("-");
		printf("%d.%d ",-correction/10, -correction%10);
	}
	else
	{
		printf("%d.%d ",correction/10, correction%10);
	}
	
	
	switch (buttons_val)
	{
		case 0:
			break;
		case 1:		//select button
			display_clear();
			return_counter = 0;
			screen++;
			break;
		case 2:		//left button
			break;
		case 3:		//down button
			correction--;
			return_counter = 0;
			break;
		case 4:		//up button
			correction++;
			return_counter = 0;
			break;
		case 5:		//right button
			break;
	}
}


/************************************************************************/
/*                     TIME AND DATE SETTINGS                           */
/************************************************************************/
void settings3_screen(){
	
	delay(250000);
	
	uint8_t buttons_val = button_state();
	
	delay(1000);
	set_pos(0,0);
	delay(1000);
	printf("Time and Date:");
	
	delay(1000);
	set_pos(0,1);
	delay(1000);
	printf("%02d:%02d  %02d/%02d/%02d ", hour, min, day, month, year);
	
	display_cursor(1);
	switch (time_set_selector)
	{
	case 0:
		set_pos(1,1);
		if (buttons_val == 4){
			 hour++;
			 return_counter = 0;}
		if (buttons_val == 3) {
			hour--;
			return_counter = 0;}
		break;
	case 1:
		set_pos(4,1);
		if (buttons_val == 4) {
			min++;
			return_counter = 0;}
		if (buttons_val == 3) {
			min--;
			return_counter = 0;}
		break;
	case 2:
		set_pos(8,1);
		if (buttons_val == 4) {
			day++;
			return_counter = 0;}
		if (buttons_val == 3) {
			day--;
			return_counter = 0;}
		break;
	case 3:
		set_pos(11,1);
		if (buttons_val == 4) {
			month++;
			return_counter = 0;}
		if (buttons_val == 3) {
			month--;
			return_counter = 0;}
		break;
	case 4:
		set_pos(14,1);
		if (buttons_val == 4) {
			year++;
			return_counter = 0;}
		if (buttons_val == 3) {
			year--;
			return_counter = 0;}
		break;
	}
	
	
	switch (buttons_val)
	{
		case 0:
			break;
		case 1:		//select button
			display_clear();
			rtc_setTimeAndDate(hour,min,0,1,day,month,year);
			return_counter = 0;
			screen++;
			break;
		case 2:		//left button
			time_set_selector--;
			if(time_set_selector == 255) time_set_selector = 4;
			return_counter = 0;
			break;
		case 3:		//down button
			break;
		case 4:		//up button
			break;
		case 5:		//right button
			time_set_selector++;
			if(time_set_selector == 5) time_set_selector = 0;
			return_counter = 0;
			break;
	}
}


/************************************************************************/
/*                          SAVE SCREEN                                 */
/************************************************************************/
void save_screen(){
	
	delay(250000);
	
	uint8_t buttons_val = button_state();
	
	display_cursor(0);
	
	delay(1000);
	set_pos(0,0);
	delay(1000);
	printf("Save to EEPROM:");
	
	delay(1000);
	set_pos(0,1);
	delay(1000);
	printf("Press UP to save");
	
		switch (buttons_val)
	{
		case 0:
			break;
		case 1:		//select button
			display_clear();
			return_counter = 0;
			screen = 0;
			break;
		case 2:		//left button
			break;
		case 3:		//down button
			break;
		case 4:		//up button
			data_to_save[0] = hour;
			data_to_save[1] = min;
			data_to_save[2] = sec;
			data_to_save[3] = weekday;
			data_to_save[4] = day;
			data_to_save[5] = month;
			data_to_save[6] = year;
			
			data_to_save[7] = hysteresis;
			data_to_save[8] = correction;
			data_to_save[9] = (temp_set>>8);
			data_to_save[10] = temp_set;

			eeprom_store(data_to_save,11);
			
			display_clear();
			delay(3000);
			set_pos(5,0);
			delay(1000);
			printf("Saved!");
			delay(1000000);
			screen = 0;
			break;
		case 5:		//right button
			break;
	}
	
}


/**check if temperature is in the limits, turn on/off relays if needed*/
void process_rellays(){
	if (temp_act < (temp_set - hysteresis/2))
	{
		PORTC &= ~REL_HEAT;
		PORTC |= REL_COOL;
	}
	
	if (temp_act > (temp_set + hysteresis/2))
	{
		PORTC &= ~REL_COOL;
		PORTC |= REL_HEAT;
	}
}


/**process received from uart data*/
void process_uart(){

	if(message[0] == 'h'){ 
		hysteresis = ((message[2]-48)*100)+((message[3]-48)*10)+(message[5]-48);
	}
	
	else if(message[0] == 's') {
		if (message[2]=='-'){
			temp_set = -((message[3]-48)*100)+((message[4]-48)*10)+(message[6]-48);
		}
		else{
			temp_set = ((message[2]-48)*100)+((message[3]-48)*10)+(message[5]-48);
		}
	}
	
	else if(message[0] == 'c') {
		if (message[2]=='-'){
			correction = -((message[3]-48)*100)+((message[4]-48)*10)+(message[6]-48);
		}
		else{
			correction = ((message[2]-48)*100)+((message[3]-48)*10)+(message[5]-48);
		}
	}
	
	else if(message[0] == 't') {
		hour = ((message[2]-48)*10)+(message[3]-48);
		min = ((message[5]-48)*10)+(message[6]-48);
		sec = ((message[8]-48)*10)+(message[9]-48);
		rtc_setTime(hour, min, sec);
	}
	
	else if(message[0] == 'd') {
		day = ((message[2]-48)*10)+(message[3]-48);
		month = ((message[5]-48)*10)+(message[6]-48);
		year = ((message[8]-48)*10)+(message[9]-48);
		rtc_setDate(1, day, month, year);
	}
	
	data_to_save[0] = hour;
	data_to_save[1] = min;
	data_to_save[2] = sec;
	data_to_save[3] = weekday;
	data_to_save[4] = day;
	data_to_save[5] = month;
	data_to_save[6] = year;
	
	data_to_save[7] = hysteresis;
	data_to_save[8] = correction;
	data_to_save[9] = (temp_set>>8);
	data_to_save[10] = temp_set;

	eeprom_store(data_to_save,11);
	
	received_flag = 0;
}