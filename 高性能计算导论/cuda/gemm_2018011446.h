// studentid: 2018011446
# pragma once
#include <math.h>
#include <cstdio>
#include <cuda.h>
#include <cuda_runtime.h>
#include "util.h" // for M, N, K

const int TILE_WIDTH = 32;
const int PAD = 0;
const int DIM_THREAD_BLOCK_X = 64;
const int DIM_THREAD_BLOCK_Y = 16;

const int stride = 4;

template<class T>
__global__ void gemm_kernel(T* A, T* B, T* C, const T alpha, const T beta, 
                            const size_t M, const size_t N, const size_t K, const int block_num) {
    //printf("%d %d %d %d\n", tx, ty, row, col);
    int block_col = threadIdx.x;
    int block_row = threadIdx.y;
    int col = blockIdx.x * blockDim.x + block_col;
    int row = blockIdx.y * blockDim.y + block_row;
    int i, j;
    T v = 0;
    __shared__ T shareM[TILE_WIDTH][TILE_WIDTH];
    __shared__ T shareN[TILE_WIDTH][TILE_WIDTH];
    for(i = 0; i < block_num; i++){
        shareM[block_row][block_col] = ((i * TILE_WIDTH+block_col < K) && (row < M)) ? A[row * K + (i * TILE_WIDTH+block_col)] : 0.;
        shareN[block_row][block_col] = ((i * TILE_WIDTH+block_row < K) && (col < N)) ? B[(i * TILE_WIDTH+block_row) * N + col] : 0.;
        __syncthreads();
        if( (col < N) && (row < M) ){
            for(j = 0; j < TILE_WIDTH; j ++){
                v += shareM[block_row][j] * shareN[j][block_col];
            }
        }
        __syncthreads();
    }
    if( (col < N) && (row < M) ) {
        C[row * N + col] = alpha*v + beta * C[row * N + col];
    }
}

template<class T> 
__global__ void gemm_pitch_kernel(T* A, T* B, T* C, const T alpha, const T beta, 
                            const size_t M, const size_t N, const size_t K, const int block_num,
                            const size_t A_pitch, const size_t B_pitch, const size_t C_pitch) {
    //printf("%d %d %d %d\n", tx, ty, row, col);
    int block_col = threadIdx.x;
    int block_row = threadIdx.y;
    int col = blockIdx.x * blockDim.x + block_col;
    int row = blockIdx.y * blockDim.y + block_row;
    T v = 0;
    __shared__ T shareA[TILE_WIDTH][TILE_WIDTH+PAD];
    __shared__ T shareB[TILE_WIDTH][TILE_WIDTH+PAD];
    for(int i = 0; i < block_num; i++){
        shareA[block_row][block_col] = ((i*TILE_WIDTH+block_col < K) && (row < M)) ? A[row * A_pitch + (i*TILE_WIDTH+block_col)] : 0.;
        shareB[block_row][block_col] = ((i*TILE_WIDTH+block_row < K) && (col < N)) ? B[(i*TILE_WIDTH+block_row) * B_pitch + col] : 0.;
        __syncthreads();
        for(int j = 0; j < TILE_WIDTH; j ++){
            v += shareA[block_row][j] * shareB[j][block_col];
        }
        __syncthreads();
    }
    if( (col < N) && (row < M) ) {
        v *= alpha;
        C[row * C_pitch + col] = v + beta * C[row * C_pitch + col];
    }
}

template<class T>
__global__ void gemm_k(T *A, T *B, T *C, int m, int n, int k, T alpha, T beta) {
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    // printf("col %d row %d\n", col, row);
    if( (col < n) && (row < m) ) {
        T tmp = 0.0;
        int row_off = row * k, i = 0;
        for(; i < k; i += stride) {
            tmp += A[row_off + i] * B[col + i*n];
            tmp += A[row_off + i + 1] * B[col + (i+1)*n];
            tmp += A[row_off + i + 2] * B[col + (i+2)*n];
            tmp += A[row_off + i + 3] * B[col + (i+3)*n];
        }
        i -= stride;
        for(; i < k; i++){
            tmp += A[row_off + i] * B[col + i*n];
        }
        tmp = tmp*alpha + beta * C[row * n + col];
        C[row * n + col] = tmp;
    }
}

//implement TILE
template<class T>
double myGEMM(T* A, T* B, T* C, T alpha, T beta){
	//printf("perform your gemm here on m=%d n=%d k=%d alpha=%.2f beta=%.2f\n", M, N, K, alpha, beta);
    //bool preprocess = false;
    bool preprocess = true;
    if(preprocess) {
        // your preprocess
        dim3 dimGrid(ceil((float)N/TILE_WIDTH), ceil((float)M/TILE_WIDTH), 1);
        dim3 dimBlock(TILE_WIDTH, TILE_WIDTH, 1);
        int block_num = ceil((float)K / TILE_WIDTH);
        
        // mem pitch
        //T *tmp_A, *tmp_B, *tmp_C;
        //size_t pitch_a_device, pitch_b_device, pitch_c_device;
        //cudaMallocPitch((void**)&tmp_A, &pitch_a_device, sizeof(T)*K, M);
        //cudaMallocPitch((void**)&tmp_B, &pitch_b_device, sizeof(T)*N, K);
        //cudaMallocPitch((void**)&tmp_C, &pitch_c_device, sizeof(T)*N, M);
        //cudaMemcpy2D(tmp_A, pitch_a_device, A, sizeof(T)*K, sizeof(T)*K, M, cudaMemcpyDeviceToDevice);
        //cudaMemcpy2D(tmp_B, pitch_b_device, B, sizeof(T)*N, sizeof(T)*N, K, cudaMemcpyDeviceToDevice);
        //cudaMemcpy2D(tmp_C, pitch_c_device, C, sizeof(T)*N, sizeof(T)*N, M, cudaMemcpyDeviceToDevice);
        //checkCudaErrors(cudaDeviceSynchronize());
        
        // compute
        timestamp(t0);
        gemm_kernel<<<dimGrid, dimBlock>>>
            (A, B, C, alpha, beta, M, N, K, block_num);
        //gemm_pitch_kernel<<<dimGrid, dimBlock>>>
        //    (tmp_A, tmp_B, tmp_C, alpha, beta, M, N, K, block_num, 
        //    pitch_a_device/sizeof(T), pitch_b_device/sizeof(T), pitch_c_device/sizeof(T));
        // don't change it
        checkCudaErrors(cudaDeviceSynchronize());
        timestamp(t1);
        //cudaMemcpy2D(C, sizeof(T)*N, tmp_C, pitch_c_device, sizeof(T)*N, M, cudaMemcpyDeviceToDevice);
        return getDuration(t0, t1);
    } else {
        dim3 block(DIM_THREAD_BLOCK_X, DIM_THREAD_BLOCK_Y);
        dim3 grid( (N + block.x - 1) / block.x, (M + block.y - 1) / block.y );
        gemm_k <<<grid, block>>>
            (A, B, C, M, N, K, alpha, beta);
        // don't change it
        checkCudaErrors(cudaDeviceSynchronize());
        return 0.f; 
    }
}
