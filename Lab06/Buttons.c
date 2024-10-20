/* 
 * File:   Buttons.c
 * Author: kimberlycamanero
 *
 * Created on May 14, 2024, 1:07 AM
 */

#include <stdint.h>
#include <genericTypeDefs.h>

// We rely on this file to define various macros for working with the hardware buttons.
#include "BOARD.h"
#include "Buttons.h"

static uint8_t debounce;
static uint8_t prev;
/**
 * This function initializes the proper pins such that the buttons 1-4 may be used by modifying
 * the necessary bits in TRISD/TRISF. Only the bits necessary to enable the 1-4 buttons are
 * modified, so that this library does not interfere with other libraries.
 */
void ButtonsInit(void) {
    // set the buttons to input mode
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
    
    // initialize debounce and prev to zero as no previous buttons have been pressed yet
    // and debounce is zero to check for button presses at the beginning
    debounce = 0;
    prev = 0x00;
}

/**
 * ButtonsCheckEvents function checks the current button states and returns
 *  any events that have occured since its last
 * call.  This function should be called repeatedly in a Timer ISR, though it can
 * be called in main() during testing.
 *
 * In normal use, this function should only be used after ButtonsInit().
 * 
 * This function should assume that the buttons start in an off state with 
 * value 0. Therefore if no buttons are
 * pressed when ButtonsCheckEvents() is first called, 
 * BUTTONS_EVENT_NONE should be returned. 
 * 
 * @return  Each bit of the return value corresponds to one ButtonEvent flag,
 *          as described in Buttons.h.  If no events are detected, BUTTONS_EVENT_NONE is returned.
 * 
 * Note that more than one event can occur simultaneously, though this situation is rare.
 * To handle this, the output should be a bitwise OR of all applicable event flags. 
 * For example, if button 1 was released at the same time that button 2 was pressed,
 * this function should return (BUTTON_EVENT_1UP | BUTTON_EVENT_2DOWN) 
 * 
 */
uint8_t ButtonsCheckEvents(void) {
    // every call buttonStatus is set to no event
    uint8_t buttonStatus = BUTTON_EVENT_NONE;
    // button states gets the states of the buttons
    uint8_t status = BUTTON_STATES();
    
    // if the debounce is greater than zero we don't check for events yet and instead return no event
    if (debounce > 0) {
        debounce--;
        return buttonStatus;
    }
    
    // if the status hasnt changed we return no events
    if (status == prev) {
        return BUTTON_EVENT_NONE;
    }
    
    // if the button was up and it is now down we add it into buttonStatus to signify the change
    // conversely if a button was down and now it is up we also update buttonStatus to reflect that
    // we do this for every button with a bitwise or
    if ((status & BUTTON_STATE_4) && ((prev & BUTTON_STATE_4) == 0x00)) {
        buttonStatus |= BUTTON_EVENT_4DOWN;
    } else if (!(status & BUTTON_STATE_4) && prev & BUTTON_STATE_4){
        buttonStatus |= BUTTON_EVENT_4UP;
    }
    if ((status & BUTTON_STATE_3) && ((prev & BUTTON_STATE_3) == 0x00)) {
        buttonStatus |= BUTTON_EVENT_3DOWN;
    } else if (!(status & BUTTON_STATE_3) && prev & BUTTON_STATE_3){
        buttonStatus |= BUTTON_EVENT_3UP;
    }
    if ((status & BUTTON_STATE_2) && ((prev & BUTTON_STATE_2) == 0x00)) {
        buttonStatus |= BUTTON_EVENT_2DOWN;
    } else if (!(status & 2) && prev & BUTTON_STATE_2){
        buttonStatus |= BUTTON_EVENT_2UP;
    }
    if ((status & BUTTON_STATE_1) && ((prev & BUTTON_STATE_1) == 0x00)) {
        buttonStatus |= BUTTON_EVENT_1DOWN;
    } else if (!(status & BUTTON_STATE_1) && prev & BUTTON_STATE_1){
        buttonStatus |= BUTTON_EVENT_1UP;
    }
    
    // we reset debounce to its value
    // and we set the previous status to the current status
    // then return the state of the buttons
    debounce = BUTTONS_DEBOUNCE_PERIOD;
    prev = status;
    return buttonStatus;
    
}
    
    
    
    /*
    int currentButtonState = BUTTON_STATES();
    int event = BUTTON_EVENT_NONE;
    if (currentButtonState & BUTTON_STATE_1 != lastButtonState & BUTTON_STATE_1) {
        buttonTimer1 = 0;



    } else if (buttonTimer1 >= BUTTONS_DEBOUNCE_PERIOD) {
        if (currentButtonState & BUTTON_STATE_1 != 0) { //if the button is down
            event = event | BUTTON_EVENT_1DOWN;

        } else {
            event = event | BUTTON_EVENT_1UP;
        }
    } else {
        buttonTimer1++;
    }

    if (currentButtonState & BUTTON_STATE_2 != lastButtonState & BUTTON_STATE_2) {
        buttonTimer2 = 0;



    } else if (buttonTimer2 >= BUTTONS_DEBOUNCE_PERIOD) {
        if (currentButtonState & BUTTON_STATE_2 != 0) { //if the button is down
            event = event | BUTTON_EVENT_2DOWN;

        } else {
            event = event | BUTTON_EVENT_2UP;
        }
    } else {
        buttonTimer2++;
    }

    if (currentButtonState & BUTTON_STATE_3 != lastButtonState & BUTTON_STATE_3) {
        buttonTimer3 = 0;



    } else if (buttonTimer3 >= BUTTONS_DEBOUNCE_PERIOD) {
        if (currentButtonState & BUTTON_STATE_3 != 0) { //if the button is down
            event = event | BUTTON_EVENT_3DOWN;

        } else {
            event = event | BUTTON_EVENT_3UP;
        }
    } else {
        buttonTimer3++;
    }

    if (currentButtonState & BUTTON_STATE_4 != lastButtonState & BUTTON_STATE_4) {
        buttonTimer4 = 0;



    } else if (buttonTimer4 >= BUTTONS_DEBOUNCE_PERIOD) {
        if (currentButtonState & BUTTON_STATE_4 != 0) { //if the button is down
            event = event | BUTTON_EVENT_4DOWN;

        } else {
            event = event | BUTTON_EVENT_4UP;
        }
    } else {
        buttonTimer4++;
    }









    lastButtonState = currentButtonState;
    return event;

*/



