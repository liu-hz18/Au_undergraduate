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
�ڶ��⣺��������ĸ��������

/*������������������ֻҪ�̶�ABC�����XYZ��λ�ü��ɣ�����XYZ��������λ���У�
����ѭ������ʵ��XYZ�Ĳ��ظ�ȫ���У�֮��������裬��һ����A������X���ڶ���λ��������
������λ�ò���X��Z*/

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

//������
#include<stdio.h>
int A,X;
 void main ()
 {
    for(A = 'A'; A <= 'D';A++)
	{
        X = (A != 'A') + (A == 'C') + (A == 'D') + (A !=' D');
        if(X == 3) 
		{
            printf("%c������\n",A);
			break;//����ѭ��
        }
    }
    if(A > 'D') printf("û��������");
 }
