/* 
 * File:   Main.c
 * Author: Cody Howard
 *
 * Created on September 30, 2020, 7:43 PM
 * working revision 11/13/20
 * RX_main_driver SLOC = 285
 */
#include "LCD_Drivers.h"
#include "DTMF_Drivers.h"

void main(void) 
{
    LATC = 0;
    TRISC = 0b00001000;         //portC = output, RC3 = input
    ANSELC = 0;                 //digital
    
    TRISB = 0b11110000;         //portB = input
    ANSELB = 0;                 //digital
    
    TRISA = 0b00000100;         //RA2 = input
    ANSELB = 0;                 //digital
    
    
    LCD_init();                                             //start LCD
    Lcd_Print_String("System status:");
    LCD_row_set(2);
    Lcd_Print_String("BOOTING");
    LCD_row_set(1);
    __delay_ms(3000);                                       // boot time
    LDC_clear();                                            //reset LCD

  while(1){
      if(DTMF_start()){                                     //if system is receiving a DTMF data packet
        Lcd_Print_String("System status:");
        LCD_row_set(2);
        Lcd_Print_String("RECEIVING");
        read_DTMF_Data();                                   //convert DTMF tones to data
      }
      else {
      LCD_row_set(1);
      Lcd_Print_String("System status:");
      LCD_row_set(2);
      Lcd_Print_String("NO SIGNAL");
      __delay_ms(100);
      LDC_clear(); 
      }
    }
}
