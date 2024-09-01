/*
 * LCD.h
 *
 * Created: 16/08/2024 12:35:46 م
 *  Author: Meteor
 */ 


#ifndef LCD_H_
#define LCD_H_
// Commands start -->
// Initialization modes start -->
#define EIGHT_BIT_2LINE_SMALL 0x38
#define FOUR_BIT_2LINE_SMALL 0x20
#define EIGHT_BIT_1LINE_SMALL 0x30
#define FOUR_BIT_1LINE_SMALL 0x28
#define ENTRY_MODE_DEC_CURSOR 0x04
#define ENTRY_MODE_INC_CURSOR 0x06
#define ENTRY_MODE_SHIFT_RIGHT 0x05
#define ENTRY_MODE_SHIFT_LEFT 0x07
// Initialization modes end <--
#define DISPLAY_OFF_CURSOR_OFF 0x08
#define DISPLAY_OFF_CURSOR_ON 0x0A
#define DISPLAY_ON_CURSOR_OFF 0x0C
#define DISPLAY_ON_CURSOR_BLINK 0x0F
#define DISPLAY_ON_CURSOR_ON 0x0E
#define SHIFT_CURSOR_LEFT 0x10
#define SHIFT_CURSOR_RIGHT 0x14
#define SHIFT_DISPLAY_LEFT 0x18
#define SHIFT_DISPLAY_RIGHT 0x1C
#define FORCE_RETURN_FIRST_LINE 0x80
#define FORCE_RETURN_SECOND_LINE 0xC0
#define CLEAR_DISPLAY 0x01
#define RETURN_HOME 0x02
// Commands end <--
#define MAX_ROW 2
#define MAX_COL 16


void SEND_COMMAND(char instruction); // Pass a command to control the LCD
void LCD_init(void); // returns 1 when completed
void LCD_WRITE_CHAR(char character); // prints only 1 character then shifts cursor
void LCD_WRITE_STRING(char string[]);// takes a string and iterates on it's characters passing them to LCD_WRITE_CHAR()
void LCD_CURSOR_MOVE(unsigned char line, unsigned char index);// Uses the parameters as coordinates to move the cursor to the specified location
void LCD_WRITE_CUSTOM_CHAR(unsigned char location, unsigned char *character);// Writes a custom Character that the user inputs

#endif /* LCD_H_ */

