#include<stdio.h>
#include<malloc.h>
#include<math.h>
void input(int***a,int *ma,int *na,int***b,int *mb,int *nb,int *loc_i,int*loc_j){
	int i,j;
	printf("请输入原始矩阵A的行、列值(m1,n1):");
	scanf_s("%d%d",ma,na);
	*a=(int**)malloc(*ma*sizeof(int*));
	for(i=0;i<*ma;i++)*((*a)+i)=(int*)malloc(*na*sizeof(int));
	printf("请输入原始矩阵A的各元素值：\n");
	for(i=0;i<*ma;i++){
		for(j=0;j<*na;j++){
			scanf_s("%d",&(*a)[i][j]);
		}
	}
	printf("请输入内嵌矩阵B的行、列值(m2,n2):");
	scanf_s("%d%d",mb,nb);
	printf("请输入内嵌矩阵B的各元素值：\n");
	*b=(int**)malloc(*mb*sizeof(int*));
	for(i=0;i<*mb;i++)*((*b)+i)=(int*)malloc(*nb*sizeof(int));
	for(i=0;i<*mb;i++){
		for(j=0;j<*nb;j++){
			scanf_s("%d",&(*b)[i][j]);
		}
	}
	while(1){
		printf("请输入嵌入位置：");
		scanf_s("%d%d",loc_i,loc_j);
		if(*loc_i<0||*loc_i>*ma||*loc_j<0||*loc_j>*na)printf("Error!please input again!\n");
		else break;
	}
}
void MatrixEmbedding(int**a,int**b,int***c,int ma,int na,int mb,int nb,int loc_i,int loc_j){
	int i,j;
	*c=(int**)malloc((ma+mb)*sizeof(int*));
	for(i=0;i<(ma+mb);i++)*((*c)+i)=(int*)malloc((na+nb)*sizeof(int));
	for(i=0;i<ma+mb;i++){
		for(j=0;j<na+nb;j++){
			if((i>=loc_i&&i<loc_i+mb)||(j>=loc_j&&j<loc_j+nb)){
				(*c)[i][j]=0;
			}else if(i<loc_i&&j<loc_j){
				(*c)[i][j]=a[i][j];
			}else if(i<loc_i&&j>=loc_j+nb){
				(*c)[i][j]=a[i][j-nb];
			}else if(i>=loc_i+mb&&j<loc_j){
				(*c)[i][j]=a[i-mb][j];
			}else if(i>=loc_i+mb&&j>=loc_j+nb){
				(*c)[i][j]=a[i-mb][j-nb];
			}
			if((i>=loc_i&&i<loc_i+mb)&&(j>=loc_j&&j<loc_j+nb)){
				(*c)[i][j]=b[i-loc_i][j-loc_j];
			}
		}
	}
}
void printc(int m,int n,int**a){
	int i,j;
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<n;j++){
			printf("%4d",a[i][j]);
		}
	}
}
void printd(int m,int n,double**a){
	int i,j;
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<n;j++){
			printf("%7.2lf",a[i][j]);
		}
	}
}
void MatrixGradientX(int**a,int m,int n,double***d){
	int i,j;
	*d=(double**)malloc((m)*sizeof(double*));
	for(i=0;i<(m);i++)*((*d)+i)=(double*)malloc((n)*sizeof(double));
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(j==0)(*d)[i][j]=a[i][j+1]-a[i][j];
			else if(j==n-1)(*d)[i][j]=a[i][j]-a[i][j-1];
			else (*d)[i][j]=(double)((a[i][j+1]-a[i][j-1])*0.5);
		}
	}
}
void MaxGradientX(int**c,int m,int n,double**d){
	int i,j;double max=abs(d[0][0]);
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(max<abs(d[i][j]))max=abs(d[i][j]);
		}
	}
	printf("矩阵C 中横向梯度绝对值最大的位置及元素值为:\n");
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(max==abs(d[i][j])){
				printf("%d,%d,%d\n",i,j,c[i][j]);
			}
		}
	}
}
void myfree(int***a,int m){
	int i;
	for(i=0;i<m;i++){
		free(*((*a)+i));
	}
	free(*a);
}
int main(){
	int**a,**b,**c,na,ma,nb,mb,loc_i,loc_j;
	double**d;
	input(&a,&ma,&na,&b,&mb,&nb,&loc_i,&loc_j);
	MatrixEmbedding(a,b,&c,ma,na,mb,nb,loc_i,loc_j);
	printf("完成嵌入后的新矩阵C为：\n");
	printc(ma+mb,na+nb,c);
	MatrixGradientX(c,ma+mb,na+nb,&d);
	printf("矩阵C的梯度矩阵D为：\n");
	printd(ma+mb,na+nb,d);
	MaxGradientX(c,ma+mb,na+nb,d);
	myfree(&a,ma);myfree(&b,mb);myfree(&c,ma+mb);
	for(int i=0;i<ma+mb;i++){
		free(*(d+i));
	}
	free(d);
	return 0;
}
