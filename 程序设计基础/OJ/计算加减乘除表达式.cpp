#include<stdio.h>
#include<math.h>
int main()
{
	int a,b,c;
	char op;
	scanf_s("%d",&a);
	scanf_s(" %c",&op);//�����ַ�����Ҫȡַ�ģ����������ַ�������Ҫȡַ��
	//Ҫ����������ַ��еĿո�ʱ��������%cǰ����һ���ո�������������пո񶼻ᱻ���ԣ�
	scanf_s("%d",&b);//�����ֵ��������ڽ�ʶ�����֣���%dǰ���Բ��ӿո�
	switch(op)
	{
        case('+'):c=a+b;break;
		case('-'):c=a-b;break;
		case('*'):c=a*b;break;
		case('/'):c=a/b;break;
		case('^'):c=pow((double) a,(double) b);break;
		default:printf("Erorr!");
	}
	printf("%d%c%d=%d\n",a,op,b,c);
return 0;
}

//��ֻ�漰�Ӽ�������scanf�ķ���ֵ

#include<stdio.h>
int main()
{
	int a,b=0;
	while(scanf_s("%d",&a))b+=a;//scanf_s�ķ���ֵ;��һ��������
	//���ȡ����׼���������������Ӻŵ�ʱ��������
	printf("%d",b);
	return 0;
}