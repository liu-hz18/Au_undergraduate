#include<stdio.h>
void multily(int i,int j,int k,int result,int a[][50],int b[][50],int **c,int m,int n,int t){
	if(k==n&&i<m&&j<t){c[i][j]=result;multily(i,j+1,0,0,a,b,c,m,n,t);}
	//�˴���c[i][j]ʵ�����ǽ��ַ���൱��*��c[i]+j),����c[i]��һ��ָ��
	else if(k<n&&i<m&&j==t)multily(i+1,0,0,0,a,b,c,m,n,t);
	else if(k<n&&i<m&&j<t)multily(i,j,k+1,result+a[i][k]*b[k][j],a,b,c,m,n,t);
	else if(i==m)return;
}
int main(){
	int i,j,a[50][50],b[50][50],c[50][50],m,n,t;
	int* p[50];//����һ��ָ�����飬����Ϊ���飬Ȼ���ָ�������е�ÿ��ָ��ѭ������ֵ����ʱÿ��ָ��ָ����Ŀ������Ķ�Ӧ��
	//ָ������int* p[];����ָ�룺int (*p)[];������������ʾֻ��һ��ָ�룡������
	//���ڶ���ָ�룬������ͨ������ָ��ķ�ʽ��ָ��һ����ά���飬���Ҫ�ö���ָ�룬��ֻ�ܶ�̬�����ѿռ�,ʹ��Ӧ��ָ��ָ����е�һ������
	for(i=0;i<50;i++){p[i]=c[i];}
	printf("please input the value of m n t:");
	scanf_s("%d%d%d",&m,&n,&t);
	printf("please input the elements of matrix a:\n");
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			scanf_s("%d",&a[i][j]);
		}
	}
	printf("please input the elements of matrix b:\n");
	for(i=0;i<n;i++){
		for(j=0;j<t;j++){
			scanf_s("%d",&b[i][j]);
		}
	}
	multily(0,0,0,0,a,b,p,m,n,t);//��ָ�����飬�����Ϳ��Զ�main����������в���
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<t;j++){
			printf("%4d",c[i][j]);
		}
	}
	return 0;
}