/* 
 * File:   Leds_Lab06.c
 * Author: kimberlycamanero
 *
 * Created on May 14, 2024, 2:03 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "BOARD.h"
#include "Leds_Lab06.h"


/*
 * 
 */

void LEDS_INIT(void){

TRISE = 0x00; //MAKES THE PIN AN OUTPUT
LATE = 0x00; //TURNS OFF LEDS
}

void LEDS_SET(char newPattern){
LATE = newPattern; //UPDATES "LATE" REGISTER AND GIVES IT A NEW PATTERN
}
char LEDS_GET(void){
return LATE; //RETURNS CURRENT VALUE OF THE LEDS (WE CAN SEE THE CURRENT STATE THE LEDS ARE IN)
}