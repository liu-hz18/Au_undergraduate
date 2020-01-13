#include<stdio.h>
void multily(int i,int j,int k,int result,int a[][50],int b[][50],int **c,int m,int n,int t){
	if(k==n&&i<m&&j<t){c[i][j]=result;multily(i,j+1,0,0,a,b,c,m,n,t);}
	//此处的c[i][j]实际上是解地址，相当于*（c[i]+j),其中c[i]是一个指针
	else if(k<n&&i<m&&j==t)multily(i+1,0,0,0,a,b,c,m,n,t);
	else if(k<n&&i<m&&j<t)multily(i,j,k+1,result+a[i][k]*b[k][j],a,b,c,m,n,t);
	else if(i==m)return;
}
int main(){
	int i,j,a[50][50],b[50][50],c[50][50],m,n,t;
	int* p[50];//定义一个指针数组，本质为数组，然后对指针数组中的每个指针循环赋初值，这时每个指针指向了目标数组的对应行
	//指针数组int* p[];数组指针：int (*p)[];括号括起来表示只有一个指针！！！！
	//对于二级指针，并不能通过二级指向的方式来指向一个二维数组，如果要用二级指针，就只能动态建立堆空间,使对应的指针指向堆中的一块区域
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
	multily(0,0,0,0,a,b,p,m,n,t);//传指针数组，这样就可以对main的作用域进行操作
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<t;j++){
			printf("%4d",c[i][j]);
		}
	}
	return 0;
}