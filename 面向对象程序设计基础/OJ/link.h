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
	// ���ݳ�Ա��
	Node<T> *front, *rear; // ��ͷ�ͱ�βָ��
	Node<T> *prevPtr, *currPtr; // ��¼��ǰ����λ�õ�ָ�룬�ɲ����ɾ����������
	int size; // ���е�Ԫ�ظ���
	int position; // ��ǰԪ���ڱ��е�λ����š��ɺ��� Reset ʹ��

				  // ������Ա��

				  // �����½�㣬������Ϊ item��ָ����Ϊ ptrNext
	Node<T>* NewNode(const T &item, Node<T> *ptrNext = NULL);

	// �ͷŽ��
	void FreeNode(Node<T> *p);

	// ������ L ��������ǰ�����赱ǰ��Ϊ�գ���
	// �����ƹ��캯���͡�operator =������
	void Copy(const LinkedList<T> &L);

public:
	LinkedList(void); // ���캯��
	LinkedList(const LinkedList<T> &L); // ���ƹ��캯��
	~LinkedList(void); // ��������
	LinkedList<T>& operator =(const LinkedList<T> &L); // ���ظ�ֵ�����

	int GetSize(void) const; // ����������Ԫ�ظ���
	bool IsEmpty(void) const; // �����Ƿ�Ϊ��

	void Reset(int pos = 0); // ��ʼ���α��λ��
	void Next(void); // ʹ�α��ƶ�����һ�����
	bool EndOfList(void) const; // �α��Ƿ�����β
	int CurrentPosition(void) const; // �����α굱ǰ��λ��

	void InsertFront(const T &item); // �ڱ�ͷ������
	void InsertRear(const T &item); // �ڱ�β������
		void InsertBefore(const T &item); // �ڵ�ǰ���֮ǰ������
	void InsertAfter(const T &item); // �ڵ�ǰ���֮�������

	T DeleteFront(void); // ɾ��ͷ���
	void DeleteCurrent(void); // ɾ����ǰ���

	T& Data(void); // ���ضԵ�ǰ����Ա���ݵ�����
	const T& Data(void) const; // ���ضԵ�ǰ����Ա���ݵĳ�����

							   // ��������ͷ����н����ڴ�ռ䡣�����������͡�operator =������
	void Clear(void);
};


/**
@brief �����½��
@param item ������
@param ptrNext ָ����
@return �½��
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
@brief �ͷŽ��
@param p ָ�����
*/
template <class T>
void LinkedList<T>::FreeNode(Node<T> *p)
{
	delete p;
}


/**
@brief ��ͬ������������ǰ�ձ�
@param L ͬ������
@note ��ǰ��Ϊ�ձ�
�����ƹ��캯���͡�operator =������
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
@brief ���캯��
@note Ĭ�Ͽձ�
*/
template <class T>
LinkedList<T>::LinkedList(void)
	: front(NULL), rear(NULL), prevPtr(NULL), currPtr(NULL), size(0), position(0)
{
}


/**
@brief ���ƹ��캯��
@param L ���ƶ���
*/
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &L)
	: front(NULL), rear(NULL), prevPtr(NULL), currPtr(NULL), size(0), position(0)
{
	Copy(L);
}


/**
@brief ��������
*/
template <class T>
LinkedList<T>::~LinkedList(void)
{
	Clear();
}


/**
@brief ���ظ�ֵ�����
@param L ���ƶ���
@return ��ǰ����
*/
template <class T>
LinkedList<T>& LinkedList<T>::operator =(const LinkedList<T> &L)
{
	Clear();
	Copy(L);

	return *this;
}


/**
@brief ����������Ԫ�ظ���
@return ��ǰ������Ԫ�ظ���
*/
template <class T>
int LinkedList<T>::GetSize(void) const
{
	return size;
}


/**
@brief �ж��Ƿ�ձ�
@return �����Ƿ�Ϊ��
*/
template <class T>
bool LinkedList<T>::IsEmpty(void) const
{
	return (size == 0);
}

/**
@brief ��ʼ���α��λ��
@param pos ��������λ�ñ��
@note pos ������
�� pos �� 0 �� size ֮��ʱ��prevPtr �� currPtr ����ָʾ;
�� pos Ϊ 0 ʱ��prevPtr = NULL, currPtr = front;
�� pos Ϊ size ʱ��prevPtr = rear, currPtr = NULL;
�� pos ȡ����ֵ


ʱ��prevPtr = currPtr = NULL��
*/
template <class T>
void LinkedList<T>::Reset(int pos)
{
	if (0 <= pos && pos <= size) {
		position = 0;
		prevPtr = NULL;
		currPtr = front;
		// �α�ص�ͷ��㣬����ǰ��
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
@brief ʹ�α��ƶ�����һ�����
@note �����α��Ƴ�����
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
@brief �α��Ƿ�����β
@return �α��Ƿ�����β
�αꡰ������β���⼴�αꡰ������������
���α���ʾ�ĵ�ǰ��㲻����ʱ���жϵ�����β��
*/
template <class T>
bool LinkedList<T>::EndOfList(void) const
{
	return (currPtr == NULL);
}


/**
@brief �����α굱ǰ��λ��
@return ��������λ�ñ��
@note �α����������֮��
*/
template <class T>
int LinkedList<T>::CurrentPosition(void) const
{
	return position;
}


/**
@brief �ڱ�ͷ������
@param item �½���������
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
@brief �ڱ�β������
@param item �½���������
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
@brief �ڵ�ǰ���֮ǰ������
@param item �½���������
@note ֻ���ǵ�ǰλ�õĽ����ڵ����
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
@brief �ڵ�ǰ���֮�������
@param item �½���������
@note ֻ���ǵ�ǰλ�õĽ����ڵ����
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
@brief ɾ��ͷ���
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
@brief ɾ����ǰ���
@note ֻ���ǵ�ǰλ�õĽ����ڵ����
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
@brief ���ضԵ�ǰ����Ա���ݵ�����
@return ��ǰ���������
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
@brief ���ضԵ�ǰ����Ա���ݵĳ�����
@return ��ǰ���������
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
@brief ��������ͷ����н����ڴ�ռ䡣
�����������͡�operator =����


��
*/
template <class T>
void LinkedList<T>::Clear(void)
{
	while (!IsEmpty())
		DeleteFront();
}


#endif // LINKEDLIST_H