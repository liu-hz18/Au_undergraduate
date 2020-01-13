//矩阵新定义运算，动态开辟内存并释放。
#include<stdio.h>
#include<malloc.h>

//核心递归函数
void multily(int i,int j,int k,int result,int **a,int **b,int **c,int m,int n,int t){
	int tmp=1;
	for(int x=0;x<k;x++){tmp*=-1;}
	if(k==n&&i<m&&j<t){c[i][j]=result;multily(i,j+1,0,0,a,b,c,m,n,t);}
	else if(k<n&&i<m&&j==t)multily(i+1,0,0,0,a,b,c,m,n,t);
	else if(k<n&&i<m&&j<t)multily(i,j,k+1,result+tmp*a[i][k]*b[k][j],a,b,c,m,n,t);
	else if(i==m)return;
}
void input(int***a,int***b,int***c,int*m,int*n,int*t){
	int i,j;
	printf("please input the value of m n t:");
	scanf_s("%d%d%d",m,n,t);//由于m,n,t已经保存了对应变量的地址，所以这里不需要进行解地址，不然就是对指针赋值
	*a=(int**)malloc((*m)*sizeof(int*));
	for(i=0;i<*m;i++){
		*((*a)+i)=(int*)malloc((*n)*sizeof(int));
	}
	*b=(int**)malloc((*n)*sizeof(int*));
	for(i=0;i<*n;i++){
		*((*b)+i)=(int*)malloc((*t)*sizeof(int));
	}
	*c=(int**)malloc((*m)*sizeof(int*));
	for(i=0;i<*m;i++){
		*((*c)+i)=(int*)malloc((*t)*sizeof(int));
	}
	printf("please input the elements of matrix a:\n");
	for(i=0;i<(*m);i++){
		for(j=0;j<(*n);j++){
			scanf_s("%d",&(*a)[i][j]);
//由于a的级别是int***，所以为了对应，应该用(*a)[i][j]，才能对应子函数中的a[i][j]，这里的a是三级指针，指向主函数a的地址
//编程时保证一一对应就好
		}
	}
	printf("please input the elements of matrix b:\n");
	for(i=0;i<(*n);i++){
		for(j=0;j<(*t);j++){
			scanf_s("%d",&(*b)[i][j]);
		}
	}
	return ;
}
void myfree(int***a,int m){
	for(int i=0;i<m;i++){
		free(*((*a)+i));
	}
	free(*a);
	return;
}
int main(){
	int i,j,**a,**b,**c,m,n,t;
	input(&a,&b,&c,&m,&n,&t);
	//传参数的地址，虽然main空间中数组是地址传递，但是此处需要在子函数中动态建立内存，所以仍然需要传地址
	multily(0,0,0,0,a,b,c,m,n,t);
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<t;j++){
			printf("%4d",c[i][j]);
		}
	}
	myfree(&a,m);myfree(&b,n);myfree(&c,m);
	return 0;
}
