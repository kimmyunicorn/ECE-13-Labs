// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CSE13E Support Library
#include "BOARD.h"
#include "Buttons.h"
#include "Adc.h"
#include "Ascii.h"
#include "Leds.h"
#include "Oled.h"
#include "OledDriver.h"
// Microchip libraries
#include <xc.h>
#include <sys/attribs.h>



// **** Set any macros or preprocessor directives here ****
// Set a macro for resetting the timer, makes the code a little clearer.
#define TIMER_2HZ_RESET() (TMR1 = 0)
#define DEFAULT_BAKE_TEMP 350
#define BROIL_TEMP 500
#define LONG_PRESS 5

// **** Set any local typedefs here ****

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

typedef enum {
    BAKE, TOAST, BROIL
} OvenCookMode;
//
typedef struct {
    uint8_t adcFlag;
    uint16_t adcKnobValue;

} adc;

typedef struct {
    OvenState state;
    uint16_t pressTime;
    uint16_t temp;
    uint16_t timeRemaining;
    uint16_t startTimer;
    OvenCookMode ovenMode;



    //add more members to this struct
} OvenData;



// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****
//initizializing struct members
static OvenData ovenData; //creating an object of a struct
static uint8_t ButtonFlag = BUTTON_EVENT_NONE; //tracks which button you're clicking
static uint8_t TIMER_TICK = 0; //flag used to determine if the user has pressed the button for more or less than a second
static uint16_t FreeRunningTimer = 0;
static uint8_t editTime = 1;
static uint16_t elapsedTime = 0; //how much time has passed, since the user pressed the button
static uint16_t storedFreeRunningTime = 0;
static uint8_t currentLED = 0;
static uint16_t one_eighth_time = 0;
static adc adc_values;

// **** Put any helper functions here ****


