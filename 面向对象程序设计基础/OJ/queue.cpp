
#include"queue.h"
using namespace std;

int main(){
	int num;
	//Queue<int> que1;
	Queue_list<int> que2;
	for(int i = 0;i < 5;i ++){
		cin>>num;
		//que1.push(num);
		que2.push(num);
	}
	for(int i = 0;i < 5;i ++){
		//cout<<que1.pop()<<' ';
		cout<<que2.pop()<<' ';
	}

	return 0;
}
