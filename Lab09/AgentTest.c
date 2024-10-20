/* 
 * File:   AgentTest.c
 * Author: kimberlycamanero
 *
 * Created on June 3, 2024, 4:03 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "Agent.h"
#include "BattleBoats.h"

/*
 * 
 */

 
int main() {
    int total_tests_passed = 0;
   
    
    
/**********************************************************
*AgentInit()
***********************************************************/
          
   printf("AgentInit()Test\n");
   AgentInit();
   if(AgentGetState() == AGENT_STATE_START){
       total_tests_passed++;
   }else{
       printf("AgentInit() failed!\n");
   }
   printf("%d/%d Tests Passed for AgentInit()\n",total_tests_passed,1);
   printf("\n");
   total_tests_passed = 0;
    

/**********************************************************
*AgentSetState() and AgentGetState()
***********************************************************/
    
    
    printf("Test: AgentSetState()\n");
    printf("Test: AgentGetState()\n");
    
    AgentSetState(AGENT_STATE_START);
    if(AgentGetState() == AGENT_STATE_START){
        printf("SUCESS: State is set to AGENT_STATE_START\n");
        total_tests_passed++;
    }else{
        printf("Failed\n");
    }
    
     AgentSetState(AGENT_STATE_ACCEPTING);
    if(AgentGetState() == AGENT_STATE_ACCEPTING){
        printf("SUCESS: State is set to AGENT_STATE_ACCEPTING\n");
        total_tests_passed++;
    }else{
        printf("Failed\n");
    }
    
      AgentSetState(AGENT_STATE_CHALLENGING);
    if(AgentGetState() == AGENT_STATE_CHALLENGING){
        printf("SUCESS: State is set to AGENT_STATE_CHALLENGING\n");
        total_tests_passed++;
    }else{
        printf("Failed\n");
    }
    
       AgentSetState(AGENT_STATE_ATTACKING);
    if(AgentGetState() == AGENT_STATE_ATTACKING){
        printf("SUCESS: State is set to AGENT_STATE_ATTACKING\n");
        total_tests_passed++;
    }else{
        printf("Failed\n");
    }
    
        AgentSetState(AGENT_STATE_DEFENDING);
    if(AgentGetState() == AGENT_STATE_DEFENDING){
        printf("SUCESS: State is set to AGENT_STATE_DEFENDING\n");
        total_tests_passed++;
    }else{
        printf("Failed\n");
    }
    
         AgentSetState(AGENT_STATE_WAITING_TO_SEND);
    if(AgentGetState() == AGENT_STATE_WAITING_TO_SEND){
        printf("SUCESS: State is set to AGENT_STATE_WAITING_TO_SEND\n");
        total_tests_passed++;
    }else{
        printf("Failed\n");
    }
    
          AgentSetState(AGENT_STATE_END_SCREEN);
    if(AgentGetState() == AGENT_STATE_END_SCREEN){
        printf("SUCESS: State is set to AGENT_STATE_END_SCREEN\n");
        total_tests_passed++;
    }else{
        printf("Failed\n");
    }

          printf("%d/%d Tests passed for AgentSetState() & AgentGetState()\n",total_tests_passed,7);
          printf("\n");
          total_tests_passed = 0;
          
    
/**********************************************************
*AgentRun()
***********************************************************/
          printf("Testing AgentRun()\n");
          AgentSetState(AGENT_STATE_START);
          printf("Set the state\n");
          BB_Event testRunAgent;
          testRunAgent.type = BB_EVENT_START_BUTTON;
          printf("Before AgentRun()\n");
          AgentRun(testRunAgent);
          if(AgentGetState() == AGENT_STATE_CHALLENGING){
              printf("Agent Run Successful\n");
              total_tests_passed++;
          }else{
              printf("Agent Run didnt properly run\n");
          }     
}

