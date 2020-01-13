#ifndef SHAPE_H
#define SHAPE_H

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
#define PI 3.1415926

//形状类
class Shape{
protected:
	double x,y;
	double area;
	double perimeter;
public:
	Shape(double a,double b):x(a),y(b){ }
	void ShowArea();
	void ShowPerimeter();
	//求取并返回当前图形的顶点个数
	virtual int getVertexCount()const;
};
void Shape::ShowArea(){printf("%.2f",area);}
void Shape::ShowPerimeter(){printf("%.2f",perimeter);}
int Shape::getVertexCount()const{}


//circle类
class Circle:public Shape{
	double radius;
public:
	double getArea();
	double getPerim();
	Circle(const double& radius);
	int getVertexCount()const;
};
Circle::Circle(const double& radius):Shape(radius,radius){ }
double Circle::getArea(){return PI * x * x;}
double Circle::getPerim(){return 2 * PI * x;}
int Circle::getVertexCount()const{return 0;}

//rectangle类
class Rectangle:public Shape{
	double length;
	double width;
public:
	double getArea();
	double getPerim();
	Rectangle(const double& length,const double& width);
	int getVertexCount()const;
};
Rectangle::Rectangle(const double& length,const double& width):Shape(length,width){}
double Rectangle::getArea(){return x * y;}
double Rectangle::getPerim(){return  2 * (x + y);}
int Rectangle::getVertexCount()const{return 4;}
//正方形类
class Square:public Rectangle{
	double width;
public:
	Square(const double& width):Rectangle(width,width){}
	Square(){};
	int getVertexCount()const;
};
int Square::getVertexCount()const{return 4;}
#endif

/*
RTTI（Run-Time Type Identification，运行时类型识别），它使程序能够获取由基指针或引用所指向的对象的实际派生类型
，即允许“用指向基类的指针或引用来操作对象”的程序能够获取到“这些指针或引用所指对象”的实际派生类型。
在C++中，为了支持RTTI提供了两个操作符：dynamic_cast和typeid
 dynamic_cast允许运行时刻进行类型转换，从而使程序能够在一个类层次结构中安全地转化类型，
 与之相对应的还有一个非安全的转换操作符static_cast
*/
