//һԪ����ʽ������ֵ����
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
void calculate(int m,int n,char*a,double*a1){//�ӵ�mλ����nλ������ʽ��ֵ
	int i,t=0;
	//�������ȼ����ȱ�������˷�
	for(i=m;i<n-t;i++){
		if(a[i]=='^'){
			a1[i-1]=pow(a1[i-1],a1[i+1]);
			move(a,a1,i);
			t+=2;i--;
		}
	}
	//��������˳�
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
	//��������Ӽ�
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
	for (i=0;i<200;i++)b[i]=a[i];//��ʱ���飬��ʱ�洢���ʽa
	for (i=0;i<200;i++){
		if(b[i]=='x')a1[i]=x;//�Ը���������a1���и�ֵ
		else if(b[i]>='0'&&b[i]<='9')a1[i]=(double)(b[i]-'0');
	}
	//���ȴ�������
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
		a[i]=b[i];//�����ʽa����ԭֵ
		a1[i]=0;//����������a1��0
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
	dfx=(f(x+delta,a,b,a1)-f(x,a,b,a1))/delta;//�ü�Сֵdelta���Ƶ���ֵ
	printf("���ʽֵΪ%.2lf\n����ֵΪ%.2lf\n",fx,dfx);
}
