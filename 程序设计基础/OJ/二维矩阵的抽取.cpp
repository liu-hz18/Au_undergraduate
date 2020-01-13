//动态抽取子矩阵
#include<stdio.h>
#include<malloc.h>
void input(int *i, int *j,int *newrl,int*newcl){
	while(1){
		printf("please input i and j:");
		scanf_s("%d%d",i,j);
		printf("please input newrl and newcl:");
		scanf_s("%d%d",newrl,newcl);
		if(*i>=0&&*i<=6-*newrl&&*j>=0&&*j<=6-*newcl&&*newrl>=0&&*newrl<=6&&*newcl>=0&&*newcl<=6)break;
		else printf("Error!please input i and j again!\n");
	}
}
void list(float **b,int newrl,int newcl){
	int i,j;
	printf("抽取的矩阵b如下：\n");
	for(i=0;i<newrl;i++,printf("\n")){
		for(j=0;j<newcl;j++){
			printf("%f ",b[i][j]);
		}
	}
}
float**submatrix(float a[][6],int i,int j,int newrl,int newcl){
	float**b;int begin_i=i,begin_j=j;
	b=(float**)malloc(newrl*sizeof(float*));
	for(int k=0;k<newrl;k++){
		*(b+k)=(float*)malloc(newcl*sizeof(float));
	}
	for(begin_i=i;begin_i<newrl+i;begin_i++){
		for(begin_j=j;begin_j<newcl+j;begin_j++){
			*(*(b+begin_i-i)+begin_j-j)=a[begin_i][begin_j];
		}
	}
	return b;
}
int main(){
	float a[6][6]={{0.1,0.2,0.3,0.4,0.5,0.6},
	               {1.1,1.2,1.3,1.4,1.5,1.6},
	               {2.1,2.2,2.3,2.4,2.5,2.6},
	               {3.1,3.2,3.3,3.4,3.5,3.6},
	               {4.1,4.2,4.3,4.4,4.5,4.6},
	               {5.1,5.2,5.3,5.4,5.5,5.6}},**b;
	int i,j,newcl,newrl;char ch;
	while(1){
		printf("按任意键继续程序，按@结束程序:\n");
		if((ch=getchar())=='@')break;
		input(&i,&j,&newrl,&newcl);
		b=submatrix(a,i,j,newrl,newcl);
		list(b,newrl,newcl);
		getchar();//在最后getchar，这样就不会导致第一次输入的时候要连按两次键
	}
	for(j=0;j<newrl;j++){
		free(*(b+j));
	}
	free(b);
	return 0;
}
