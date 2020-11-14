/* 
 * File:   configs.h
 * Author: Cody Howard
 * Comments: Configurations for PIC16F18344 8MHz external oscillator
 * Revision history: 10/1/20
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic16f18344.h>
#define _XTAL_FREQ  8000000
#pragma config FEXTOSC = HS    // FEXTOSC External Oscillator mode Selection bits->HS (crystal oscillator) above 4 MHz
#pragma config RSTOSC = EXT1X    // Power-up default value for COSC bits->EXTOSC operating per FEXTOSC bits
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; I/O or oscillator function on OSC2
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is disabled
#pragma config WDTE = OFF
#pragma config LVP = OFF
#define LED RC2