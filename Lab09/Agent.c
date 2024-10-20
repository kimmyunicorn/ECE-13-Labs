/* 
 * File:   Agent.c
 * Author: kimberlycamanero
 *
 * Created on June 3, 2024, 4:05 PM
 */

 

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "Agent.h"
#include "BattleBoats.h"
#include "Field.h"
#include "FieldOled.h"
#include "Negotiation.h"
#include "BOARD.h"
#include "Message.h"
#include "Uart1.h"


#define RANDOM_RANGE 0x0F
#define SUNK 0b00000000

typedef struct {
    NegotiationData secret;
    NegotiationData hash;
    AgentState state;
    uint8_t playerTurns;
    Field OledDisplay;
    Field userField;
    Field opponentField;
    FieldOledTurn turn;
    Message msgtype;
    GuessData userGuess;
    GuessData opponentGuess;
} player;
static player myPlayer;
static char *endMessage;

/**
 * The Init() function for an Agent sets up everything necessary for an agent before the game
 * starts.  At a minimum, this requires:
 *   -setting the start state of the Agent SM.
 *   -setting turn counter to 0
 * If you are using any other persistent data in Agent SM, that should be reset as well.
 * 
 * It is not advised to call srand() inside of AgentInit.  
 *  */
void ErrorMessage(uint16_t BB_ERROR);

void AgentInit(void) { //finished


    for (int i = 0; i < FIELD_ROWS; i++) {
        for (int j = 0; j < FIELD_ROWS; j++) {
            myPlayer.userField.grid[i][j] = 0;
            myPlayer.opponentField.grid[i][j] = 0;
        }
    }


    myPlayer.state = AGENT_STATE_START;
    myPlayer.secret = 0;
    myPlayer.hash = 0;
    myPlayer.playerTurns = 0;
    myPlayer.turn = FIELD_OLED_TURN_NONE;
    myPlayer.msgtype.type = MESSAGE_NONE;
    myPlayer.msgtype.param0 = 0;
    myPlayer.msgtype.param1 = 0;
    myPlayer.msgtype.param2 = 0;
    myPlayer.userGuess.row = 0;
    myPlayer.userGuess.col = 0;
    myPlayer.userGuess.result = 0;
    myPlayer.opponentGuess.row = 0;
    myPlayer.opponentGuess.col = 0;
    myPlayer.opponentGuess.result = 0;




}

/**
 * AgentRun evolves the Agent state machine in response to an event.
 * 
 * @param  The most recently detected event
 * @return Message, a Message struct to send to the opponent. 
 * 
 * If the returned Message struct is a valid message
 * (that is, not of type MESSAGE_NONE), then it will be
 * passed to the transmission module and sent via UART.
 * This is handled at the top level! AgentRun is ONLY responsible 
 * for generating the Message struct, not for encoding or sending it.
 */
