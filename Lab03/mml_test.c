#include <stdio.h>
#define FP_DELTA 0.0001
#define DIM 3 
#include <math.h>
#include "MatrixMath.h"
//use the DIM instead of 3 in all of ur functions ?

int MatrixEquals2x2(float mat1[2][2], float mat2[2][2]);
// main function
int main(void) {
  
  //defining result matrices to keep track of results from the operations
  float result[3][3];
  float result2[2][2];
  float percent;



  //defining the different test matrices 

 
  float testmatrix00[3][3] = {{7.7867,7.0,4.8},
                              {7.9,-4.1,9.3},
                              {1.2,8.4,-3.0}}; 
  
  float testmatrix01[3][3] = {{7.7866,7.0,4.8},
                              {7.9,-4.1,9.3},
                              {1.2,8.4,0.2}};

  float testmatrix02[3][3] = {{42.8,-4.1,-100.222},
                              {363.4,-323.4,-344.3},
                              {44.3,-23.5353,-92.1}};

  float testmatrix03[3][3] = {{-1.8,8.0,2.5},
                              {4.6,-4.1,9.3},
                              {7.9,9.9,-9.0}}; 

  float testmatrix04[3][3] =  {{-1.8,8.0,2.5},
                              {4.6,-4.1,9.3},
                              {7.9,9.9,-9.0}}; //same as matrix03
  //float zeromatrix[3][3]= {{},{},{}};

  int totalPassed=10,localPassed = 0;
  int matrix_equals =0;


  //Check MatrixEquals functions passed
  if(!MatrixEquals(testmatrix00,testmatrix01)){ // Check to make sure equals fails
    matrix_equals += 1; //passed the 1st test case increment it
    
  }
  if(MatrixEquals(testmatrix03,testmatrix04) == 1){
      matrix_equals +=1; // passed the 2nd test case increment it
  } 
  if(matrix_equals != 2){
    totalPassed -=1;
  }
  printf("PASSED (%d/2): MatrixEquals()\n",matrix_equals);

//FOR EACH FUNCTION, U GET THE EXPECTED OUTPUT FROM RUNNING UR FUNCTION ON THE MATRIX
//SO MAKE SURE TO TAKE NOTE OF THAT OUTPUT

  //Check MatrixAdd functions passed
  //expected matrices
  float expectedAdd1[3][3] = {{50.586601,2.900000,-95.421997},
                              {371.299988,-327.500000,-335.000000}, //result of matrix02 + matrix01
                              {45.500000,-15.135300,-91.900002}}; 
  

  float expectedAdd2[3][3] = {{50.586700,2.900000,-95.421997}, //result of matrix00 + matrix02
                                {371.299988,-327.500000,-335.000000},    
                               {45.500000,-15.135300,-95.099998}}; 

  MatrixAdd(testmatrix02,testmatrix01,result);//call the function to get result matrix
  //MatrixPrint(result);
  if(MatrixEquals(result,expectedAdd1)==1){
    localPassed+=1;
    
  }
  MatrixAdd(testmatrix00,testmatrix02,result);
  //MatrixPrint(result);
  if(MatrixEquals(result,expectedAdd2)==1){
    localPassed+=1;
  }
  if(localPassed == 2){
    printf("PASSED (%d/2): MatrixAdd()\n",localPassed); //should be 2/2
    localPassed = 0; //reset counter to 0
  }else if (localPassed != 2){ //in case 0/2 or 1/2 cases didnt pass
    printf("PASSED (%d/2): MatrixAdd()\n",localPassed);
    totalPassed-=1;
    localPassed = 0;
  }


  //Check MatrixMultiply functions passed 
  float expectedMul1[3][3] = {{56.103943,81.113594,41.366749},
                                {40.390003,172.080002,-102.080002},    //result of matrix00 x matrix03
                              {12.779995,-54.539993,108.119995}}; 
  float expectedMul2[3][3] = {{52.183941,-24.399998,58.260002}, //result of matrix03 x matrix00
                              {14.588819,127.129997,-43.950001},
                              {128.924927,-60.889996,156.990005}}; 
  MatrixMultiply(testmatrix00,testmatrix03,result); 
  //MatrixPrint(result);
  if(MatrixEquals(result,expectedMul1)==1){
    localPassed+=1;
  }
  MatrixMultiply(testmatrix03,testmatrix00,result);
  //MatrixPrint(result);
  if(MatrixEquals(result,expectedMul2)==1){
    localPassed+=1;
  }
  if(localPassed == 2){
    printf("PASSED (%d/2): MatrixMultiply()\n",localPassed); //should b 2/2
    localPassed = 0; //reset counter to 0
  }else if (localPassed != 2){ //in case 0/2 or 1/2 cases didnt pass
    printf("PASSED (%d/2): MatrixMultiply()\n",localPassed);
    totalPassed-=1;
    localPassed = 0;
  }


  //Check MatrixScalarAdd functions passed 
  float expectedScAdd1[3][3] = {{11.1867,10.4,8.2},
                                  {11.3,-0.7,12.7},
                                  {4.6,11.8,0.4}}; //result of 3.4 + matrix00,result
  float expectedScAdd2[3][3] = {{5.7766,4.99,2.79},
                                  {5.89,-6.11,7.29},
                                    {-0.81,6.39,-1.81}}; //result of -2.01 + matrix01,result

  MatrixScalarAdd(3.4,testmatrix00,result);
  if(MatrixEquals(result,expectedScAdd1)==1){
    localPassed+=1;
  }
  MatrixScalarAdd(-2.01,testmatrix01,result);
  if(MatrixEquals(result,expectedScAdd2)==1){
    localPassed+=1;
  }
  if(localPassed == 2){
    printf("PASSED (%d/2): MatrixScalarAdd()\n",localPassed); //should b 2/2
    localPassed = 0; //reset counter to 0
  }else if (localPassed != 2){ //in case 0/2 or 1/2 cases didnt pass
    printf("PASSED (%d/2): MatrixScalarAdd()\n",localPassed);
    totalPassed-=1;
    localPassed = 0;
  }

  //Check MatrixScalarMultiply
  float expectedScMul1[3][3] = {{24.917120,22.400000,15.360001},
                                {25.280001,-13.120000,29.760000},
                                {3.840000,26.879999,0.640000}}; //result of 3.9 x matrix01,result
  float expectedScMul2[3][3] = {{-21.400000,2.050000,50.111000},
                                {-181.699997,161.699997,172.149994},
                                {-22.150000,11.767650,46.049999}}; // result of -0.6 x matrix02,result

  MatrixScalarMultiply(3.2,testmatrix01,result);
  //MatrixPrint(result);
  if(MatrixEquals(result,expectedScMul1)==1){
    localPassed+=1;
  }
  MatrixScalarMultiply(-0.5,testmatrix02,result);
  //MatrixPrint(result);
    if(MatrixEquals(result,expectedScMul2)==1){
      localPassed+=1;
    }
  if(localPassed == 2){
    printf("PASSED (%d/2): MatrixScalarMultiply()\n",localPassed); //should b 2/2
    localPassed = 0; //reset counter to 0
  }else if (localPassed != 2){ //in case 0/2 or 1/2 cases didnt pass
    printf("PASSED (%d/2): MatrixScalarMultiply()\n",localPassed);
    totalPassed-=1;
    localPassed = 0;
  }

  //Check MatrixTrace functions passed
  //returns a single float val
  float expectedTrace1= 3.886600; //result of trace on matrix01 
  //float expectedTrace2= -10.958400; //result of trace on matrix00 

  MatrixTrace(testmatrix01);
  //MatrixPrint(result);
  if(fabs(MatrixTrace(testmatrix01)-expectedTrace1)<FP_DELTA){ //to account for roundofferror
    localPassed+=1;
  }
  MatrixTrace(testmatrix00); 
  //MatrixPrint(result);
  if(fabs(MatrixTrace(testmatrix01)-expectedTrace1)<FP_DELTA){//account for roundofferror
    localPassed+=1;
  }

  if(localPassed == 2){
    printf("PASSED (%d/2): MatrixTrace()\n",localPassed); //should b 2/2
    localPassed = 0; //reset counter to 0
  }else if (localPassed != 2){ //in case 0/2 or 1/2 cases didnt pass
    printf("PASSED (%d/2): MatrixTrace()\n",localPassed);
    totalPassed-=1;
    localPassed = 0;
  }


  //Check MatrixTranspose functions passed
  float expectedTrans1[3][3] = {{-21.400000,2.050000,50.111000},
                                {-181.699997,161.699997,172.149994},
                                {-22.150000,11.767650,46.049999}}; //result of matrix00 transposed
  float expectedTrans2[3][3] =  {{-21.400000,2.050000,50.111000},
                                {-181.699997,161.699997,172.149994},
                                {-22.150000,11.767650,46.049999}};//result of matrix02 transposed

  MatrixTranspose(testmatrix00,result);
  
  if(MatrixEquals(result,expectedTrans1)==1){ 
    localPassed +=1;
  }
  MatrixTranspose(testmatrix02,result);
  
  if(MatrixEquals(result,expectedTrans2)==1){ 
    localPassed+=1;
  }
  if(localPassed == 2){
    printf("PASSED (%d/2): MatrixTranspose()\n",localPassed); //should b 2/2
    localPassed = 0; //reset counter to 0
  }else if (localPassed != 2){ //in case 0/2 or 1/2 cases didnt pass
    printf("PASSED (%d/2): MatrixTranspose()\n",localPassed);
    totalPassed-=1;
    localPassed = 0;
  }

  //Check MatrixSubmatrix functions passed 
  float expectedSub1[2][2] = {{42.800000,-100.222000},
                              {44.300000,-92.100000}};//result of 1,1 matrix02,result2

  float expectedSub2[2][2] = {{7.786600,7.000000},
                              {1.200000,8.400000}};//result of 1,2 matrix01,result2

  MatrixSubmatrix(1,1,testmatrix02,result2); 
  //MatrixPrint(result);
  if(MatrixEquals2x2(result2,expectedSub1)==1){//copy n paste all of ur matrix equality out here
    localPassed+=1;
  }
  MatrixSubmatrix(1,2,testmatrix01,result2);
  //MatrixPrint(result);
  if(MatrixEquals2x2(result2,expectedSub2)==1){
    localPassed+=1;
  }
  if(localPassed == 2){
    printf("PASSED (%d/2): MatrixSubmatrix()\n",localPassed); //should b 2/2
    localPassed = 0; //reset counter to 0
  }else if (localPassed != 2){ //in case 0/2 or 1/2 cases didnt pass
    printf("PASSED (%d/2): MatrixSubmatrix()\n",localPassed);
    totalPassed-=1;
    localPassed = 0;
  }

  //Check MatrixDeterminant functions passed MAKE SURE TO ACCOUNT FOR ROUND OFF ERROR
  float expectedDeterm1 = 1213.091; //result of determinant on matrix03
  float expectedDeterm2 = -205.470204; //result of determinant on matrix01

  MatrixDeterminant(testmatrix03);
  
  if(fabs(MatrixDeterminant(testmatrix03)-expectedDeterm1) < FP_DELTA){
    localPassed+=1;
  }
  MatrixDeterminant(testmatrix01);
  
  if(fabs(MatrixDeterminant(testmatrix01)-expectedDeterm2) < FP_DELTA){
    localPassed+=1;
  }
  if(localPassed == 2){
    printf("PASSED (%d/2): MatrixDeterminant()\n",localPassed); //should b 2/2
    localPassed = 0; //reset counter to 0
  }else if (localPassed != 2){ //in case 0/2 or 1/2 cases didnt pass
    printf("PASSED (%d/2): MatrixDeterminant()\n",localPassed);
    totalPassed-=1;
    localPassed = 0;
  }

  //Check MatrixInverse 
  float expectedInverse1[3][3] = {{-0.893766,0.832661,1.121223},
                                  {0.473362,-0.395420,-0.468424},
                                  {0.967907,-0.774112,-1.184430}}; //result of matrix00 inverse
  float expectedInverse2[3][3] = {{},{},{}}; //result of matrix02 inverse

  MatrixInverse(testmatrix00,result);
  //MatrixPrint(result);
  if(MatrixEquals(result,expectedInverse1)==1){
    localPassed+=1;
  }
  MatrixInverse(testmatrix02,result);
  //MatrixPrint(result);
  if(MatrixEquals(result,expectedInverse2)==1){
    localPassed+=1;
  }
  if(localPassed == 2){
    printf("PASSED (%d/2): MatrixInverse()\n",localPassed); //should b 2/2
    localPassed = 0; //reset counter to 0
  }else if (localPassed != 2){ //in case 0/2 or 1/2 cases didnt pass
    printf("PASSED (%d/2): MatrixInverse()\n",localPassed);
    totalPassed-=1;
    localPassed = 0;
  }
  percent = (((float)totalPassed/10)*100);
  printf("-----------------------------------------\n");
  printf("%d out of 10 functions passed (%.2f%%)\n",totalPassed,percent);
  printf("\n");
  printf("Output of MatrixPrint():\n");
  MatrixPrint(testmatrix01);
  printf("\n");
  printf("Expected output of MatrixPrint():\n");
  MatrixPrint(testmatrix01);
  return 0;
}


//function definitions should go below this comment
