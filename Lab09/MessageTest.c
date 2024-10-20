/* 
 * File:   MessageTest.c
 * Author: kimberlycamanero
 *
 * Created on June 3, 2024, 4:04 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Message.h"
#include "BattleBoats.h"
#include "BOARD.h"
/*
 * 
 */
int main() {
    int total_tests_passed = 0;

    printf("----------------------------------------\n");
    printf("CheckSum Test:\n");

    char* checkSum_CHA = "CHA,0417"; //0x64
    char* checkSum_SHO = "SHO,0,1"; //0x55
    char* checkSum_ACC = "ACC,1116"; //0x6A
    char* checkSum_RES = "RES,1,2,3"; //0x58
    char* checkSum_REV = "REV,2004"; //0x6B

    uint8_t expectedCHA = 0x64;
    uint8_t expectedSHO = 0x55;
    uint8_t expectedACC = 0x6A;
    uint8_t expectedRES = 0x58;
    uint8_t expectedREV = 0x6B;

    uint8_t CalculatedCheckSum = Message_CalculateChecksum(checkSum_CHA);
    if (CalculatedCheckSum == expectedCHA) {
        printf("PASSED!\n");
        total_tests_passed++;
    } else {
        printf("FAILED.\n");
    }

    CalculatedCheckSum = Message_CalculateChecksum(checkSum_SHO);
    if (CalculatedCheckSum == expectedSHO) {
        printf("PASSED!\n");
        total_tests_passed++;
    } else {
        printf("FAILED.\n");
    }

    CalculatedCheckSum = Message_CalculateChecksum(checkSum_ACC);
    if (CalculatedCheckSum == expectedACC) {
        printf("PASSED!\n");
        total_tests_passed++;
    } else {
        printf("FAILED.\n");
    }

    CalculatedCheckSum = Message_CalculateChecksum(checkSum_RES);
    if (CalculatedCheckSum == expectedRES) {
        printf("PASSED!\n");
        total_tests_passed++;
    } else {
        printf("FAILED.\n");
    }

    CalculatedCheckSum = Message_CalculateChecksum(checkSum_REV);
    if (CalculatedCheckSum == expectedREV) {
        printf("PASSED!\n");
        total_tests_passed++;
    } else {
        printf("FAILED.\n");
    }

    printf("(%d/%d) TESTS PASSED FOR CHECKSUM", total_tests_passed, 5);
    printf("\n");
    total_tests_passed = 0;
    printf("----------------------------------------\n");





    //testing message parse message
    BB_Event message_type_event;
    printf("Message Parse Message Test:\n");
    
    char *test_payload = "CHA,0417";
    char *payloadChecksum = "64";
//    printf("calling function\n");
    uint8_t *messageParseCalculation = (uint8_t *)Message_ParseMessage(test_payload, payloadChecksum, &message_type_event);

    if (messageParseCalculation && message_type_event.type == BB_EVENT_CHA_RECEIVED) {
        printf("CHA PASSED!\n");
        total_tests_passed++;

    } else {
        printf("CHA FAILED.\n");
    }

    test_payload = "SHO,0,1";
    payloadChecksum = "55";
    messageParseCalculation = (uint8_t *)Message_ParseMessage(test_payload, payloadChecksum, &message_type_event);

    if (messageParseCalculation && message_type_event.type == BB_EVENT_SHO_RECEIVED) {
        printf("SHO PASSED!\n");
        total_tests_passed++;

    } else {
        printf("SHO FAILED.\n");
    }

    test_payload = "ACC,1116";
    payloadChecksum = "6A";
    messageParseCalculation = (uint8_t *)Message_ParseMessage(test_payload, payloadChecksum, &message_type_event);

    if (messageParseCalculation && message_type_event.type == BB_EVENT_ACC_RECEIVED) {
        printf("ACC PASSED!\n");
        total_tests_passed++;

    } else {
        printf("ACC FAILED.\n");
    }

    test_payload = "RES,1,2,3";
    payloadChecksum = "58";
    messageParseCalculation = (uint8_t *)Message_ParseMessage(test_payload, payloadChecksum, &message_type_event);

    if (messageParseCalculation && message_type_event.type == BB_EVENT_RES_RECEIVED) {
        printf("RES PASSED!\n");
        total_tests_passed++;

    } else {
        printf("Message Parse Calculation: %u",messageParseCalculation);
        printf("RES FAILED.\n");
    }

    test_payload = "REV,2004";
    payloadChecksum = "6B";
    messageParseCalculation = (uint8_t *)Message_ParseMessage(test_payload, payloadChecksum, &message_type_event);

    if (messageParseCalculation && message_type_event.type == BB_EVENT_REV_RECEIVED) {
        printf(" REV PASSED!\n");
        total_tests_passed++;

    } else {
        printf("REV FAILED.\n");
    }

    printf("(%d/%d) TESTS PASSED FOR PARSE MESSAGE", total_tests_passed, 5);
    printf("\n");
    total_tests_passed = 0;
    printf("----------------------------------------\n");

    //testing message decode
    printf("Message Decode Test: \n");
    BB_Event DecoderEvents;
    char* DecodeString;
    DecodeString = "$CHA,1417*65\n";

    for (int i = 0; i < strlen(DecodeString); i++) {
        Message_Decode(DecodeString[i], &DecoderEvents);
    }
    if (DecoderEvents.type == BB_EVENT_CHA_RECEIVED && DecoderEvents.param0 == 1417) {
        printf("PASSED!\n");
        total_tests_passed++;
    }
    else{
        printf("Param0: %u ",DecoderEvents.param0);
        printf("FAILED.\n");
    }
    
    DecodeString = "$SHO,0,1*55\n";

    for (int i = 0; i < strlen(DecodeString); i++) {
        Message_Decode(DecodeString[i], &DecoderEvents);
    }
    if (DecoderEvents.type == BB_EVENT_SHO_RECEIVED && DecoderEvents.param0 == 0 && DecoderEvents.param1 == 1) {
        printf("PASSED!");
        total_tests_passed++;
    }
    else{
        printf("FAILED.\n");
    }
    
    DecodeString = "$ACC,1116*6A\n";

    for (int i = 0; i < strlen(DecodeString); i++) {
        Message_Decode(DecodeString[i], &DecoderEvents);
    }
    if (DecoderEvents.type == BB_EVENT_ACC_RECEIVED && DecoderEvents.param0 == 1116) {
        printf("PASSED!\n");
        total_tests_passed++;
    }
    else{
        printf("FAILED.");
    }
    
    DecodeString = "$RES,1,2,3*58\n";

    for (int i = 0; i < strlen(DecodeString); i++) {
        Message_Decode(DecodeString[i], &DecoderEvents);
    }
    if (DecoderEvents.type == BB_EVENT_RES_RECEIVED && DecoderEvents.param0 == 1 && DecoderEvents.param1 == 2 && DecoderEvents.param2 == 3) {
        printf("PASSED!\n");
        total_tests_passed++;
    }
    else{
        printf("FAILED.\n");
        
    }
    
    DecodeString = "$REV,2004*6B\n";

    for (int i = 0; i < strlen(DecodeString); i++) {
        Message_Decode(DecodeString[i], &DecoderEvents);
    }
    if (DecoderEvents.type == BB_EVENT_REV_RECEIVED && DecoderEvents.param0 == 2004) {
        printf("PASSED!\n");
        total_tests_passed++;
    }
    else{
        printf("FAILED.\n");
    }
    
    DecodeString = "$REV,2004*6A\n";

    for (int i = 0; i < strlen(DecodeString); i++) {
        Message_Decode(DecodeString[i], &DecoderEvents);
    }
    if (DecoderEvents.type == BB_EVENT_ERROR && DecoderEvents.param0 == BB_ERROR_INVALID_MESSAGE_TYPE) {
        printf("PASSED!\n");
    }
    else{
        total_tests_passed++; //since it detected there was an invalid message type error 
        printf("FAILED.\n");
    }
    
    
    printf("(%d/%d) TESTS PASSED FOR DECODE MESSAGE", total_tests_passed, 6);
    total_tests_passed = 0;
    printf("\n");
    printf("----------------------------------------\n");
    
//testing message encode
    printf("Message Encode Test: \n");
    char EncodedMessage[MESSAGE_MAX_LEN];
    Message message_encoded;
    message_encoded.type = MESSAGE_CHA;
    message_encoded.param0 = 1417;
    Message_Encode(EncodedMessage, message_encoded);
    
    if(strcmp(EncodedMessage, "$CHA,1417*65\n")==0 ){ //0x65
        printf("PASSED! \n");
        total_tests_passed++;
    }
    else{
        printf("FAILED. \n");
    }
    
    
    
    
    
    message_encoded.type = MESSAGE_SHO;
    message_encoded.param0 = 0;
    message_encoded.param1 = 1;
    Message_Encode(EncodedMessage, message_encoded);
    if(strcmp(EncodedMessage, "$SHO,0,1*55\n")==0 ){
        printf("PASSED! \n");
        total_tests_passed++;
    }
    else{
        printf("FAILED. \n");
    }
    
    
    message_encoded.type = MESSAGE_ACC;
    message_encoded.param0 = 1116;
    Message_Encode(EncodedMessage, message_encoded);
    if(strcmp(EncodedMessage, "$ACC,1116*6A\n")==0 ){
        printf("PASSED! \n");
        total_tests_passed++;
    }
    else{
        printf("FAILED. \n");
    }
    
    
    
    message_encoded.type = MESSAGE_RES;
    message_encoded.param0 = 1;
    message_encoded.param1 = 2;
    message_encoded.param2 = 3;
    Message_Encode(EncodedMessage, message_encoded);
    if(strcmp(EncodedMessage, "$RES,1,2,3*58\n")==0 ){
        printf("PASSED! \n");
        total_tests_passed++;
    }
    else{
        printf("FAILED. \n");
    }
    
    
    
    message_encoded.type = MESSAGE_REV;
    message_encoded.param0 = 2004;   
    Message_Encode(EncodedMessage, message_encoded);
    if(strcmp(EncodedMessage, "$REV,2004*6B\n")==0 ){
        printf("PASSED! \n");
        total_tests_passed++;
    }
    else{
        printf("FAILED. \n");
    }
    
    printf("(%d/%d) TESTS PASSED FOR MESSAGE ENCODE", total_tests_passed, 5);
    total_tests_passed = 0;


    return 0;
}

