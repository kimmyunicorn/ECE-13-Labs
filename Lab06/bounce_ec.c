// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>

// User libraries
#include "Leds_Lab06.h"
#include "Oled.h"
#include "OledDriver.h"
#include "Buttons.h"
// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct result {
    uint8_t event;
    uint16_t voltage;
};

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};
// **** Define global, module-level, or external variables here ****
static uint8_t timerEvent;
static struct result result1;
static struct Timer TimerA;
enum direction {
    LEFT,
    RIGHT
};
#define SIZE 5
// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();

    
    T1CON = 0; 
    T1CONbits.TCKPS = 1; 
    PR1 = 0xFFFF;
    T1CONbits.ON = 1;

    
    IFS0bits.T1IF = 0; 
    IPC1bits.T1IP = 4; 
    IPC1bits.T1IS = 0; 
    IEC0bits.T1IE = 1; 


   
    IPC6bits.AD1IP = 2;
    IPC6bits.AD1IS = 0;
    IEC1bits.AD1IE = 1;

    
    TRISBbits.TRISB2 = 1;

  
    AD1CHSbits.CH0SA = 2; 
    AD1PCFGbits.PCFG2 = 0; 
    AD1CSSLbits.CSSL2 = 1;

    AD1CON1 = 0; 
    AD1CON1bits.SSRC = 0b111; 
    AD1CON1bits.ASAM = 1;

    AD1CON2 = 0; 
    AD1CON2bits.SMPI = 7; 

    AD1CON3 = 0; 
    AD1CON3bits.SAMC = 29; 
    AD1CON3bits.ADCS = 50; 

    AD1CON1bits.ADON = 1; 

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to kcamaner's lab6 part6 (Extra Credit).  Compiled on %s %s.\n",__TIME__,__DATE__);

    OledInit();
    result1.event = TRUE;
    char stringToDraw[35];
    
    ButtonsInit();
    LEDS_INIT();
    TimerA.event = FALSE;
    int frozen = 0;
    int state = -1;
    char leftMost = 0x80;
    char rightMost = 0x01;
    char currentLED = 0x01;
    
    while (1) {

        if (result1.event) {
            int percent = result1.voltage / 1023.0 * 100;
            sprintf(stringToDraw, "Potentiometer value:\n   %d\n   %d%%", result1.voltage, percent);
            OledClear(OLED_COLOR_BLACK);
            OledDrawString(stringToDraw);
            OledUpdate();
            result1.event = FALSE;
        }
        
        
        if (timerEvent != BUTTON_EVENT_NONE) {
            uint8_t switchesState = SWITCH_STATES();

         
            if ((switchesState & SWITCH_STATE_SW1) && (timerEvent & BUTTON_EVENT_1UP)) {
                if (frozen) {
                    frozen = 0;
                } else {
                    frozen = 1;
                }
            } else if (!(switchesState & SWITCH_STATE_SW1) && timerEvent & BUTTON_EVENT_1DOWN) {
                if (frozen) {
                    frozen = 0;
                } else {
                    frozen = 1;
                }
            } else if ((switchesState & SWITCH_STATE_SW2) && (timerEvent & BUTTON_EVENT_2UP)) {
                if (frozen) {
                    frozen = 0;
                } else {
                    frozen = 1;
                }
            } else if (!(switchesState & SWITCH_STATE_SW2) && timerEvent & BUTTON_EVENT_2DOWN) {
                if (frozen) {
                    frozen = 0;
                } else {
                    frozen = 1;
                }
            } if ((switchesState & SWITCH_STATE_SW3) && (timerEvent & BUTTON_EVENT_3UP)) {
                if (frozen) {
                    frozen = 0;
                } else {
                    frozen = 1;
                }
            } else if (!(switchesState & SWITCH_STATE_SW3) && timerEvent & BUTTON_EVENT_3DOWN) {
                if (frozen) {
                    frozen = 0;
                } else {
                    frozen = 1;
                }
            } else if ((switchesState & SWITCH_STATE_SW4) && (timerEvent & BUTTON_EVENT_4UP)) {
                if (frozen) {
                    frozen = 0;
                } else {
                    frozen = 1;
                }
            } else if (!(switchesState & SWITCH_STATE_SW4) && timerEvent & BUTTON_EVENT_4DOWN) {
                if (frozen) {
                    frozen = 0;
                } else {
                    frozen = 1;
                }
            }
            timerEvent = BUTTON_EVENT_NONE;
        }
    
        if (TimerA.event && frozen == 0) {
            
            LEDS_SET(currentLED);
            if (currentLED == leftMost) {
                state = RIGHT;
            } else if (currentLED == rightMost) {
                state = LEFT;
            }
            if (state == LEFT) {
                currentLED <<= 1;
            } else {
                if (currentLED == leftMost) {
                    currentLED = (currentLED >> 1) ^ currentLED;
                } else {
                    currentLED >>= 1;
                }
            }
            TimerA.event = FALSE;
        }
    }
  
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}


void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
  
    IFS0bits.T1IF = 0;

    TimerA.timeRemaining--;
    if (TimerA.timeRemaining <= 0) {

        TimerA.event = TRUE;
        
    
        TimerA.timeRemaining = 100 - ((result1.voltage / 1023.0) * 100);
        
    }

    timerEvent = ButtonsCheckEvents();
    
}


void __ISR(_ADC_VECTOR, IPL2AUTO) AdcHandler(void)
{
 
    IFS1bits.AD1IF = 0;
    

    uint16_t average = ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7;
    average /= 8;
    if (average - result1.voltage >= SIZE || result1.voltage - average >= SIZE) {
        result1.event = TRUE;
        if (average + SIZE >= 1023) {
            result1.voltage = 1023;
        } else if (average - SIZE <= 0) {
            result1.voltage = 0;
        } else {
            result1.voltage = average;
        }
    }

}