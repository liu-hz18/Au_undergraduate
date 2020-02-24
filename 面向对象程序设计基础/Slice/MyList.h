
#pragma once
#include <list>
#include <memory>
#include <iostream>
using namespace std;

//使用std::list可以避免迭代器失效
//使用std::vector，修改数组大小会使得迭代器失效
class MyList{
private:
	std::shared_ptr< std::list<int> > pt; // a pointer to the real container
	std::list<int>::iterator left, right; // the position of slice is [left, right). 
	//'left' is included, 'right' is excluded.

	std::list<int>::iterator forward(int pos) const{
		// count from 'left', find the element at position 'pos'.
		auto now = left;
		while(pos--) now++;
		return now;
	}

public:
	MyList(): pt(new std::list<int>()){
		left = pt->begin();
		right = pt->end();
		// Actually, left = right = pt->end(), because there is no element in the list.
	}

	void append(int i){
		pt->insert(right, i); //insert i just before 'right'. 'right' and 'left' will be still valid \\
		(because we use list, not vector).
		// DEBUG !! Why I can't insert i??
		if(left == right)left--;//注意！！！插入数据后，两个迭代器指针会同步移动，所以最初时要将左侧指针left指向队首。
	}

	int& operator[](int pos) const{
		return *forward(pos); // access the element at the 'pos'
	}

	friend ostream& operator<<(std::ostream& out, const MyList& mylist){
		out << "[";
		if (mylist.left != mylist.right){
			auto now = mylist.left;
			out << *now;
			now ++;
			for(; now != mylist.right; now++){
				out << "," << *now;
			}
		}
		out << "]";
		return out;
	}
	MyList operator()(int a, int b){
		auto newleft = left;
		auto newright = left;
		while(a--)newleft++;
		while(b--)newright++;
		MyList alist;
		alist.pt = pt;
		alist.left = newleft;
		alist.right = newright;
		return alist;
	}
};