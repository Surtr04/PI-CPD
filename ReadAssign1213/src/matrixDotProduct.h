#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma once

#define SIZE 10

#include "matrixDotProduct.h"


void showMatrix(float **matrix);
float** transposeMatrix(float** matrix) ;
int dotProduct (float** matrixA, float** matrixB, float** matrixC);
float** initRandMatrix();
float** initMatrix();
float** initUnitMatrix();
float** transposeMatrix(float** matrix);