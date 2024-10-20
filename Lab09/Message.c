/* 
 * File:   Message.c
 * Author: kimberlycamanero
 *
 * Created on June 3, 2024, 4:05 PM
 */
  

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "BattleBoats.h"
#include "BOARD.h"
#include "Message.h"
/** According to the NMEA standard, messages cannot be longer than 82,
 * including the delimiters $, *, and \n.
 */
//#define MESSAGE_MAX_LEN 82

/** The maximum payload length is the maximum message length,
 * -1 start delimiter ($) <- start delimeter 
 * -1 checksum delimiter (*), <- checksum delimeter 
 * -2 checksum characters,  
 * -1 end delimiter (\n) <- end delimeter 
 */

#define START_DELIMETER '$'
#define END_DELIMETER '\n'
#define CHECKSUM_DELIMETER '*'


typedef enum {
    WAIT_FOR_START,
    RECORD_PAYLOAD,
    RECORD_CHECKSUM,
} DECODERSM;

static DECODERSM state;
static char create_payload_string[MESSAGE_MAX_PAYLOAD_LEN];
static int payload_string_len = 0;
static int create_checksum_len = 0;
static char create_checksum_string[MESSAGE_CHECKSUM_LEN];

static uint8_t payload_argument = 0;

/*

typedef enum {
    MESSAGE_NONE, //used if no message is to be sent
    MESSAGE_CHA,
    MESSAGE_ACC,
    MESSAGE_REV,
    MESSAGE_SHO,
    MESSAGE_RES,

    //while not required, an error message can be a useful debugging tool:
    MESSAGE_ERROR = -1,
} MessageType;
*/

/*
typedef struct {
    MessageType type;
    unsigned int param0;
    unsigned int param1;
    unsigned int param2;
} Message;

*/

/** Message payloads will have the following syntax. 
 * Each (almost*) follows the NMEA0183 syntax for message payloads:  
 *		The first three characters describe the message type
 * 		Zero or more comma-separated fields follow, containing various kinds of data
 *
 * (* true NEMA0183 payloads begin with two characters that describe the "talker", which we 
 *    omit from the BattleBoats protocol)
 */
//#define PAYLOAD_TEMPLATE_CHA "CHA,%u" 		// Challenge message:  		hash_a (see protocol)
//#define PAYLOAD_TEMPLATE_ACC "ACC,%u" 		// Accept message:	 		B (see protocol)
//#define PAYLOAD_TEMPLATE_REV "REV,%u"       // Reveal message: 			A (see protocol)
//#define PAYLOAD_TEMPLATE_SHO "SHO,%d,%d"    // Shot (guess) message: 	row, col
//#define PAYLOAD_TEMPLATE_RES "RES,%u,%u,%u" // Result message: 			row, col, GuessResult


/** 
 * NEMA0183 messages wrap the payload with a start delimiter, 
 * a checksum to verify the contents of   
 * the message in case of transmission errors, and an end delimiter.
 * This template defines the wrapper.
 * Note that it uses printf-style tokens so that it can be used with sprintf().
 * 
 * Here is an example message:
 *                 
 * 1 start delimiter    (a literal $)
 * 2 payload            (any string, represented by %s in the template)
 * 3 checksum delimiter (a literal *)
 * 4 checksum			(two ascii characters representing hex digits, %02x in the template)
 * 5 end delimiter      (a literal \n)
 * 
 * example message:      1       3  5      
 *						 v       v  vv
 *                       $SHO,2,9*5F\n
 *                        ^^^^^^^ ^^      
 *                          2     4      
 * 
 * Note that 2 and 4 correspond to %s and %02x in the template.
 * 
 * Also note that valid BattleBoats messages use 
 * strictly upper-case letters, so $SHO,2,3*5f\n is an invalid message.
 */
//#define MESSAGE_TEMPLATE "$%s*%02X\n"

/**
 * Given a payload string, calculate its checksum
 * 
 * @param payload       //the string whose checksum we wish to calculate
 * @return   //The resulting 8-bit checksum 
 */

