#include<iostream>
using namespace std;
//public继承时子类成员函数可以访问父类的public和protected成员
//子类对象可以访问public成员
class Animal{
protected:
	int age;
};
class Dog:public Animal{
public:
	void SetAge(int n);
};
void Dog::SetAge(int n){
	age = n;
}
int main(){
	Dog dog;
	dog.SetAge(10);
	return 0;
}