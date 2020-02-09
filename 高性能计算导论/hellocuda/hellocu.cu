
#include <iostream>
#include <time.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cublas_v2.h"//矩阵运算库cuBLAS

//本文件将调用GPU进行运算
//注意将本文件添加到 源文件中， 而不是资源文件
//本项目的属性可以通过 “cuda_debug_x64_PropertySheet”添加

// defining
void nvcc_test(){
	std::cout << "I have been processed by NVCC!" << std::endl;
}

//打印GPU设备信息
void print_GPU_device_info(){
	int deviceCount;
	cudaGetDeviceCount(&deviceCount);
	for (int i = 0; i<deviceCount; i++){
		cudaDeviceProp devProp;
		cudaGetDeviceProperties(&devProp, i);
		std::cout << "使用GPU device " << i << ": " << devProp.name << std::endl;
		std::cout << "设备全局内存总量： " << devProp.totalGlobalMem / 1024 / 1024 << "MB" << std::endl;
		std::cout << "SM的数量：" << devProp.multiProcessorCount << std::endl;
		std::cout << "每个SM的最大线程数：" << devProp.maxThreadsPerMultiProcessor << std::endl;
		std::cout << "每个SM的最大线程束数：" << devProp.maxThreadsPerMultiProcessor / 32 << std::endl;
		std::cout << "每个Block的共享内存大小：" << devProp.sharedMemPerBlock / 1024.0 << " KB" << std::endl;
		std::cout << "每个Block的最大线程数：" << devProp.maxThreadsPerBlock << std::endl;
		std::cout << "每个Block中可用的32位寄存器数量： " << devProp.regsPerBlock << std::endl;
		std::cout << "======================================================" << std::endl;
	}
}

//运算测试
void testoperation(){
	srand(unsigned(time(NULL)));
	// 定义状态变量
	cublasStatus_t status;
	const int N = 10, M = 5;
 
	// 在 "内存" 中为将要计算的矩阵开辟空间
	float *h_A = (float*)malloc(N * M * sizeof(float));
	float *h_B = (float*)malloc(N * M * sizeof(float));
	// 在 "内存" 中为将要存放运算结果的矩阵开辟空间
	float *h_C = (float*)malloc(M * M * sizeof(float));
 
	// 为待运算矩阵的元素赋予 0-10 范围内的随机数
	for (int i = 0; i < N * M; i++) {
		h_A[i] = (float)(rand() % 10 + 1);
		h_B[i] = (float)(rand() % 10 + 1);
	}
 
	// 打印待测试的矩阵
	std::cout << "矩阵 A :" << std::endl;
	for (int i = 0; i < N * M; i++){
		std::cout << h_A[i] << " ";
		if ((i + 1) % N == 0) std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "矩阵 B :" << std::endl;
	for (int i = 0; i < N * M; i++){
		std::cout << h_B[i] << " ";
		if ((i + 1) % M == 0) std::cout << std::endl;
	}
	std::cout << std::endl;

	// GPU 计算矩阵相乘

	// 创建并初始化 CUBLAS 库对象
	cublasHandle_t handle;
	status = cublasCreate(&handle);
 
	if (status != CUBLAS_STATUS_SUCCESS){
		if (status == CUBLAS_STATUS_NOT_INITIALIZED){
			std::cout << "CUBLAS 对象实例化出错" << std::endl;
		}
		return;
	}
 
	float *d_A, *d_B, *d_C;
	// 在 "显存" 中为将要计算的矩阵开辟空间
	cudaMalloc(
		(void**)&d_A,    // 指向开辟的空间的指针
		N*M * sizeof(float)    //　需要开辟空间的字节数
		);
	cudaMalloc((void**)&d_B, N * M * sizeof(float));
	// 在 "显存" 中为将要存放运算结果的矩阵开辟空间
	cudaMalloc((void**)&d_C, M * M * sizeof(float));
 
	// 将矩阵数据传递进 显存 中已经开辟好了的空间
	cublasSetVector(
		N * M,    // 要存入显存的元素个数
		sizeof(float),    // 每个元素大小
		h_A,    // 主机端起始地址
		1,      // 连续元素之间的存储间隔
		d_A,    // GPU 端起始地址
		1       // 连续元素之间的存储间隔
		);
	cublasSetVector(N * M, sizeof(float), h_B, 1, d_B, 1);
 
	// 同步函数
	cudaThreadSynchronize();
 
	// 传递进矩阵相乘函数中的参数，具体含义请参考函数手册。
	float a = 1; float b = 0;
	// 矩阵相乘。该函数必然将数组解析成列优先数组
	cublasSgemm(
		handle,    // blas 库对象 
		CUBLAS_OP_T,    // 矩阵 A 属性参数
		CUBLAS_OP_T,    // 矩阵 B 属性参数
		M,      // A, C 的行数 
		M,      // B, C 的列数
		N,      // A 的列数和 B 的行数
		&a,     // 运算式的 α 值
		d_A,    // A 在显存中的地址
		N,      // lda
		d_B,    // B 在显存中的地址
		M,      // ldb
		&b,     // 运算式的 β 值
		d_C,    // C 在显存中的地址(结果矩阵)
		M       // ldc
		);
 
	// 同步函数
	cudaThreadSynchronize();
	
	// 从 显存 中取出运算结果至 内存中去
	cublasGetVector(
		M*M,    //  要取出元素的个数
		sizeof(float),    // 每个元素大小
		d_C,    // GPU 端起始地址
		1,      // 连续元素之间的存储间隔
		h_C,    // 主机端起始地址
		1       // 连续元素之间的存储间隔
		);
 
	// 打印运算结果
	std::cout << "计算结果的转置 ( (A*B)的转置 )：" << std::endl;
 
	for (int i = 0; i<M*M; i++){
		std::cout << h_C[i] << " ";
		if ((i + 1) % M == 0) std::cout << std::endl;
	}
 
	// 清理掉使用过的内存
	free(h_A); free(h_B); free(h_C);
	cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
	// 释放 CUBLAS 库对象
	cublasDestroy(handle);
}
