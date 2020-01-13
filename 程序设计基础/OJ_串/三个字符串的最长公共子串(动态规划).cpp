//LCS 问题
//三个字符串

#include<stdio.h>
#include<string.h>
#include<malloc.h>
void LCS(char*str1,char*str2,char*str3,char*LCSstr)
{
	int len1,len2,len3,i,j,k,flagx,flagy,flagz,max=0;
	len1=strlen(str1);
	len2=strlen(str2);
	len3=strlen(str3);
	int***flag;//定义一个三维对应矩阵，存放三个数组的匹配情况。
	//动态分配内存
	while((flag=(int***)malloc((len1+1)*sizeof(int**)))==NULL);
	for(i=0;i<len1+1;i++)
	{
		while((flag[i]=(int**)malloc((len2+1)*sizeof(int*)))==NULL);
		for(j=0;j<len2+1;j++)
			while((flag[i][j]=(int*)malloc((len3+1)*sizeof(int)))==NULL);
	}
	for(i=0;i<=len1;i++)
		for(j=0;j<=len2;j++)
			for(k=0;k<=len3;k++)
				flag[i][j][k]=0;
	for(i=1;i<=len1;i++)
		for(j=1;j<=len2;j++)
			for(k=1;k<=len3;k++)
			{
				if(str1[i-1]==str2[j-1]&&str2[j-1]==str3[k-1])
					flag[i][j][k]=flag[i-1][j-1][k-1]+1;
				if(flag[i][j][k]>max)
				{
					max=flag[i][j][k];
					flagx=i-1;
					flagy=j-1;
					flagz=k-1;
				}
			}
	LCSstr[max]='\0';
	for(i=flagx;i>=0;i--)
		for(j=flagy;j>=0;j--)
			for(k=flagz;k>=0;k--)
				if(str1[i]==str2[j]&&str2[j]==str3[k])
					if(max>0)
					{
						max--;
						LCSstr[max]=str1[i];
					}
	for(i=0;i<len1+1;i++)
	{
		for(j=0;j<len2+1;j++)
			free(flag[i][j]);
		free(flag[i]);
	}
	free(flag);
}
int main()
{
	char a[100],b[100],c[100],d[100];
	printf("please input string1:\n");
	gets_s(a);
	printf("please input string2:\n");
	gets_s(b);
	printf("please input string3:\n");
	gets_s(c);
	LCS(a,b,c,d);
	printf("\nLCS is:\n");
	printf("%s\n",d);
return 0;
}