/*This function will update your OLED to reflect the state .*/
void updateOvenOLED(OvenData ovenData) { //finished
    //update OLED here
    char ovenMessage[1000];
    sprintf(ovenMessage, "hi");

    switch (ovenData.ovenMode) {
        case BAKE:
            if ((ovenData.state != COOKING) || (ovenData.state != RESET_PENDING)) {
                if (editTime == 1) {
                    sprintf(ovenMessage, "|%s%s%s%s%s%s| Mode: %s" \
                                         "\n|%s| >Time: %d:%02d"\
                                         "\n|%s| Temp: %d%sF" \
                                         "\n|%s%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, "Bake", "      ", ovenData.startTimer / 60, ovenData.startTimer % 60, "------", ovenData.temp, DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
                    //sprintf(ovenMessage, "hi");
                } else {
                    //sprintf(ovenMessage, "hi 2");
                    sprintf(ovenMessage, "|%s%s%s%s%s%s| Mode: %s" \
                                         "\n|%s| Time: %d:%02d"\
                                         "\n|%s| >Temp: %d%sF" \
                                         "\n|%s%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, "Bake", "      ", ovenData.startTimer / 60, ovenData.startTimer % 60, "------", ovenData.temp, DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
                }
            }
            if ((ovenData.state == COOKING) || (ovenData.state == RESET_PENDING)) {
                //sprintf(ovenMessage, "hi 3");

                sprintf(ovenMessage, "|%s%s%s%s%s%s| Mode: %s" \
                                   "\n|%s| Time: %d:%02d" \
                                   "\n|%s| Temp: %3d%sF" \
                                   "\n|%s%s%s%s%s%s|", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, "Bake", "      ", ovenData.timeRemaining / 60, ovenData.timeRemaining % 60, "------", ovenData.temp, DEGREE_SYMBOL, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
            }

            break;


        case BROIL:
            if ((ovenData.state != COOKING) || (ovenData.state != RESET_PENDING)) {
                
                sprintf(ovenMessage, "|%s%s%s%s%s%s| Mode: %s" \
                                   "\n|%s| Time: %d:%02d" \
                                   "\n|%s| Temp: %d%sF" \
                                   "\n|%s%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, "Broil", "      ", ovenData.startTimer / 60, ovenData.startTimer % 60, "------", BROIL_TEMP, DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);
                //oventop is off ovenbottom is off
            }
            if ((ovenData.state == COOKING) || (ovenData.state == RESET_PENDING)) {
                //sprintf(ovenMessage, "hi 5");
                sprintf(ovenMessage, "|%s%s%s%s%s%s| Mode: %s" \
                                     "\n|%s| Time: %d:%02d" \
                                     "\n|%s| Temp: %d%sF" \
                                     "\n|%s%s%s%s%s%s|", OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, OVEN_TOP_ON, "Broil", "      ", ovenData.timeRemaining / 60, ovenData.timeRemaining % 60, "------", BROIL_TEMP, DEGREE_SYMBOL, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);

                //oventop is on ovenbottom is off
            }
            break;


        case TOAST:
            if ((ovenData.state != COOKING) || (ovenData.state != RESET_PENDING)) {
//                sprintf(ovenMessage, "hi 6");
                //oventop is off ovenbottom is off
                 sprintf(ovenMessage,  "|%s%s%s%s%s%s| Mode: %s" \
                                     "\n|%s| Time: %d:%02d" \
                                     "\n|%s|" \
                                     "\n|%s%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, "Toast", "      ", ovenData.startTimer / 60, ovenData.startTimer % 60, "------", OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF, OVEN_BOTTOM_OFF);

            }
            if ((ovenData.state == COOKING) || (ovenData.state == RESET_PENDING)) {
//                sprintf(ovenMessage, "hi 7");
               sprintf(ovenMessage,  "|%s%s%s%s%s%s| Mode: %s" \
                                     "\n|%s| Time: %d:%02d" \
                                     "\n|%s|" \
                                     "\n|%s%s%s%s%s%s|", OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, OVEN_TOP_OFF, "Toast", "      ", ovenData.startTimer / 60, ovenData.startTimer % 60, "------", OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON, OVEN_BOTTOM_ON);
                //oventop is off ovenbottom is on
            }
            break;
    }
    OledClear(OLED_COLOR_BLACK);
    OledDrawString(ovenMessage);
    OledUpdate();

}


//This function will execute your state machine.  
//It should ONLY run if an event flag has been set.*/
//GOING TO BE YOUR MAIN PROGRAM 

void runOvenSM(void) {
    switch (ovenData.state) {

        case SETUP:

            if (ButtonFlag & BUTTON_EVENT_4DOWN) {
                ovenData.pressTime = FreeRunningTimer; //store free running time
                LEDS_SET(0x0FF); //turns on all the lights
                ovenData.state = COOKING;
                updateOvenOLED(ovenData);
            }



            if (ButtonFlag & BUTTON_EVENT_3DOWN) {
                ovenData.pressTime = FreeRunningTimer; //store free running time                               
                ovenData.state = SELECTOR_CHANGE_PENDING;
            }



            //bake
            if (adc_values.adcFlag == 1) {    
                adc_values.adcKnobValue = adc_values.adcKnobValue >> 2; //bit shifting by 2 bits so I isolate the 8 bits
                if ((editTime == 1) && (ovenData.ovenMode == BAKE)) {
                    ovenData.startTimer =  adc_values.adcKnobValue + 1;
                    ovenData.timeRemaining = ovenData.startTimer;
                } else if ((editTime == 0) && (ovenData.ovenMode == BAKE)) {
                    ovenData.temp =  adc_values.adcKnobValue+ 300;
                }



                //toast
                //broil
                if (((editTime == 1) && (ovenData.ovenMode == TOAST)) || ((editTime == 1) && (ovenData.ovenMode == BROIL))) {
                    ovenData.startTimer =  adc_values.adcKnobValue + 1;
                    ovenData.timeRemaining = ovenData.startTimer;

                }
                updateOvenOLED(ovenData);
                ovenData.state = SETUP;
            }
            break;


        case SELECTOR_CHANGE_PENDING: //finished

            if (ButtonFlag & BUTTON_EVENT_3UP) { //button flag returns the bit of the button that was pressed & ur comparing that to a button 3 up event
                elapsedTime = FreeRunningTimer - ovenData.pressTime;
                if (elapsedTime < LONG_PRESS) { //if it's less than 5 seconds we switch to the next mode, checking if user is trying to switch baking modes
                    if (ovenData.ovenMode != BROIL) {
                        ovenData.ovenMode++; //switch to next mode
                    } else {
                        ovenData.ovenMode = BAKE;
                    }



                } else {
                    if (ovenData.ovenMode == BAKE) {
                        if (editTime == 0) {
                            editTime = 1;
                        } else {
                            editTime = 0;
                        }
                    }
                }
                updateOvenOLED(ovenData);//added
                ovenData.state = SETUP;
            }
            break;

        case COOKING: //finished

            currentLED = LEDS_GET();
           
            if (ButtonFlag & BUTTON_EVENT_4DOWN) {
                ovenData.pressTime = FreeRunningTimer; //store free running time 
                ovenData.state = RESET_PENDING;     
            }



            if (TIMER_TICK != 0) {
                if (ovenData.timeRemaining > 0) {
                    if (((FreeRunningTimer - ovenData.startTimer) % 5) == 0) {
                        ovenData.timeRemaining--;
                        uint8_t individual_LED_time = 0;
                        one_eighth_time = (ovenData.timeRemaining * 8) / ovenData.startTimer;
                        for (int i = 0; i < one_eighth_time; i++) {
                            individual_LED_time += 0x80 >> i;
                        }
                        LEDS_SET(individual_LED_time);
                        updateOvenOLED(ovenData);



                    }
                } else {
                    LEDS_SET(0x00); //turns off all leds
                    ovenData.timeRemaining = ovenData.startTimer;
                    ovenData.state = SETUP;
                    updateOvenOLED(ovenData);
                }
            }
                break;


        case RESET_PENDING:

            while(!(ButtonFlag & BUTTON_EVENT_4UP)){
               elapsedTime = FreeRunningTimer - ovenData.pressTime;
            }
                if (elapsedTime >= LONG_PRESS) {
                    updateOvenOLED(ovenData);
                    LEDS_SET(0x00); //turns off all lights 
                    ovenData.timeRemaining = ovenData.startTimer;
                    ovenData.temp = DEFAULT_BAKE_TEMP;
                    ovenData.state = SETUP;

                } else {

                    ovenData.state = COOKING;
                }
                updateOvenOLED(ovenData);
                break;
            }
            updateOvenOLED(ovenData);
    }


//write your SM logic here.

int main() { //finished
    BOARD_Init();

    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.

    T2CON = 0; // everything should be off
    T2CONbits.TCKPS = 0b100; // 1:16 prescaler
    PR2 = BOARD_GetPBClock() / 16 / 100; // interrupt at .5s intervals
    T2CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T2IF = 0; //clear the interrupt flag before configuring
    IPC2bits.T2IP = 4; // priority of  4
    IPC2bits.T2IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T2IE = 1; // turn the interrupt on

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescaler, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.

    T3CON = 0; // everything should be off
    T3CONbits.TCKPS = 0b111; // 1:256 prescaler
    PR3 = BOARD_GetPBClock() / 256 / 5; // interrupt at .5s intervals
    T3CONbits.ON = 1; // turn the timer on

    // Set up the timer interrupt with a priority of 4.
    IFS0bits.T3IF = 0; //clear the interrupt flag before configuring
    IPC3bits.T3IP = 4; // priority of  4
    IPC3bits.T3IS = 0; // subpriority of 0 arbitrarily 
    IEC0bits.T3IE = 1; // turn the interrupt on;

    // </editor-fold>

    printf("Welcome to kcamaner's Lab07 (Toaster Oven).  Compiled on %s %s.", __TIME__, __DATE__);

    //initialize state machine (and anything else you need to init) here
    OledInit(); //initialize ur oled 
    ButtonsInit(); //initialize ur buttons 
    AdcInit(); //initialize adc 
    LEDS_INIT(); //initialize the leds 

    //initialize all of the data in the struct 
    ovenData.ovenMode = BAKE; //set ur oven mode to bake 
    ovenData.state = SETUP; //set ur state to setup 
    ovenData.temp = DEFAULT_BAKE_TEMP; //set your oven temperature to the default baking temperature(350)
    ovenData.pressTime = 0; //initiailizee oven press time to 0
    ovenData.startTimer = 1; //initialize cook start timer to 1 
    ovenData.timeRemaining = 0; //initialize cooktimeremaining to 0
    updateOvenOLED(ovenData);

    while (1) {
        //button flag checks which button got pushed down or released
        if (ButtonFlag != BUTTON_EVENT_NONE) {
            runOvenSM();
            ButtonFlag = BUTTON_EVENT_NONE;
        }

        if (adc_values.adcFlag) {
            runOvenSM();
            adc_values.adcFlag = 0;
        }
        if (TIMER_TICK != 0) {
            runOvenSM();
            TIMER_TICK = 0;
        }
    };
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void) //finished
{
    // Clear the interrupt flag.

    IFS0CLR = 1 << 12;

    //add event-checking code here
    TIMER_TICK = 1;
    FreeRunningTimer++;



}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void) //finished
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;
    //add event-checking code here
    ButtonFlag = ButtonsCheckEvents();
    adc_values.adcFlag = AdcChanged(); //returns true or false
    if (adc_values.adcFlag) {
        adc_values.adcKnobValue = AdcRead();
    }
}


