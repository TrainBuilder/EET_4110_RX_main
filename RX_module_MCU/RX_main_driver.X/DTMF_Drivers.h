/* 
 * File:   
 * Author: Cody HOward
 * Comments: all code to convert DTMF tones into 8-bit data
 * Revision history: 
 */
#include "configs.h"
#include <stdbool.h> 
#define D0 RB4
#define D1 RB5
#define D2 RB6
#define D3 RB7
#define RX RC3
#define data PORTB;

bool DTMF_start();
void read_DTMF_Data();
void Print_DTMF_data(int,int,int);
void hexTest();

bool DTMF_start(){
    if(!RX && D0 &&!D1 && !D2 && !D3)return true;  //0x01 start nibble
    else return false;
}

//takes data from MT 8870 and stores the entire DTMF data packet
//converts 6 nibbles from MT 8870 into 3 usable bytes of data
void read_DTMF_Data(){
    int up,low,temp,wind,press;
    __delay_ms(1500);                    //sample middle of next tone
    up = data;                           //first tone = upper nibble of data
    __delay_ms(1000);                    //sample middle of next tone
    low = data;                          //second tone = lower nibble of data
    low = low>>4;
    temp = up|low;                       //combine nibbles into byte of data
    __delay_ms(1000);    
    
    up = data;                           //repeat for wind
    __delay_ms(1000);                    
    low = data;
    low = low>>4;
    wind = up|low;
    __delay_ms(1000);
    
    up = data;                           //repeat for press
    __delay_ms(1000);                  
    low = data;
    low = low>>4;
    press = up|low;

    Print_DTMF_data(temp, wind, press);  // send data to print function
}

//function takes data received by RX unit and displays it to the user LCD

void Print_DTMF_data(int temp,int speed, int press){
    LDC_clear(); 
    LCD_row_set(1); 
    Lcd_Print_String("Temperature:");                  
    LCD_row_set(2);
    LCD_Print_num(temp);
    Lcd_Print_Char(223);//degree symbol
    Lcd_Print_String("F");
    __delay_ms(5000);                                       //display each data value for 5 seconds
    
    LDC_clear(); 
    LCD_row_set(1);
    Lcd_Print_String("Wind Speed:");
    LCD_row_set(2);
    LCD_Print_num(speed);
    Lcd_Print_String(" MPH");
    __delay_ms(5000);
    
    LDC_clear(); 
    LCD_row_set(1);
    Lcd_Print_String("Air Pressure:");
    LCD_row_set(2);
    LCD_Print_num(press);
    Lcd_Print_String(" kPa");
    __delay_ms(5000);
    LDC_clear(); 
    
}

