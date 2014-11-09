
#include "utils/ustdlib.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"



#ifndef _LCD_PINS_
#define _LCD_PINS_

// Control
#define LCD_CONTROL_PORT   GPIO_PORTD_BASE
#define LCD_CONTROL_PERIF  SYSCTL_PERIPH_GPIOD
#define RESET_PIN          GPIO_PIN_0
#define RS_PIN             GPIO_PIN_1
#define RW_PIN             GPIO_PIN_2
#define E_PIN              GPIO_PIN_3

// parallel data interface
#define LCD_DATA_PORT  GPIO_PORTB_BASE
#define LCD_DATA_PERIF SYSCTL_PERIPH_GPIOB
#define LCD_DATA_PINS  0xFF

// blinkenlights
#define STATUS_LED_PORT  GPIO_PORTF_BASE
#define STATUS_LED_PERIF SYSCTL_PERIPH_GPIOF
#define RED_LED          GPIO_PIN_1
#define BLUE_LED         GPIO_PIN_2
#define GREEN_LED        GPIO_PIN_3
#define RED_ON      GPIOPinWrite(STATUS_LED_PORT, RED_LED, RED_LED);
#define RED_OFF     GPIOPinWrite(STATUS_LED_PORT, RED_LED, 0);
#define BLUE_ON     GPIOPinWrite(STATUS_LED_PORT, BLUE_LED, BLUE_LED);
#define BLUE_OFF    GPIOPinWrite(STATUS_LED_PORT, BLUE_LED, 0);
#define GREEN_ON    GPIOPinWrite(STATUS_LED_PORT, GREEN_LED, GREEN_LED);
#define GREEN_OFF   GPIOPinWrite(STATUS_LED_PORT, GREEN_LED, 0);


// control macros
#define RESET_HI             GPIOPinWrite(LCD_CONTROL_PORT, RESET_PIN, RESET_PIN);
#define RESET_LO             GPIOPinWrite(LCD_CONTROL_PORT, RESET_PIN, 0);
#define RS_HI                GPIOPinWrite(LCD_CONTROL_PORT, RS_PIN, RS_PIN);
#define RS_LO                GPIOPinWrite(LCD_CONTROL_PORT, RS_PIN, 0);
#define RW_HI                GPIOPinWrite(LCD_CONTROL_PORT, RW_PIN, RW_PIN);
#define RW_LO                GPIOPinWrite(LCD_CONTROL_PORT, RW_PIN, 0);
#define E_HI                 GPIOPinWrite(LCD_CONTROL_PORT, E_PIN, E_PIN);
#define E_LO                 GPIOPinWrite(LCD_CONTROL_PORT, E_PIN, 0);

//parallel data write macro
#define LCD_DATA_WRITE(ucByte)  { GPIOPinWrite(LCD_DATA_PORT, LCD_DATA_PINS, ucByte); }



#endif

// public stuff
void LCDInitialize();
void LCDWriteString( char *s);


//internal widgets
void ResetLCD();
void LCDClearScreen();
void LCDClockByte(char c);
void LCDClockBanner();
void LCDWriteChar(char c);
void LCDCommand(char c);
void LCDResetChar(); 
char * itoa(int value, char *result, int base);

