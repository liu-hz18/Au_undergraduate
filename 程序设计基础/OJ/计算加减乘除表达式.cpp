#include<stdio.h>
#include<math.h>
int main()
{
	int a,b,c;
	char op;
	scanf_s("%d",&a);
	scanf_s(" %c",&op);//输入字符是需要取址的，但是输入字符串不需要取址。
	//要求忽略输入字符中的空格时，可以在%c前加上一个空格，这样输入的所有空格都会被忽略！
	scanf_s("%d",&b);//但数字的输入由于仅识别数字，在%d前可以不加空格
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

//若只涉及加减，利用scanf的返回值

#include<stdio.h>
int main()
{
	int a,b=0;
	while(scanf_s("%d",&a))b+=a;//scanf_s的返回值;是一个整数，
	//则读取到标准输入流。即遇到加号的时候跳过。
	printf("%d",b);
	return 0;
}