#include<iostream>
#include<string>
using namespace std;
class Test{
public:
	int operator()(int a,int b){
		cout<<"operator()called."<<a<<' '<<b<<endl;
		return a + b;
	}
};

int main(){
	Test sum;
	int s = sum(4,3);//不是构造函数，也被成为函数对象
	cout << "a + b = " << s << endl;


	//两种方式等价！！！
	
	int t = sum.operator()(5,6);
	cout << "a + b = " << t << endl;

	return 0;
}
