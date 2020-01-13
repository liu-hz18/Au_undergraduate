#ifndef QUEUE_H
#define QUEUE_H
#include<iostream>
#include "Node.h"
using namespace std;

//队列(Queue)是只允许在一端进行插入操作，而在另一端进行删除操作的线性表。允许插入的端是队尾，允许删除的端是队头。
//所以说队列是一个先进先出的线性表，相应的也有顺序存储和链式存储两种方式
//顺序存储就是用数组实现，比如有一个ｎ个元素的队列，数组下标0的一端是队头，入队操作就是通过数组下标一个个顺序追加，不需要移动元素，但是如果删除队头元素，后面的元素就要往前移动，对应的时间复杂度就是O(n)，性能自然不高。
//为了提高出队的性能，就有了循环队列，什么是循环队列呢？就是有两个指针，front指向队头，rear指向对尾元素的下一个位置，元素出队时front往后移动，如果到了对尾则转到头部，同理入队时rear后移，如果到了对尾则转到头部，这样通过下标front出队时，就不需要移动元素了。
//当队列为空时，front和rear相等，那么队列什么时候判断为满呢？按照循环操作rear依次后移，然后再从头开始，也是出现rear和front相等时，队列满。
//实现顺序存储和链式存储
//队列没有iterator,不能进行遍历，只有 入队，出队，获取首尾元素的操作。
//模板队列类


//以数组为容器
template <typename T>
class Queue{
	int MaxSize;
	int front,rear;//front指向第一个元素，rear指向最后一个元素的后一个位置
	T* element;
public:
	Queue(int size = 100):MaxSize(size),front(0),rear(0){element = new T[MaxSize];}
	~Queue(){delete[] element;}
	void push(const T& val){
		if(isFull())throw"QUEUE IS FULL!\n";
		element[rear] = val; 
		rear = (rear + 1) % MaxSize;
	}
	T pop(){
		if(isEmpty())throw"QUEUE IS EMPTY!\n";
		T temp = element[front];
		front = (front + 1) % MaxSize;
		return temp;
	}
	T getfront(){return element[front];}
	T getback(){return element[rear - 1];}
	bool isEmpty(){return front == rear;}
	bool isFull(){return front == (rear + 1) % MaxSize;}
};

//以链表为容器
template <typename T,typename Sequence = List<T> > //默认容器为list
class Queue_list{
	Sequence c;
public:
	Queue_list(){}
	~Queue_list(){}
	void push(const T& val){c.push_back(val);}
	T pop(){T temp = c.begin() -> val;c.pop_front();return temp;}
	T getfront(){return c.begin()->val;}
	T getback(){return c.end()->val;}
	bool isEmpty(){return c.isEmpty();}
};

#endif
