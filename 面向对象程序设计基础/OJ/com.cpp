#include<iostream>
#include<iomanip>
using namespace std;
class Complex{
	float re,im;
public:
	Complex(){
		cout<<"contruct complex()"<<endl;
	}
	Complex(const Complex& com){
		cout<<"Copy constuction"<<endl;
		re = com.re;
		im = com.im;
	}
	//引用的使用必须一一对应，构造函数实参为常量时，形参若使用引用，应为const float&
	//构造函数实参为变量。形参使用引用，则应为float
	//并且形参使用const float& 或 float的时候才能使用默认参数，float&不可以
	//Complex a;a = 4.5;调用赋值运算符重载，形式必须一一对应。
	//赋值运算符重载应使用 引用，防止拷贝构造函数的使用。同时返回类型为Compelx& 便于连等的使用，最后return *this
	//Complex a = 4.5;调用构造函数，形式必须一一对应
	//拷贝构造函数的形参是同类对象的常量引用 Complex&
	//两个类对象之间的赋值（在声明时赋值）调用拷贝构造函数(注意拷贝构造函数为系统自动执行，如果自己定义过，那么就执行用户自定义的拷贝构造，也就是会覆盖)
	//两个类对象之间赋值（先声明后赋值）在声明时调用默认构造函数，之后调用赋值运算符重载
	Complex(const float &a){
		cout<<"contruct complex(float)"<<endl;
		re = a;
		im = 0.0;
	}
	Complex(const float& a, const float& b){
		cout<<"contruct complex(float,float)"<<endl;
		re = a;
		im = b;
	}
	void show()const{
		cout<<fixed<<setprecision(2)<<re<<" + "<<im<<'i'<<endl;
	}
	Complex& operator=(const float& src){
		cout<<"operator= float"<<endl;
		this->re = src;
		this->im = 0.0;
		return *this;
	}
	Complex& operator=(const int& src){
		cout<<"operator= int"<<endl;
		this->re = float(src);
		this->im = 0.0;
		return *this;
	}
	Complex& operator=(const double& src){
		cout<<"operator= double"<<endl;
		this->re = float(src);
		this->im = 0.0;
		return *this;
	}
	Complex& operator=(const Complex& src){
		cout<<"operator= complex"<<endl;
		this->re = src.re;
		this->im = src.im;
		return *this;
	}
};
ty
int main(){
	Complex a = 4.5;	//construct complex(float)
	Complex b;			//construct complex()
	b = 4.5;			//operator= (float)
	Complex d(4.5,10.0);//construct complex(float,float)
	Complex c = d;		//Copy constuction
	c.show();
	d.show();
	return 0;
}
