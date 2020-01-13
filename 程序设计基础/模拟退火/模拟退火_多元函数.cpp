//time:  2019/3/7 19:12
//task:  SA(variable function)

#include<iostream>
#include<math.h>
#include<time.h>
#include<Windows.h>
using namespace std;

//玻尔兹曼常量
#define K 8.6173324e-5
#define PI 3.1415926

//约束条件
#define x_floor -1.0		//x区间上界
#define x_ceiling 1.0		//x区间下界
#define y_floor -1.0		//y区间上界
#define x_ceiling 1.0		//x区间下界

//退火初始温度
double T0 = 10000000.0;
//退火最终温度
#define Tf 10.0

//势能函数
double E(double x,double y){
	return sin(x*y)+exp(x*y);			//请在次数定义二元函数
}

//产生从low到high的浮点随机数
double rnd(double low,double high){
	double temp = rand()/((double)RAND_MAX+1.0);
	return low+temp*(high-low);
}

//伪随机数产生新解,必须采用随机方式
double NewSolution(double x,double ceiling ,double floor){
	//伪随机数产生位移
	double delta = rnd(-1.0,1.0);			//扰动步长随机
	x = x + delta;
	//对于超出区间长度的判定
	if(x>=ceiling){
		x = x - 2*abs(delta);
	}else if(x<=floor){
		x = x + 2*abs(delta);
	}
	return x;
}

//输出各组解
void output(double x,double y,double e,int count,double T){
	printf("x=%-8.5lf    y=%-8.5lf   f(x,y)=%-10.5lf   Times=%-5d    Tempreture=%-.5lf\n",x,y,e,count,T);
}

//退火核心函数
int SA(double*x,double*y,double*e){
	double T = T0;
	//随机产生初始解
	double old_x = 1.;double old_y = 1.;
	double old_e = E(old_x,old_y);
	double new_x,new_y,new_e;double r,P;
	int count = 0;//记录迭代次数
	//退火核心循环
	while(T > Tf){
		new_x = NewSolution(old_x,x_ceiling,x_floor);
		new_y = NewSolution(old_y,x_ceiling,x_floor);
		new_e = E(new_x,new_y);
		//output(old_x,old_y,old_e,count,T);		   //输出每次选取的解
		//Sleep(40);
		count++;
		if(new_e < old_e){
			old_x = new_x;
			old_y = new_y;
			old_e = new_e;	
		}else if(new_e >= old_e){
			//srand((unsigned)time(NULL));
			r = rand()/(double)(RAND_MAX+1);
			P=exp((E(old_x,old_y)-E(new_x,new_y))/(K*T));
			if( P> r){
				old_x = new_x;
				old_y = new_y;
				old_e = new_e;
			}
		}
		if(count%1000== 0 &&count>=1000 ){
			T = 0.99 * T;		         		   //缓慢冷却达到最佳结构
			if(count%10000 == 0)output(old_x,old_y,old_e,count,T);		   //输出每次选取的解
			//Sleep(30);
		}
	}
	//output(old_x,old_y,old_e,count,T);
	*x = old_x;
	*y = old_y;
	*e = old_e;
	return count;
}

//主函数调用
int main(){
	clock_t start ,finish;
	double totaltime;
	double x = 0.,y = 0.,e = 0.;
	srand((unsigned)time(NULL));
	printf("\n模拟退火过程开始！\n");
	//printf("\n自变量值       函数值      迭代次数    当前温度\n");
	start = clock();
	int count = SA(&x,&y,&e);
	finish = clock();
	totaltime = (double) (finish - start)/CLOCKS_PER_SEC;
	printf("\n退火过程结束！\n");
	printf("冷却时间：%.5lf\n",totaltime);
	printf("最优解:(x,y)=(%.2lf,%.2lf)\n全局最小值f(x,y)=%.2lf\n迭代次数%d\n",x,y,e,count);
	system("pause");
	return 0;
}
