//
//
//time:  2019/3/7 13:56
//Copyright@LiuHongzun
//task:  SA(one variable function)
//
//

#include<iostream>
#include<math.h>
#include<time.h>
#include<Windows.h>

using namespace std;

//模拟玻尔兹曼常量
#define K 8.6173324e-5
#define PI 3.1415926

//划定区间
#define floor -1.0		//区间上界
#define ceiling 1.0		//区间下界

//退火初始温度
double T0 = 1000000.0;
//退火最终温度
#define Tf 10.0

//势能函数
double E(double x){
	return x*x*x-x;
	//7*sin(6*x)+6*cos(5*x);
	//0.3*sin(x/10)*exp(-abs(x/300))-1.5*exp(-abs(x/400));
}

double rnd(double low,double high){
	double temp = rand()/((double)RAND_MAX+1.0);
	return low+temp*(high-low);
}

//伪随机数产生新解
double NewSolution(double x){
	//伪随机数产生位移
	double delta = rnd(-1.0,1.0);			//扰动步长
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
void output(double x,double e,int count,double T){
	printf("%.5lf    %.5lf     %d    %.5lf\n",x,e,count,T);
}

//退火核心函数
int SA(double*x,double*e){
	double T = T0;
	//随机产生初始解
	double old_x = 0.;
	double old_e = E(old_x);
	double new_x,new_e;double r,P;
	int count = 0;//记录迭代次数
	//退火核心循环
	while(T > Tf){
		new_x = NewSolution(old_x);
		new_e = E(new_x);
		//output(old_x,old_e,count,T);		   //输出每次选取的解
		//Sleep(40);
		count++;
		if(new_e < old_e){
			old_x = new_x;
			old_e = new_e;	
		}else if(new_e >= old_e){
			//srand((unsigned)time(NULL));
			r = rand()/(double)(RAND_MAX+1);
			P=exp((E(old_x)-E(new_x))/(K*T));
			if( P> r){
				old_x = new_x;
				old_e = new_e;
			}
		}
		if(count%1000== 0 &&count>=1000 ){
			T = 0.99 * T;		         		   //缓慢冷却达到最佳结构
			//output(old_x,old_e,count,T);		   //输出每次选取的解
			//Sleep(40);
		}
	}
	//output(old_x,old_e,count,T);
	*x = old_x;
	*e = old_e;
	return count;
}

//主函数调用
int main(){
	clock_t start ,finish;
	double totaltime;
	double x = 0.,e = 0.;
	srand((unsigned)time(NULL));
	printf("The min of 7*sin(x)+6*cos(x) between -1.0 and 4.0\n");
	printf("\n模拟退火过程开始！\n");
	//printf("\n自变量值       函数值      迭代次数    当前温度\n");
	start = clock();
	int count = SA(&x,&e);
	finish = clock();
	totaltime = (double) (finish - start)/CLOCKS_PER_SEC;
	printf("\n\n退火过程结束！\n");
	printf("冷却时间：%.5lf\n",totaltime);
	printf("最优解:x=%.3lf\n全局最小值f(x)=%.3lf\n迭代次数%d\n",x,e,count);
	system("pause");
	return 0;
}
