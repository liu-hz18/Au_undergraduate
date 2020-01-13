#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdlib>
#include <iostream>
#include "Node.h"

using namespace std;


template <class T>
class LinkedList {
private:
	// 数据成员：
	Node<T> *front, *rear; // 表头和表尾指针
	Node<T> *prevPtr, *currPtr; // 记录表当前遍历位置的指针，由插入和删除操作更新
	int size; // 表中的元素个数
	int position; // 当前元素在表中的位置序号。由函数 Reset 使用

				  // 函数成员：

				  // 生成新结点，数据域为 item，指针域为 ptrNext
	Node<T>* NewNode(const T &item, Node<T> *ptrNext = NULL);

	// 释放结点
	void FreeNode(Node<T> *p);

	// 将链表 L 拷贝到当前表（假设当前表为空）。
	// 被复制构造函数和“operator =”调用
	void Copy(const LinkedList<T> &L);

public:
	LinkedList(void); // 构造函数
	LinkedList(const LinkedList<T> &L); // 复制构造函数
	~LinkedList(void); // 析构函数
	LinkedList<T>& operator =(const LinkedList<T> &L); // 重载赋值运算符

	int GetSize(void) const; // 返回链表中元素个数
	bool IsEmpty(void) const; // 链表是否为空

	void Reset(int pos = 0); // 初始化游标的位置
	void Next(void); // 使游标移动到下一个结点
	bool EndOfList(void) const; // 游标是否到了链尾
	int CurrentPosition(void) const; // 返回游标当前的位置

	void InsertFront(const T &item); // 在表头插入结点
	void InsertRear(const T &item); // 在表尾插入结点
		void InsertBefore(const T &item); // 在当前结点之前插入结点
	void InsertAfter(const T &item); // 在当前结点之后插入结点

	T DeleteFront(void); // 删除头结点
	void DeleteCurrent(void); // 删除当前结点

	T& Data(void); // 返回对当前结点成员数据的引用
	const T& Data(void) const; // 返回对当前结点成员数据的常引用

							   // 清空链表：释放所有结点的内存空间。被析构函数和“operator =”调用
	void Clear(void);
};


/**
@brief 生成新结点
@param item 数据域
@param ptrNext 指针域
@return 新结点
*/
template <class T>
Node<T>* LinkedList<T>::NewNode(const T &item, Node<T> *ptrNext)
{
	Node<T> *newNode;

	newNode = new Node<T>(item, ptrNext);

	if (newNode == NULL) {
		cerr << "Memory allocation failure!" << endl;
		exit(1);
	}

	return newNode;
}


/**
@brief 释放结点
@param p 指定结点
*/
template <class T>
void LinkedList<T>::FreeNode(Node<T> *p)
{
	delete p;
}


/**
@brief 将同类链表拷贝到当前空表
@param L 同类链表
@note 当前表为空表
被复制构造函数和“operator =”调用
*/
template <class T>
void LinkedList<T>::Copy(const LinkedList<T> &L)
{
	if (L.size == 0)
		return;

	front = rear = NewNode(L.front->Data);

	for (Node<T> *srcNode = L.front->NextNode();
		srcNode != NULL;
		srcNode = srcNode->NextNode())
	{
		Node<T> *newNode = NewNode(srcNode->Data);
		rear->InsertAfter(newNode);
		rear = newNode;
	}

	size = L.size;
	Reset(position = L.CurrentPosition());
}


/**
@brief 构造函数
@note 默认空表
*/
template <class T>
LinkedList<T>::LinkedList(void)
	: front(NULL), rear(NULL), prevPtr(NULL), currPtr(NULL), size(0), position(0)
{
}


/**
@brief 复制构造函数
@param L 复制对象
*/
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &L)
	: front(NULL), rear(NULL), prevPtr(NULL), currPtr(NULL), size(0), position(0)
{
	Copy(L);
}


/**
@brief 析构函数
*/
template <class T>
LinkedList<T>::~LinkedList(void)
{
	Clear();
}


/**
@brief 重载赋值运算符
@param L 复制对象
@return 当前对象
*/
template <class T>
LinkedList<T>& LinkedList<T>::operator =(const LinkedList<T> &L)
{
	Clear();
	Copy(L);

	return *this;
}


/**
@brief 返回链表中元素个数
@return 当前链表中元素个数
*/
template <class T>
int LinkedList<T>::GetSize(void) const
{
	return size;
}


/**
@brief 判断是否空表
@return 链表是否为空
*/
template <class T>
bool LinkedList<T>::IsEmpty(void) const
{
	return (size == 0);
}

