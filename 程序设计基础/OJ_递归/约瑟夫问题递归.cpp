#include<stdio.h>
int joseph(int sum,int flag,int count)
{
	if(count==1)return (sum+flag-1)%sum;
	else return (joseph(sum-1,flag,count-1)+flag)%sum;
}
//�ڹ��������н�����⡣�ڱ�Ŵ�0��ʼ�������
//�����ݹ鵽��һ�ν�����̭�����Σ�����flag������һ���˳����ˡ�
//֮��ص���һ�㣬����һ���˳����˵���һ���˱��Ϊ0��+flag���ٶԵ�ǰ��sumȡģ�͵ó���һ�㣨��һ�Σ��˳����ˡ�
int main()
{
	int sum,flag;
	printf("please input the num of persons:");
	scanf_s("%d",&sum);
	printf("please input the num who have to quit:");
	scanf_s("%d",&flag);
	printf("the person left is:%d\n",joseph(sum,flag,sum)+1);
	return 0;
}
