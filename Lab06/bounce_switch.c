//works
// **** Include libraries here ****
// old bounce
// Standard libraries
#include <stdio.h>



//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>
#include "Leds_Lab06.h"
// **** Declare any datatypes here ****

struct Timer {
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static struct Timer TimerA;

enum direction {
    LEFT, //0
    RIGHT //1
};

// **** Declare function prototypes ****
static struct Timer TimerA = {FALSE, 72};

int main(void) {
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    T1CON = 0; // everything should be off
    T1CONbits.TCKPS = 1; // 1:8 prescaler
    PR1 = 0xFFFF; // interrupt at max interval
    T1CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T1IF = 0; //clear the interrupt flag before configuring
    IPC1bits.T1IP = 4; // priority of  4
    IPC1bits.T1IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T1IE = 1; // turn the interrupt on

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    printf("Welcome to kcamaner's lab6 part2 (bounce_switch).  Compiled on %s %s.\n", __TIME__, __DATE__);

    // **** Define global, module-level, or external variables here ****
    TimerA.event = FALSE;
    
    int state = -1;
    char left = 0x80;
    char right = 0x01;
    
    char currentLED = 0x01;

    LEDS_INIT();

    while (1) {
        
        if (TimerA.event) {
            LEDS_SET(currentLED);

            
            if (currentLED == left) {
                state = RIGHT;
            } else if (currentLED == right) {
                state = LEFT;
            }
            
            if (state == LEFT) {
                currentLED <<= 1;
            } else {
                
                if (currentLED == left) {
                    currentLED = (currentLED >> 1) ^ currentLED;
                } else {
                    currentLED >>= 1;
                }
            }
            
            TimerA.event = FALSE;
        }


    }
    /*
    LEDS_INIT();

    

    int direction = LEFT;



    while (1) {

        if (TimerA.event == TRUE) { //check to see if its true
            TimerA.event = FALSE;
            char state = LEDS_GET();
            if (state == 1) {
                direction = LEFT;


            } else if (state == 128) {
                direction = RIGHT;

            }
            if (direction == RIGHT){
                LEDS_SET (LEDS_GET () >> 1);
                
            }
            else{
                LEDS_SET (LEDS_GET () << 1);
                
            }



            //poll timer events and react if any occur
        }

     */
    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}

/**
 * This is the interrupt for the Timer1 peripheral. It will trigger at the frequency of the peripheral
 * clock, divided by the timer 1 prescaler and the interrupt interval.
 * 
 * It should not be called, and should communicate with main code only by using module-level variables.
 */




void __ISR(_TIMER_1_VECTOR, ipl4auto) Timer1Handler(void) {
    // Clear the interrupt flag.
    IFS0bits.T1IF = 0;

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    // 0 is slow

    int scale = 3; 
    TimerA.timeRemaining--; 

    
    if (TimerA.timeRemaining <= 0) {
        TimerA.event = TRUE;

        
       
        uint8_t switchCount = 0x00;

        
        uint8_t State = SWITCH_STATES();

        
        if (State & SWITCH_STATE_SW4) {
            switchCount |= SWITCH_STATE_SW4;
        }
        if (State & SWITCH_STATE_SW3) {
            switchCount |= SWITCH_STATE_SW3;
        }
        if (State & SWITCH_STATE_SW2) {
            switchCount |= SWITCH_STATE_SW2;
        }
        if (State & SWITCH_STATE_SW1) {
            switchCount |= SWITCH_STATE_SW1;
        }
        switchCount *= scale; 
        TimerA.timeRemaining = switchCount;

    }



    /*
    TimerA.timeRemaining -- ;
    if (TimerA.timeRemaining < 0){
        TimerA.event = TRUE;
        TimerA.timeRemaining = 200;
            
            
    }
    if (SWITCH_STATES() == 0){
            TimerA.timeRemaining -= 4;
                
        }
        else{
            TimerA.timeRemaining -= 10*SWITCH_STATES();
        }
                
     */








    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

}
