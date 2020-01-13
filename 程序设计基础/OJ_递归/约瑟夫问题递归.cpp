#include<stdio.h>
int joseph(int sum,int flag,int count)
{
	if(count==1)return (sum+flag-1)%sum;
	else return (joseph(sum-1,flag,count-1)+flag)%sum;
}
//在归来过程中解决问题。在编号从0开始的情况下
//先逐层递归到第一次进行淘汰的情形，返回flag，即第一次退出的人。
//之后回到上一层，在上一次退出的人的下一个人编号为0，+flag后再对当前的sum取模就得出上一层（下一次）退出的人。
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
