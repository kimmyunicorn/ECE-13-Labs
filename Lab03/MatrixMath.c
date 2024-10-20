/* 
 * File:   MatrixMath.c
 * Author: kimberlycamanero
 *
 * Created on April 19, 2024, 1:46 PM
 */
#define DIM 3
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MatrixMath.h"
#include "BOARD.h"


void MatrixPrint(float mat[3][3]){
    printf("-----------------------------------");
     printf("|\n");
for(int i=0; i<DIM; i++){
        for(int j=0; j<DIM; j++){
//            if(j % 2 == 0){
//                
//            }
            printf("| %lf ", mat[i][j]);
        }
        
        printf("|\n");
        printf("----------------------------------");
                printf("|\n");
    }

}

/*
int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    int i;
    int j;
    float round = 0;
    
    
    for(i=0; i<DIM; i++){
        for(j=0; i<DIM; j++){
            round = mat1[i][j] - mat2[i][j];
            if(round < 0){
                round *= -1;
            }
            if (round > FP_DELTA) {
             
                return 0;
            }
        }
    }
    //return an int
    return 1;
}
*/

int MatrixEquals(float mat1[3][3], float mat2[3][3]) {
    int i, j;
    float roundOffError;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            roundOffError = (mat1[i][j] - mat2[i][j]);


            if (roundOffError < 0) { // to find the abs of the value
                roundOffError = -roundOffError;
                if (roundOffError > FP_DELTA) {
                    return 0; // return false, b/c immediately numbers r !=
                } else {
                    continue; //roundofferror less than FP_DELTA, means the numbers considered ==
                }
            } else { // in the case that the round off is not negative
                if (roundOffError > FP_DELTA) {
                    return 0;
                } else {
                    continue;
                }
            }
        }
    }
    return 1; // b/c all numbers are equal,return true
}


int MatrixEquals2x2(float mat1[2][2], float mat2[2][2])
{
    int i, j;
    float roundOffError;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            roundOffError = (mat1[i][j] - mat2[i][j]);


            if (roundOffError < 0) { // to find the abs of the value
                roundOffError = -roundOffError;
                if (roundOffError > FP_DELTA) {
                    return 0; // return false, b/c immediately numbers r !=
                } else {
                    continue; //roundofferror less than FP_DELTA, means the numbers considered ==
                }
            } else { // in the case that the round off is not negative
                if (roundOffError > FP_DELTA) {
                    return 0;
                } else {
                    continue;
                }
            }
        }
    }
    return 1; // b/c all numbers are equal,return true
}


void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int i;
    int j;
    
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}


void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}


 
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    int i;
    int j;
    
    for(i = 0; i< DIM; i++) {
        for (j = 0; j < DIM; j ++) {
            result[i][j] = mat[i][j] + x;
        }
    }
        
}




void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    int i;
    int j;
    
    for(i = 0; i< DIM; i++) {
        for (j = 0; j < DIM; j ++) {
            result[i][j] = mat[i][j] * x;
        }
    }
        
}


 
float MatrixTrace(float mat[3][3])
{
float trace = 0;

    for (int i = 0; i < 3; i++) {
            trace += mat[i][i];
        }

return trace; 
}




void MatrixTranspose(float mat[3][3], float result[3][3])
{

int t;
    
    
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            t = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = t;
        }
    }
}





void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2]) {
    
    int sub_i = 0, sub_j = 0;
    for (int row = 0; row < 3; row++) {
        if (row == i) // Skip the excluded row
            continue;
        for (int col = 0; col < 3; col++) {
            if (col == j) // Skip the excluded column
                continue;
            result[sub_i][sub_j++] = mat[row][col];
        }
        sub_i++;
        sub_j = 0;
    }
}





float MatrixDeterminant(float mat[3][3]) {
    float determinant = 0;

    for (int i = 0; i < 3; i++) {
        determinant += mat[0][i] * (mat[1][(i + 1) % 3] * mat[2][(i + 2) % 3] - mat[1][(i + 2) % 3] * mat[2][(i + 1) % 3]);
    }

    return determinant;
}






    


float Determinant2x2 (float mat[2][2])
{
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}
// Function to calculate the inverse of a 3x3 matrix
void MatrixInverse(float mat[3][3], float result[3][3]) {
    float det = MatrixDeterminant(mat);
    

    if (det == 0) {
        printf("Matrix is singular, cannot find its inverse.\n");
        return;
    }

    float invDet = 1.0f / det;

    float adj[3][3];

    // Calculate the adj matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            float minor[2][2];
            int mrow = 0, mcol = 0;
            for (int row = 0; row < 3; row++) {
                if (row == i) continue;
                for (int col = 0; col < 3; col++) {
                    if (col == j) continue;
                    minor[mrow][mcol++] = mat[row][col];
                }
                mrow++;
                mcol = 0;
            }
            adj[j][i] = sign * Determinant2x2(minor);
        }
    }

    // Calculate the inverse matrix
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = adj[i][j] * invDet;
        }
    }
}

    
    
    
    

