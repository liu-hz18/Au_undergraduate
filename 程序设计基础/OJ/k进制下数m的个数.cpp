#include<stdio.h>
int main()
{
    int numberof1(int n);
	int numberof0(int k);
	int x,m,j;
	printf("please input a number:");
	scanf_s("%d",&x);
	m=numberof1(x);
	j=numberof0(x);
	printf("the times of 1:%d\nthe times of 0:%d\n",m,j);
return 0;
}
int numberof1(int n)
{
	int count=0;
	while(n)//n��Ϊ0ʱ����ִ�г���
	{
		count++;
		n=(n-1)&n;//�������㣬�м���1�Ϳ�������������
	}
    return count;
}

int numberof0(int k)
{
	int count0=0;
	if(k==0)count0=1;
	else for(;k;k/=2)count0+=(!(k%2));
	return count0;//�ǳ����׵õ��㷨
}
//���������ϳ�����Ա�д���������ĳ�������ֵĴ���
//�����k������m�ĸ���
//int numberofm��int i��
//{
//    int count=0;
//    for(;i;i/=k)if((i%k)==m)count++;
//    return count0;
//}
//�����㷨��ȱ�ݣ������������ֵΪ0ʱ�ĸ�������Ҫ���������