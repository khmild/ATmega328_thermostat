# include "rtc.h"

/**convert data to required format*/
uint8_t convert(uint8_t data){
	uint8_t output = ((data/10)<<4)|(data%10);
	return output;
}

/**convert received data to decimal format*/
uint8_t convert_back(uint8_t data){
	uint8_t output = ((data>>4)*10+(0b00001111&data));
	return output;
}

/**set time, weekday and date as one function*/
void rtc_setTimeAndDate(uint8_t hours, uint8_t minutes, uint8_t seconds,uint8_t weekday, uint8_t day, uint8_t month, uint8_t year){
	
	i2c_Start();		//start bit
	i2c_send_byte(0b11010000);	//set address and write
	i2c_send_byte(0);		//go to 00
	
	i2c_send_byte(convert(seconds)); //seconds
	i2c_send_byte(convert(minutes)); //minutes
	i2c_send_byte(convert(hours)); //hours
	i2c_send_byte(convert(weekday)); //weekday
	i2c_send_byte(convert(day)); //day
	i2c_send_byte(convert(month)); //month
	i2c_send_byte(convert(year)); //year
	
	i2c_Stop();
	
}

/**set time without impact on date*/
void rtc_setTime(uint8_t hours, uint8_t minutes, uint8_t seconds){
	
	i2c_Start();			//start bit
	i2c_send_byte(0b11010000);	//set address and write
	i2c_send_byte(0);		//go to 00
	
	i2c_send_byte(convert(seconds)); //seconds
	i2c_send_byte(convert(minutes)); //minutes
	i2c_send_byte(convert(hours)); //hours
	
	i2c_Stop();
	
}

/**set date without impact on time*/
void rtc_setDate(uint8_t weekday, uint8_t day, uint8_t month, uint8_t year){
	
	i2c_Start();				//start bit
	i2c_send_byte(0b11010000);	//set address and write
	i2c_send_byte(0b00000011);	//go to address
	
	i2c_send_byte(convert(weekday));	//weekday
	i2c_send_byte(convert(day));		//day
	i2c_send_byte(convert(month));		//month
	i2c_send_byte(convert(year));		//year
	
	i2c_Stop();
	
}

/**set generator to generate 1Hz pulses*/
void rtc_setGenerator(){
	
		i2c_Start();				//start bit
		i2c_send_byte(0b11010000);	//set address and write
		i2c_send_byte(0b00000111);	//go to address
		i2c_send_byte(0b00010000);	//set 1Hz outputs
		i2c_Stop();
	
}

/**read and convert actual time and date*/
void rtc_readTimeAndDate(uint8_t *hours, uint8_t *minutes, uint8_t *seconds,uint8_t *weekday, uint8_t *day, uint8_t *month, uint8_t *year){
	
	i2c_send_byteAddr(0,0b11010000);
	//delay(30000);

	i2c_Start();
	i2c_send_byte(0b11010001);
	*seconds = i2c_read_byte();
	*minutes = i2c_read_byte();
	*hours = i2c_read_byte();
	*weekday = i2c_read_byte();
	*day = i2c_read_byte();
	*month = i2c_read_byte();
	*year = i2c_read_lastByte();
	i2c_Stop();
	
	*seconds = convert_back(*seconds);
	*minutes = convert_back(*minutes);
	*hours = convert_back(*hours);
	*weekday = convert_back(*weekday);
	*day = convert_back(*day);
	*month = convert_back(*month);
	*year = convert_back(*year);
	
}