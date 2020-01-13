#include<stdio.h>
#include<math.h>
double calculation(double a,double b,char c)
{
	double result;
	switch(c)
	{
	case '+':result=a+b;break;
	case '-':result=a-b;break;
	case '*':result=a*b;break;
	case '/':result=a/b;break;
	case '^':result=pow(a,b);break;
	}
	return result;
}
int judge(char x)
{
	if(x>='0'&&x<='9')return 1;
	if(x=='+'||x=='-'||x=='*'||x=='/'||x=='^')return 0;
	else return -1;
}
int main()
{
    char s[100];
	int i,k=-1,flag;
	double result[100];
	while(1)
	{
		flag=1;
		printf("please input your expression£º\n");
		gets_s(s);
		for(i=0;s[i]!='\0';i++)
		{
			if(judge(s[i])==-1)
			{
				printf("Error!please input again!\n");
				flag=0;
				fflush(stdin);
				break;
			}
		}
		if(flag)
		{
			for(i=0;s[i]!='\0';i++)
			{
				if(judge(s[i])==1)
				{
					k++;
					result[k]=s[i]-'0';
				}
				else if(judge(s[i])==0)
				{
					result[k-1]=calculation(result[k-1],result[k],s[i]);
					result[k]=0;
					k--;
				}
			}
		printf("=%.3f\n",result[k]);
		break;
		}
	}
return 0;
}