uint8_t Message_CalculateChecksum(const char* payload) { //finished
    uint8_t checkSum = 0;

    while (*payload != '\0') {//if payload is not equal to NULL, then
        checkSum ^= *payload; //xor the checksum with the payload 
        payload++; //go through the payload, and increments by 1
    }
    printf("CheckSum: %u\n",checkSum);
    return checkSum; //if it does equal  0, then none of the above happens, and it just returns the checksum
}

/**
 * ParseMessage() converts a message string into a BB_Event.  The payload and
 * checksum of a message are passed into ParseMessage(), and it modifies a
 * BB_Event struct in place to reflect the contents of the message.
 * 
 * @param payload       //the payload of a message
 * @param checksum      //the checksum (in string form) of  a message,
 *                          should be exactly 2 chars long, plus a null char
 * @param message_event //A BB_Event which will be modified by this function.
 *                      //If the message could be parsed successfully,
 *                          message_event's type will correspond to the message type and 
 *                          its parameters will match the message's data fields.
 *                      //If the message could not be parsed,
 *                          message_events type will be BB_EVENT_ERROR
 * 
 * @return STANDARD_ERROR if:
 *              the payload does not match the checksum
 *              the checksum string is not two characters long
 *              the message does not match any message template
 *          SUCCESS otherwise
 * 
 * Please note!  sscanf() has a couple compiler bugs that make it a very
 * unreliable tool for implementing this function. * 
 */
int Message_ParseMessage(const char* payload,const char* checksum_string, BB_Event * message_event) { 
    
    uint8_t testCheckSum = Message_CalculateChecksum(payload);
    uint8_t checkSumConversion = strtoul(checksum_string,NULL,16);
    
    if(testCheckSum != checkSumConversion){
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR;
    }

    

    //checking if the checksum length is lower or greater than the required amount
    //greater than
//    printf("after first if statement\n");
    if (strlen(checksum_string) > MESSAGE_CHECKSUM_LEN) {
        message_event->type = BB_EVENT_ERROR;
        message_event->param0 = BB_ERROR_CHECKSUM_LEN_EXCEEDED;
        return STANDARD_ERROR;
    }
    //less than
    if (strlen(checksum_string) < MESSAGE_CHECKSUM_LEN) {
        message_event->type = BB_EVENT_ERROR;
        message_event->param0 = BB_ERROR_CHECKSUM_LEN_INSUFFICIENT;
        return STANDARD_ERROR;
    }


    //get id from payload

    message_event->param0 = 0;
    message_event->param1 = 0;
    message_event->param2 = 0;


    //make a copy of the payload since i dont want to overide the original payload mssg, and also b/c its a pointer 

    char payload_duplicate[MESSAGE_MAX_PAYLOAD_LEN];
    strcpy(payload_duplicate, payload);
    char *payloadID = strtok(payload_duplicate, ",");
    printf("Payload ID: %s\n",payloadID);
    //-> //"$RES,1,2,3*5A\n"
    if (strcmp(payloadID, "RES") == 0) {
        payload_argument = 3;
        message_event->type = BB_EVENT_RES_RECEIVED;
    } else if (strcmp(payloadID, "CHA") == 0) {
        payload_argument = 1;
        message_event->type = BB_EVENT_CHA_RECEIVED;
    } else if (strcmp(payloadID, "REV") == 0) {
         payload_argument = 1;
        message_event->type = BB_EVENT_REV_RECEIVED;
    } else if (strcmp(payloadID, "SHO") == 0) {
       payload_argument = 2;
        message_event->type = BB_EVENT_SHO_RECEIVED;
    } else if (strcmp(payloadID, "ACC") == 0) {
        payload_argument = 1;
        message_event->type = BB_EVENT_ACC_RECEIVED;
    } else {
        message_event->type = BB_EVENT_ERROR;
        message_event->param0 = BB_ERROR_INVALID_MESSAGE_TYPE;
        return STANDARD_ERROR;
    }

    //parsing the rest of the tokens in the payload id
    //your mom ur mom ur mom ur mom


    for(int i = 0; i < payload_argument; i++) {
        payloadID = strtok(NULL, ",");
        if (payloadID) {
            if (i == 0) {
                message_event->param0 = atoi(payloadID);
            }
            if (i == 1) {
                message_event->param1 = atoi(payloadID);
            }
            if (i == 2) {
                message_event->param2 = atoi(payloadID);
            }
        }
    }
    payloadID = strtok(NULL, "");
    if (payloadID) {
        message_event->type = BB_EVENT_ERROR;
        return STANDARD_ERROR;
    }
    return SUCCESS;
}

