

#include "lcd_wintek_wdc2401p.h"






// void LCDInitialize(void)
// {
//   SysCtlPeripheralEnable(STATUS_LED_PERIF);
//   GPIOPinTypeGPIOOutput(STATUS_LED_PORT, RED_LED|BLUE_LED|GREEN_LED);
//   RED_ON;
//   BLUE_ON;

// }


void LCDInitialize(void)
{

  SysCtlPeripheralEnable(LCD_CONTROL_PERIF);
  SysCtlPeripheralEnable(LCD_DATA_PERIF);
  SysCtlPeripheralEnable(STATUS_LED_PERIF);
  
  GPIOPinTypeGPIOOutput(LCD_CONTROL_PORT, RESET_PIN|RS_PIN|RW_PIN|E_PIN);
  GPIOPinTypeGPIOOutput(LCD_DATA_PORT, LCD_DATA_PINS);
  GPIOPinTypeGPIOOutput(STATUS_LED_PORT, RED_LED|BLUE_LED|GREEN_LED);
  
  GPIOPadConfigSet(LCD_DATA_PORT, 0xff, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
  GPIOPadConfigSet(LCD_CONTROL_PORT, 0xff, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);

  RED_ON;
  RS_LO;
  E_LO;
  RW_LO;

  RESET_HI;

  LCDCommand(0x1C);

  LCDCommand(0x14);

  LCDCommand(0x28);
  LCDCommand(0x4f);


  LCDClearScreen();

  RED_OFF;
}

void ResetLCD(void)
{
  GREEN_ON
  RESET_HI;
  SysCtlDelay(4000000);
  RESET_HI;
  SysCtlDelay(4000000);

  GREEN_OFF;

}

void LCDClearScreen()
{
 SysCtlDelay(200);
 LCDCommand(0x01);
 SysCtlDelay(100000);
 LCDCommand(0xE0);
 SysCtlDelay(100000);
}

void LCDWriteChar(char c)
{ 
 RS_HI;
 SysCtlDelay(2000);
 LCDClockByte(c);
}

void LCDResetChar()
{
 RS_LO;
 LCDClockByte(0x02);

}

void LCDWriteString(char *s)
{
   LCDResetChar();
   LCDClearScreen();
   char buffer [24];
   usprintf(buffer, "%24s", s);
   // SysCtlDelay(2000);

   for(int i=0;i< 24;i++) {
    LCDWriteChar(buffer[i]);  
   }
}

void LCDClockByte(char c)
{

  LCD_DATA_WRITE(c);
  E_HI;
  SysCtlDelay(200);
  E_LO;
  SysCtlDelay(200);
}

void LCDCommand(char c)
{
  RS_LO;
  SysCtlDelay(2000);
  LCDClockByte(c);
  SysCtlDelay(2000);
}

