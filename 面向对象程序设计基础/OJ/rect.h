#ifndef RECT_H
#define RECT_H
#include<iostream>
using namespace std;
class Rect{
	float top,bottom,right,left;
public:
	//构造函数重载
	Rect();
	Rect(const float& to,const float& le,const float& bot,const float& ri);
	float getArea()const;//const的函数不能对其数据成员进行修改操作,const的对象，不能引用非const的成员函数。
	//把类成员函数声明为const   以表明它们不修改类对象
	//任何不会修改数据成员的函数都应该声明为const类型。如果在编写const成员函数时，不慎修改了数据成员，或者调用了其它非const成员函数，编译器将指出错误，这样做的好处是提高程序了的健壮性。

};
Rect::Rect(const float& to,const float& le,const float& bot,const float& ri){
	top = to;
	left = le;
	bottom = bot;
	right = ri;
}
float Rect::getArea()const{
	if((top >= bottom) && (right >= left))
		return (top - bottom) * (right - left);
	else return 0.0;
}

#endif