Message AgentRun(BB_Event event) {

    switch (myPlayer.state) {
            /**********************************************************
             *AGENT STATE START
             ***********************************************************/

        case AGENT_STATE_START:
            //            printf("in agent start\n");
            if (event.type == BB_EVENT_ERROR) {
                //                printf("bb_event_error\n");
                ErrorMessage(event.param0);
                AgentSetState(AGENT_STATE_END_SCREEN);
                myPlayer.msgtype.type = MESSAGE_ERROR;
            } else if (event.type == BB_EVENT_RESET_BUTTON) {
                //                printf("bb_event_reset button\n");
                AgentInit();
            } else if (event.type == BB_EVENT_START_BUTTON) {
                //                printf("bb_event_start_button\n");
                myPlayer.secret = rand() & RANDOM_RANGE;
                myPlayer.msgtype.param0 = NegotiationHash(myPlayer.secret);
                myPlayer.msgtype.type = MESSAGE_CHA;
                FieldInit(&myPlayer.userField, &myPlayer.opponentField);
                FieldAIPlaceAllBoats(&myPlayer.userField);
                //                printf("sending to agent state challenging\n");
                AgentSetState(AGENT_STATE_CHALLENGING);
            } else if (event.type == BB_EVENT_CHA_RECEIVED) {
                //                printf("bb_event_cha_received\n");
                myPlayer.secret = rand() & RANDOM_RANGE;
                myPlayer.msgtype.param0 = myPlayer.secret;
                myPlayer.msgtype.type = MESSAGE_ACC;
                FieldInit(&myPlayer.userField, &myPlayer.opponentField);
                FieldAIPlaceAllBoats(&myPlayer.userField);

            } else {
                myPlayer.msgtype.type = MESSAGE_NONE;
            }

            break;
            /**********************************************************
             *AGENT STATE CHALLENGING
             ***********************************************************/
        case AGENT_STATE_CHALLENGING:
            //             printf("in state challenging\n");
            if (event.type == BB_EVENT_ACC_RECEIVED) {
                myPlayer.msgtype.type = MESSAGE_REV;
                myPlayer.msgtype.param0 = myPlayer.secret;
                if (NegotiateCoinFlip(myPlayer.secret, event.param0) == TAILS) {
                    myPlayer.turn = FIELD_OLED_TURN_THEIRS;
                    AgentSetState(AGENT_STATE_DEFENDING);
                } else {
                    myPlayer.turn = FIELD_OLED_TURN_MINE;
                    AgentSetState(AGENT_STATE_WAITING_TO_SEND);
                }
            } else if (event.type == BB_EVENT_ERROR) {
                ErrorMessage(event.param0);
                AgentSetState(AGENT_STATE_END_SCREEN);
                myPlayer.msgtype.type = MESSAGE_ERROR;
            } else if (event.type == BB_EVENT_RESET_BUTTON) {
                AgentInit();
            } else {
                myPlayer.msgtype.type = MESSAGE_NONE;
            }
            break;
            /**********************************************************
             *AGENT STATE ACCEPTING 
             ***********************************************************/
        case AGENT_STATE_ACCEPTING:
            //             printf("in agent accepting\n");
            if (event.type == BB_EVENT_ERROR) {
                ErrorMessage(event.param0);
                AgentSetState(AGENT_STATE_END_SCREEN);
                myPlayer.msgtype.type = MESSAGE_ERROR;
            } else if (event.type == BB_EVENT_RESET_BUTTON) {
                AgentInit();
            } else if (event.type == BB_EVENT_REV_RECEIVED) {
                if (NegotiateCoinFlip(myPlayer.secret, event.param0) == HEADS) {
                    myPlayer.turn = FIELD_OLED_TURN_THEIRS;
                    AgentSetState(AGENT_STATE_DEFENDING);

                } else {
                    myPlayer.turn = FIELD_OLED_TURN_MINE;
                    myPlayer.userGuess = FieldAIDecideGuess(&myPlayer.opponentField);
                    myPlayer.msgtype.type = MESSAGE_SHO;
                    AgentSetState(AGENT_STATE_ATTACKING);
                }
                if (NegotiationVerify(myPlayer.secret, myPlayer.hash) == 1) {
                    char* cheatingDetectedMssg;
                    sprintf(cheatingDetectedMssg, "Cheating");
                    OledDrawString(cheatingDetectedMssg);
                    OledUpdate();
                    AgentSetState(AGENT_STATE_END_SCREEN);
                    myPlayer.msgtype.type = MESSAGE_ERROR;
                }
            } else {
                myPlayer.msgtype.type = MESSAGE_NONE;
            }
            break;
            /**********************************************************
             *AGENT STATE ATTACKING
             ***********************************************************/
        case AGENT_STATE_ATTACKING:
            //            printf("in agent attacking\n");
            if (event.type == BB_EVENT_RES_RECEIVED) {
                FieldRegisterEnemyAttack(&myPlayer.opponentField, &myPlayer.userGuess);
                myPlayer.opponentGuess.row = event.param0;
                myPlayer.opponentGuess.col = event.param1;
                FieldUpdateKnowledge(&myPlayer.opponentField, &myPlayer.opponentGuess);
                if (FieldGetBoatStates(&myPlayer.opponentField) == SUNK && FieldGetBoatStates(&myPlayer.userField) != SUNK) {
                    char* victoryMssg;
                    sprintf(victoryMssg, "Win!");
                    OledDrawString(victoryMssg);
                    OledUpdate();
                    AgentSetState(AGENT_STATE_END_SCREEN);
                } else {
                    AgentSetState(AGENT_STATE_DEFENDING);
                }
            }
            break;
            /**********************************************************
             *AGENT STATE DEFENDING
             ***********************************************************/

        case AGENT_STATE_DEFENDING:
            //               printf("in agent defending\n");
            if (event.type == BB_EVENT_SHO_RECEIVED) {
                FieldRegisterEnemyAttack(&myPlayer.userField, &myPlayer.opponentGuess);
                myPlayer.opponentGuess.row = event.param0;
                myPlayer.opponentGuess.col = event.param1;
                FieldUpdateKnowledge(&myPlayer.userField, &myPlayer.userGuess);
                myPlayer.msgtype.type = MESSAGE_RES;
                if (FieldGetBoatStates(&myPlayer.userField) == SUNK && FieldGetBoatStates(&myPlayer.opponentField) != SUNK) {
                    char* gameLoss;
                    sprintf(gameLoss, "Defeat!");
                    OledDrawString(gameLoss);
                    OledUpdate();
                    AgentSetState(AGENT_STATE_END_SCREEN);
                } else {
                    AgentSetState(AGENT_STATE_DEFENDING);
                }
            }
            break;
            /**********************************************************
             *AGENT STATE DEFENDING
             ***********************************************************/
        case AGENT_STATE_WAITING_TO_SEND:
            //             printf("in agent waiting to send\n");
            if (event.type == BB_EVENT_ERROR) {
                ErrorMessage(event.param0);
                AgentSetState(AGENT_STATE_END_SCREEN);
                myPlayer.msgtype.type = MESSAGE_ERROR;
            } else if (event.type == BB_EVENT_RESET_BUTTON) {
                AgentInit();
            } else if (event.type == BB_EVENT_MESSAGE_SENT) {
                myPlayer.playerTurns++;
                myPlayer.userGuess = FieldAIDecideGuess(&myPlayer.opponentField);
                myPlayer.msgtype.type = MESSAGE_SHO;
                myPlayer.msgtype.param0 = myPlayer.userGuess.row;
                myPlayer.msgtype.param1 = myPlayer.userGuess.col;
                AgentSetState(AGENT_STATE_ATTACKING);

            } else {
                myPlayer.msgtype.type = MESSAGE_NONE;
            }
            break;
            /**********************************************************
             *AGENT STATE END SCREEN
             ***********************************************************/
        case AGENT_STATE_END_SCREEN:
            //            printf("in end screen\n");
            OledClear(OLED_COLOR_BLACK);
            sprintf(endMessage, "Game Over! Press BTN4 to start new game\n");
            OledUpdate();
            AgentSetState(AGENT_STATE_START);
            break;

    }
    OledClear(OLED_COLOR_BLACK);
    FieldOledDrawScreen(&myPlayer.userField, &myPlayer.opponentField, myPlayer.turn, myPlayer.playerTurns);
    OledUpdate();
    //    printf("returning\n");
    return myPlayer.msgtype;
}

