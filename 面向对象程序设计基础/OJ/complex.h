#ifndef COMPLEX_H
#define COMPLEX_H
#include<iostream>
#include<iomanip>
using namespace std;
class Complex{
	float re,im;
	
public:
	//传递一个类对象时，形参应设为引用，因为不引用就会调用 拷贝构造函数。传递int double时。可以不使用引用
	//默认拷贝构造函数会将非静态对象逐个“浅拷贝”，遇到指针就会指向同一个区域，所以应避免使用默认拷贝构造函数
	//赋值运算符也需要自定义重载，不然系统会默认调用“浅拷贝”的赋值运算符
	Complex();
	Complex(int a,int b);
	Complex(float a);//赋值构造函数可以不采用引用，增加了一次拷贝
	Complex(float a,float b);//引用参数的默认参数只能在函数体外对b赋值，再传递进去，不能直接赋值。
	void add(Complex& b);
	void show()const;
	Complex(const Complex& com){//拷贝构造函数的形参必须是引用，防止无限递归
		cout<<"Copy constuction"<<endl;
	}
	//返回值是对象的引用，使得 连等 可以进行
	//Complex c;c = 4.5;重载了等号，只传递一个参数，实际上是先 利用4.5 拷贝构造了一个对象，而4.5不满足拷贝构造的要求，所以编译错误
	//Complex c = 4.5;等价于Complex c(4.5);不调用运算符重载，只调用构造函数
	Complex& operator=(const float& src){
		cout<<"operator= float"<<endl;
		this->re = src;
		this->im = 0.0;
		return *this;
	}
	Complex& operator=(const int& src){
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

Complex::Complex(int a,int b){
	re = float(a);
	im = float(b);
}

Complex::Complex(float a,float b){
	re = a;
	im = b;
}

Complex::Complex(float a){
	cout<<"contruct complex(a)"<<endl;
	re = a;
	im = 0.0;
}

void Complex::add(Complex& b){
	this->re += b.re;
	this->im += b.im;
}
void Complex::show()const{
	cout<<fixed<<setprecision(2)<<re<<" + "<<im<<'i'<<endl;
}
//是否将返回值的类型声明为该类型的引用，并在函数结束前返回实参自身的引用（即*this）。
//只有返回一个引用，才可以允许连续赋值
//否则如果函数的返回是void，将不能做连续赋值，即类似于str1=str2=str3将不能通过编译。 
/*
是否将传入的参数的类型声明为常量引用。
如果传入的是实参而不是引用，那么从形参到实参将会调用一次复制构造函数。这样会增大无谓的消耗。
赋值运算符不会改变传入的实例的状态，所以应该为传入的引用的参数加上const关键字
*/
/*
是否释放实例自身已有的内存。如果在分配新内存之前释放自身已有的空间，程序会出现内存泄露
*/
/*
是否判断传入的参数和当前的实例（*this）是不是同一个实例 ，类似于（a=a）
如果是，则不需要进行赋值操作，直接返回。
如果是，一旦释放自身的内存时，传入的参数的内存也同时被释放，就会找不到需要赋值的内容了。 
*/
//如果是类中含有动态分配的内存，不能使用系统赋值运算符，因为等号两边的两个类在析构时的空间被释放了两次。
//需要在重载函数中重新开辟内存，而不是使得两个指针指向同一个内存。
/*
为什么拷贝构造函数必须是引用传递，不能是值传递？
     简单的回答是为了防止递归引用。
     当 一个对象需要以值方式传递时，编译器会生成代码调用它的拷贝构造函数以生成一个复本。
     如果类A的拷贝构造函数是以值方式传递一个类A对象作为参数的话，当 需要调用类A的拷贝构造函数时，
     需要以值方式传进一个A的对象作为实参； 而以值方式传递需要调用类A的拷贝构造函数；
     结果就是调用类A的拷贝构造函数导 致又一次调用类A的拷贝构造函数，这就是一个无限递归。

*/
/*
拷贝构造函数在四种情况下被调用：
1、对象以值传递的方式传入函数参数
2、对象以值传递的方式从函数返回
3、新建一个对象并将其初始化为同类现有对象
*/

#endif