/**
 * Encodes the coordinate data for a guess into the string `message`. This string must be big
 * enough to contain all of the necessary data. The format is specified in PAYLOAD_TEMPLATE_COO,
 * which is then wrapped within the message as defined by MESSAGE_TEMPLATE. 
 * 
 * The final length of this
 * message is then returned. There is no failure mode for this function as there is no checking
 * for NULL pointers.
 * 
 * @param message            The character array used for storing the output. 
 *                              Must be long enough to store the entire string,
 *                              see MESSAGE_MAX_LEN.
 * @param message_to_encode  A message to encode
 * @return                   The length of the string stored into 'message_string'.
                             Return 0 if message type is MESSAGE_NONE.
 */
int Message_Encode(char *message_string, Message message_to_encode){
  
   char payloadMessage[MESSAGE_MAX_PAYLOAD_LEN];
   char messageStringCopy[MESSAGE_MAX_LEN];
   
   if(message_to_encode.type == MESSAGE_RES){
       printf("message res\n");
       sprintf(payloadMessage, PAYLOAD_TEMPLATE_RES, message_to_encode.param0, message_to_encode.param1, message_to_encode.param2);
       sprintf(messageStringCopy, MESSAGE_TEMPLATE, payloadMessage, Message_CalculateChecksum(payloadMessage));
       strcpy(message_string, messageStringCopy);
       printf("Length: %d\n",strlen(message_string));
  
   }else if(message_to_encode.type == MESSAGE_ACC){
       sprintf(payloadMessage, PAYLOAD_TEMPLATE_ACC, message_to_encode.param0);
       sprintf(messageStringCopy, MESSAGE_TEMPLATE, payloadMessage, Message_CalculateChecksum(payloadMessage));
       strcpy(message_string, messageStringCopy);
        printf("Length: %d\n",strlen(message_string));
 
   }else if(message_to_encode.type == MESSAGE_CHA){
       sprintf(payloadMessage, PAYLOAD_TEMPLATE_CHA, message_to_encode.param0);
       sprintf(messageStringCopy, MESSAGE_TEMPLATE, payloadMessage, Message_CalculateChecksum(payloadMessage));
       strcpy(message_string, messageStringCopy);
       printf("Length: %d\n",strlen(message_string));
   }else if(message_to_encode.type == MESSAGE_REV){
       sprintf(payloadMessage, PAYLOAD_TEMPLATE_REV, message_to_encode.param0);
       sprintf(messageStringCopy, MESSAGE_TEMPLATE, payloadMessage, Message_CalculateChecksum(payloadMessage));
       strcpy(message_string, messageStringCopy);
        printf("Length: %d\n",strlen(message_string));
   }else if (message_to_encode.type == MESSAGE_SHO){
       sprintf(payloadMessage, PAYLOAD_TEMPLATE_SHO, message_to_encode.param0, message_to_encode.param1);
       sprintf(messageStringCopy, MESSAGE_TEMPLATE, payloadMessage, Message_CalculateChecksum(payloadMessage));
       strcpy(message_string, messageStringCopy);
        printf("Length: %d\n",strlen(message_string));
   }
   else{
       return 0;//in the case that the message is none
      
   }
    printf("Length: %d\n",strlen(message_string));
   return strlen(message_string);  
   
}




/**
 * Message_Decode reads one character at a time.  If it detects a full NMEA message,
 * it translates that message into a BB_Event struct, which can be passed to other 
 * services.
 * 
 * @param char_in - The next character in the NMEA0183 message to be decoded.
 * @param decoded_message - a pointer to a message struct, used to "return" a message
 *                          if char_in is the last character of a valid message, 
 *                              then decoded_message
 *                              should have the appropriate message type.
 *                          if char_in is the last character of an invalid message,
 *                              then decoded_message should have an ERROR type.
 *                          otherwise, it should have type NO_EVENT.
 * @return SUCCESS if no error was detected
 *         STANDARD_ERROR if an error was detected
 * 
 * note that ANY call to Message_Decode may modify decoded_message.
 */