/** * 
 * @return Returns the current state that AgentGetState is in.  
 * 
 * This function is very useful for testing AgentRun.
 */
AgentState AgentGetState(void) { //finished
    return myPlayer.state;
}

/** * 
 * @param Force the agent into the state given by AgentState
 * 
 * This function is very useful for testing AgentRun.
 */
void AgentSetState(AgentState newState) { //finished
    myPlayer.state = newState;
    //    printf("State Switched to: %d",myPlayer.state);
}

void ErrorMessage(uint16_t BB_ERROR) { //finished
    //    
    //    printf("in the error message function\n");

    char* DisplayMessage;
    if (BB_ERROR == BB_ERROR_BAD_CHECKSUM) {
        sprintf(DisplayMessage, "BadChecksum");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(DisplayMessage);
        OledUpdate();
    }

    if (BB_ERROR == BB_ERROR_PAYLOAD_LEN_EXCEEDED) {
        sprintf(DisplayMessage, "PayloadExceeded");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(DisplayMessage);
        OledUpdate();
    }

    if (BB_ERROR == BB_ERROR_CHECKSUM_LEN_EXCEEDED) {
        sprintf(DisplayMessage, "ChecksumLenExceeded");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(DisplayMessage);
        OledUpdate();
    }

    if (BB_ERROR == BB_ERROR_CHECKSUM_LEN_INSUFFICIENT) {
        sprintf(DisplayMessage, "checksumLenInsufficient");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(DisplayMessage);
        OledUpdate();
    }

    if (BB_ERROR == BB_ERROR_INVALID_MESSAGE_TYPE) {
        sprintf(DisplayMessage, "invalidMessage");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(DisplayMessage);
        OledUpdate();
    }

    if (BB_ERROR == BB_ERROR_MESSAGE_PARSE_FAILURE) {
        sprintf(DisplayMessage, "parseFailure");
        OledClear(OLED_COLOR_BLACK);
        OledDrawString(DisplayMessage);
        OledUpdate();
    }
}

