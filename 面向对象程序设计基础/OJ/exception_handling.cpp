#include<iostream>
#include<cmath>
using namespace std;

class CException{
	unsigned trigger;
public:
	CException() = default;
	CException(const unsigned& tri):trigger(tri){}
	void Reason(){
		if(trigger == 0)cout<<"divided by zero"<<endl;
		else if(trigger == 1)cout<<"out of memory"<<endl;
		else if(trigger == 2)cout<<"index out of range"<<endl;
	}
};
//相除函数（重载）
double divide(const int& a,const int& b){
	if(b == 0)throw CException(0);
	return a/b;
}
double divide(const double&a,const double& b){
	if(abs(b) < 1e-10)throw CException(0);
	return double(a/b);
}

const unsigned MaxSize = 100;//数组大小
const unsigned threshold = 1024 * 32;//剩余内存数
//数组访问越界
template <typename T>
int take(T* arr,const int& index){
	if(index >= MaxSize || index < 0)throw CException(2);
	return arr[index];
}

//内存不足
template <typename T>
T* newArray(const unsigned& size){
	if(size > threshold)throw CException(1);
	T* ptr = new T [size];
	return ptr;
}

int main(){
	//内存不足
	try{
		int *ptr = newArray<int>(threshold + 1);
		delete[] ptr;
	}catch(CException& a){
		a.Reason();
	}
	//index越界
	try{
		int arr[MaxSize];
		int temp = take<int>(arr,MaxSize + 1);
	}catch(CException& b){
		b.Reason();
	}
	//除以0
	try{
		double result = divide(3,0);
	}catch(CException& c){
		c.Reason();
	}
	return 0;
}