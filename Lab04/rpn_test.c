// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"

//mtchun@ucsc.edu

// User libraries
#include "rpn.h"

int main()
{
    BOARD_Init();
    int error;

    printf("\n###### Beginning kcamaner's rpn test harness: ####\n\n");

    //What follows is starter code.  You will need to modify it!
   //StackPush(&sandwich, 1);
   //StackPush(&sandwich, 1);
  
    //Test 0 (provided Test)
    char test0[] = "1 1 +";
    double result0;
    double expected0 = 2;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test0);
    error = RPN_Evaluate(test0, &result0);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result0 != expected0) {
        printf("Failed, expected = %f , result = %f\n", expected0, result0);
    } else {
        printf("Success!\n");
    }
    
    
    
    //Test 1 (adds 6 & 5 and result should be 11)
    char test1[] = "6 5 +";
    double result1;
    double expected1 = 11;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test1);
    error = RPN_Evaluate(test1, &result1);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result1 != expected1) {
        printf("Failed, expected = %f , result = %f\n", expected1, result1);
    } else {
        printf("Success!\n");
    }
    
    
    //Test 2 (adds 3 & 3 & 10 and result should be 16)
    char test2[] = "6 10 +";
    double result2;
    double expected2 = 16;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test2);
    error = RPN_Evaluate(test2, &result2);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result2 != expected2) {
        printf("Failed, expected = %f , result = %f\n", expected2, result2);
    } else {
        printf("Success!\n");
    }
    
    
    //Test 3 (Subtracts 2010 & 6 and result should be 2004)
    char test3[] = "2010 6 -";
    double result3;
    double expected3 = 2004;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test3);
    error = RPN_Evaluate(test3, &result3);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result3 != expected3) {
        printf("Failed, expected = %f , result = %f\n", expected3, result3);
    } else {
        printf("Success!\n");
    }
    
    
    //Test 4 (Multiplies 3 & 4 and result should be 12)
    char test4[] = "3 4 *";
    double result4;
    double expected4 = 12;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test4);
    error = RPN_Evaluate(test4, &result4);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result4 != expected4) {
        printf("Failed, expected = %f , result = %f\n", expected4, result4);
    } else {
        printf("Success!\n");
    }
    
    
    //Test 5 (Divides 100 & 4 and result should be 25)
    char test5[] = "100 4 /";
    double result5;
    double expected5 = 25;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test5);
    error = RPN_Evaluate(test5, &result5);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result5 != expected5) {
        printf("Failed, expected = %f , result = %f\n", expected5, result5);
    } else {
        printf("Success!\n");
    }
    
    
    //TESTING FOR ERRORS (6 errors)
    //Test 6 (test for overflow)
    char test6[] = "6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6";
    double result6;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test6);
    error = RPN_Evaluate(test6, &result6);
    if (error == RPN_ERROR_STACK_OVERFLOW) {
        printf("ERROR!: Stack Overflow\n");
    } else {
        printf("Something else happened\n");
    }
    
    //Test 7 (test for underflow)
    char test7[] = "6 7 * +";
    double result7;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test7);
    error = RPN_Evaluate(test7, &result7);
    if (error == RPN_ERROR_STACK_UNDERFLOW) {
        printf("ERROR!: Stack Underflow\n");
    } else {
        printf("Something else happened\n");
    }
    
    //Test 8 (test for invalid token)
    char test8[] = "1 2 . *";
    double result8;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test8);
    error = RPN_Evaluate(test8, &result8);
    if (error == RPN_ERROR_INVALID_TOKEN) {
        printf("ERROR!: Invalid Token\n");
    } else {
        printf("Something else happened\n");
    }
    
    //Test 9 (test for divide by 0)
    char test9[] = "6 -0.0000 /";
    double result9;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test9);
    error = RPN_Evaluate(test9, &result9);
    if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
        printf("ERROR!: Divided by 0\n");
    } else {
        printf("Something else happened\n");
    }
    
    //Test 10 (test for too few items)
    char test10[] = "";
    double result10;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test10);
    error = RPN_Evaluate(test10, &result10);
    if (error == RPN_ERROR_TOO_FEW_ITEMS_REMAIN) {
        printf("ERROR!: Too few items remain\n");
    } else {
        printf("Something else happened\n");
    }
    
    //Test 11 (test for underflow)
    char test11[] = "11 16 * 2004";
    double result11;
    printf("Testing RPN_Evaluate with \"%s\"... \n ", test11);
    error = RPN_Evaluate(test11, &result11);
    if (error == RPN_ERROR_TOO_MANY_ITEMS_REMAIN) {
        printf("ERROR!: Too many items remain\n");
    } else {
        printf("Something else happened\n");
    }

    
    
    
    
    
    printf("Testing ProcessBackspaces:\n");
    char test_pb1[] = "666\b34";
    ProcessBackspaces(test_pb1);
    printf("result    : %s\n", test_pb1);
    printf("should be : 6634\n");
    BOARD_End();
    while (1);
}