int Message_Decode(unsigned char char_in, BB_Event * decoded_message_event) { //finished
    /*
        typedef enum {
        WAIT_FOR_START,
        RECORD_PAYLOAD,
        RECORD_CHECKSUM,
    } DECODERSM; */

    switch (state) {
        case WAIT_FOR_START:
            if (char_in == START_DELIMETER) {
                state = RECORD_PAYLOAD;
                decoded_message_event->type = BB_EVENT_NO_EVENT;
                return SUCCESS;
            } else {
                decoded_message_event->type = BB_EVENT_ERROR;
                decoded_message_event->param0 = BB_ERROR_INVALID_MESSAGE_TYPE;
                return STANDARD_ERROR;
            }
            break;




//---------------------------------------------------------------------------------------------------------------------------            


        case RECORD_PAYLOAD:
            if (char_in == END_DELIMETER) {
                state = WAIT_FOR_START;
                decoded_message_event->type = BB_ERROR_INVALID_MESSAGE_TYPE;
                return STANDARD_ERROR;
            }

            if (char_in == START_DELIMETER) {
                state = WAIT_FOR_START;
                decoded_message_event->type = BB_ERROR_INVALID_MESSAGE_TYPE;
                return STANDARD_ERROR;
            }
            
            if (char_in == CHECKSUM_DELIMETER) {
                decoded_message_event->type = BB_EVENT_NO_EVENT;
                create_payload_string[payload_string_len] = '\0';
                state = RECORD_CHECKSUM;
                payload_string_len = 0;
                return SUCCESS;
            } else if (payload_string_len > MESSAGE_MAX_PAYLOAD_LEN) {
                state = WAIT_FOR_START;
                decoded_message_event->type = BB_EVENT_ERROR;
                decoded_message_event->param0 = BB_ERROR_PAYLOAD_LEN_EXCEEDED;
                payload_string_len = 0;
                return STANDARD_ERROR;
            } else {
                decoded_message_event->type = BB_EVENT_NO_EVENT;
                create_payload_string[payload_string_len] = char_in;
                payload_string_len++;
            }
            break;

//----------------------------------------------------------------------------------------------------------------------------- 


        case RECORD_CHECKSUM:
            if (create_checksum_len > MESSAGE_CHECKSUM_LEN) {
                create_checksum_len = 0;
                decoded_message_event->type = BB_EVENT_ERROR;
                decoded_message_event->param0 = BB_ERROR_CHECKSUM_LEN_EXCEEDED;
                state = WAIT_FOR_START;
                return STANDARD_ERROR;
            } else if (char_in >= 65 && char_in <= 70 || char_in >= 48 && char_in <= 57) { //checking for valid letters, and valid numbers to make sure I don't get any weird symbols :(
                decoded_message_event->type = BB_EVENT_NO_EVENT;
                create_checksum_string[create_checksum_len] = char_in;
                create_checksum_len++;
                return SUCCESS;
            } else if (char_in == END_DELIMETER) {
                if (create_checksum_len < MESSAGE_CHECKSUM_LEN) {
                    decoded_message_event->type = BB_EVENT_ERROR;
                    decoded_message_event->param0 = BB_ERROR_CHECKSUM_LEN_INSUFFICIENT;
                    state = WAIT_FOR_START;
                    return STANDARD_ERROR;
                } else {
                    create_checksum_string[create_checksum_len] = '\0';
                    create_checksum_len = 0;
                    int parseReturnValue = Message_ParseMessage(create_payload_string, create_checksum_string, decoded_message_event);
                    if (parseReturnValue == STANDARD_ERROR) {
                        decoded_message_event->type = BB_EVENT_ERROR;
                        decoded_message_event->param0 = BB_ERROR_MESSAGE_PARSE_FAILURE;
                        state = WAIT_FOR_START;
                        return STANDARD_ERROR;
                    }
                    state = WAIT_FOR_START;
                }
            }else{
                    decoded_message_event->type = BB_EVENT_NO_EVENT;
                    create_payload_string [create_checksum_len]= char_in;
                    create_checksum_len++;
                }
                break;


            }
              return SUCCESS;
    }

          





  


