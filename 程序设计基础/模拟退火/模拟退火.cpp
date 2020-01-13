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

//ģ�ⲣ����������
#define K 8.6173324e-5
#define PI 3.1415926

//��������
#define floor -1.0		//�����Ͻ�
#define ceiling 1.0		//�����½�

//�˻��ʼ�¶�
double T0 = 1000000.0;
//�˻������¶�
#define Tf 10.0

//���ܺ���
double E(double x){
	return x*x*x-x;
	//7*sin(6*x)+6*cos(5*x);
	//0.3*sin(x/10)*exp(-abs(x/300))-1.5*exp(-abs(x/400));
}

double rnd(double low,double high){
	double temp = rand()/((double)RAND_MAX+1.0);
	return low+temp*(high-low);
}

//α����������½�
double NewSolution(double x){
	//α���������λ��
	double delta = rnd(-1.0,1.0);			//�Ŷ�����
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
void output(double x,double e,int count,double T){
	printf("%.5lf    %.5lf     %d    %.5lf\n",x,e,count,T);
}

//�˻���ĺ���
int SA(double*x,double*e){
	double T = T0;
	//���������ʼ��
	double old_x = 0.;
	double old_e = E(old_x);
	double new_x,new_e;double r,P;
	int count = 0;//��¼��������
	//�˻����ѭ��
	while(T > Tf){
		new_x = NewSolution(old_x);
		new_e = E(new_x);
		//output(old_x,old_e,count,T);		   //���ÿ��ѡȡ�Ľ�
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
			T = 0.99 * T;		         		   //������ȴ�ﵽ��ѽṹ
			//output(old_x,old_e,count,T);		   //���ÿ��ѡȡ�Ľ�
			//Sleep(40);
		}
	}
	//output(old_x,old_e,count,T);
	*x = old_x;
	*e = old_e;
	return count;
}

//����������
int main(){
	clock_t start ,finish;
	double totaltime;
	double x = 0.,e = 0.;
	srand((unsigned)time(NULL));
	printf("The min of 7*sin(x)+6*cos(x) between -1.0 and 4.0\n");
	printf("\nģ���˻���̿�ʼ��\n");
	//printf("\n�Ա���ֵ       ����ֵ      ��������    ��ǰ�¶�\n");
	start = clock();
	int count = SA(&x,&e);
	finish = clock();
	totaltime = (double) (finish - start)/CLOCKS_PER_SEC;
	printf("\n\n�˻���̽�����\n");
	printf("��ȴʱ�䣺%.5lf\n",totaltime);
	printf("���Ž�:x=%.3lf\nȫ����Сֵf(x)=%.3lf\n��������%d\n",x,e,count);
	system("pause");
	return 0;
}
