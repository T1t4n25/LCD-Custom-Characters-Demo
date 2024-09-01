/*
 * LCD.c
 *
 * Created: 16/08/2024 12:35:28 م
 *  Author: Meteor
 */ 
#define F_CPU 8000000UL
#include "LCD.h"
#include "conf.h"
#include<util/delay.h>

char is_init = 0;

void LCD_init(void){
	_delay_ms(30);
	#if (BIT_MODE == FOUR_BIT)
		SEND_COMMAND(FOUR_BIT_2LINE_SMALL); // 4-bit 2 line 5x7 dots
	#elif (BIT_MODE == EIGHT_BIT)
		SEND_COMMAND(EIGHT_BIT_2LINE_SMALL); // 8-bit 2 line 5x7 dots
	#endif
	_delay_ms(1);
	SEND_COMMAND(CLEAR_DISPLAY); // Clear
	_delay_ms(1);
	SEND_COMMAND(DISPLAY_ON_CURSOR_ON); // Display on cursor on
	is_init = 1;
}

void SEND_COMMAND(char instruction){
	#if (BIT_MODE == FOUR_BIT)
		COMMAND_PORT &= ~(1<<RS);
		COMMAND_PORT |= (1<<E);
		DATA_PORT = (DATA_PORT & 0x0F) | (instruction & 0xF0);
		_delay_ms(1);
		COMMAND_PORT &= ~(1<<E);
		COMMAND_PORT |= (1<<E);
		DATA_PORT = (DATA_PORT & 0x0F) | (instruction << 4);
		_delay_ms(1);
		COMMAND_PORT &= ~(1<<E);
	#elif (BIT_MODE == EIGHT_BIT)
		COMMAND_PORT |= (1<<E);
		COMMAND_PORT &= ~(1<<RS);
		DATA_PORT = instruction;
		_delay_ms(1);
		COMMAND_PORT &= ~(1<<E);
		DATA_PORT = 0;
	#endif
}

void LCD_WRITE_CHAR(char character){
	if (is_init == 1  || COMPILER_ERRORS == 0){
		#if (BIT_MODE == FOUR_BIT)
			COMMAND_PORT |= (1<<RS);
			COMMAND_PORT |= (1<<E);
			DATA_PORT = (DATA_PORT & 0x0F) | (character & 0xF0);
			_delay_ms(1);
			COMMAND_PORT &= ~(1<<E);
			COMMAND_PORT |= (1<<E);
			DATA_PORT = (DATA_PORT & 0x0F) | (character << 4);
			_delay_ms(1);
			COMMAND_PORT &= ~(1<<E);
		#elif (BIT_MODE == EIGHT_BIT)
			COMMAND_PORT |= (1<<E);
			COMMAND_PORT |= (1<<RS);
			DATA_PORT = character;
			_delay_ms(1);
			COMMAND_PORT &= ~(1<<E);
		#endif
	}
	else{
		LCD_init();
		LCD_WRITE_CHAR(character);
	}
}


void LCD_WRITE_STRING(char string[]){
	#if LIMIT_WRITES == 0
		for (unsigned char i = 0; string[i] != '\0'; i++){
			LCD_WRITE_CHAR(string[i]);
		}
	#else
		for (unsigned char i = 0; i < MAX_COL; i++){
			if (string[i] == '\0')
				break;
			LCD_WRITE_CHAR(string[i]);
		}
	#endif
}

void LCD_CURSOR_MOVE(unsigned char line, unsigned char index){
	
	#if LIMIT_WRITES == 0
		if (is_init == 1 || COMPILER_ERRORS == 0){
			if (0 == line)
			SEND_COMMAND(FORCE_RETURN_FIRST_LINE + index;
			else
			SEND_COMMAND(FORCE_RETURN_SECOND_LINE + index);
		}
		else{
			LCD_init();
			LCD_CURSOR_MOVE(line, index);
		}
	#else
		if (is_init == 1 || COMPILER_ERRORS == 0){
			if (0 == line)
			SEND_COMMAND(FORCE_RETURN_FIRST_LINE + index % MAX_COL);
			else
			SEND_COMMAND(FORCE_RETURN_SECOND_LINE + index % MAX_COL);
		}
		else{
			LCD_init();
			LCD_CURSOR_MOVE(line, index);
		}
	#endif
}

void LCD_WRITE_CUSTOM_CHAR(unsigned char location, unsigned char *character)
{
    if(location<8)
    {
     SEND_COMMAND(0x40 | (location << 3));  // Command 0x40 and onwards forces  the device to point CGRAM address 					
       for(unsigned char i = 0; i < 8; i++)  /* Write 8 byte for generation of 1 character */
           LCD_WRITE_CHAR(character[i]);  
    }   
}
