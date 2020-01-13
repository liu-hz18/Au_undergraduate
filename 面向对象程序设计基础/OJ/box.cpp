#include<iostream>
using namespace std;
class BOX{
	int length;
public:
	BOX();
	void show();
};
BOX::BOX(){
	cin>>length;
}
void BOX::show(){
	cout<<length * length * length<<' '<<6 * length * length;
}
int main(){
	BOX box;
	box.show();
	return 0;
}