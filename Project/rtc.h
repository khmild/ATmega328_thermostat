#ifndef RTC_LIB
#define RTC_LIB

/** LIBRARIES */
#include <avr/io.h>
#include "i2c.h"

/** DEFINES */


/** VARIABLES */


/** FUNCTIONS */
void rtc_setTimeAndDate(uint8_t hours, uint8_t minutes, uint8_t seconds,uint8_t weekday, uint8_t day, uint8_t month, uint8_t year);
void rtc_setTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
void rtc_setDate(uint8_t weekday, uint8_t day, uint8_t month, uint8_t year);
void rtc_setGenerator();
uint8_t convert_back(uint8_t data);
void rtc_readTimeAndDate(uint8_t *hours, uint8_t *minutes, uint8_t *seconds,uint8_t *weekday, uint8_t *day, uint8_t *month, uint8_t *year);


#endif