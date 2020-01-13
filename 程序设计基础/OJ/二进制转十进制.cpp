#include<stdio.h>
#include<string.h>
#include<math.h>
int main()
{
	char Binarynumber[32];
	int Decimalnumber=0;
	printf("Please input a binary number: ");
	scanf_s("%s",Binarynumber,32);
	int len=strlen(Binarynumber),i;
	for(i=0;i<len;i++)
		if(Binarynumber[i]=='1')Decimalnumber+=pow(2.0,len-1-i);
	printf("The corresponding decimal number is: %d\n",Decimalnumber); 
return 0;
}
