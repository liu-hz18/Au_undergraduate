#include<stdio.h>
int main()
{
    int StationNumber[150],CheckOrder[150];//CheckOrder��ż��˳��
	int m,n,i,j,count=1,t;
	printf("Please input the value of n,i,m:");
	scanf_s("%d%d%d",&n,&i,&m);
    for(j=1;j<=n;j++)StationNumber[j]=j;//��վ��ų�ʼ��
	CheckOrder[1]=i;
	StationNumber[i]=0;//����֮����Ϊ0
	j=i;
	while(count<n)
	{
		t=0;
		while(t<=m)//ʵ��ÿ��m�����һ���������Ѽ��ĳ�վ����
		{
			j=(j+1)%n;
			if(!j)j=n;//ʵ�ֻ��μ��
			if(StationNumber[j]!=0)t++;//�ж��Ƿ񱻼���
		}
		count++;
		CheckOrder[count]=StationNumber[j];
		StationNumber[j]=0;//����֮����Ϊ0
	}
	printf("\nThe order is:\n");
	for(j=1;j<n;j++)
		printf("%2d >>",CheckOrder[j]);
	printf("%2d\n\n",CheckOrder[n]);
    return 0;
}
