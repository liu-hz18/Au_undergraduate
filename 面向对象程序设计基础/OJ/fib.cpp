#include<iostream>
using namespace std;
class Fib{
	int num;
	int result;
public:
	int fib(int num){
		if(num != 1 && num != 2)
			return fib(num - 1) + fib (num - 2);
		else if (num == 1)
			return 1;
		else if(num == 2)
			return 1;
	}
	Fib(){
		cin>>num;
	}
	void show(){
		cout<<fib(num);
	}
};

int main(){
	Fib f;
	f.show();
	return 0;
}