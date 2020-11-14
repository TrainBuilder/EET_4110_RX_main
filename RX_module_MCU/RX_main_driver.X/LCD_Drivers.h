/* 
 * File:   LCD_Drivers.h
 * Author: Cody Howard
 * Comments: code to run a 2x16 LCD via a PIC16F18344
 * Revision history: 
 * initial working 9/30/20
 */

#include "configs.h"
//LCD to PIC connections
#define RS RC0
#define EN RC1
#define D4 RC4
#define D5 RC5
#define D6 RC6
#define D7 RC7


void LCD_init();
void send_CMD(int, int, int, int);
void Lcd_Print_Char(char);
void Lcd_SetBit(char);
void Lcd_Print_String(char *a);
void LCD_row_set(int);
void LDC_clear();
void LCD_Print_num(int);



void LCD_init(){
    send_CMD(0,0,0,0);  
    send_CMD(0,0,0,0);         //0x00;
    __delay_ms(100);//clear data pins
    
    send_CMD(0,0,1,1);           //0x3;
    send_CMD(0,0,1,1);           //0x3;
    send_CMD(0,0,1,1);           //0x3;CMD 3 x 0x3 as per data sheet
    send_CMD(0,0,1,0);           //0x2; CMD 0x2 for 4-bit mode
    send_CMD(0,0,1,0);           //0x2;
    send_CMD(1,0,0,0);           //0x8; cmd 0x28 for 2x16 display
    send_CMD(0,0,0,0);           //0x0;
    send_CMD(1,1,0,0);           //0xC; cmd 0x0C turn on display/no cursor
    send_CMD(0,0,0,0);           //0x0;
    send_CMD(0,1,1,0);           //0x6; cmd 0x06 for auto increment of position
    LCD_row_set(1);
    LDC_clear();
}


void send_CMD(int d7, int d6, int d5, int d4){
  RS=0;//set RS to 0 to send cmds
  if(d7 == 1){D7=1;}
  else {D7=0;}
  if(d6 == 1){D6=1;}
  else {D6=0;}
  if(d5 == 1){D5=1;}
  else {D5=0;}
  if(d4 == 1){D4=1;}
  else {D4=0;}
  
  EN=1;
  __delay_us(500);
  EN=0;
 __delay_ms(1);
  }

void Lcd_Print_Char(char data)  //Send 8-bits through 4-bit mode
{
   char Lower_Nibble,Upper_Nibble;
   Lower_Nibble = data&0x0F;
   Upper_Nibble = data&0xF0;
   RS = 1;             // => RS = 1
   Lcd_SetBit(Upper_Nibble>>4);             //Send upper half by shifting by 4
   EN = 1;
   __delay_us(500);
   EN = 0;
   Lcd_SetBit(Lower_Nibble); //Send Lower half
   EN = 1;
   __delay_us(500);
   EN = 0;
}
void Lcd_SetBit(char data_bit) //Based on the Hex value Set the Bits of the Data Lines
{
	if(data_bit& 1) 
		D4 = 1;
	else
		D4 = 0;

	if(data_bit& 2)
		D5 = 1;
	else
		D5 = 0;

	if(data_bit& 4)
		D6 = 1;
	else
		D6 = 0;

	if(data_bit& 8) 
		D7 = 1;
	else
		D7 = 0;
}

void Lcd_Print_String(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Print_Char(a[i]);  //Split the string using pointers and call the Char function 
}

void LCD_row_set(int row){
    if(row == 1){
    send_CMD(1,0,0,0);           //0x8;
    send_CMD(0,0,0,0);           //0x0; cmd 0x80 to set cursor at 1,0
    }
    if(row == 2){
    send_CMD(1,1,0,0);           //0xC; 
    send_CMD(0,0,0,0);           //0x0 cmd 0xC0 to set cursor at 2,0
    }
}

void LDC_clear(){
    send_CMD(0,0,0,0);           //0x0
    send_CMD(0,0,0,1);           //0x1 cmd 0x01 to clear display
}

void LCD_Print_num(int num){
  char str[10];
  sprintf(str, "%d", num);
  Lcd_Print_String(str); 
}