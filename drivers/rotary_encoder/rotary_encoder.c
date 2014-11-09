#include "rotary_encoder.h"


unsigned char    encoder_a;
unsigned long    encoder_a_hits=0;
unsigned char    encoder_a_prev=0;

unsigned char    encoder_b;
unsigned char    encoder_b_prev=0;
unsigned long    encoder_b_hits=0;

unsigned char    encoder_p;
unsigned char    encoder_p_prev=0;
unsigned long    encoder_p_hits=0;

unsigned int*    push_button_ptr;
unsigned int*    enc_step_ptr;



void
EncTimerIntHandler(void)
{
    TimerIntClear(TIMER4_BASE, TIMER_TIMA_TIMEOUT);
    ReadPushButton();
    ReadEncoder();
}

void
ReadPushButton(void){
    encoder_p = GPIOPinRead(ENC_BASE, ENC_PUSH);

    if(encoder_p != encoder_p_prev) {
        if (!encoder_p) {
            encoder_p_hits += 1;
        } else {
            encoder_p_hits -= 1;
        }

        if (abs(encoder_p_hits) > ENC_HIT_MIN) {
            encoder_p_prev = encoder_p;
            if (encoder_p_hits > 0) {
                *push_button_ptr = 1;
            } else {
                *push_button_ptr = 0;
            }
            encoder_p_hits = 0;
        }
    }
}

void
ReadEncoder(void) {
    //
    // Get the counter value
    //
    encoder_a = GPIOPinRead(ENC_BASE, ENC_A);
    encoder_b = GPIOPinRead(ENC_BASE, ENC_B);

    

    // detect edge on A
    if (encoder_a != encoder_a_prev) {

        //if new values are high, incr, otherwise decr
        if (!encoder_a) {
            encoder_a_hits += 1;
        } else {
            encoder_a_hits -= 1;
        }
        
        // edge detect on B
        if (encoder_b != encoder_b_prev) {
            if (!encoder_b) {
                encoder_b_hits -= 1;
            } else {
                encoder_b_hits += 1;
            }

        }

        // hit detection limit rising A
        if (encoder_a_hits > ENC_HIT_LIMIT) {
            //rising B during rising A indicates CW
            if (encoder_b_hits > ENC_HIT_MIN) {
                *enc_step_ptr -= 1;
            } else {
                *enc_step_ptr += 1;
            }

            ResetValues();
          
        }

        // hit detection limit falling A
        else if (encoder_a_hits < -ENC_HIT_LIMIT) {
            //rising B during falling A indicates CCW
            if (encoder_b_hits > ENC_HIT_MIN) {
                *enc_step_ptr += 1;
            } else {
                *enc_step_ptr -= 1;
            }

            ResetValues();
        }
    } //edge detect
}

void
ResetValues(void) {
    encoder_b_prev = encoder_b;
    encoder_a_prev = encoder_a;
    encoder_a_hits = 0;
    encoder_b_hits = 0;
}

void
InitEncoder(unsigned int * push_button_store, unsigned int * enc_step_store) {
    enc_step_ptr = enc_step_store;
    push_button_ptr = push_button_store;
    ConfigTimer(); 
}

void
ConfigTimer(void) {
    SysCtlPeripheralEnable(ENC_PERIPH);
    GPIOPinTypeGPIOInput(ENC_BASE, ENC_PUSH|ENC_A|ENC_B);
    SysCtlPeripheralEnable(ENC_TIMER_PERIPH);
    TimerConfigure(ENC_TIMER_BASE, TIMER_CFG_PERIODIC);
    unsigned long EncReadUlPeriod = (SysCtlClockGet() / ENC_READ_DIVIDER) / 2;
    TimerLoadSet(ENC_TIMER_BASE, ENC_TIMER_SIDE, EncReadUlPeriod -1);
    IntEnable(ENC_TIMER_INT);
    TimerIntEnable(ENC_TIMER_BASE, ENC_TIMER_TIMEOUT);
    TimerIntRegister(ENC_TIMER_BASE, ENC_TIMER_SIDE, EncTimerIntHandler);
    TimerEnable(ENC_TIMER_BASE, ENC_TIMER_SIDE);

}