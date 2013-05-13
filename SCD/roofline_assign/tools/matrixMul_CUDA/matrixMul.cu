/*
 * Copyright 1993-2009 NVIDIA Corporation.  All rights reserved.
 *
 * NVIDIA Corporation and its licensors retain all intellectual property and 
 * proprietary rights in and to this software and related documentation and 
 * any modifications thereto.  Any use, reproduction, disclosure, or distribution 
 * of this software and related documentation without an express license 
 * agreement from NVIDIA Corporation is strictly prohibited.
 * 
 */

/* Matrix multiplication: C = A * B.
 * Host code.
 *
 * This sample implements matrix multiplication and is exactly the same as
 * Chapter 7 of the programming guide.
 * It has been written for clarity of exposition to illustrate various CUDA
 * programming principles, not with the goal of providing the most
 * performant generic kernel for matrix multiplication.
 *
 * CUBLAS provides high-performance matrix multiplication.
 */

// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// includes, project
#include <cutil_inline.h>

// includes, kernels
#include <matrixMul_kernel.cu>
#include <matrixMul_naive.cu>
#include <matrixMul_tiling.cu>
#include <matrixMul_coalescing.cu>
#include <matrixMul_noBankConflict.cu>
#include <matrixMul_outerProduct.cu>
#include <matrixMul_fpPortion.cu>
#include <matrixMul_prefetch.cu>

////////////////////////////////////////////////////////////////////////////////
// declaration, forward
void runTest(int argc, char** argv);
void randomInit(float*, int);
void printDiff(float*, float*, int, int);

extern "C"
void computeGold(float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int
main(int argc, char** argv)
{
    runTest(argc, argv);

    cutilExit(argc, argv);
}

////////////////////////////////////////////////////////////////////////////////
//! Run a simple test for CUDA
////////////////////////////////////////////////////////////////////////////////
void
runTest(int argc, char** argv)
{

    /****************************************************/
    /*  Preparations                                    */
    /****************************************************/

    if( cutCheckCmdLineFlag(argc, (const char**)argv, "device") )
        cutilDeviceInit(argc, argv);
    else
        cudaSetDevice( cutGetMaxGflopsDeviceId() );

    // set seed for rand()
    srand(2006);

    // allocate host memory for matrices A and B
    unsigned int size_A = WA * HA;
    unsigned int mem_size_A = sizeof(float) * size_A;
    float* h_A = (float*) malloc(mem_size_A);
    unsigned int size_B = WB * HB;
    unsigned int mem_size_B = sizeof(float) * size_B;
    float* h_B = (float*) malloc(mem_size_B);
    float flop = 2 * (float)WC * (float)HC * (float)WA;

    // initialize host memory
    randomInit(h_A, size_A);
    randomInit(h_B, size_B);
    
    // allocate device memory
    float* d_A;
    cutilSafeCall(cudaMalloc((void**) &d_A, mem_size_A));
    float* d_B;
    cutilSafeCall(cudaMalloc((void**) &d_B, mem_size_B));

    // allocate device memory for result
    unsigned int size_C = WC * HC;
    unsigned int mem_size_C = sizeof(float) * size_C;
    float* d_C;
    cutilSafeCall(cudaMalloc((void**) &d_C, mem_size_C));

    // allocate host memory for the result
    float* h_C = (float*) malloc(mem_size_C);

#if CHECK_RESULT == 1
    // compute reference solution
    float* reference = (float*) malloc(mem_size_C);
    computeGold(reference, h_A, h_B, HA, WA, WB);
    CUTBoolean res;
#endif

    unsigned int timer = 0;
    dim3 threads,grid;

    /****************************************************/
    /*  CUDA SDK example                                */
    /****************************************************/

    // create and start timer
    cutilCheckError(cutCreateTimer(&timer));
    cutilCheckError(cutStartTimer(timer));
    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );
    // setup execution parameters
    threads = dim3(BLOCK_SIZE, BLOCK_SIZE);
    grid = dim3(WC / threads.x, HC / threads.y);
    // execute the kernel
    matrixMul<<< grid, threads >>>(d_C, d_A, d_B, WA, WB);
    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");
    // copy result from device to host
    cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );
    // stop and destroy timer
    cutilCheckError(cutStopTimer(timer));
    printf("SDK Sample\n");
    printf("Processing time: %f (ms), GFLOPS: %f \n", cutGetTimerValue(timer), flop/cutGetTimerValue(timer) / 1e+6);
    cutilCheckError(cutDeleteTimer(timer));
