#include<iostream>
#include<string>
using namespace std;
class Empolyee{
	string name;
	string address;
	string city;
	string code;
public:
	void change_name();
	void display();
	Empolyee();
};
Empolyee::Empolyee(){
	getline(cin,name);
	getline(cin,city);
	getline(cin,address);
	getline(cin,code);
}
void Empolyee::display(){
	cout<<"Name: "<<name<<endl;
	cout<<"City: "<<city<<endl;
	cout<<"Address: "<<address<<endl;
	cout<<"Postcode: "<<code<<endl;
}
void Empolyee::change_name(){
	getline(cin,name);
}
int main(){
	Empolyee empolyee;
	empolyee.display();
	empolyee.change_name();
	empolyee.display();
	return 0;
}