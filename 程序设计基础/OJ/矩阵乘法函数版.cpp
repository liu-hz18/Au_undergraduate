#include<stdio.h>
#include<malloc.h>
void input_num(int*m,int*n,int*r){
	printf("please input the value of m n r:\n");
	scanf_s("%d%d%d",m,n,r);
	return;
}
void input_arr(int m,int n,int r,int***arr1,int***arr2){
	int i,j;
	*arr1=(int**)malloc(m*sizeof(int*));
	for(int i=0;i<m;i++){
		*((*arr1)+i)=(int*)malloc(n*sizeof(int));
	}
	*arr2=(int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++){
		*((*arr2)+i)=(int*)malloc(r*sizeof(int));
	}
	printf("please input %dX%d matrix:\n",m,n);
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			scanf_s("%d",&(*arr1)[i][j]);
		}
	}
	printf("please input %dX%d matrix:\n",n,r);
	for(i=0;i<n;i++){
		for(j=0;j<r;j++){
			scanf_s("%d",&(*arr2)[i][j]);
		}
	}
	return ;
}
int**multiply(int m,int n,int r,int**arr1,int**arr2){
	int**arr3,i,j,k;
	arr3=(int**)malloc(m*sizeof(int*));
	for(i=0;i<m;i++){
		*(arr3+i)=(int*)malloc(r*sizeof(int));
		for(j=0;j<r;j++)*(*(arr3+i)+j)=0;
	}
	for(i=0;i<m;i++){
		for(j=0;j<r;j++){
			for(k=0;k<n;k++){
				arr3[i][j]+=arr1[i][k]*arr2[k][j];
			}
		}
	}
	return arr3;
}
void output(int**arr,int m,int r){
	int i,j;
	printf("the new matrix is:\n");
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<r;j++){
			printf("%4d",arr[i][j]);
		}
	}
	return;
}
int main(){
	int m,n,r,**arr1,**arr2,**arr3;char ch;
	do{
		input_num(&m,&n,&r);
		input_arr(m,n,r,&arr1,&arr2);
		arr3=multiply(m,n,r,arr1,arr2);
		output(arr3,m,r);
		printf("任意键继续，按@退出\n");
		getchar();
	}while((ch=getchar())!='@');
	return 0;
}