#if CHECK_RESULT == 1
    // check result
    res = cutCompareL2fe(reference, h_C, size_C, 1e-6f);
    printf("Test %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C, WC, HC);
#endif

    /****************************************************/
    /*  naive implementation on GPU                     */
    /****************************************************/

#if ENABLE_NAIVE == 1

    // create and start timer
    cutilCheckError(cutCreateTimer(&timer));
    cutilCheckError(cutStartTimer(timer));
    // setup execution parameters
    threads = dim3(BLOCK_SIZE, BLOCK_SIZE);
    grid = dim3(WC / threads.x, HC / threads.y);
    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );
    // naive implementation
    matrixMul_naive<<< grid, threads >>>(d_C, d_A, d_B, WA, WB);
    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");
    // copy result from device to host
    cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );
    // stop and destroy timer
    cutilCheckError(cutStopTimer(timer));
    printf("Naive\n");
    printf("Processing time: %f (ms), GFLOPS: %f \n", cutGetTimerValue(timer), flop/cutGetTimerValue(timer) / 1e+6);
    cutilCheckError(cutDeleteTimer(timer));
#if CHECK_RESULT == 1
    // check result
    res = cutCompareL2fe(reference, h_C, size_C, 1e-6f);
    printf("Test %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C, WC, HC);
#endif

#endif
    /****************************************************/
    /*  Tiling without global mem coalescing            */
    /****************************************************/

    // create and start timer
    cutilCheckError(cutCreateTimer(&timer));
    cutilCheckError(cutStartTimer(timer));
    // setup execution parameters
    threads = dim3(BLOCK_SIZE, BLOCK_SIZE);
    grid = dim3(WC / threads.x, HC / threads.y);
    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );
    // naive implementation
    matrixMul_tiling<<< grid, threads >>>(d_C, d_A, d_B, WA, WB);
    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");
    // copy result from device to host
    cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );
    // stop and destroy timer
    cutilCheckError(cutStopTimer(timer));
    printf("Tiling\n");
    printf("Processing time: %f (ms), GFLOPS: %f \n", cutGetTimerValue(timer), flop/cutGetTimerValue(timer) / 1e+6);
    cutilCheckError(cutDeleteTimer(timer));
#if CHECK_RESULT == 1
    // check result
    res = cutCompareL2fe(reference, h_C, size_C, 1e-6f);
    printf("Test %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C, WC, HC);
#endif

    /****************************************************/
    /*  Global mem coalescing with smem bank conflict   */
    /****************************************************/

    // create and start timer
    cutilCheckError(cutCreateTimer(&timer));
    cutilCheckError(cutStartTimer(timer));
    // setup execution parameters
    threads = dim3(BLOCK_SIZE, BLOCK_SIZE);
    grid = dim3(WC / threads.x, HC / threads.y);
    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );
    // naive implementation
    matrixMul_coalescing<<< grid, threads >>>(d_C, d_A, d_B, WA, WB);
    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");
    // copy result from device to host
    cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );
    // stop and destroy timer
    cutilCheckError(cutStopTimer(timer));
    printf("Global mem coalescing\n");
    printf("Processing time: %f (ms), GFLOPS: %f \n", cutGetTimerValue(timer), flop/cutGetTimerValue(timer) / 1e+6);
    cutilCheckError(cutDeleteTimer(timer));
#if CHECK_RESULT == 1
    // check result
    res = cutCompareL2fe(reference, h_C, size_C, 1e-6f);
    printf("Test %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C, WC, HC);
#endif

    /****************************************************/
    /*  Global mem coalescing w/o smem bank conflict    */
    /****************************************************/

    // create and start timer
    cutilCheckError(cutCreateTimer(&timer));
    cutilCheckError(cutStartTimer(timer));
    // setup execution parameters
    threads = dim3(BLOCK_SIZE, BLOCK_SIZE);
    grid = dim3(WC / threads.x, HC / threads.y);
    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );
    // naive implementation
    matrixMul_noBankConflict<<< grid, threads >>>(d_C, d_A, d_B, WA, WB);
    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");
    // copy result from device to host
    cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );
    // stop and destroy timer
    cutilCheckError(cutStopTimer(timer));
    printf("Remove shared mem bank conflict\n");
    printf("Processing time: %f (ms), GFLOPS: %f \n", cutGetTimerValue(timer), flop/cutGetTimerValue(timer) / 1e+6);
    cutilCheckError(cutDeleteTimer(timer));
