#include<stdio.h>
#include<malloc.h>

void input(int*m,int*n,int***a){
	int i,j; 
	printf("请输入m和n的值:");
	scanf_s("%d%d",m,n);
	*a=(int**)malloc(*m*sizeof(int*));
	for(i=0;i<*m;i++){
		*((*a)+i)=(int*)malloc(*n*sizeof(int));
	}
	printf("请输入矩阵各行元素值：\n");
	for(i=0;i<*m;i++){
		for(j=0;j<*n;j++){
			scanf_s("%d",&(*a)[i][j]);
		}
	}
	getchar();
	return;
}
void myfree(int m,int n,int***a){
	int i;
	for(i=0;i<m;i++){
		free(*((*a)+i));
	}
	free(*a);
}
void print(int m,int n,int **a){
	int i,j;
	printf("排序后的矩阵:\n");
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<n;j++){
			printf("%4d",a[i][j]);
		}
	}
}
//矩阵行内递减冒泡排序
void Rowsort(int m,int n,int ***a){
	int i,j,k,tmp;
	for(i=0;i<m;i++){
		for(j=n-1;j>=0;j--){
			for(k=0;k<j;k++){
				if((*a)[i][k]<(*a)[i][k+1]){
					tmp=(*a)[i][k];
					(*a)[i][k]=(*a)[i][k+1];
					(*a)[i][k+1]=tmp;
				}
			}
		}
	}
	return ;
}
//对矩阵按行和排序
void MatrixSort(int m,int n,int***a){
	int i,j,k,*sum,tmp,t,*tmpa;
	Rowsort(m,n,a);
	sum=(int*)malloc(m*sizeof(int));
	for(i=0;i<m;i++){
		sum[i]=0;
		for(j=0;j<n;j++){
			sum[i]+=(*a)[i][j];
		}
	}
	for(i=m-1;i>=0;i--){
		for(j=0;j<i;j++){
			if(sum[j]<sum[j+1]){
				tmp=sum[j];sum[j]=sum[j+1];sum[j+1]=tmp;
				//对行内元素依次交换
				/*for(k=0;k<n;k++){
					t=(*a)[j][k];(*a)[j][k]=(*a)[j+1][k];(*a)[j+1][k]=t;
				}*/
				//使用行指针进行交换
				tmpa=(*a)[j];(*a)[j]=(*a)[j+1];(*a)[j+1]=tmpa;
			}
		}
	}
	free(sum);
	return ;
}
int main(){
	int m,n,**a;char ch;
	while((ch=getchar()!='@')){
		input(&m,&n,&a);
		MatrixSort(m,n,&a);
		print(m,n,a);
		myfree(m,n,&a);
		printf("是否继续？按@结束程序！\n");
	}
	return 0;
}
