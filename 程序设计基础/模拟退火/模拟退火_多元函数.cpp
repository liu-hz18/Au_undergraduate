//time:  2019/3/7 19:12
//task:  SA(variable function)

#include<iostream>
#include<math.h>
#include<time.h>
#include<Windows.h>
using namespace std;

//������������
#define K 8.6173324e-5
#define PI 3.1415926

//Լ������
#define x_floor -1.0		//x�����Ͻ�
#define x_ceiling 1.0		//x�����½�
#define y_floor -1.0		//y�����Ͻ�
#define x_ceiling 1.0		//x�����½�

//�˻��ʼ�¶�
double T0 = 10000000.0;
//�˻������¶�
#define Tf 10.0

//���ܺ���
double E(double x,double y){
	return sin(x*y)+exp(x*y);			//���ڴ��������Ԫ����
}

//������low��high�ĸ��������
double rnd(double low,double high){
	double temp = rand()/((double)RAND_MAX+1.0);
	return low+temp*(high-low);
}

//α����������½�,������������ʽ
double NewSolution(double x,double ceiling ,double floor){
	//α���������λ��
	double delta = rnd(-1.0,1.0);			//�Ŷ��������
	x = x + delta;
	//���ڳ������䳤�ȵ��ж�
	if(x>=ceiling){
		x = x - 2*abs(delta);
	}else if(x<=floor){
		x = x + 2*abs(delta);
	}
	return x;
}

//��������
void output(double x,double y,double e,int count,double T){
	printf("x=%-8.5lf    y=%-8.5lf   f(x,y)=%-10.5lf   Times=%-5d    Tempreture=%-.5lf\n",x,y,e,count,T);
}

//�˻���ĺ���
int SA(double*x,double*y,double*e){
	double T = T0;
	//���������ʼ��
	double old_x = 1.;double old_y = 1.;
	double old_e = E(old_x,old_y);
	double new_x,new_y,new_e;double r,P;
	int count = 0;//��¼��������
	//�˻����ѭ��
	while(T > Tf){
		new_x = NewSolution(old_x,x_ceiling,x_floor);
		new_y = NewSolution(old_y,x_ceiling,x_floor);
		new_e = E(new_x,new_y);
		//output(old_x,old_y,old_e,count,T);		   //���ÿ��ѡȡ�Ľ�
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
			T = 0.99 * T;		         		   //������ȴ�ﵽ��ѽṹ
			if(count%10000 == 0)output(old_x,old_y,old_e,count,T);		   //���ÿ��ѡȡ�Ľ�
			//Sleep(30);
		}
	}
	//output(old_x,old_y,old_e,count,T);
	*x = old_x;
	*y = old_y;
	*e = old_e;
	return count;
}

//����������
int main(){
	clock_t start ,finish;
	double totaltime;
	double x = 0.,y = 0.,e = 0.;
	srand((unsigned)time(NULL));
	printf("\nģ���˻���̿�ʼ��\n");
	//printf("\n�Ա���ֵ       ����ֵ      ��������    ��ǰ�¶�\n");
	start = clock();
	int count = SA(&x,&y,&e);
	finish = clock();
	totaltime = (double) (finish - start)/CLOCKS_PER_SEC;
	printf("\n�˻���̽�����\n");
	printf("��ȴʱ�䣺%.5lf\n",totaltime);
	printf("���Ž�:(x,y)=(%.2lf,%.2lf)\nȫ����Сֵf(x,y)=%.2lf\n��������%d\n",x,y,e,count);
	system("pause");
	return 0;
}
