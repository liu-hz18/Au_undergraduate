
#include <stdio.h>
#include <iostream>
#include <pthread.h>
using namespace std;

#define NUM_THREADS 5

//����ƽ̨ת��Ϊ x64
//ע���������ԣ�����->��������->VC++Ŀ¼->����Ŀ¼(���� include E:\pthreads\Pre-built.2\include)&
//                                     ��Ŀ¼(���� lib E:\pthreads\Pre-built.2\lib\x64)
//�Լ� ����->��������->������->����->����������(pthreadVC2.lib)

//�̺߳���
void* run(void* args){
	cout<<"Hello Pthreads"<<endl;
	return 0;
}

int main(){
	pthread_t tids[NUM_THREADS];
	for(int i = 0; i < NUM_THREADS; i++){
		//���������ǣ��������߳�id���̲߳��������õĺ���������ĺ�������
		int ret = pthread_create(&tids[i], NULL, run, NULL);
		if(ret){
			cout<<"pthread_create error: error code = "<<ret<<endl;
		}
	}
	//�ȸ����߳��˳��󣬽��̲Ž������������ǿ�ƽ����ˣ��߳̿��ܻ�û��Ӧ����
	pthread_exit(NULL);
	return 0;
}
