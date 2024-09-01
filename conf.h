/*
 * conf.h
 *
 * Created: 16/08/2024 04:44:42 م
 *  Author: Meteor
 */ 


#ifndef CONF_H_
#define CONF_H_
// include the MCAL library 
#include <avr/io.h>

#define FOUR_BIT 4
#define EIGHT_BIT 8

#define BIT_MODE EIGHT_BIT
// Set the ports used to communicate with the LCD
#define DATA_PORT PORTC
#define COMMAND_PORT PORTD
// Set the indexes of the pins
#define RS 2
#define RW 1
#define E 0
// Set to 1 to get errors if initialization in missed - 0 to ignore errors
// it is preferred to leave it = 1 if you don't know how to initialize LCDs
#define COMPILER_ERRORS 1
// Set to 1 limits the string write length and LCD_CURSOR_MOVE() to MAX_COL size which is 16 for 16*2 displays
// Set to 0 will result in ignoring the limit
#define LIMIT_WRITES 1

#endif /* CONF_H_ */


