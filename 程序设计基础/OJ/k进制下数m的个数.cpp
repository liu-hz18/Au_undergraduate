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
	while(n)//n不为0时继续执行程序
	{
		count++;
		n=(n-1)&n;//作与运算，有几个1就可以做几次运算
	}
    return count;
}

int numberof0(int k)
{
	int count0=0;
	if(k==0)count0=1;
	else for(;k;k/=2)count0+=(!(k%2));
	return count0;//非常简单易得的算法
}
//类似于以上程序可以编写任意进制下某个数出现的次数
//如输出k进制下m的个数
//int numberofm（int i）
//{
//    int count=0;
//    for(;i;i/=k)if((i%k)==m)count++;
//    return count0;
//}
//但此算法有缺陷，不能输出测试值为0时的个数，需要单独输出！