#include<iostream>
#include<iomanip>
using namespace std;

//不能有CV限定符，在C++中CV限定符指const和volatile。
//a、在C++中，普通函数(非类的成员函数)不能有CV限定，即const和volatile(变化的)限定。
//在C++中，静态成员函数(static成员函数)不能有CV限定，即const和volatile限定。即类的静态成员函数，也不能有CV约束:
template<typename T>
int getindex(T data[],const T& val,const int& size){
	int i;
	for(i = 0;i < size;i++){
		if(data[i] == val)return i;
	}
	if(i == size)throw "Not Found!\n";
}

int main(){
	int data1[] = {1,3,5,7,9,11,13,15,17,19,2,4,6,8,10,12,14,16,18,20};
	int num,val;
	cin>>num;
	for(int i = 0;i < num;i ++){
		cin>>val;
		cout<<getindex<int>(data1,val,20)<<endl;
	}
	return 0;
}