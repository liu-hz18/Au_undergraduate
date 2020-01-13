#include<stdio.h>
#include<math.h>
void rank(int a,int*p)
{
	int b[5],i,j;
	b[1]=a/1000;
	b[2]=(a/100)%10;
	b[3]=(a%100)/10;
	b[4]=a%10;
	for(i=4;i>1;i--)//找到最大排列和最小排列
		for(j=1;j<i;j++)
			if(b[j+1]>b[j])
			{
				int tmp=b[j];
				b[j]=b[j+1];
				b[j+1]=tmp;
			}
    p[1]=b[1]*1000+b[2]*100+b[3]*10+b[4];
	p[2]=b[4]*1000+b[3]*100+b[2]*10+b[1];
	p[3]=p[1]-p[2];
	//输出三个数，数位不足左补零
	printf("(%04d,%04d,%04d)\n",p[1],p[2],p[3]);
}

int main()
{
	int a[5],tmp;
	while(1)
	{
		printf("please input a number(except 'xxxx'):");
		scanf_s("%d",&a[3]);
		if(a[3]==0)break;
		else if(a[3]/1000==0||a[3]/1000>9)printf("Error!please input again!\n");
		else{
			while(1)
			{
				tmp=a[3];
				rank(a[3],a);
				if(a[3]==tmp)break;
			}
		}		
	}
	return 0;
}
