
#ifndef SHAPE_H
#define SHAPE_H

#include<iostream>
#include<cmath>
#include<iomanip>
#include<typeinfo>
#include<cxxabi.h>
using namespace std;
#define PI 3.1415926

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
	int getVertexCount()const override{return 0;}
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
	int getVertexCount()const override{return 4;}
};
Rectangle::Rectangle(const double& length,const double& width):Shape(length,width){}
double Rectangle::getArea(){return x * y;}
double Rectangle::getPerim(){return  2 * (x + y);}

//正方形类
class Square:public Rectangle{
public:
	Square(const double& width):Rectangle(width,width){}
	Square(){}
	int getVertexCount()const override{return 4;}
};


#endif