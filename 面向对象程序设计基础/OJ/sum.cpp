#include<iostream>
#include<cstdlib>
using namespace std;
int main(int argc,char**argv){
	//总是考虑边界和异常的情况！！！
	if(argc != 3){
		cout << "Usage:" << argv[0] << " op1 op2"<<endl;
		return 1;
	}
	int a,b;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	cout<<"a + b = "<<a+b<<endl;
	return 0;
}
