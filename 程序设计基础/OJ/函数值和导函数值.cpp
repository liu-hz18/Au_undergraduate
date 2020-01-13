//一元多项式函数求值和求导
#include <stdio.h>
#include<math.h>
#define delta 1e-6
void move(char*a,double*a1,int i){
	int j;
	for(j=i;j<200;j++){
		a[j]=a[j+2];
		a1[j]=a1[j+2];
	}
}
void calculate(int m,int n,char*a,double*a1){//从第m位到第n位计算表达式的值
	int i,t=0;
	//按照优先级，先遍历计算乘方
	for(i=m;i<n-t;i++){
		if(a[i]=='^'){
			a1[i-1]=pow(a1[i-1],a1[i+1]);
			move(a,a1,i);
			t+=2;i--;
		}
	}
	//遍历计算乘除
	for(i=m;i<n-t;i++){
		if(a[i]=='*'){
			a1[i-1]=a1[i-1]*a1[i+1];
			move(a,a1,i);
			t+=2;i--;
		}else if(a[i]=='/'){
			a1[i-1]=a1[i-1]/a1[i+1];
			move(a,a1,i);
			t+=2;i--;
		}
	}
	//遍历计算加减
	for(i=m;i<n-t;i++){
		if(a[i]=='+'){
			a1[i-1]=a1[i-1]+a1[i+1];
			move(a,a1,i);
			t+=2;i--;
		}else if(a[i]=='-'){
			a1[i-1]=a1[i-1]-a1[i+1];
			move(a,a1,i);
			t+=2;i--;
		}
	}
	return;
}
double f(double x,char*a,char*b,double*a1){
	int i, j;
	for (i=0;i<200;i++)b[i]=a[i];//临时数组，暂时存储表达式a
	for (i=0;i<200;i++){
		if(b[i]=='x')a1[i]=x;//对浮点型数组a1进行赋值
		else if(b[i]>='0'&&b[i]<='9')a1[i]=(double)(b[i]-'0');
	}
	//优先处理括号
	for(i=0;i<200;i++){
		if(a[i]=='('){
			for(j=i;j<200; j++){
				if(a[j]==')')calculate(i,j,a,a1);
			}
			a[i]=a[i+1];a1[i]=a1[i+1];
			for(j=i+1;j<200;j++){
				a[j]=a[j+2];
				a1[j]=a1[j+2];
			}
			i--;
		}
	}
	calculate(0,200,a,a1);
	x=a1[0];
	for(i=0;i<200;i++){
		a[i]=b[i];//将表达式a赋回原值
		a1[i]=0;//浮点型数组a1置0
	}
	return x;
}
int main(){
	double x,fx,dfx,a1[200];char a[200],b[200];
	printf("please input f(x):\n");
	gets_s(a);
	printf("please input the value of x:");
	scanf_s("%lf", &x);
	fx=f(x,a,b,a1);
	dfx=(f(x+delta,a,b,a1)-f(x,a,b,a1))/delta;//用极小值delta估计导数值
	printf("表达式值为%.2lf\n导数值为%.2lf\n",fx,dfx);
}
