/*
 * LCD Driver.c
 *
 * Created: 16/08/2024 12:32:29 PM
 * Author : Meteor
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include "LCD.h"
#include "conf.h"
#include<util/delay.h>

#define ANIMATION_DELAY 20


void custom_char_init(void);
void animation1(char x);
void animationReverse(char x);
void animationBattery(char x);
void animationBatteryReverse(char x);

int main(void)
{
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	LCD_init();
	SEND_COMMAND(DISPLAY_ON_CURSOR_OFF);
	
	custom_char_init();// save the characters before using it 
	
	SEND_COMMAND(FORCE_RETURN_FIRST_LINE);
	
	LCD_WRITE_STRING("Custom character");
	
	SEND_COMMAND(FORCE_RETURN_SECOND_LINE);
	
	unsigned char counter = 0;// use this to iterate on different phases of animations
	while(1){
		 /* we use a technique called multiplexing 
		    to show animations of several characters
		    in the same time */
		SEND_COMMAND(FORCE_RETURN_SECOND_LINE);
		LCD_CURSOR_MOVE(2, 1);
		animation1(counter % 3);// we use % so we always have a number between 0 and 2
		
		LCD_CURSOR_MOVE(2, 3);
		animationBattery(counter % 3);
		
		LCD_CURSOR_MOVE(2, 5);
		animationReverse(counter % 3);
		
		LCD_CURSOR_MOVE(2, 7);
		LCD_WRITE_CHAR(6);

		
		LCD_CURSOR_MOVE(2, 9);
		LCD_WRITE_CHAR(7);
		
		
		LCD_CURSOR_MOVE(2, 11);
		animation1(counter % 3);
		
		LCD_CURSOR_MOVE(2, 13);
		animationBatteryReverse(counter % 3);
		
		LCD_CURSOR_MOVE(2, 15);
		animationReverse(counter % 3);
		counter++;// The counter is going up to 255 and then resets to 0
	}
	
}
/* here's how to save a custom character to the memory 
   to generate a custom character code you can use online tools
   just search for custom character generator, draw the shape,
   and copy either the binary or the hex version and save it
    in a char array just like below code is showing */
void custom_char_init(void){
	unsigned char customChar1[8] = {0x00,0x00,0x00,0x00,0x04,0x0E,0x1F,0x15};// arrow low
	unsigned char customChar2[8] = {0x04,0x0E,0x1F,0x15,0x04,0x04,0x04,0x04};// arrow half
	unsigned char customChar3[8] = {0x00,0x00,0x04,0x0E,0x1F,0x15,0x04,0x04};// arrow high

	unsigned char customChar4[8] = {0x04,0x0E,0x11,0x11,0x11,0x11,0x1F,0x1F};// battery low
	unsigned char customChar5[8] = {0x04,0x0E,0x11,0x11,0x1F,0x1F,0x1F,0x1F};// battery half
	unsigned char customChar6[8] = {0x04,0x0E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};// battery full

	unsigned char customChar7[8] = {0x0A,0x0A,0x1F,0x11,0x0A,0x04,0x04,0x04};// plug
	unsigned char customChar8[8] = {0x0E,0x1F,0x1F,0x15,0x04,0x04,0x05,0x02};// umbrella
		
	/* in this part we save the custom characters
	   to the ram of the LCD to use it later*/
		
	LCD_WRITE_CUSTOM_CHAR(0, customChar1);
	LCD_WRITE_CUSTOM_CHAR(1, customChar2);
	LCD_WRITE_CUSTOM_CHAR(2, customChar3);
	LCD_WRITE_CUSTOM_CHAR(3, customChar4);
	LCD_WRITE_CUSTOM_CHAR(4, customChar5);
	LCD_WRITE_CUSTOM_CHAR(5, customChar6);
	LCD_WRITE_CUSTOM_CHAR(6, customChar7);
	LCD_WRITE_CUSTOM_CHAR(7, customChar8);
}

/* functions are used to initiate a sequence for every animation
   by passing the frame we want to be displayed */
void animation1(char x){
	unsigned char i = 0 + x; //the value is always between 0-2 so it'll iterate on the first 3 custom characters
	LCD_WRITE_CHAR(i);
	_delay_ms(ANIMATION_DELAY);
	SEND_COMMAND(SHIFT_CURSOR_LEFT);
}

void animationReverse(char x){
	unsigned char i = 2 - x;// reverse animation is done by starting at the end and going to the start
	LCD_WRITE_CHAR(i);// we write the custom character on the LCD by accessing the addresses from 0 to 7
	_delay_ms(ANIMATION_DELAY);
	SEND_COMMAND(SHIFT_CURSOR_LEFT);
}

void animationBattery(char x){
	unsigned char i = 3 + x;
	LCD_WRITE_CHAR(i);
	_delay_ms(ANIMATION_DELAY);
	SEND_COMMAND(SHIFT_CURSOR_LEFT);
}

void animationBatteryReverse(char x){
	unsigned char i = 5 - x;
	LCD_WRITE_CHAR(i);
	_delay_ms(ANIMATION_DELAY);
	SEND_COMMAND(SHIFT_CURSOR_LEFT);
}
