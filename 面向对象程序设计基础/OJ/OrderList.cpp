#include<iostream>
using namespace std;

template <typename T>
class Node{
public:
	T val;
	Node<T>* next;
	//Node() = default;
	Node(T value,Node<T>* ptr):val(value),next(ptr){};
	Node(Node<T>* ptr):next(ptr){};
};

template <typename T>
class OrderList{
	Node<T>* pHead;
	Node<T>* pThis;
public:
	//OrderList() = default;//使用无参版本
	OrderList(){pHead = new Node<T>(nullptr);pThis = pHead;}//调用构造函数必须加上type-specifier:  <T>
	//~OrderList() = default;
	//注意析构函数释放空间！
	~OrderList(){pThis = pHead; Node<T>* temp ; while(pThis){temp = pThis->next; delete pThis; pThis = temp;}}
	void insert(const T& value){
		Node<T>* pPre = pHead;
		for(pThis = pHead -> next;pThis != nullptr && pThis -> val < value ;pPre = pThis,pThis = pThis -> next);
		Node<T>* temp = new Node<T>(value,pThis);
		pPre -> next = temp;
	}
	void insert(Node<T>* pNode){
		Node<T>* pPre = pHead;
		for(pThis = pHead -> next;pThis != nullptr && pThis -> val < pNode -> val ;pPre = pThis,pThis = pThis -> next);
		pNode -> next = pThis;
		pPre -> next = pNode;
	}
	void display(){for(pThis = pHead->next;pThis != nullptr;pThis = pThis->next){cout<<pThis->val<<" ";}cout<<endl;}
	Node<T>* begin(){if(pHead->next != nullptr)return pHead->next; else return nullptr;}
};


int main(){
	OrderList<int> listA;
	OrderList<int> listB;
	int num_this;
    for(int i=0; i < 5; ++i){
        cin >> num_this;
        listA.insert(num_this);
        listA.display();
    }
    for(int i=0; i < 5; ++i){
        cin >> num_this;
        listB.insert(num_this);
        listB.display();
    }
    Node<int>* ptr = listB.begin();
    while(ptr){
		Node<int>* temp = ptr->next;
    	listA.insert(ptr);
    	listA.display();
    	ptr = temp;
    }
	return 0;
}
