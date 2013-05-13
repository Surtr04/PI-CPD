#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "papi_errors.h"
#include <papi.h>


int size;

typedef struct mat {
        float** matrixA;
        float** matrixB;
        float** matrixC;
}matrices;


matrices *m;

void showMatrix(float **matrix);
float** transposeMatrix(float** matrix) ;
int dotProduct (float** matrixA, float** matrixB, float** matrixC);
float** initRandMatrix();
float** initMatrix();
float** initUnitMatrix();
float** transposeMatrix(float** matrix);
int dotProduct_papi();
int dotProductTransposed_papi();