#include<iostream>
#include<string>
#include<iomanip>
using namespace std;
class RAM{
	string type;
public:
	RAM();
	void run();
	void stop();
	void set();
};
RAM::RAM(){//cin>>type;}
void RAM::set(){cin>>type;}
void RAM::run(){
	cout<<"RAM RUN"<<endl;
	cout<<"RAM type: "<<type<<endl;
}
void RAM::stop(){cout<<"RAM STOP"<<endl;}

class CDROM{
	string type;
public:
	CDROM();
	void set();
	void run();
	void stop();
};
CDROM::CDROM(){	//cin>>type;}
void CDROM::set(){	cin>>type;}
void CDROM::run(){
	cout<<"CDROM RUN"<<endl;
	cout<<"CDROM type: "<<type<<endl;
}
void CDROM::stop(){cout<<"CDROM STOP"<<endl;}

enum CPU_Rank {P1 = 1,P2,P3,P4,P5,P6,P7};
class CPU{
	CPU_Rank cpu_rank;
	unsigned int frequency;
	double voltage;
public:
	CPU();
	~CPU();
	void run();
	void stop();
	void set();
	//类内进行友元的生命，可以访问该类一切成员，friend修饰的函数不受private的影响
	//构造函数、析构函数也可以是友元，别的类的函数也可以是本类的友元。
	//友元不传递、友元不继承、不可定义class
	friend istream& operator>>(istream& in,CPU& dst);
	friend ostream& operator<<(ostream& out,const CPU& src);
};
//不能直接用cin直接输入数据到枚举变量，但可以先输入到整形变量，再赋值给枚举变量，也可以直接赋值常量：
//枚举变量可以直接输出，但不能直接输入.\
//C++里枚举变量可以赋值给非枚举变量，非枚举变量不能赋给枚举变量。
//枚举变量不支持算数运算
istream& operator>>(istream& in,CPU_Rank& dst){
	int temp;
	in>>temp;
	dst = CPU_Rank(temp);//强制类型转换,也可以用static_cast<CPU_Rank>(temp),没有安全检查
	return in;
}
//如果不在输出流重载，则枚举类型输出的是一个整型
ostream& operator<<(ostream& out,const CPU_Rank& src){
	static const string str[] = {"P1","P2","P3","P4","P5","P6","P7"};
	//vector<string>不可以用此形式初始化，要先构建二维数组，在push_back或者vector<string> strArray(str, str+str.size());
	cout<<str[src - 1];
	return out;
}
CPU::CPU(){
	//cin>>cpu_rank;
	//cin>>frequency>>voltage;
	//cout<<"CPU Construct"<<endl;
}
CPU::~CPU(){//cout<<"CPU Destroy"<<endl;}
void CPU::set(){
	cin>>cpu_rank;
	cin>>frequency>>voltage;
}
void CPU::run(){
	cout<<"CPU RUN"<<endl;
	cout<<"CPU rank: "<<cpu_rank<<endl;
	cout<<"CPU frequency: "<<frequency<<" MHz"<<endl;
	cout<<fixed<<setprecision(2)<<"CPU voltage: "<<voltage<<" V"<<endl;
}
void CPU::stop(){cout<<"CPU STOP"<<endl;}

class Computer{
	CPU cpu;
	RAM ram;
	CDROM cdrom;
public:
	Computer();
	void run();
	void stop();
};
//子对象构造时若需要参数，则应在当前类的构造函数的初始化列表中进行。
//若使用默认构造函数来构造子对象，则不用做任何处理
//先完成子对象构造，再完成当前对象构造,子对象构造的次序仅由在类中声明的次序所决定
//如果想根据输入决定对象的赋值顺序，就不能在子类中使用构造函数初始化，必须自定义set函数初始化
//因此在本例中，把子类中的析构函数初始化去掉了，换成了set()函数初始化
Computer::Computer(){
	string str;
	for(int i = 0;i < 3;i ++){
		cin>>str;
		if(str == "CPU")cpu.set();
		else if (str == "RAM")ram.set();
		else if (str == "CDROM")cdrom.set();
	}
}
void Computer::run(){
	cout<<"Computer RUN"<<endl;
	cpu.run();
	ram.run();
	cdrom.run();
}
void Computer::stop(){
	cdrom.stop();
	ram.stop();
	cpu.stop();
	cout<<"Computer STOP"<<endl;
}
int main(){
	//CPU cpu;
	//cpu.run();
	//cpu.stop();
	Computer computer;
	computer.run();
	computer.stop();
	return 0;
}