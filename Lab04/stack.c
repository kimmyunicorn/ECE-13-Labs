/* 
 * File:   stack.c
 * Author: kimberlycamanero
 *
 * Created on April 25, 2024, 3:12 PM
 */


#include "stack.h"

void StackInit(struct Stack *stack) {

    stack->initialized = TRUE;
    stack->currentItemIndex = -1;


}

int StackPush(struct Stack *stack, double value) {
    if (stack->initialized == TRUE && stack->currentItemIndex < STACK_SIZE - 1) {
        stack->currentItemIndex++;
        stack->stackItems[stack->currentItemIndex] = value;
        return (SUCCESS);
    } else {
        return (STANDARD_ERROR);

    }
}

int StackPop(struct Stack *stack, double *value) {
    if (stack->initialized == TRUE && stack->currentItemIndex > -1) {

        *value = stack->stackItems[stack->currentItemIndex];
        stack->currentItemIndex--;
        return (SUCCESS);
    } else {
        return (STANDARD_ERROR);

    }
}

int StackIsEmpty(const struct Stack *stack) {
    if (stack->initialized == TRUE && stack->currentItemIndex == -1) {


        return (TRUE);
    } else {
        return (FALSE);

    }
}

int StackIsFull(const struct Stack *stack) {
    if (stack->initialized == TRUE && stack->currentItemIndex == STACK_SIZE - 1) {


        return (TRUE);
    } else {
        return (FALSE);

    }
}

int StackGetSize(const struct Stack *stack) {
    if (stack->initialized == TRUE) {


        return (stack -> currentItemIndex + 1);
    } else {
        return (SIZE_ERROR);

    }
}









