#include<iostream>
using namespace std;

class Exception{
public:
	virtual void disp()const = 0;
};

class OutOfMemory:public Exception{
public:
	//OutOfMemory(){cout<<"OutOfMemory Constructed"<<endl;}
	//OutOfMemory(const OutOfMemory& a){cout<<"Copy construction"<<endl;}//拷贝构造函数形参要加const
	void disp()const override{
		cout<<"Out Of Memory!"<<endl;
	}
};

class RangeError:public Exception{
public:
	void disp()const override{
		cout<<"Number Out Of Range!"<<endl;
	}
};

template<typename T>
T* newArray(const int& size){
	T* ptr;
	if(size > 10000)throw OutOfMemory();//实际是实例化了一个临时变量，会调用默认构造函数
	else ptr = new T[size];
	return ptr;
}

template<typename T>
T getvalue(T* arr,const int& index,const int& size){
	if(index >= size || index < 0)throw RangeError();
	return arr[index];
}

int main(){
	int n,k;
	cin >> n;
	cin >> k;
	int m[k];
	for(int i = 0;i < k;i ++){cin>>m[i];}
	try{
		int *ptr = newArray<int>(n);	
		for(int i = 0;i < k;i ++){
			getvalue<int>(ptr,m[i],n);
		}
		delete[] ptr;//记得释放内存
	}catch(OutOfMemory &a){//此处传引用，不会调用拷贝构造函数
		a.disp();
	}catch(RangeError &b){
		b.disp();
	}
	return 0;
}
