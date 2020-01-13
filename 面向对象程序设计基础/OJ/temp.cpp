#include<iostream>
using namespace std;

class Temprature{
	double clesius;
	double fanhrenheit;
	void change();
public:
	Temprature();
	void show();
};
Temprature::Temprature(){
	cin>>fanhrenheit;
	clesius = 0.0;
}
void Temprature::change(){
	clesius = ((fanhrenheit - 32.0) * 5.0) / 9.0;
}
void Temprature::show(){
	change();//记得调用函数！！！
	printf("%.2f",clesius);
}
int main(){
	Temprature temp;
	temp.show();
	return 0;
}
