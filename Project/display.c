#include "display.h"

/** MACROS */
#define set_e1 E_PORT |= E_PIN
#define set_e0 E_PORT &= ~E_PIN
#define set_rs1 RS_PORT |= RS_PIN
#define set_rs0 RS_PORT &= ~RS_PIN

// variable disp_settings is used for storing display settings
// bit0 - display on/off
// bit1 - cursor on/off
// bit2 - cursor blinking on/off
// bit3 - cursor move dir 1-right, 0-left
// bit4 - display shift on/off
uint8_t disp_settings = 0;

/** function for 4bit communication */
void send4bites(uint8_t data){
	data<<=4;
	
	set_e1;			//set E line to 1
	delay(50);		//delay 50us
	
	//write data to port D
	PORTD &= ((1<<3)|(1<<2)|(1<<1)|(1<<0));
	PORTD |= data;
	
	set_e0;			//set E line to 0
}


/** function for sending one byte by parts using send4bites */
void sendbyte (uint8_t data, uint8_t mode){
	uint8_t buffer = 0;
	
	if (mode == 0) set_rs0;		//sending data or command
	else set_rs1;

	buffer = data >> 4;
	send4bites(buffer);
	send4bites(data);
}


/** setup display for 4bit communication
sending specified in datasheet commands */
void display_init(){ 
	
	//set pins as outputs
	LCD_DDR |= LCD_PINS;
	E_DDR	|= E_PIN;
	RS_DDR	|= RS_PIN;
	
	//initializing algorithm
	send4bites((1 << 1)|(1 << 0));
	delay(15000);
	send4bites((1 << 1)|(1 << 0));
	delay(4000);
	send4bites((1 << 1)|(1 << 0));
	delay(100);
	send4bites((1 << 1)|(1 << 0));
	delay(1000);	
	send4bites((1 << 1));
	delay(1000);
	//initialization finish
	
	//setup display
	sendbyte((1 << 5)|(1 << 3), 0); // 4bit, 2line, 5x8dots display
	delay(1000);
	sendbyte((1 << 3)|(1 << 2), 0); // display on, cursor off, blinking off
	delay(1000);
	sendbyte((1 << 2)|(1 << 1), 0); // cursor moves to right
	delay(1000);
	sendbyte((1 << 0), 0); // clear display
	delay(1000);
	
	disp_settings = 0b00001001;
	
}


/** function for sending one symbol using sendbyte */
void display_print(uint8_t data){
	sendbyte(data,1);
}


/** function for showing/hiding display cursor */
void display_cursor(uint8_t state){
	uint8_t bufer = 0;
	delay(1000);
	
	bufer |= ((disp_settings & (1 << 0)) << 2); //check if power on/off
	bufer |= ((disp_settings & (1 << 2)) >> 2); //check if blink on/off
		
	if (state == 0){
		sendbyte((1 << 3)|bufer, 0); //cursor off
		disp_settings &= ~(1 << 1);
	}
	else{
		sendbyte((1 << 3)|(1 << 1)|bufer, 0); //cursor on
		disp_settings |= (1 << 1);
	}
}


/** function for turning on and off cursor blinking */
void display_cursor_blink(uint8_t state){
	uint8_t bufer = 0;
	delay(1000);
	
	bufer |= ((disp_settings & (1 << 0)) << 2); //check if power on/off
	bufer |= ((disp_settings & (1 << 1)) >> 0); //check if cursor on/off

	if (state == 0){
		sendbyte((1 << 3)|bufer, 0); // blinking off
		disp_settings &= ~(1 << 2);
	}
	else{
		sendbyte((1 << 3)|bufer|(1 << 0), 0); //blinking on
		disp_settings |= (1 << 2);
	}
}


/** function for display clearing */
void display_clear(){
 	sendbyte(1,0);
}


/** set cursor position (X, Y) */
void set_pos(uint8_t x, uint8_t y){		//1line 00H - 27H , 2line 40H - 67H
	sendbyte((1<<7)|(0x40*y+x),0);
}


/** set cursor movement direction */
/* 1 -right, 0 - left */
void cursor_move_dir(uint8_t dir){
	uint8_t buffer = 0;
	buffer |= ((disp_settings & ( 1 << 4 )) >> 4); //check display shift bit state
	
	if (dir == 0){
		sendbyte((1<<2)|buffer,0);
	}
	else{
		sendbyte((1<<2)|buffer|(1 << 1),0);
	}
}


/** enable/disable display shift */
void display_shift(uint8_t state){
	uint8_t buffer = 0;
	buffer |= ((disp_settings & ( 1 << 3 )) >> 2); //check cursor movement dir bit state
	
	if (state == 0){
		sendbyte((1<<2)|buffer,0);
	}
	else{
		sendbyte((1<<2)|buffer|(1 << 0),0);
	}
}

/** scroll display left by 1 */
void display_scroll_left(){
	sendbyte((1 << 4)|(1 << 3)|(1 << 2), 0);
}

/** scroll display right by 1 */
void display_scroll_right(){
	sendbyte((1 << 4)|(1 << 3), 0);
}