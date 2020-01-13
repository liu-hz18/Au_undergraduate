//利用 QR 迭代思想求矩阵特征值 

//算法缺陷：由于根据施密特正交化方法进行QR 分解，只能对可逆矩阵进行QR分解，即矩阵的特征值不可非零！！！
//更好的办法：可以用对矩阵用初等相似变换约化为上Hessenberg阵，再用QR方法求解Hessenberg阵的全部特征值。

//期待改进！！！

#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<Windows.h>

//创建正交矩阵和两个中间矩阵
void create(double***orth,double***tmp1,double***tmp2,int dim){
	int i,j;
	*orth=(double**)malloc((dim)*sizeof(double*));
	for(i=0;i<dim;i++){
		*((*orth)+i)=(double*)malloc((dim)*sizeof(double));
	}
	*tmp1=(double**)malloc((dim)*sizeof(double*));
	for(i=0;i<dim;i++){
		*((*tmp1)+i)=(double*)malloc((dim)*sizeof(double));
		for(j=0;j<i;j++)(*tmp1)[i][j]=0.0;//赋初值保证下三角为0
		(*tmp1)[i][i]=1.0;
	}
	*tmp2=(double**)malloc((dim)*sizeof(double*));
	for(i=0;i<dim;i++){
		*((*tmp2)+i)=(double*)malloc((dim)*sizeof(double));
		for(j=0;j<dim;j++)(*tmp2)[i][j]=0.0;//赋初值为0
	}
}
//矩阵乘法
void matrix_multi(double***result,double**a,double**b,int m,int n,int r){
	int i,j,k;
	*result=(double**)malloc(m*sizeof(double*));
	for(i=0;i<m;i++){
		*((*result)+i)=(double*)malloc(r*sizeof(double));
		for(j=0;j<r;j++)(*result)[i][j]=0.0;//赋初值为0
	}
	for(i=0;i<m;i++){
		for(j=0;j<r;j++){
			for(k=0;k<n;k++){
				(*result)[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
}
//转置
void trans(double***a,int dim){
	double tmp;int i,j;
	for(i=0;i<dim;i++){
		for(j=i;j<dim;j++){
			tmp=(*a)[j][i];
			(*a)[j][i]=(*a)[i][j];
			(*a)[i][j]=tmp;
		}
	}
}
//向量乘法
double multiply(double*a,double*b,int dim){
	int i;double result=0.0;
	for(i=0;i<dim;i++){
		result+=a[i]*b[i];
	}
	return result;
}
//输入
void input(double***a,int*dim){
	int i,j;
	printf("*********************\n    矩阵的QR分解\n*********************\n\n请输入空间维数：");
	scanf_s("%d",dim);
	*a=(double**)malloc((*dim)*sizeof(double*));
	for(i=0;i<*dim;i++){
		*((*a)+i)=(double*)malloc((*dim)*sizeof(double));
	}
	printf("请输入列向量构成的矩阵A：\n");
	for(i=0;i<*dim;i++){
		for(j=0;j<*dim;j++){
			scanf_s("%lf",&(*a)[i][j]);
		}
	}
	return ;
}
//向量减法
void subtraction(double**a,double*b,int dim){
	int i;
	for(i=0;i<dim;i++){
		(*a)[i]-=b[i];
	}
}
//向量数乘
double*num_multi(double*a,double coe,int dim){
	int i;double*result;
	result=(double*)malloc(dim*sizeof(double));
	for(i=0;i<dim;i++){
		result[i]=a[i]*coe;
	}
	return result;
}
//单位化
void unitization(double***a,double***tmp2,int dim){
	for(int i=0;i<dim;i++){
		(*tmp2)[i][i]=sqrt(multiply((*a)[i],(*a)[i],dim));
		(*a)[i]=num_multi((*a)[i],1/(*tmp2)[i][i],dim);
	}
}
//正交化
void Schmidt(double***orth,double**vertor,double***tmp1,double***tmp2,double***up_tri,int dim){
	int i,j,k;double coe;
	create(orth,tmp1,tmp2,dim);
	for(i=0;i<dim;i++){
		for(k=0;k<dim;k++){
			(*orth)[i][k]=vertor[i][k];
		}
		for(j=0;j<i;j++){
			coe=multiply(vertor[i],(*orth)[j],dim)/multiply((*orth)[j],(*orth)[j],dim);
			(*tmp1)[j][i]=coe;
			subtraction(&(*orth)[i],num_multi((*orth)[j],coe,dim),dim);
		}
	}
	unitization(orth,tmp2,dim);//单位化
	matrix_multi(up_tri,*tmp2,*tmp1,dim,dim,dim);
}
//输出
void output(double**orth,double**up_tri,int dim){
	int i,j;
	printf("\n  正交矩阵 Q=\n");
	for(i=0;i<dim;i++,putchar(10)){
		for(j=0;j<dim;j++){
			printf("%11.6f ",orth[i][j]);
		}
	}
	printf("上三角矩阵 R=\n");
	for(i=0;i<dim;i++,putchar(10)){
		for(j=0;j<dim;j++){
			printf("%11.6f ",up_tri[i][j]);
		}
	}
}
//释放内存
void myfree(double***a,int m){
	int i;
	for(i=0;i<m;i++){free(*((*a)+i));}
	free(*a);
}
//QR分解
void QR(double**vector,double***orth,double***up_tri,int dim){
	double **tmp1,**tmp2;
	trans(&vector,dim);
	Schmidt(orth,vector,&tmp1,&tmp2,up_tri,dim);
	trans(orth,dim);
	myfree(&tmp1,dim);myfree(&tmp2,dim);
}
//判断下三角元素是否收敛
int judge(double**vector,int dim){
	int i,j,flag=0;
	for(i=0;i<dim;i++){
		for(j=0;j<i;j++){
			if(abs(vector[i][j])>1e-7){flag=1;break;}
		}
		if(flag==1)break;
	}
	return flag;
}
//输出迭代后的矩阵
void print(double**vector,int dim){
	int i,j;
	printf("迭代后的矩阵：\n");
	for(i=0;i<dim;i++,putchar(10)){
		for(j=0;j<dim;j++){
			printf("%11.6f ",vector[i][j]);
		}
	}
	return;
}
//QR迭代方法求解特征值，并输出
void eigenvalue(double***orth,double***up_tri,double***vector,double**value,int dim){
	int k=1;
	*value=(double*)malloc(dim*sizeof(double));
	const int end=100;//迭代次数
	for(k=1;judge(*vector,dim)!=0;k++){
		matrix_multi(vector,*up_tri,*orth,dim,dim,dim);
		QR(*vector,orth,up_tri,dim);
		trans(vector,dim);
	}
	printf("迭代次数：%d\n",k);
	print(*vector,dim);
	for(k=0;k<dim;k++){
		(*value)[k]=(*vector)[k][k];
	}
	printf("特征值为:\n");
	for(k=1;k<=dim;k++){
		if(k%4==0)putchar(10);
		printf("%11.6lf",(*value)[k-1]);
	}
	putchar(10);
}
//主函数调用
int main(){
	double**vector,**orth,**up_tri,*value;int dim;
	system("color F0");
	input(&vector,&dim);
	QR(vector,&orth,&up_tri,dim);
	output(orth,up_tri,dim);
	eigenvalue(&orth,&up_tri,&vector,&value,dim);
	myfree(&vector,dim);myfree(&orth,dim);
	myfree(&up_tri,dim);
	return 0;
}