#if CHECK_RESULT == 1
    // check result
    res = cutCompareL2fe(reference, h_C, size_C, 1e-6f);
    printf("Test %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C, WC, HC);
#endif

    /****************************************************/
    /*  Threads perform outer product                   */
    /****************************************************/

    // create and start timer
    cutilCheckError(cutCreateTimer(&timer));
    cutilCheckError(cutStartTimer(timer));
    // setup execution parameters
    threads = dim3(BLOCK_SIZE, 4);
    grid = dim3(WC / (BLOCK_SIZE*4), HC / BLOCK_SIZE);
    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );
    // naive implementation
    matrixMul_outerProduct<<< grid, threads >>>(d_C, d_A, d_B, WA, WB);
    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");
    // copy result from device to host
    cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );
    // stop and destroy timer
    cutilCheckError(cutStopTimer(timer));
    printf("Threads perform outer product\n");
    printf("Processing time: %f (ms), GFLOPS: %f \n", cutGetTimerValue(timer), flop/cutGetTimerValue(timer) / 1e+6);
    cutilCheckError(cutDeleteTimer(timer));
#if CHECK_RESULT == 1
    // check result
    res = cutCompareL2fe(reference, h_C, size_C, 1e-6f);
    printf("Test %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C, WC, HC);
#endif


    /****************************************************/
    /*  Increasing fp Proportion                        */
    /****************************************************/

    // create and start timer
    cutilCheckError(cutCreateTimer(&timer));
    cutilCheckError(cutStartTimer(timer));
    // setup execution parameters
    threads = dim3(BLOCK_SIZE, 4);
    grid = dim3(WC / (BLOCK_SIZE*4), HC / BLOCK_SIZE);
    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );
    // naive implementation
    matrixMul_fpPortion<<< grid, threads >>>(d_C, d_A, d_B, WA, WB);
    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");
    // copy result from device to host
    cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );
    // stop and destroy timer
    cutilCheckError(cutStopTimer(timer));
    printf("Increase fp Portion\n");
    printf("Processing time: %f (ms), GFLOPS: %f \n", cutGetTimerValue(timer), flop/cutGetTimerValue(timer) / 1e+6);
    cutilCheckError(cutDeleteTimer(timer));
#if CHECK_RESULT == 1
    // check result
    res = cutCompareL2fe(reference, h_C, size_C, 1e-6f);
    printf("Test %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C, WC, HC);
#endif

    /****************************************************/
    /*  Prefetching                                     */
    /****************************************************/

    // create and start timer
    cutilCheckError(cutCreateTimer(&timer));
    cutilCheckError(cutStartTimer(timer));
    // setup execution parameters
    threads = dim3(BLOCK_SIZE, 4);
    grid = dim3(WC / (BLOCK_SIZE*4), HC / BLOCK_SIZE);
    // copy host memory to device
    cutilSafeCall(cudaMemcpy(d_A, h_A, mem_size_A,
                              cudaMemcpyHostToDevice) );
    cutilSafeCall(cudaMemcpy(d_B, h_B, mem_size_B,
                              cudaMemcpyHostToDevice) );
    // naive implementation
    matrixMul_prefetch<<< grid, threads >>>(d_C, d_A, d_B, WA, WB);
    // check if kernel execution generated and error
    cutilCheckMsg("Kernel execution failed");
    // copy result from device to host
    cutilSafeCall(cudaMemcpy(h_C, d_C, mem_size_C,
                              cudaMemcpyDeviceToHost) );
    // stop and destroy timer
    cutilCheckError(cutStopTimer(timer));
    printf("Prefetching\n");
    printf("Processing time: %f (ms), GFLOPS: %f \n", cutGetTimerValue(timer), flop/cutGetTimerValue(timer) / 1e+6);
    cutilCheckError(cutDeleteTimer(timer));
#if CHECK_RESULT == 1
    // check result
    res = cutCompareL2fe(reference, h_C, size_C, 1e-6f);
    printf("Test %s \n", (1 == res) ? "PASSED" : "FAILED");
    if (res!=1) printDiff(reference, h_C, WC, HC);
#endif

    /****************************************************/
    /*  Cleaning                                        */
    /****************************************************/

    // clean up memory
    free(h_A);
    free(h_B);
    free(h_C);
#if CHECK_RESULT == 1
    free(reference);
#endif
    cutilSafeCall(cudaFree(d_A));
    cutilSafeCall(cudaFree(d_B));
    cutilSafeCall(cudaFree(d_C));

    cudaThreadExit();
}

// Allocates a matrix with random float entries.
void randomInit(float* data, int size)
{
    for (int i = 0; i < size; ++i)
        data[i] = rand() / (float)RAND_MAX;
}

void printDiff(float *data1, float *data2, int width, int height)
{
  int i,j,k;
  int error_count=0;
  for (j=0; j<height; j++) {
    for (i=0; i<width; i++) {
      k = j*width+i;
      if (fabs(data1[k] - data2[k]) > 0.1 ) {
         printf("diff(%d,%d) CPU=%4.4f, GPU=%4.4f \n", i,j, data1[k], data2[k]);
         error_count++;
      }
    }
  }
  printf(" nTotal Errors = %d n", error_count);
}

