// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"



// User libraries
#include "rpn.h"

// **** Set macros and preprocessor directives ****
// The lab calls for 60 characters of user input
#define MAX_INPUT_LENGTH 60
int error;
int main() {
    BOARD_Init();

    //What follows is starter code.  You will need to modify it!

    char rpn_sentence[MAX_INPUT_LENGTH + 2];
    double result;

    printf("Welcome to kcamaner's RPN calculator.  Compiled on %s %s", __DATE__, __TIME__);
    while (1) {

        printf("Enter floats and + - / * in RPN format:\n");

        fgets(rpn_sentence, sizeof (rpn_sentence), stdin);
        error = RPN_Evaluate(rpn_sentence, &result);
        
        if (error == RPN_NO_ERROR){
            printf("result = %f\n", result);
            
        }
        if (error == RPN_ERROR_STACK_OVERFLOW){
            printf("ERROR:STACK_OVERFLOW\n");
        }
        if (error == RPN_ERROR_STACK_UNDERFLOW){
            printf("ERROR:STACK_UNDERFLOW\n");
        }
        if (error == RPN_ERROR_INVALID_TOKEN){
            printf("ERROR:INVALID_TOKEN\n");
        }
        if (error == RPN_ERROR_DIVIDE_BY_ZERO){
            printf("ERROR:DIVIDE_BY_ZERO\n");
        }
        if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN){
            printf("ERROR:TOO_FEW_ITEMS_REMAIN\n");
        }
        if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN){
            printf("ERROR:TOO_MANY_ITEMS_REMAIN\n");
        }
        


        result = 0;

      

    }

    while (1);
}




