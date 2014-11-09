#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

#define ENC_TIMER_PERIPH    SYSCTL_PERIPH_TIMER4
#define ENC_TIMER_BASE      TIMER4_BASE
#define ENC_TIMER_INT       INT_TIMER4A
#define ENC_TIMER_SIDE      TIMER_A
#define ENC_TIMER_TIMEOUT   TIMER_TIMA_TIMEOUT

#define ENC_PUSH            GPIO_PIN_7
#define ENC_A               GPIO_PIN_1
#define ENC_B               GPIO_PIN_2
#define ENC_PERIPH          SYSCTL_PERIPH_GPIOE
#define ENC_BASE            GPIO_PORTE_BASE
#define ENC_HIT_LIMIT       100 
#define ENC_HIT_MIN         20
#define ENC_READ_DIVIDER    1000

void EncTimerIntHander();
void ReadPushButton();
void ReadEncoder();
void ResetValues();
void ConfigTimer();
void InitEncoder(unsigned int * push_button_store, unsigned int * enc_step_store);