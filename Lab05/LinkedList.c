/* 
 * File:   LinkedList.c
 * Author: kimberlycamanero
 *
 * Created on May 7, 2024, 3:10 PM
 */

//C Libraries
#include <stdio.h>
#include <stdlib.h>

//Personal Libraries
#include "LinkedList.h"
#include "BOARD.h"

/*
 * 
 */


//FIRST FUNCTION 

ListItem *LinkedListNew(char *data) {
    //Creates a list
    ListItem* ProsteticBall = (ListItem*) malloc(sizeof (ListItem)); //This allocates memory for the size of the List Item



    if (ProsteticBall == NULL) {
        return NULL; //if allocation fails (so if there is an ERROR) then NULL will be returned. Sigh.
    } else {
        ProsteticBall->previousItem = NULL; //previous item is NULL
        ProsteticBall->nextItem = NULL; //next item is NULL
        ProsteticBall->data = data; //current item is the data


        return ProsteticBall;
    }


}

//SECOND FUNCTION

ListItem *LinkedListCreateAfter(ListItem *item, char *data) {

    //adds an item to the right

    ListItem* Ball2 = LinkedListNew(data); //new Item was created (Ball2 must be to the right of item)


    if (Ball2 == NULL) {
        return Ball2; //if error, return NULL
    }


    //Case 1: If item is NULL
    if (item == NULL) {
        return Ball2;
        /*
        //if "item" is NULL then we just create a new string again, which is why previous & next item are set to NULL
        Ball2->previousItem = NULL;
        Ball2->nextItem = NULL;
        Ball2-> data = data;
        */
        //Case 2: If we are at the tail of the list
    }
    if (item->nextItem == NULL) {
        item->nextItem = Ball2;
        Ball2->previousItem = item;
    }//Case 3: If we are in between lists
    else {
        item->nextItem->previousItem = Ball2;
        Ball2->nextItem = item->nextItem;
        item->nextItem = Ball2;
        Ball2 -> previousItem = item;


    }
    return Ball2;
}

/* 
    Ball2 ->previousItem = item;
    Ball2 ->nextItem = NULL;
    Ball2 ->data = data;

}
 */



//THIRD FUNCTION

char *LinkedListRemove(ListItem *item) {
    //printf("1 we're in remove\n");
    char *data;

    if (item == NULL) {
        data = NULL;
        return data;
    }
    //printf("we're in remove\n");

    data = item->data;


    if (item->previousItem
            && item->nextItem) {
        item->previousItem->nextItem = item->nextItem;
        item->nextItem->previousItem = item->previousItem;
        //printf("we're in remove 3\n");
    } else if (item->previousItem == NULL
            && item->nextItem) {

        item->nextItem->previousItem = NULL;
        //printf("we're in remove2\n");
        ///free(item);
    } else if (item->previousItem
            && item->nextItem == NULL) {

        item->previousItem->nextItem = NULL;
        //printf("we're in remove7\n");
    }
   //printf("we're in remove after\n");

    free(item);
    //printf("we're in remove free\n");
    return data;
}





//FOURTH FUNCTION

int LinkedListSize(ListItem * list) {
    // printf("this is size\n");
    int i = 0;
    ListItem *head = LinkedListGetFirst(list);
    while (head) { //we start @ the head, and as long as the next item isn't NULL we keep adding
        i++;
        head = head->nextItem;
        //printf("this is i\n");

    }
    return i;
}

//FIFTH FUNCTION

ListItem *LinkedListGetFirst(ListItem *list) {

    //if null, return null
    if (list == NULL) {
        return NULL;
    }

    //CASE 1: if we are @ the head of the list, we just return
    if (list->previousItem == NULL) {
        return list;
    }

    //CASE 2: just go to the head
    return LinkedListGetFirst(list->previousItem);
}



//SIXTH FUNCTION

ListItem * LinkedListGetLast(ListItem * list) {

    //if null, return null
    if (list == NULL) {
        return NULL;
    }

    //CASE 1: if we are @ the tail of the list, we just return
    if (list->nextItem == NULL) {
        return list;
    }

    //CASE 2: just go to the tail
    return LinkedListGetLast(list->nextItem);
}


//SEVENTH FUNCTION

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem) {

    if (firstItem == NULL || secondItem == NULL) {
        return STANDARD_ERROR;
    }

    char* temp = firstItem->data; //temp placeholder

    //SWAP
    firstItem->data = secondItem->data;
    secondItem->data = temp;
    return SUCCESS;
}







//EIGHTH FUNCTION

int LinkedListPrint(ListItem *list) {

    //CASE 1: If it is @ NULL then just return ERROR
    if (list == NULL) {
        return STANDARD_ERROR;
    }


    //HOWEVER, if it is not @ NULL then we start by being @ the head and we work our way to the right (until we reach the tail)
    ListItem *head = LinkedListGetFirst(list);
    printf("[");
    while (head != NULL) { //while head does not equal NULL, we keep going to the next item
        if (head->nextItem) {
            printf("%s ", head->data);
        } else {
            printf("%s]\n", head->data); //once it hits the end, it will print the last data followed by a closing bracket & will start a new line
        }
        head = head->nextItem;
    }

    return SUCCESS;
}






