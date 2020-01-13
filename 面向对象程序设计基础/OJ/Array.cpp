#include"Array.h"
#include<iomanip>
using namespace std;

int main(){
	unsigned size;int k;
	//int val;
	cin>>size>>k;
	int m[k];
	for(int i = 0;i < k;i ++){
		cin>>m[i];
	}
	try{
		Array<int> array(size);
		for(int i = 0;i < k;i++){
			try{
				array[m[i]];
			}catch(const char*msg){//本层处理的异常不会传递给上一层
				cout<<msg<<endl;
			}
		}
	}catch(const char*msg){//catch(...)可以用来捕获任何形式的异常
		cout<<msg<<endl;
	}
	return 0;
	/*
	for(int i = 0;i < size;i ++){
		cin>>val;
		array.setval(val,i);
	}
	cout<<fixed<<setprecision(2)<<array.average();
	*/	
}

