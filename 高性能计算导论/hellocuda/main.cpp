
// main.cpp
#include "hellocu.cuh"

//注意平台要选择 x64

int main(){
	nvcc_test();
	print_GPU_device_info();
	testoperation();
	return 0;
}