/**
@brief 初始化游标的位置
@param pos 从零计起的位置编号
@note pos 无限制
当 pos 在 0 和 size 之间时，prevPtr 和 currPtr 正常指示;
当 pos 为 0 时，prevPtr = NULL, currPtr = front;
当 pos 为 size 时，prevPtr = rear, currPtr = NULL;
当 pos 取其他值


时，prevPtr = currPtr = NULL。
*/
template <class T>
void LinkedList<T>::Reset(int pos)
{
	if (0 <= pos && pos <= size) {
		position = 0;
		prevPtr = NULL;
		currPtr = front;
		// 游标回到头结点，再逐步前移
		while (pos--)
			Next();
	}
	else {
		position = pos;
		prevPtr = NULL;
		currPtr = NULL;
	}
}


/**
@brief 使游标移动到下一个结点
@note 允许游标移出链表
*/
template <class T>
void LinkedList<T>::Next(void)
{
	position++;
	prevPtr = currPtr;

	if (currPtr != NULL)
		currPtr = currPtr-> NextNode();
}


/**
@brief 游标是否到了链尾
@return 游标是否到了链尾
游标“到了链尾”意即游标“超出了链表”，
当游标所示的当前结点不存在时即判断到了链尾。
*/
template <class T>
bool LinkedList<T>::EndOfList(void) const
{
	return (currPtr == NULL);
}


/**
@brief 返回游标当前的位置
@return 从零计起的位置编号
@note 游标可以在链表之外
*/
template <class T>
int LinkedList<T>::CurrentPosition(void) const
{
	return position;
}


/**
@brief 在表头插入结点
@param item 新结点的数据域
*/
template <class T>
void LinkedList<T>::InsertFront(const T &item)
{
	front = NewNode(item, front);

	if (IsEmpty())
		rear = front;

	size++;
	Reset(++position);
}


/**
@brief 在表尾插入结点
@param item 新结点的数据域
*/
template <class T>
void LinkedList<T>::InsertRear(const T &item)
{
	Node<T> *newNode = NewNode(item);

	if (IsEmpty()) {
		front = rear = newNode;
	}
	else {
		rear->InsertAfter(newNode);
		rear = newNode;
	}

	size++;
	Reset(position);
}


/**
@brief 在当前结点之前插入结点
@param item 新结点的数据域
@note 只考虑当前位置的结点存在的情况
*/
template <class T>
void LinkedList<T>::InsertBefore(const T &item)
{
	if (currPtr != NULL) {
		Node<T> *newNode = GetNode(item, currPtr);

		if (prevPtr != NULL)
			prevPtr->InsertAfter(newNode);
		else
			front = prevPtr = newNode;

		size++;
		Reset(++position);
	}
}


/**
@brief 在当前结点之后插入结点
@param item 新结点的数据域
@note 只考虑当前位置的结点存在的情况
*/
template <class T>
void LinkedList<T>::InsertAfter(const T &item)
{
	if (currPtr != NULL) {
		Node<T> *newNode = NewNode(item, currPtr->NextNode());
		currPtr->InsertAfter(newNode);

		if (rear == currPtr)
			rear = newNode;

		size++;
	}
}


/**
@brief 删除头结点
*/
template <class T>
T LinkedList<T>::DeleteFront(void)
{
	if (IsEmpty()) {
		cerr << "List is empty, delete error." << endl;
		exit(1);
	}

	Node<T> *delNode = front;
	front = front->NextNode();

	if (--size == 0)
		rear = NULL;

	Reset(--position);

	T item = delNode->data;
	FreeNode(delNode);

	return item;
}


/**
@brief 删除当前结点
@note 只考虑当前位置的结点存在的情况
*/


template <class T>
void LinkedList<T>::DeleteCurrent(void)
{
	if (currPtr != NULL) {
		if (front == currPtr)
			front = currPtr->NextNode();

		if (rear == currPtr)
			rear = prevPtr;

		if (prevPtr != NULL)
			prevPtr->DeleteAfter();

		FreeNode(currPtr);
		size--;
		Reset(position);
	}
}


/**
@brief 返回对当前结点成员数据的引用
@return 当前结点数据域
*/
template <class T>
T& LinkedList<T>::Data(void)
{
	if (currPtr == NULL) {
		cerr << "Current node is invalid." << endl;
		exit(1);
	}

	return currPtr->data;
}


/**
@brief 返回对当前结点成员数据的常引用
@return 当前结点数据域
*/
template <class T>
const T& LinkedList<T>::Data(void) const
{
	if (currPtr == NULL) {
		cerr << "Current node is invalid." << endl;
		exit(1);
	}

	return currPtr->data;
}


/**
@brief 清空链表：释放所有结点的内存空间。
被析构函数和“operator =”调


用
*/
template <class T>
void LinkedList<T>::Clear(void)
{
	while (!IsEmpty())
		DeleteFront();
}


#endif // LINKEDLIST_H