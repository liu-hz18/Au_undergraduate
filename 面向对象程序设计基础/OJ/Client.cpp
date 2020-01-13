#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Client{
	//静态数据在实现文件中赋值
	static string SeverName;
	static int ClientNum;
public:
	static void ChangeSeverName(string& str);
	static void ChangeClientNum(const int& flag,int& num);
	Client(){
		cout<<"server name: "<<SeverName<<endl;
  		cout<<"client number: "<<ClientNum<<endl;
	};
	void show()const;
	void operate();
};
void Client::show()const{
	cout<<"server name: "<<SeverName<<endl;
	cout<<"client number: "<<ClientNum<<endl;
}
void Client::ChangeSeverName(string& str){
	SeverName = str;
	
}	
void Client::ChangeClientNum(const int& flag,int& num){
	if(flag == 1){
		ClientNum += num;
		if(ClientNum > 100000)ClientNum = 100000;
	}else if (flag == 0){
		ClientNum -= num;
		if(ClientNum < 0)ClientNum = 0;
	}

}
void Client::operate(){
	int num,change;
	string temp,str;
	cin>>num;
	/*
	vector<int> change;vector<int>::iterator it_change;
	vector<string> str;vector<string>::iterator it_str;
	vector<string> op;
	for(int i = 0;i < num;i ++){
		cin>>temp;
		op.push_back(temp);
		if(temp == "add"||temp == "sub"){
			int chan;
			cin>>chan;
			change.push_back(chan);	
		}else if(temp == "rename"){
			string s;
			cin>>s;
			str.push_back(s);
		}
	}
	it_change = change.begin();
	it_str = str.begin();
	*/
	for(int i = 0;i < num;i ++){
		cin>>temp;
		if(temp == "add"){
			cin>>change;
			ChangeClientNum(1,change);
				show();
			//it_change++;
		}else if(temp == "sub"){
			cin>>change;
			ChangeClientNum(0,change);
				show();
			//it_change++;
		}else if(temp == "rename"){
			cin>>str;
			ChangeSeverName(str);
				show();
			//it_str++;
		}
	}
}
//严格来讲应在.h中声明，在.cpp中初始化
string Client::SeverName = "Server1";
int Client::ClientNum = 0; 
int main(){
	Client client;
	client.operate();
	return 0;
}

