#include<iostream>
using namespace std;
class Pow{
	int y;
	double x;
public:
	Pow();
	void show();
	double pow();
};
Pow::Pow(){
	cin>>x>>y;
}
double Pow::pow(){
	double temp = 1.0;
	for(int i = 0; i < y;i++){
		temp *= x;
	}
	return temp;
}
void Pow::show(){
	cout<<pow();
}
int main(){
	Pow p;
	p.show();
	return 0;
}