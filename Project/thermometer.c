#include "thermometer.h"

/**setup adc to read thermistor values*/
void adc_init(){
	
	ADCSRA |= (1 << ADEN)		//ADC Enable
	|(1 << ADPS2)|(1 << ADPS1);	//Prescaler 64
	
	ADMUX |= (1 << REFS0)		//AVcc reference
	|(1 << MUX0);				//ADC1 select
	
}

/**read adc values*/
uint16_t adc_read(){
	
	ADMUX |= (1 << REFS0)		//AVcc reference
	|(1 << MUX0);				//ADC1 select
	
	ADCSRA |= (1 << ADSC);
	while((ADCSRA & (1<<ADSC)));
	return (uint16_t)ADC;
	
}

/**returns calculated temperature in C*/
float calculate_temp(uint16_t adc_val){
	
	float volt;
	float resistance;
	float temp;
	
	//Voltage calculation
	volt = (float)adc_val * 5.0 / 1024.0;		//ADC*Vref/1024
	
	//Resistance calculation
	resistance = (float)(20000.0 * volt/(5.0 - volt)) - 1500.0;
	
	//Temperature calculation
	temp = (float)resistance/10000.0;
	temp = (float)log(temp);
	temp = (float)temp/3895.0;
	temp = (float)temp + 1.0/(25.0+273.0);
	temp = (float)1.0/(temp);
	temp = (float)temp - 273.0;
	return temp;
}