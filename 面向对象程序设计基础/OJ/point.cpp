#include<iostream>
using namespace std;
class Point{
	int _x;int _y;
public:
	Point(int x,int y):_x(x),_y(y){};
	Point(){};//加上函数体{}才是定义，否则只是声明！！！
	//前置自增运算符重载，有返回值便于连续进行运算
	Point operator++(){
		++ _x;
		++ _y;
		return Point(_x,_y);
	}
	//后置自增运算符重载,先创建临时变量再返回！！！
	Point operator++(int dummy){//哑元参数
		Point point(_x,_y);//创建中间变量
		++ _x;
		++ _y;
		return point;
	}
	//前置自减运算符
	Point operator--(){
		-- _x;
		-- _y;
		return Point(_x,_y);
	}
	//后置自减运算符
	Point operator--(int dummy){
		Point point(_x,_y);
		++ _x;
		++ _y;
		return point;
	}
	void show(){cout<<_x<<' '<<_y<<endl;}
};
int main(){
	int num,num1,num2;
	cin>>num>>num1>>num2;
	Point point(num1,num2);
	if(num == 1){++point;}
	else if(num == 2){--point;}
	point.show();
	return 0;
}