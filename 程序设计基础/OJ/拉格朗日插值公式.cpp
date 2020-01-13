
//拉格朗日插值公式

#include<stdio.h>

struct Point{
	double x;
	double y;
}point[105];

int n;//点的个数

//返回获得的横坐标
double input(){
	int i;double goal;
	printf("请输入坐标个数（小于100）:");
	scanf_s("%d",&n);
	printf("请输入点的坐标，每行分别为x,y,坐标值，各点之间换行输入:\n");
	for(i=0;i<n;i++){
		scanf_s("%lf%lf",&point[i].x,&point[i].y);
	}
	printf("请输入要计算的坐标值:");
	scanf_s("%lf",&goal);
	return goal;
}

//获取拉格朗日基函数的值
double SubFunction(int i,double x){
	int j;
	double a=1.0,b=1.0;
	for(j=0;j<n;j++){
		if(j!=i){
			a*=(x-point[j].x);
			b*=(point[i].x-point[j].x);
		}
	}
	return a/b;
}

//合并基函数
double Lagerange(double x){
	int i;
	double result=0.;
	for(i=0;i<n;i++){
		result+=(point[i].y)*SubFunction(i,x);
	}
	return result;
}

int main(){
	double x;
	x=input();
	printf("\n拉格朗日插值结果(x=%.3f):\n",x);
	printf("%lf\n",Lagerange(x));
	return 0;
}
