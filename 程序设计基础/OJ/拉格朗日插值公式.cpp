
//�������ղ�ֵ��ʽ

#include<stdio.h>

struct Point{
	double x;
	double y;
}point[105];

int n;//��ĸ���

//���ػ�õĺ�����
double input(){
	int i;double goal;
	printf("���������������С��100��:");
	scanf_s("%d",&n);
	printf("�����������꣬ÿ�зֱ�Ϊx,y,����ֵ������֮�任������:\n");
	for(i=0;i<n;i++){
		scanf_s("%lf%lf",&point[i].x,&point[i].y);
	}
	printf("������Ҫ���������ֵ:");
	scanf_s("%lf",&goal);
	return goal;
}

//��ȡ�������ջ�������ֵ
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

//�ϲ�������
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
	printf("\n�������ղ�ֵ���(x=%.3f):\n",x);
	printf("%lf\n",Lagerange(x));
	return 0;
}
