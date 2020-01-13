
#include<iostream>
#include<cmath>
#include<iomanip>
#include<typeinfo>
#include<cxxabi.h>
using namespace std;
#define PI 3.1415926

//抽象类：至少含有一个纯虚函数
class Shape{
protected:
	double x,y;
	double area;
	double perimeter;
public:
	Shape(const double& a,const double& b):x(a),y(b){ }
	Shape(){}
	void ShowArea();
	void ShowPerimeter();
	//求取并返回当前图形的顶点个数
	//定义为纯虚函数，在子类中进行具体实现
	//dynamic_cast方法
	//virtual int getVertexCount(Shape *pshape)const;//虚函数实现多态，向下类型转换的父类必须实现多态，即至少声明或继承了一个虚函数
	//typeid方法
	//virtual int getVertexCount(Shape& shape)const;
	//纯虚函数方法
	virtual int getVertexCount()const = 0;
};
void Shape::ShowArea(){printf("%.2f",area);}
void Shape::ShowPerimeter(){printf("%.2f",perimeter);}

//circle
class Circle:public Shape{
	double radius;
public:
	double getArea();
	double getPerim();
	Circle(){};
	Circle(const double& radius);
	//override关键字明确地告诉编译器一个函数是对基类中一个虚函数的重写覆盖，
	//编译器将对重写覆盖要满足的条件进行检查，正确的重写覆盖才能通过编译。
	/*
	如果没有override关键字，但是满足了重写覆盖的各项条件，也能实现重写覆盖。
	但是如果没有满足重写覆盖的各项条件，如参数写错了，此时会出现想实现的是重写覆盖，实际却是重写隐藏的情况。
	*/
	int getVertexCount()const override{
		//cout<<"Circle::getVertexCount()"<<endl;
		return 0;
	}
};
Circle::Circle(const double& radius):Shape(radius,radius){ }
double Circle::getArea(){return PI * x * x;}
double Circle::getPerim(){return 2 * PI * x;}

//rectangle类
class Rectangle:public Shape{
	double length;
	double width;
public:
	double getArea();
	double getPerim();
	Rectangle(){}
	Rectangle(const double& length,const double& width);
	/*
	int getVertexCount()const{
		//cout<<"Rectangle::getVertexCount()"<<endl;
		return 4;
	}
	*/
	int getVertexCount()const override{
		return 4;
	}
};
Rectangle::Rectangle(const double& length,const double& width):Shape(length,width){}
double Rectangle::getArea(){return x * y;}
double Rectangle::getPerim(){return  2 * (x + y);}

//正方形类
class Square:public Rectangle{
public:
	Square(const double& width):Rectangle(width,width){}
	Square(){}
	int getVertexCount()const{
		//cout<<"Square::getVertexCount()"<<endl;
		return 4;
	}
};
/*
//dynamic_cast方法，需要定义为虚函数，但不是纯虚函数
int Shape::getVertexCount(Shape* pshape)const{	
	Rectangle* prectangle = dynamic_cast<Rectangle*>(pshape);
	if(prectangle != nullptr){
		//cout<<"getit!\n";
		return 4;
	}
	Circle* pcircle = dynamic_cast<Circle*>(pshape);
	if(pcircle != nullptr){
		return 0;
	}
}
*/
/*
//typeid().name()方法，虚函数，但不是纯虚函数
int Shape::getVertexCount(Shape& shape)const{
	int status;
	string str = string(abi::__cxa_demangle(typeid(shape).name(),0,0,&status));
	if(str == "Rectangle"){
		return 4;
	}else if(str == "Circle"){
		return 0;
	}
}
*/
int main(){
	Rectangle rec(3.0,4.0);
	//Shape shape;
	//抽象类Shape不可以定义对象！！
	//实现向下类型转换要有纯虚函数！！
	//cout<<shape.getVertexCount(&rec);//dynamic_cast方法
	//cout<<shape.getVertexCount(rec);//typeid方法

	cout<<rec.getVertexCount();
	return 0;
}

/*
基类指针/引用转换成派生类指针/引用，则称为向下类型转换。（类层次中向下移动）
当我们用基类指针表示各种派生类时(向上类型转换)，保留了他们的共性，但是丢失了他们的特性。如果此时要表现特性，则可以使用向下类型转换。
比如我们可以使用基类指针数组对各种派生类对象进行管理，当具体处理时我们可以将基类指针转换为实际的派生类指针，进而调用派生类专有的接口。
如何保证基类指针指向的对象也可以被要转换的派生类的指针指向？——借助虚函数表进行动态类型检查！
c++提供了一个特殊的显式类型转换，称为dynamic_cast，是一种安全类型向下类型转换。
使用dynamic_cast必须有虚函数，因为它使用了存储在虚函数表中的信息判断实际的类型。
*/