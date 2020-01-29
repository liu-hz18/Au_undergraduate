
#ifndef _MINHEAP_H_
#define _MINHEAP_H_

#include "util.h"

//最小堆
template<typename T>
class MinHeap{
	int _size;//堆容量
	T* arr;//存放rank的rank
	int _currentSize;//当前大小
	//上滤
	int percolateUp(){
		int i = _currentSize - 1;
		while(i > 0){
			int j = i>>1;
			if(j <= 0)break;
			if(arr[j] < arr[i])break;
			T temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
			i = j;
		}
		return i;
	}
	//判断两个rank对应节点哪个小
	int smaller(int i, int j){
		return arr[i] < arr[j] ? i : j;
	}
	//返回父子三个中(如果有)最小的那个
	int properParent(int i){
		if(i<<1 >= _currentSize)return i;
		if((i<<1|1) == _currentSize)return smaller(i, i<<1);
		return smaller(i<<1|1, smaller(i, i<<1));
	}
	//下滤
	int percolateDown(){
		int j, i = 1;//堆顶
		while(i != (j = properParent(i))){
			T temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
			i = j;
		}
		return i;
	}
public:
	MinHeap(int k = 64):_size(k + 1), arr(new T[_size]), _currentSize(1){};
	~MinHeap(){
		delete[] arr;
	};
	//加入元素,维护size始终为k
	void push(T data){
		arr[_currentSize++] = data;
		percolateUp();
	}
	//删除元素
	T pop(){
		assert(_currentSize >= 1);
		T minNode = arr[1];
		arr[1] = arr[--_currentSize];
		percolateDown();
		return minNode;
	}
	//获得最小值
	T top()const{
		return arr[1];
	}
	bool empty(){
		return _currentSize <= 1;
	}
};

#endif
