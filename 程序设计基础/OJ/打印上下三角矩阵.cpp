#include<stdio.h>
int main()
{
	int n;
	scanf_s("%d",&n);
	for(int i=0;i<n;i++)
   {		
	   for(int j=1;j<n-i;j++)printf("%3d",i);
	   printf("  *\n");
   }
return 0;
}
//ÏÂÈý½Ç
/*
#include<stdio.h>
int main()
{
	int n;
	scanf_s("%d",&n);
	for(int i=0;i<n;i++)
	{
		for(int j=1;j<=i;j++)printf("%3d",i);
		printf("  *\n");
	}
return 0;
}
*/