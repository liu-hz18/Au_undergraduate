#include<stdio.h>
int main()
{
    int StationNumber[150],CheckOrder[150];//CheckOrder存放检查顺序
	int m,n,i,j,count=1,t;
	printf("Please input the value of n,i,m:");
	scanf_s("%d%d%d",&n,&i,&m);
    for(j=1;j<=n;j++)StationNumber[j]=j;//车站编号初始化
	CheckOrder[1]=i;
	StationNumber[i]=0;//检查过之后标记为0
	j=i;
	while(count<n)
	{
		t=0;
		while(t<=m)//实现每隔m个检查一个，并且已检查的车站跳过
		{
			j=(j+1)%n;
			if(!j)j=n;//实现环形检查
			if(StationNumber[j]!=0)t++;//判断是否被检查过
		}
		count++;
		CheckOrder[count]=StationNumber[j];
		StationNumber[j]=0;//检查过之后标记为0
	}
	printf("\nThe order is:\n");
	for(j=1;j<n;j++)
		printf("%2d >>",CheckOrder[j]);
	printf("%2d\n\n",CheckOrder[n]);
    return 0;
}
