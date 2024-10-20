/* 
 * File:   rpn.c
 * Author: kimberlycamanero
 *
 * Created on April 25, 2024, 3:12 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "rpn.h"
#include <string.h>
#include <ctype.h>

#define zero 0
//Function YAS
//int ValidToken(char * floor); //need this to check if it is a token or not
int i, j;

int RPN_Evaluate(char * rpn_string, double * result) {


    char* floor = strtok(rpn_string, " ");

    //double number; 
    double number1_popped;
    double number2_popped;


    //create a stack
    struct Stack sandwich = {};
    StackInit(&sandwich);





    while (floor != NULL) {
        if (isdigit(*floor)) {
            if (StackIsFull(&sandwich) == SUCCESS) {
                return RPN_ERROR_STACK_OVERFLOW;
            } else {
                StackPush(&sandwich, atof(floor));
            }




            //Addition
        } else if (floor[0] == '+') {
            if (StackPop(&sandwich, &number1_popped) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            if (StackPop(&sandwich, &number2_popped) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            *result = number1_popped + number2_popped;
            StackPush(&sandwich, *result);



            //Subtraction
        } else if (floor[0] == '-') {
            if (StackPop(&sandwich, &number1_popped) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            if (StackPop(&sandwich, &number2_popped) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            *result = number2_popped - number1_popped;
            StackPush(&sandwich, *result);



            //Multiplication    
        } else if (floor[0] == '*') {
            if (StackPop(&sandwich, &number1_popped) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            if (StackPop(&sandwich, &number2_popped) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            *result = number1_popped * number2_popped;
            StackPush(&sandwich, *result);





            //Division     
        } else if (floor[0] == '/') {
            if (StackPop(&sandwich, &number1_popped) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }
            if (StackPop(&sandwich, &number2_popped) == STANDARD_ERROR) {
                return RPN_ERROR_STACK_UNDERFLOW;
            }


            //Dividing by 0 Error
            if (number1_popped == 0) {
                return RPN_ERROR_DIVIDE_BY_ZERO;
            }
            *result = number2_popped / number1_popped;
            StackPush(&sandwich, *result);
        } else {
            return RPN_ERROR_INVALID_TOKEN;
        }
        floor = strtok(NULL, " ");
    }

    //Testing for Overflow Error & Underflow Error 
    if (StackGetSize(&sandwich) < 1) {
        return RPN_ERROR_TOO_FEW_ITEMS_REMAIN;
    }
    if (StackGetSize(&sandwich) > 1) {
        return RPN_ERROR_TOO_MANY_ITEMS_REMAIN;
    }
    return 0;
}

int ProcessBackspaces(char *rpn_sentence) {
    int len = strlen(rpn_sentence);
    int i, j;

    for (i = 0, j = 0; i < len; i++) {
        if (rpn_sentence[i] == '\b') { // Check for backspace character
            if (j > 0) {
                j--;
            }
        } else {
            rpn_sentence[j] = rpn_sentence[i];
            j++;
        }
    }
    rpn_sentence[j] = '\0';
    return j;
}









