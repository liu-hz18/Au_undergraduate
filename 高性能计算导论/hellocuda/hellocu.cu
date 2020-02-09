
#include <iostream>
#include <time.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cublas_v2.h"//���������cuBLAS

//���ļ�������GPU��������
//ע�⽫���ļ���ӵ� Դ�ļ��У� ��������Դ�ļ�
//����Ŀ�����Կ���ͨ�� ��cuda_debug_x64_PropertySheet�����

// defining
void nvcc_test(){
	std::cout << "I have been processed by NVCC!" << std::endl;
}

//��ӡGPU�豸��Ϣ
void print_GPU_device_info(){
	int deviceCount;
	cudaGetDeviceCount(&deviceCount);
	for (int i = 0; i<deviceCount; i++){
		cudaDeviceProp devProp;
		cudaGetDeviceProperties(&devProp, i);
		std::cout << "ʹ��GPU device " << i << ": " << devProp.name << std::endl;
		std::cout << "�豸ȫ���ڴ������� " << devProp.totalGlobalMem / 1024 / 1024 << "MB" << std::endl;
		std::cout << "SM��������" << devProp.multiProcessorCount << std::endl;
		std::cout << "ÿ��SM������߳�����" << devProp.maxThreadsPerMultiProcessor << std::endl;
		std::cout << "ÿ��SM������߳�������" << devProp.maxThreadsPerMultiProcessor / 32 << std::endl;
		std::cout << "ÿ��Block�Ĺ����ڴ��С��" << devProp.sharedMemPerBlock / 1024.0 << " KB" << std::endl;
		std::cout << "ÿ��Block������߳�����" << devProp.maxThreadsPerBlock << std::endl;
		std::cout << "ÿ��Block�п��õ�32λ�Ĵ��������� " << devProp.regsPerBlock << std::endl;
		std::cout << "======================================================" << std::endl;
	}
}

//�������
void testoperation(){
	srand(unsigned(time(NULL)));
	// ����״̬����
	cublasStatus_t status;
	const int N = 10, M = 5;
 
	// �� "�ڴ�" ��Ϊ��Ҫ����ľ��󿪱ٿռ�
	float *h_A = (float*)malloc(N * M * sizeof(float));
	float *h_B = (float*)malloc(N * M * sizeof(float));
	// �� "�ڴ�" ��Ϊ��Ҫ����������ľ��󿪱ٿռ�
	float *h_C = (float*)malloc(M * M * sizeof(float));
 
	// Ϊ����������Ԫ�ظ��� 0-10 ��Χ�ڵ������
	for (int i = 0; i < N * M; i++) {
		h_A[i] = (float)(rand() % 10 + 1);
		h_B[i] = (float)(rand() % 10 + 1);
	}
 
	// ��ӡ�����Եľ���
	std::cout << "���� A :" << std::endl;
	for (int i = 0; i < N * M; i++){
		std::cout << h_A[i] << " ";
		if ((i + 1) % N == 0) std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "���� B :" << std::endl;
	for (int i = 0; i < N * M; i++){
		std::cout << h_B[i] << " ";
		if ((i + 1) % M == 0) std::cout << std::endl;
	}
	std::cout << std::endl;

	// GPU ����������

	// ��������ʼ�� CUBLAS �����
	cublasHandle_t handle;
	status = cublasCreate(&handle);
 
	if (status != CUBLAS_STATUS_SUCCESS){
		if (status == CUBLAS_STATUS_NOT_INITIALIZED){
			std::cout << "CUBLAS ����ʵ��������" << std::endl;
		}
		return;
	}
 
	float *d_A, *d_B, *d_C;
	// �� "�Դ�" ��Ϊ��Ҫ����ľ��󿪱ٿռ�
	cudaMalloc(
		(void**)&d_A,    // ָ�򿪱ٵĿռ��ָ��
		N*M * sizeof(float)    //����Ҫ���ٿռ���ֽ���
		);
	cudaMalloc((void**)&d_B, N * M * sizeof(float));
	// �� "�Դ�" ��Ϊ��Ҫ����������ľ��󿪱ٿռ�
	cudaMalloc((void**)&d_C, M * M * sizeof(float));
 
	// ���������ݴ��ݽ� �Դ� ���Ѿ����ٺ��˵Ŀռ�
	cublasSetVector(
		N * M,    // Ҫ�����Դ��Ԫ�ظ���
		sizeof(float),    // ÿ��Ԫ�ش�С
		h_A,    // ��������ʼ��ַ
		1,      // ����Ԫ��֮��Ĵ洢���
		d_A,    // GPU ����ʼ��ַ
		1       // ����Ԫ��֮��Ĵ洢���
		);
	cublasSetVector(N * M, sizeof(float), h_B, 1, d_B, 1);
 
	// ͬ������
	cudaThreadSynchronize();
 
	// ���ݽ�������˺����еĲ��������庬����ο������ֲᡣ
	float a = 1; float b = 0;
	// ������ˡ��ú�����Ȼ���������������������
	cublasSgemm(
		handle,    // blas ����� 
		CUBLAS_OP_T,    // ���� A ���Բ���
		CUBLAS_OP_T,    // ���� B ���Բ���
		M,      // A, C ������ 
		M,      // B, C ������
		N,      // A �������� B ������
		&a,     // ����ʽ�� �� ֵ
		d_A,    // A ���Դ��еĵ�ַ
		N,      // lda
		d_B,    // B ���Դ��еĵ�ַ
		M,      // ldb
		&b,     // ����ʽ�� �� ֵ
		d_C,    // C ���Դ��еĵ�ַ(�������)
		M       // ldc
		);
 
	// ͬ������
	cudaThreadSynchronize();
	
	// �� �Դ� ��ȡ���������� �ڴ���ȥ
	cublasGetVector(
		M*M,    //  Ҫȡ��Ԫ�صĸ���
		sizeof(float),    // ÿ��Ԫ�ش�С
		d_C,    // GPU ����ʼ��ַ
		1,      // ����Ԫ��֮��Ĵ洢���
		h_C,    // ��������ʼ��ַ
		1       // ����Ԫ��֮��Ĵ洢���
		);
 
	// ��ӡ������
	std::cout << "��������ת�� ( (A*B)��ת�� )��" << std::endl;
 
	for (int i = 0; i<M*M; i++){
		std::cout << h_C[i] << " ";
		if ((i + 1) % M == 0) std::cout << std::endl;
	}
 
	// �����ʹ�ù����ڴ�
	free(h_A); free(h_B); free(h_C);
	cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
	// �ͷ� CUBLAS �����
	cublasDestroy(handle);
}
