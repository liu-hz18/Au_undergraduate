#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
int main()
{
	char expression[10];
	char*GetRanddomExpression(char expr[],int*result);
	int re,*p,result;
	p=&re;
	char flag;
	printf("100以内的加减乘除运算,按任意键开始和继续,按q/Q结束练习\n");
	while(1)
	{
		fflush(stdin);
		expression[0]='\0';
		flag=_getch();
		if(flag!='q'&&flag!='Q')
		{
			char*exp=GetRanddomExpression(expression,p);
			printf(" %s",exp);
			scanf_s("%d",&result);
			if(result==*p)printf(" 计算正确！非常棒！O(∩_∩)O\n");
			else printf(" 计算错误！加油啊!o(≧v≦)o \n");
		}
		else break;
	}
	return 0;
}
char*GetRanddomExpression(char expr[],int*result)
{
	int n,a,b,flag=0;
	char*s;
	char op;
	s=expr;
	int*pointer_a,*pointer_b;
	pointer_a=&a;pointer_b=&b;
	srand((unsigned int)time(NULL));
	*pointer_a=rand()%100+1;
	*pointer_b=rand()%100+1;//100以内正整数
	n=rand()%4;
	switch(n)
	{
	case 0:
		while(*pointer_a+*pointer_b>=100)
			*pointer_b=rand()%100+1;
		op='+';
		*result=*pointer_a+*pointer_b;
		break;
	case 1:
		while(*pointer_a-*pointer_b<=0)
			*pointer_b=rand()%100+1;
		op='-';
		*result=*pointer_a-*pointer_b;
		break;
	case 2:
		while((*pointer_a)*(*pointer_b)>=100)
			*pointer_b=rand()%100+1;
		op='*';
		*result=(*pointer_a)*(*pointer_b);
		break;
	default:
		while((*pointer_a)%(*pointer_b)!=0)
			*pointer_b=rand()%100+1;
		op='/';
		*result=(*pointer_a)/(*pointer_b);
		break;
	}
	if((*pointer_a)/10>0)
	{
		*s=(*pointer_a)/10+'0';
		*(s+1)=(*pointer_a)%10+'0';
		flag+=2;
	}
	else {*s=(*pointer_a)%10+'0';flag+=1;}
	*(s+flag)=op;
	flag++;
	if((*pointer_b)/10>0)
	{
		*(s+flag)=(*pointer_b)/10+'0';
		*(s+flag+1)=(*pointer_b)%10+'0';
		flag+=2;
	}
	else {*(s+flag)=(*pointer_b)%10+'0';flag++;}
	*(s+flag)='=';
	*(s+flag+1)='\0';
	return(s);
}
