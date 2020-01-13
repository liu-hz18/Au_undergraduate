#include<stdio.h>
//½×³Ë
/*int main()
{
    unsigned long fact(int x);
	int n;
	printf("please input a number:");
	scanf_s("%d",&n);
	printf("%d!=%u\n",n,fact(n));
	return 0;
}
unsigned long fact(int x)
{
	if(x==1)return 1;
	else return(x*fact(x-1));
}*/

//hanoi
/*int main()
{
	void move(int n,char L,char M,char R);
	int m;
	printf("ººÅµËşÎÊÌâ\nplease input the number of plates:");
	scanf_s("%d",&m);
	printf("the steps to move %d plates are:\n",m);
	move(m,'A','B','C');
return 0;
}
void move(int n,char L,char M,char R)
{
	if(n==1)printf(" move #1 from %c to %c\n",L,R);
	else
	{
		move(n-1,L,R,M);
		printf(" move #%d from %c to %c\n",n,L,R);
		move(n-1,M,L,R);
	}
}*/
