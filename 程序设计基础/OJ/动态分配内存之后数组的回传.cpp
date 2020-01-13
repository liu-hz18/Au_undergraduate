#include<stdio.h>
#include<time.h>
#include<malloc.h>
#include<stdlib.h>
void CountEvensAndOdds(int a[],int n,int*counteven,int*countodd)
{
	int i;
	//�˴����������µ�odd��even������������Ϊ��ʹָ��ָ���µĵ�ַ���������ַ�ں�������֮�����ʧ��
	*counteven=0;
	*countodd=0;
	for(i=0;i<n;i++)
		if((*(a+i))%2)(*counteven)++;
		else (*countodd)++;
}
void Partition(int a[],int n,int**arr1,int*counteven,int**arr2,int*countodd)
//�����е����в��������βΣ��Ѷ�̬�ռ丳���β���û���κ�����ģ�������ı�ʵ�Σ�������Ҫ����ʵ�εĵ�ַ
//�β�Ϊָ��ָ���ָ�룬��*b��*c�ĵ�ַ����,�����ռ�ֱ�Ӹ���*arr1(��b)��*arr2(��c)
//����������ڴ��ַ������β�*arr1�е�����������ʱ���β���ʧ������ĵ�ַҲ����֮��ʧ
//����**arr1�ķ�ʽ���Խ�����b�ĵ�ַ���룬���ѿռ�ĵ�ַ����b��c�У���ֹ��ַ�Ķ�ʧ
//�������Ӻ������ͷ�����Ŀռ䣬����ִ����֮����о�û���˿ռ䣬�޷����ʡ�����main�������ͷ�
{
	while((*arr1=(int*)malloc((*counteven)*sizeof(int)))==NULL);
	while((*arr2=(int*)malloc((*countodd)*sizeof(int)))==NULL);
	int i,j,k;
	for(i=0,k=0,j=0;i<n;i++)
	{
		if((*(a+i)%2))*((*arr1)+k++)=*(a+i);
		else *((*arr2)+j++)=*(a+i);
	}
}
int main()
{
	int *a,n,even,odd;
	int *b,*c;//����������ָ��*b,*c
	int *p1,*p2;
	p1=&even;
	p2=&odd;
	srand((unsigned int)time(NULL));
	n=rand()%50+1;//����������鳤�ȣ�1��50��
    while((a=(int*)malloc(n*sizeof(int)))==NULL);
	printf("�������:len=%d\n",n);
	for(int i=0;i<n;i++)
	{
		*(a+i)=rand()%100;
		printf("%3d",*(a+i));
	}
	CountEvensAndOdds(a,n,p1,p2);
	Partition(a,n,&b,p1,&c,p2);//��b,c�ĵ�ַ
	printf("\n��������:len=%d\n",*p1);
	for(int i=0;i<(*p1);i++)
		printf("%3d",*(b+i));
	printf("\nż������:len=%d\n",*p2);
	for(int i=0;i<(*p2);i++)
		printf("%3d",*(c+i));
	putchar(10);
	free(a);
	free(b);
	free(c);
return 0;
}
