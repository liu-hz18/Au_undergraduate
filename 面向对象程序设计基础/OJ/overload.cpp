#include<iostream>
using namespace std;
class Max{
public:
	int int_a,int_b;
	double dou_a,dou_b;
	int max(int a,int b){
		return (a > b) ? a : b;
	}
	double max(double a,double b){
		return (a > b) ? a : b;
	}
};

int main(){
	Max m;
	int num;
	cin>>num;
	if(num == 1){
		cin>>m.int_a>>m.int_b;
		cout<<m.max(m.int_a,m.int_b);
	}else if(num == 2){
		cin>>m.dou_a>>m.dou_b;
		printf("%.1f",m.max(m.dou_a,m.dou_b));	
	}
	return 0;
}