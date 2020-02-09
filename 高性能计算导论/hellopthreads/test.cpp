
#include <stdio.h>
#include <iostream>
#include <pthread.h>
using namespace std;

#define NUM_THREADS 5

//编译平台转换为 x64
//注意配置属性：属性->配置属性->VC++目录->包含目录(配置 include E:\pthreads\Pre-built.2\include)&
//                                     库目录(配置 lib E:\pthreads\Pre-built.2\lib\x64)
//以及 属性->配置属性->链接器->输入->附加依赖项(pthreadVC2.lib)

//线程函数
void* run(void* args){
	cout<<"Hello Pthreads"<<endl;
	return 0;
}

int main(){
	pthread_t tids[NUM_THREADS];
	for(int i = 0; i < NUM_THREADS; i++){
		//参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
		int ret = pthread_create(&tids[i], NULL, run, NULL);
		if(ret){
			cout<<"pthread_create error: error code = "<<ret<<endl;
		}
	}
	//等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来
	pthread_exit(NULL);
	return 0;
}
