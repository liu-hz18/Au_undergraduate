#ifndef NODE_H
#define NODE_H
#include<iostream>
using namespace std;
//nullptr为c++11标准！！-std=c++11
//定义链表数据结构
//模板的声明可以使用 typename 或 class!!
//template <class T>
//.....

//T成为“模板参数”分为类型参数T 和 非类型参数int,enum,int*等
//template <typename T,ungisned size>//成为多参数模板
//class array{
//	T elems[size];
//};

//成员函数模板：
//1.“普通类”的成员函数也可以定义为模板函数，只需在"定义"时加上template <typename> T
//2.“模板类”的成员函数也可以定义为模板函数，且可以定义额外的模板参数，只需在“定义”时加上templat<typename T1>
//对于模板类的模板成员函：注意类内定义和类外定义的不同，类外定义需要加上 两个模板参数列表，不能在一个参数列表内

//调用时可以自己指定类型，也可以编译器自己推导

template <typename T> class Node{
public:
	T val;
	Node<T>* next;
	Node(const T& val,Node<T>* next){this->val = val;this->next = next;}
	Node(Node<T>* next){this->next = next;}
	Node() = default;
};

template <typename T> class List{
	Node<T>* pHead;
	Node<T>* pThis;
	inline void swap(T& a,T& b){T temp = a;a = b;b = temp;}
public:
	//构造函数,使用有头节点（无数据成员）的链表
	//List() = default;
	//~List() = default;
	//重写默认构造函数
	List(){ pHead = new Node<T>(nullptr); pThis = pHead; }//调用类模板应使用Node<T>::func()
	~List(){ pThis = pHead; Node<T>* temp ; while(pThis){temp = pThis->next; delete pThis; pThis = temp;} }
	void push_back(const T& value){
		for(pThis = pHead;pThis -> next != nullptr;pThis = pThis->next);
		Node<T>* temp = new Node<T>(value,nullptr);
		pThis->next = temp;
	}
	bool isEmpty(){return (pHead->next == nullptr);}
	void push_front(const T& value){Node<T>* temp = new Node<T>(value,pHead->next);pHead->next = temp;}
	bool pop_back(){
		if(isEmpty()){cout<<"IS EMPTY!\n";return false;}
		for(pThis = pHead;pThis -> next -> next != nullptr;pThis = pThis->next);
		Node<T>* temp = pThis -> next;
		delete temp;
		pThis->next = nullptr;
		return true;
	}
	bool pop_front(){
		if(isEmpty()){cout<<"IS EMPTY!\n";return false;}
		pThis = pHead;
		pHead = pHead->next;
		delete pThis;
		pThis = pHead;
		return true;
	}
	void del_by_index(const int index){
		pThis = pHead;
		for(int i = 0;i < index; ++i ){
			if(pThis->next != nullptr) pThis = pThis->next;
			else throw "Node not found!\n";
		}
		Node<T>* pNext = pThis->next;
		pThis->next = pNext->next;
		delete pNext;
	}
	void del_by_val(const T value){
		Node<T>* pPre;
		for(pThis = pHead->next,pPre = pHead;pThis != nullptr;){
			if(pThis->val == value){
				Node<T>* temp = pThis->next;pPre->next = pThis->next;
				delete pThis;pThis = temp;
			}else {pThis = pThis->next,pPre = pPre->next;}
		}
	}
	//此函数尽管没有修改链表，但对类内成员pThis进行了修改，不可以声明为const
	void display(){
		for(pThis = pHead->next;pThis != nullptr;pThis = pThis->next){cout<<pThis->val<<" ";}
		cout<<endl;
	}
	//此函数尽管没有修改链表，但对类内成员pThis进行了修改，不可以声明为const
	int size(){
		int num = 0;
		for(pThis = pHead->next;pThis != nullptr;pThis = pThis->next){num++;}
		return num;
	}
	void clear(){
		pThis = pHead->next; Node<T>* temp ; while(pThis){temp = pThis->next; delete pThis; pThis = temp;}
	}
	void insert(const T& value,int index){
		pThis = pHead;
		for(int i = 0;i < index; ++i ){if(pThis->next != nullptr)pThis = pThis->next;}
		Node<T>* temp = new Node<T>(value,pThis->next);
		pThis->next = temp;
	}
	void sort(){
		Node<T>*p1;Node<T>*p2;
		for(p1 = pHead->next;p1 != nullptr;p1 = p1->next)
			for(p2 = p1->next;p2 != nullptr;p2 = p2->next)
				if(p1->val > p2->val)  swap(p1->val,p2->val);
	}
	Node<T>* begin(){
		if(pHead->next != nullptr)return pHead->next; else return nullptr;
	}
	Node<T>* end(){
		for(pThis = pHead->next;pThis->next != nullptr;pThis = pThis->next); return pThis;
	}
	void set(const T& value,int index){
		pThis = pHead;
		for(int i = 0;i < index; ++i ){if(pThis->next != nullptr)pThis = pThis->next;}
		pThis->next->val = value;
	}
	friend List<T>& operator+(List<T>& listA,List<T>& listB){
		Node<T>* b;
		if((b = listB.begin()) !=  nullptr){
			for(;b != nullptr;b = b->next){
				listA.push_back(b->val);
			}
		}
		return listA;
	}
};
#endif
//有些算法实现与参数无关，可以将函数的参数类型定义为一种特殊的“参数”，得到“函数模板”
//定义模板方法：template<typename T> ReturnType
//             Func(Agrs);
//函数模板在调用时，因为编译器能自动推导出实际参数的类型（这个过程叫做实例化）。
//所以，形式上调用一个函数模板与普通函数没有区别
//需要调用类型满足函数的要求。如要求类型T定义了加法运算符。当多个参数的类型不一致时，无法推导：cout<< sum(9, 2.1); //编译错误
//手工指定调用类型：sum<int>(9, 2.1)
//在定义类时也可以将一些类型信息抽取出来，用模板参数来替换，从而使类更具通用性。这种类被称为“类模板”
//有时，有些类型并不合适，则需要对模板进行特殊化处理，这称为“模板特化”
//模板特化时，特化的参数不能写进模板参数列表中，而是在函数名或类名后加上 <... , ...>
//模板的关联是在编译器处理，成为 静多态，基于继承和虚函数的多态在运行期处理，称为 动多态
