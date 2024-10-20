
/* 
 * File:   LinkedListTest.c
 * Author: kimberlycamanero
 *
 * Created on May 7, 2024, 3:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "BOARD.h"

/*
 * 
 */


int main(int argc, char** argv) {



    //TEST FOR LINKED LIST NEW
    char *ball_1 = "Just";
    char *ball_2 = "the";
    char *ball_3 = "two";
    char *ball_4 = "of";
    char *ball_5 = "us";

    ListItem *List_1 = LinkedListNew(ball_1);
    printf("Test for LINKED_LIST_NEW:\n");
    if (List_1 == NULL) {
        printf("ERROR\n");

    } else {
        printf("TEST PASSED!\n");
    }

    if (strcmp(ball_1, List_1->data) == 0) {
        printf("TEST PASSED!\n");

    } else {
        printf("TEST FAILED :(\n");
    }





    //TEST FOR LINKED LIST CREATE AFTER

    //creates 2
    ListItem *List_2 = LinkedListCreateAfter(List_1, ball_2);





    //printf("this is ball 2 %s\n", List_1 ->nextItem ->data);


    //LinkedListCreateAfter(List_1, ball_2);
    printf("Test for LINKED_LIST_CREATE_AFTER:\n");
    if (strcmp(List_1 ->nextItem ->data, ball_2) == 0) {
        printf("TEST PASSED!\n");

    } else {
        //printf("this is linked list: %s ball2: %s\n", List_1 ->nextItem ->data, ball_2);
        printf("TEST FAILED :(\n");
    }

    //creates 3
    ListItem *List_3 = LinkedListCreateAfter(List_1, ball_3);
    if (strcmp(List_1 ->nextItem ->data, ball_3) == 0) {
        printf("TEST PASSED!\n");

    } else {
        //printf("this is linked list: %s ball2: %s\n", List_1 ->nextItem ->data, ball_2);
        printf("TEST FAILED :(\n");
    }
    LinkedListPrint(List_3);

    //Test for size
    printf("this is size %d", LinkedListSize(List_1));
    //printf("testing...");
    if (LinkedListSize(List_1) == 3) {
        printf("TEST PASSED!\n");
    } else {
        printf("TEST FAILED :(\n");
    }

    //creates after (creates 4)
    ListItem *List_4 = LinkedListCreateAfter(List_1, ball_4);
    if (strcmp(List_1 ->nextItem ->data, ball_4) == 0) {
        printf("TEST PASSED!\n");

    } else {
        printf("TEST FAILED :(\n");
    }
    LinkedListPrint(List_4);

    //creates after (creates 5)
    ListItem *List_5 = LinkedListCreateAfter(List_1, ball_5);
    if (strcmp(List_1 ->nextItem ->data, ball_5) == 0) {
        printf("TEST PASSED!\n");
    } else {
        printf("TEST FAILED :(\n");
    }
    LinkedListPrint(List_5);


    //TEST FOR REMOVE

    printf("this is before we are removing actually\n");
    char *removed = LinkedListRemove(List_1);
    printf("this is removing the first data, it should print Just this is removed: %s\n", removed);
    if (LinkedListSize(List_2) == 4) {
        printf("TEST PASSED!\n");
    } else {
        printf("TEST FAILED :(\n");
    }

    removed = LinkedListRemove(List_2);
    printf("this is removing the first data, it should print the this is removed: %s\n", removed);
    if (LinkedListSize(List_3) == 3) {
        printf("TEST PASSED!\n");
    } else {
        printf("TEST FAILED :(\n");
    }



    //Test for first

    ListItem *List_first = LinkedListGetFirst(List_3);
    printf("this is first %s\n", List_first->data);
    LinkedListPrint(List_3);
    if (strcmp(List_first->data, ball_5) == 0) {
        printf("TEST PASSED!\n");

    } else {
        printf("TEST FAILED :(\n");
    }
    
    //Test for last 

    ListItem *List_last = LinkedListGetLast(List_3);
    printf("this is last %s\n", List_last->data);
    LinkedListPrint(List_3);
    if (strcmp(List_last->data, ball_3) == 0) {
        printf("TEST PASSED!\n");

    } else {
        printf("TEST FAILED :(\n");
    }


    //TEST FOR SWAP DATA
    printf("This is before swapping\n");


    LinkedListPrint(List_3);
    LinkedListSwapData(List_first, List_last);
    printf("This is after swapping\n");
    LinkedListPrint(List_3);

    //test 2 for swapping

    printf("This is before swapping\n");
    LinkedListPrint(List_4);
    LinkedListSwapData(List_last, List_first);
    printf("This is after swapping\n");
    LinkedListPrint(List_4);

    printf("This is before swapping\n");
    LinkedListPrint(List_5);
    LinkedListSwapData(List_3, List_4);
    printf("This is after swapping\n");
    LinkedListPrint(List_5);


}