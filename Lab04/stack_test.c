// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"


// User libraries
#include "stack.h"

int main() {
    BOARD_Init();
    double popped_value = 1;
    printf("\n###### Beginning CRUZID's stack test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!

    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    if (stack.initialized == TRUE) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }

    StackPush(&stack, 0);
    if (stack.currentItemIndex == 0 && stack.stackItems[stack.currentItemIndex] == 0) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    if(StackGetSize(&stack) == 1){
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    
    StackPop(&stack, &popped_value);
    if (stack.currentItemIndex == -1 && popped_value == 0) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    StackPop(&stack, &popped_value);
    if (StackPop(&stack, &popped_value) == STANDARD_ERROR) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    //fills stack up with 3's
    for(int i=0; i<STACK_SIZE; i++){
        StackPush(&stack, 3.0);
    }
    
    //TRYING TO PUSH BUT ITS FULL SO ERROR
    if (StackPush(&stack, 11) == STANDARD_ERROR) { //first number is the spot, second is the value
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    // TEST STACK FULL
    if (StackIsFull(&stack)) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    //popped the top value
    StackPop(&stack, &popped_value);
    if (stack.currentItemIndex == STACK_SIZE -2 && popped_value == 3.0) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    //Empty stack
    for(int i=0; i<STACK_SIZE - 1; i++){
        StackPop(&stack, &popped_value);
    }
    
    
    // TEST STACK EMPTY
    if (StackIsEmpty(&stack)) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
    
    if(StackGetSize(&stack) == 0){
        printf("passed\n");
    } else {
        printf("failed\n");
    }
    
            

    BOARD_End();
    
    
    
    //test stackInit:
    while (1);
    return 0;
}




