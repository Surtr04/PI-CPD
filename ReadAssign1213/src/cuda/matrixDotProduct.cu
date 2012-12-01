#include <cuda.h>
#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__global__ void dotProduct( float* matrixA, float* matrixB, float* matrixC, int n) {
 
   int j = blockIdx.x * blockDim.x + threadIdx.x;
   int i = blockIdx.y * blockDim.y + threadIdx.y;
      
   float value = 0;
   int k;
   for (k = 0; k < n; k++) {  	    	 
      value += matrixA[i * n + k] * matrixB[k * n + j];           
   }  

   matrixC[i * n + j] = value;
}


int main() {
	
	int size = 20;
	//host
	float *matrixA = (float*) malloc(size * size * sizeof(float));
	float *matrixB = (float*) malloc(size * size * sizeof(float));
	float *matrixC = (float*) malloc(size * size * sizeof(float));
	//device
	float *matrixA_d;
	float *matrixB_d;
	float *matrixC_d;

	int i = 0;

	while (i < size * size) {
		matrixA[i] = rand()%100;
		matrixB[i] = 1;		
		i++;
	}	

	
	
	cudaMalloc((void**)&matrixA_d, size * size * sizeof(float)); 
	cudaMalloc((void**)&matrixB_d, size * size * sizeof(float));
	cudaMalloc((void**)&matrixC_d, size * size * sizeof(float)); 

	dim3 dimBlock(size , size);
   	dim3 dimGrid(size / dimBlock.x , size / dimBlock.y);

	cudaMemcpy(matrixA_d, matrixA, size * size * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(matrixB_d, matrixB, size * size * sizeof(float), cudaMemcpyHostToDevice);



	dotProduct<<<dimGrid,dimBlock>>>(matrixA_d,matrixB_d,matrixC_d,size);	
	

	cudaMemcpy(matrixC, matrixC_d, size * size * sizeof(float), cudaMemcpyDeviceToHost);
	

	for (i = 0; i < size * size; i ++) {
		if(i > 0 && i % size == 0)
			printf("\n");
		printf("%.2f ", matrixC[i]);
	}

	printf("\n");
}