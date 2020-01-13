#include<stdio.h>
int main()
{
	int a,b,c,d,e;
	printf("0 stands for he is sincere,1 stands for he is a criminal\n\n");
	for(a=0;a<=1;a++)
	  for(b=0;b<=1;b++)
	    for(c=0;c<=1;c++)
		  for(d=0;d<=1;d++)
			 for(e=0;e<=1;e++)
				{
				   if((a+b)&&(1<(a+d+e))&&((a+c)!=2)&&(c+d==1))
				   printf("the result is a=%d,b=%d,c=%d,d=%d,e=%d\n",a,b,c,d,e);
			    }
    return 0;
}
第二题：可以用字母代替数字

/*由于求分组情况，所以只要固定ABC，求解XYZ的位置即可，即把XYZ放入三个位置中，
采用循环可以实现XYZ的不重复全排列，之后根据题设，第一个（A）不放X，第二个位置无条件
第三个位置不放X和Z*/

#include<stdio.h>
int main()
{
	char i,j,k;
	for(i='X';i<='Z';i++)
		for(j='X';j<='Z';j++)
			if(i!=j)
				for(k='X';k<='Z';k++)
					if(i!=k&&i!=j&&j!=k)
						if(i!='X'&&k!='X'&&k!='Z')
							printf("A`s partrner is%c,B`s partener is%c,C`s partener is%c\n",i,j,k);
	return 0;
}

//第三题
#include<stdio.h>
int A,X;
 void main ()
 {
    for(A = 'A'; A <= 'D';A++)
	{
        X = (A != 'A') + (A == 'C') + (A == 'D') + (A !=' D');
        if(X == 3) 
		{
            printf("%c做好事\n",A);
			break;//跳出循环
        }
    }
    if(A > 'D') printf("没人做好事");
 }
