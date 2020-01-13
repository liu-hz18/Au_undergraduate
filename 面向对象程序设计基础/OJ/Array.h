#ifndef ARRAY_H
#define ARRAY_H
#include<iostream>
using namespace std;

//数组 类模板，只限于数字类型使用，没有实现模板特化
//有异常处理，是安全的数组类
template <typename T>
class Array{
	T* pThis;
	int size;
public:
	Array(int s = 100):size(s){
		if(s > 1024 * 64)throw"Out Of Memory!";
		pThis = new T[s];
	}
	//对于字符串数组的特化,函数模板不能部分特化
	//template <> Array<char>(char* str) {pThis = new char[str.len()]; pThis = str;}
	~Array(){delete[] pThis;}
	void setval(const T& val,int index){
		//超过访问区间就一次性扩大至index
		if(index >= size){
			T* temp = new T[index + 1];
			for(int i = 0;i < size;i ++){temp[i] = pThis[i];}
			delete[] pThis;
			pThis = temp;
			pThis[index] = val;
		}else{
			pThis[index] = val;
		}
	}
	inline void swap(T& a,T& b){T temp = a;a = b;b = temp;}
	void sort(){
		for(int i = 0; i < size; i++)
			for(int j = i + 1;j < size;j ++)
				if(pThis[i] > pThis[j])
					swap(pThis[i],pThis[j]);
	}
	inline T sum()const{
		T sum = (T)0;
		for(int i = 0;i < size;i ++){sum += pThis[i];}
		return sum;
	}
	inline T average()const{ return this->sum() / T(size); }
	void show()const{
		for(int i = 0;i < size;i ++){cout<<pThis[i]<<' ';}
		cout<<endl;
	}
	//下标运算符重载,设为成员函数.自定义Array类必须进行下标运算重载才能使用[ ]
	T& operator[](const int& index){
		if(index >= (this->size) || index < 0)throw "invalid position";
		else return pThis[index];
	}
	
};


#endif