#include<stdio.h>
#include<malloc.h>

//二维数组的创建
void creat(int***a,int*m,int*n){
	int i,j;
	printf("请输入数组的大小m n:");
	scanf_s("%d%d",m,n);
	*a=(int**)malloc(*m*sizeof(int*));
	for(i=0;i<*m;i++){
		*((*a)+i)=(int*)malloc(*n*sizeof(int));
	}
	printf("请输入数组各元素的值:\n");
	for(i=0;i<*m;i++){
		for(j=0;j<*n;j++){
			scanf_s("%d",&(*a)[i][j]);
		}
	}
	getchar();
}

//输出数组各元素
void print(int**a,int m,int n){
	int i,j;
	printf("数组a为：\n");
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<n;j++){
			printf("%5d ",a[i][j]);
		}
	}
}

//数组行内递减冒泡排序
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
void MatrixRowSort(int m,int n,int***a){
	int i,j,*sum,tmp,*tmpa;
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

//矩阵 按行按列 递增排序,冒泡
void  swap(int*a,int*b){int tmp=*a;*a=*b;*b=tmp;return;}
void MatrixSort(int m,int n,int***a){
	int i,j,loc1_i,loc1_j,loc2_i,loc2_j;
	for(i=m*n-1;i>=0;i--){
		for(j=0;j<i;j++){
			loc1_i=j/n;loc1_j=j%n;
			loc2_i=((j+1)/n);loc2_j=(j+1)%n;
			if((*a)[loc1_i][loc1_j]<(*a)[loc2_i][loc2_j]){
				swap(&(*a)[loc1_i][loc1_j],&(*a)[loc2_i][loc2_j]);
			}
		}
	}
}

//释放二维数组
void FreeMatrix(int***a,int m){
	int i;
	for(i=0;i<m;i++){
		free((*a)[i]);
	}
	free(*a);
}

//主函数调用
int main(){
	int**a,m,n;char ch;
	while((ch=getchar())!='@'){
		creat(&a,&m,&n);
		print(a,m,n);
		
		//行内递减排序
		Rowsort(m,n,&a);
		printf("行内递减排序:\n");
		print(a,m,n);

		//按行和递增排序
		MatrixRowSort(m,n,&a);
		printf("按行和递增排序:\n");
		print(a,m,n);

		//按行按列递减排序
		MatrixSort(m,n,&a);
		printf("按行按列递增排序:\n");
		print(a,m,n);

		FreeMatrix(&a,m);
		
		printf("是否继续?按@结束程序\n");
	};
	return 0;
}
