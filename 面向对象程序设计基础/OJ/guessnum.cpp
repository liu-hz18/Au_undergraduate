#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
class Guess{
private:
	int realnum,guessnum;
public:
	void WhileLoop();
	void DoWhileLoop();
	Guess();
};
Guess::Guess(){
	//srand((unsigned) time(0));//强制类型转换要加括号！！！
	cin>>realnum;//rand()%100 + 1;
}
void Guess::WhileLoop(){
	while(1){
		cin>>guessnum;
		if(guessnum != realnum)cout<<"False"<<'\n';
		else {
			cout<<"True"<<'\n';
			break;
		}
	}
}
void Guess::DoWhileLoop(){
	do{
		cin>>guessnum;
		if(guessnum != realnum)cout<<"False"<<'\n';
		else{
			cout<<"True"<<'\n';
			break;
		}
	}while(1);
}
int main(){
	char num;
	cin>>num;
	Guess gue;
	switch(num){
	case'w':{
		gue.WhileLoop();
		break;
	}
	case'd':{
		gue.DoWhileLoop();
		break;
	}
	default:break;
	};
	return 0;
}