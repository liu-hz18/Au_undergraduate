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
	Shape(){};
	Shape(double a,double b):x(a),y(b){ }
	void ShowArea();
	void ShowPerimeter();
	virtual double getArea() = 0;
	virtual double getPerim() = 0;
	//求取并返回当前图形的顶点个数
	//实现了多态
	virtual int getVertexCount()const = 0;//纯虚函数可以在类外实现定义！
};
void Shape::ShowArea(){printf("%.2f",area);}
void Shape::ShowPerimeter(){printf("%.2f",perimeter);}
int Shape::getVertexCount()const{
	cout<<"Shape::getVertexCount"<<endl;
}


//circle类
class Circle:public Shape{
	double radius;
public:
	double getArea();
	double getPerim();
	Circle(){};
	Circle(const double& radius);
	int getVertexCount()const override;//纯虚函数在子类必须有实现，否则子类也为抽象类
};
Circle::Circle(const double& radius):Shape(radius,radius){ }
double Circle::getArea(){return PI * x * x;}
double Circle::getPerim(){return 2 * PI * x;}
int Circle::getVertexCount()const{
	cout<<"Circle::getVertexCount"<<endl;
	return 0;
}

//rectangle类
class Rectangle:public Shape{
	double length;
	double width;
public:
	double getArea();
	double getPerim();
	Rectangle(){};
	Rectangle(const double& length,const double& width);
	int getVertexCount()const override;//父类为虚函数，则子类默认为虚函数
};
Rectangle::Rectangle(const double& length,const double& width):Shape(length,width){}
double Rectangle::getArea(){return x * y;}
double Rectangle::getPerim(){return  2 * (x + y);}
int Rectangle::getVertexCount()const{
	cout<<"Rectangle::getVertexCount"<<endl;
	return 4;
}
//正方形类
class Square:public Rectangle{
	double width;
public:
	Square(){};
	Square(const double& width):Rectangle(width,width){}
	//Square(){};
	//子类的构造函数必须和父类构造函数对应，子类有默认构造函数则基类必须有默认构造函数。
	int getVertexCount()const override;
};
int Square::getVertexCount()const{
	cout<<"Square::getVertexCount"<<endl;
	return 4;
}
//父类为虚函数，则子类均为虚函数，参数相同，为重写覆盖（override）
//override关键字明确地告诉编译器一个函数是对基类中一个虚函数的重写覆盖，编译器将对重写覆盖要满足的条件进行检查，正确的重写覆盖才能通过编译，防止参数写错的情况发生
//在虚函数声明或定义中使用时，final确保函数为虚且不可被派生类重写。可在继承关系链的“中途”进行设定，禁止后续派生类对指定虚函数重写。使得虚函数链中断
//在类定义中使用时，final指定此类不可被继承。只有虚函数才可以定义final。
//class B final 表示B类不可以被继承
//void function() final 表示虚函数继承中断，其子类不可以override，但子类对象仍然可以调用
//虚函数进一步被声明为纯虚函数，则为“抽象类”，不允许定义对象，可以定义对象指针对子类进行取址
//抽象类（至少含有一个纯虚函数）不允许定义对象，定义基类为抽象类的主要用途是为派生类规定共性“接口”getVertexCount();
//抽象类可以避免对象切片：保证只有指针和引用可以被向上类型转换
int main(){

	Rectangle rec(3.0,4.0);
	
	Shape* pshape1 = &rec;
	Circle cir(1.0);
	Shape* pshape2 = &cir;
	//不同调用方法，编译时绑定
	rec.getVertexCount();
	cir.getVertexCount();
	//同一调用方法，根据实际对象类型完成相应动作，虚函数运行时绑定
	pshape1 -> getVertexCount();//父类（纯）虚函数：Rectangle::getVertexCount；父类普通函数：Shape::getVertexCount
	pshape2 -> getVertexCount();//父类（纯）虚函数：Circle::getVertexCount；父类普通函数：Shape::getVertexCount
	
	Square squ(1.0);
	Shape* pshape3 = &squ;
	Rectangle* prectangle = &squ;
	pshape3 -> getVertexCount();//父父类（纯）虚函数：Square::getVertexCount；父父类普通函数：Shape::getVertexCount
	prectangle -> getVertexCount();//父父类（纯）虚函数：Square::getVertexCount；父父类普通函数：Rectangle::getVertexCount
	//Shape shape(1.0,1.0);//Shape类虚函数：Shape::getVertexCount；Shape类纯虚函数（抽象类）：编译错误！！
	//shape.getVertexCount();
	rec.Shape::getVertexCount();//Shape::getVertexCount
	//Shape类定义为虚函数或纯虚函数，派生类成员函数 或 派生类对象可以通过Shape::getVertexCount()调用基类函数
	
	//向上类型转换（基类指针表示派生类对象）保留了共性，丢失了特性
	//向上类型转换：1.转换为基类指针或引用，对应虚函数表仍为派生类虚函数表（晚绑定）2.转换为基类对象，对应虚函数表示基类虚函数表（早绑定）
	Shape* pshape4 = new Rectangle;//向上类型转换
	pshape4 -> getVertexCount();//Rectangle::getVertexCount
	delete pshape4;//删除的是内存，但指针变量没有被删除
	pshape4 = new  Circle;
	pshape4 -> getVertexCount();//Circle::getVertexCount
	delete pshape4;
	//shape4 = new Shape;//抽象类不允许定义对象

	//向下类型转换（基类指针/引用 转换为 派生类指针/引用）
	//显式类型转换（dynamic_cast)是安全类型的向下类型转换，必须有继承关系，使用时必须有虚函数，因为它使用了虚函数表
	//static_cast 不进行类型检查，只检查继承关系，不安全，不能保证转换之后是期望类型的指针或引用
	Shape* pshape5 = &rec;
	Rectangle* prec1 = dynamic_cast<Rectangle*>(pshape5);//失败时返回nullptr
	//Rectangle* prec = dynamic_cast<Rectangle*>(&rec);//等价写法
	if(prec1 != nullptr){
		cout<<"OK"<<endl;
		prec1 -> getVertexCount();//Rectangle::getVertexCount
	}
	Shape& pshape6 = rec;
	Rectangle& prec2 = dynamic_cast<Rectangle&>(pshape6);//传入是一个上层引用，失败时抛出bad_cast异常
	//Rectangle& prec2 = dynamic_cast<Rectangle&>(rec);//等价写法
	prec2.getVertexCount();//Rectangle::getVertexCount

	Shape& shape7 = rec;//此处是有虚函数的引用，相当于rec!!不需要使用->，直接成员访问即可
	shape7.getVertexCount();//Rectangle::getVertexCount
}
/*
多态的条件：继承，虚函数，引用或指针
按照基类的接口定义，调用指针或引用所指对象的接口函数，函数执行过程因对象实际所属派生类的不同而呈现不同的效果（表现），这个现象被称为“多态”
当利用基类指针/引用调用函数时,虚函数在运行时确定执行哪个版本，取决于引用或指针对象的真实类型,非虚函数在编译时绑定
当利用类的对象直接调用函数时,无论什么函数，均在编译时绑定
*/
/*
通过基类定好接口后，不必对每一个派生类特殊处理，只需要调用抽象基类的接口即可。大大提高程序的可复用性。
不同派生类对同一接口的实现不同，能达到不同的效果，提高了程序可拓展性和可维护性。
*/
//类库提供公共行为，用户定制特殊细节。在父类中定义算法骨架，在子类中写出具体实现细节
