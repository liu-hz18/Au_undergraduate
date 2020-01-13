#include<iostream>
using namespace std;
class Ball{
private:
	int way;
	int total,num;
	int count,begin;
	void show(int total,int num,int begin,int count);
	int fact(int num);
public:
	//为了使得对象可以访问数据，使得函数得以传参，使用public变量
	Ball(int,int);
	int result();
};	
//可以同时使用初始化列表和函数体实现构造函数
Ball::Ball(int t,int n):count(0),begin(1),way(0){
	total = t;
	num = n;
}
//最初的从begin = 1开始计数！！
//面向对象的递归！！！
void Ball::show(int total,int num,int begin,int count){
	if(count == num){
		way += 1;
		return ;
	}
	else{
		for(int i = begin;i - count <= total - num + 1;i++ ){
			show(total,num,i + 1,count + 1);
		}
	}
}
//求阶乘
int Ball::fact(int num){
	if(num == 0)return 1;
	else return num * fact(num - 1);
}
int Ball::result(){
	show(total,num,begin,count);
	return way * fact(num);
}
int main(){
	Ball ball(5,3);
	//仅提供对外的函数接口，其内部实现和私有成员均不可访问！！体现了面向对象特点。
	cout<<ball.result();
	return 0;
}
