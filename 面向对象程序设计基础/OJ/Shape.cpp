#include<iostream>
#include<cmath>
#include<iomanip>//manipulator（操纵器）
using namespace std;
#define PI 3.1415926

//形状类，父类
class Shape{
//为了子类成员函数可以访问x,y,z,设为保护成员
//私有成员不可以通过对象进行访问，只可以通过类内公有函数提供接口访问，对派生类不可见
//保护成员不可以通过对象访问，只可以通过接口，但对派生类可见
//公有成员外界可以访问
protected:
	double x,y,z;
	//面积和长度是父类的特性，不是父类的对象的特性，设为静态,要在类外赋初值
	double area;
	double perimeter;
public:
	Shape(double a,double b,double c):x(a),y(b),z(c){ }//采用初始化列表初始化，更加方面简洁
	void ShowArea();
	void ShowPerimeter();
};
//double Shape::area = 0.0;//注意类外静态变量赋初值！！！
//double Shape::perimeter = 0.0;
void Shape::ShowArea(){
	printf("%.2f",area);
}
void Shape::ShowPerimeter(){
	printf("%.2f",perimeter);
}


//circle类
class circle:public Shape{
	double radius;
public:
	double getArea();
	double getPerimeter();
	circle(const double& radius);
};
//初始化列表初始化，可以用于：子类初始化父类的私有成员、显示调用父类的构造函数对父类数据成员进行初始化、需要初始化const修饰的类成员或初始化引用成员数据；
//初始化列表初始化不可以将不属于本类的成员的成员列入列表，只可以通过显式或隐式调用父类构造函数，之后再函数体内进行初始化，或者也可以将参数值直接传入列表，更加方便
circle::circle(const double& radius):Shape(radius,radius,radius){ }//显示调用父类的构造函数对父类数据成员进行初始化
//	x = y = z = radius;
//}
double circle::getArea(){//基类中的保护成员对子类可见
	area = PI * x * x;
}
double circle::getPerimeter(){
	perimeter =  2 * PI * x;
}


//square类
class square:public Shape{
	double sidelength;
public:
	double getArea();
	double getPerimeter();
	square(const double& length);
};
//如果想通过输入进行初始化，只需将输入操作放入构造函数内。
square::square(const double& length):Shape(x,y,z){
	x = y = z = length;
}
double square::getArea(){
	return x * x;
}
double square::getPerimeter(){
	return 4 * x;
}


//rectangle类
class rectangle:public Shape{
	double length;
	double width;
public:
	void getArea();
	void getPerimeter();
	rectangle(const double& length,const double& width);
};
//采用形参初始化，体现“函数”特性，实质上为第一个形参列表传入第二个形参列表
rectangle::rectangle(const double& length,const double& width):Shape(x,y,z){
	x = length;
	y = z = width;
}
void rectangle::getArea(){
	//printf("impelemented\n");
	area = x * y;//子类成员函数可以访问父类保护或公有变量，对外提供接口。
	//printf("%.2f",area);
}
void rectangle::getPerimeter(){
	perimeter = 2 * (x + y);
}


//triangle类
class triangle:public Shape{
	double side1,side2,side3;
public:
	double getArea();
	double getPerimeter();
	triangle(const double& side,const double& side2,const double& side3);
};
triangle::triangle(const double& side1,const double& side2,const double& side3):Shape(x,y,z){
	x = side1;
	y = side2;
	z = side3;
}
double triangle::getArea(){
	double p = (x + y + z)/2.0;
	return sqrt(p * (p - x) * (p - y) * (p - z) );
}
double triangle::getPerimeter(){
	return x + y + z;
}


int main(){
	int num;
	//Shape sha;
	cin>>num;
	switch(num){
	case 1:{
		//该部分完全使用接口进行。子类函数对父类属性进行了修改。
		rectangle rec(3.0,4.0);
		rec.getArea();
		rec.ShowArea();
		break;
	}
	//赋值 + 调用子类函数 
	case 2:{
		square squ(2.0);
		printf("%.2f",squ.getArea());
		break;
	}
	case 3:{
		triangle tri(2.0,2.0,2.0);
		//cin>>tri.side1>>tri.side2>>tri.side3;
		//tri.getArea();
		printf("%.2f",tri.getArea());
		break;
	}
	case 4:{
		circle cir(2.0);
		//cin>>cir.radius;
		//cir.getArea();
		printf("%.2f",cir.getArea());
		break;
	}
	default:
		break;
	}
	return 0;
}
