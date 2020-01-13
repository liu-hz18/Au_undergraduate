
//CopyRight@LiuHongzun
//Created by LiuHongzun at Tsinghua University.
// 2019/1/16

//Basic Operations of <Linear Algebra>.

#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<Windows.h>

//判断浮点数是否为0
int JudgeZero(double a){
	if(abs(a)<1e-7)return 1;
	else return 0;
};

//交换两个数的值
void Swap(double&a,double&b){
	double tmp=a;
	a=b;
	b=tmp;
	return;
}

//交换两个向量的值
void SwapVector(double**a,double**b,int n){
	int i;double tmp;
	for(i=0;i<n;i++){
		tmp=(*a)[i];
		(*a)[i]=(*b)[i];
		(*b)[i]=tmp;
	}
}

//获得矩阵的行数和列数
void GetMatrixSize(int*m,int*n){
	printf("请输入矩阵行列值:\n");
	scanf_s("%d%d",m,n);
}

//输入矩阵各元素的值
double**InputMatrix(int m,int n){
	int i,j;
	double**a;
	a=(double**)malloc(m*sizeof(double*));
	for(i=0;i<m;i++){
		*(a+i)=(double*)malloc(n*sizeof(double));
	}
	printf("请输入矩阵各元素值:\n");
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			scanf_s("%lf",&a[i][j]);
		}
	}
	return a;
}

//输入解向量的值
double*InputVector(int m){
	printf("请输入m维解向量各元素的值:\n");
	int i;double*b;
	b=(double*)malloc(m*sizeof(double));
	for(i=0;i<m;i++){
		scanf_s("%lf",&b[i]);
	}
	return b;
}

//复制矩阵a到b
void CopyMatrix(double**b,double**a,int m,int n){
	int i,j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			b[i][j]=a[i][j];
		}
	}
}

//创建一个矩阵
double**CreatMatrix(int m,int n){
	int i;
	double**a;
	a=(double**)malloc(m*sizeof(double*));
	for(i=0;i<m;i++){
		*(a+i)=(double*)malloc(n*sizeof(double));
	}
	return a;
}

//求增广矩阵
double**CombinMatrix(double**a,double*b,int m,int n){
	int i;
	double**Ab;
	Ab=(double**)malloc(m*sizeof(double*));
	for(i=0;i<m;i++){
		*(Ab+i)=(double*)malloc((n+1)*sizeof(double));
	}
	CopyMatrix(Ab,a,m,n);
	for(i=0;i<m;i++){
		Ab[i][n]=b[i];
	}
	return Ab;
}

//Gauss消元
double**Gauss(double**a,int m,int n){
	int i,j,k,flag;
	double coe;
	for(j=0;j<n&&j<m;j++){
		if(JudgeZero(a[j][j])){
			flag=0;
			for(i=j+1;i<m;i++){
				if(!JudgeZero(a[i][j])){
					SwapVector(&a[i],&a[j],n);
					flag=1;break;
				}
			}
			if(flag==0)continue;
		}
		for(i=0;i<m;i++){
			if(i!=j){
				coe=a[i][j]/a[j][j];
				for(k=j;k<n;k++){
					a[i][k]=a[i][k]-coe*a[j][k];
				}
			}
		}
	}
	return a;
}

//求行列式的值
double GetDatValue(double**a,int n){
	double result=1.0;int i;
	a=Gauss(a,n,n);
	for(i=0;i<n;i++){
		result*=a[i][i];
	}
	return result;
}

//方块矩阵求逆
double**GetNi(double**a,int n){
	int i,j,k,flag;double**re,coe;
	re=(double**)malloc(n*sizeof(double*));
	for(i=0;i<n;i++){
		*(re+i)=(double*)malloc(n*sizeof(double));
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j)re[i][j]=1.0;
			else re[i][j]=0.0;
		}
	}
	for(j=0;j<n&&j<n;j++){
		if(JudgeZero(a[j][j])){
			flag=0;
			for(i=j+1;i<n;i++){
				if(!JudgeZero(a[i][j])){
					SwapVector(&re[i],&re[j],n);
					SwapVector(&a[i],&a[j],n);
					flag=1;break;
				}
			}
			if(flag==0)continue;
		}
		for(i=0;i<n;i++){
			if(i!=j){
				coe=a[i][j]/a[j][j];
				for(k=j;k<n;k++){
					re[i][k]=re[i][k]-coe*re[j][k];
					a[i][k]=a[i][k]-coe*a[j][k];
				}
			}
		}
	}
	return re;
}

//取子式
double**GetSubMatrix(double**a,int m,int n,int p,int q){
	int i,j;
	double**SubMatrix;
	SubMatrix=CreatMatrix(m-1,n-1);
	for(i=0;i<m-1;i++){
		for(j=0;j<n-1;j++){
			if(i<p&&j<q)SubMatrix[i][j]=a[i][j];
			else if(i<p&&j>=q)SubMatrix[i][j]=a[i][j+1];
			else if(i>=p&&j<q)SubMatrix[i][j]=a[i+1][j];
			else if(i>=p&&j>=q)SubMatrix[i][j]=a[i+1][j+1];
		}
	}
	return SubMatrix;
}

//求-1的n次方
double GetPow(int i){
	if(i%2==0)return 1.0;
	else return -1.0;
}

//求伴随矩阵
double**GetBansui(double**a,int n){
	int i,j;
	double**re;
	re=(double**)malloc(n*sizeof(double*));
	for(i=0;i<n;i++){
		*(re+i)=(double*)malloc(n*sizeof(double));
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			re[i][j]=GetDatValue(GetSubMatrix(a,n,n,j,i),n-1)*GetPow(i+j);
		}
	}
	return re;
}

//交换两列
void SwapCol(double**a,int m,int t,int k){
	int i;double tmp;
	for(i=0;i<m;i++){
		tmp=a[i][t];
		a[i][t]=a[i][k];
		a[i][k]=tmp;
	}
}

//调整变量顺序化为行阶梯型
int*AdjustMatrix(double**a,int m,int n){
	int *loc,i,j,sum[100],count,tmp;
	loc=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++){
		loc[i]=i;
	}
	for(i=0;i<m;i++){
		count=0;
		for(j=i;j<n;j++){
			if(!JudgeZero(a[i][j]))count++;
		}
		sum[i]=count;
	}
	for(i=m-1;i>=0;i--){
		for(j=0;j<i;j++){
			if(sum[j]<sum[j+1]){
				SwapVector(&a[j],&a[j+1],n+1);
				tmp=sum[j];
				sum[j]=sum[j+1];
				sum[j+1]=tmp;
			}
		}
	}
	for(i=0;i<m;i++){
		if(JudgeZero(a[i][i])){
			for(j=i;j<n;j++){
				if(!JudgeZero(a[i][j])){
					SwapCol(a,m,i,j);
					loc[i]=j;
					loc[j]=i;
					break;
				}
			}
		}
	}
	return loc;
}

//输出矩阵
void OutputMatrix(double**a,int m,int n){
	int i,j;
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<n;j++){
			printf("%9.5lf",a[i][j]);
		}
	}
	return ;
}

//求矩阵的秩
int GetRank(double**a,int m,int n){
	int i,rank=0;
	a=Gauss(a,m,n);
	AdjustMatrix(a,m,n);
	for(i=0;i<m&&i<n;i++){
		if(!JudgeZero(a[i][i]))rank++;
	}
	return rank;
}

//解对角化之后的满秩方程组
void GetFullSolution(double**a,double*solution,int r){
	int i;
	for(i=0;i<r;i++){
		solution[i]=a[i][r]/a[i][i];
	}
}

//输出解
void OutputSolution(double*b,int n){
	int i;
	for(i=0;i<n;i++){
		printf("%9.5lf ",b[i]);
	}
	putchar(10);
}

//解齐次线性方程组
void GetSolution(double**a,int m,int n){
	int*loc,r,i,j,k;
	double*b,**Ab,**solution,**tmp,**real_solu;
	b=(double*)malloc(m*sizeof(double));
	for(i=0;i<n;i++){
		b[i]=0;
	}
	Ab=CombinMatrix(a,b,m,n);
	Gauss(Ab,m,n+1);
	r=GetRank(a,m,n);
	printf("高斯消元结果:\n");
	OutputMatrix(Ab,m,n+1);
	if(r==n){printf("齐次方程只有零解！\n");return;}
	loc=AdjustMatrix(Ab,m,n);
	solution=CreatMatrix(n-r,n);real_solu=CreatMatrix(n-r,n);
	tmp=CreatMatrix(m,n+1);
	for(j=r;j<n;j++){
		CopyMatrix(tmp,Ab,m,n+1);
		for(i=r;i<n;i++){
			if(i==j)solution[j-r][i]=1.0;
			else solution[j-r][i]=0.0;
		}
		for(k=0;k<m;k++){
			tmp[k][r]=tmp[k][n]-tmp[k][j];
		}
		GetFullSolution(tmp,solution[j-r],r);
		for(i=0;i<n;i++){
			real_solu[j-r][loc[i]]=solution[j-r][i];
		}
	}
	printf("齐次方程解空间维度:%d\n齐次方程的基础解系为:\n",n-r);
	for(i=0;i<n-r;i++){
		OutputSolution(real_solu[i],n);
	}
	return ;
}

//解非齐次线性方程组特解
void GetNonHomoSolution(double**a,double*b,int m,int n){
	int i,k,r=0,*loc;double**tmp,**Ab,*solution,*real_solution;
	tmp=CreatMatrix(m,n);CopyMatrix(tmp,a,m,n);
	Ab=CombinMatrix(a,b,m,n);
	Gauss(Ab,m,n+1);
	loc=AdjustMatrix(Ab,m,n);
	printf("高斯消元结果:\n");
	OutputMatrix(Ab,m,n+1);
	for(i=0;i<m&&i<n;i++){
		if(!JudgeZero(Ab[i][i]))r++;
	}
	for(i=r;i<m;i++){
		if(!JudgeZero(Ab[i][n])){
			printf("非齐次线性方程组无解!\n");
			return;
		}
	}
	solution=(double*)malloc(n*sizeof(double));
	real_solution=(double*)malloc(n*sizeof(double));
	if(r<n){
		GetSolution(tmp,m,n);
		for(i=r;i<n;i++){
			if(i==r)solution[i]=1.0;
			else solution[i]=0.0;
		}
		for(k=0;k<m;k++){
			Ab[k][r]=Ab[k][n]-Ab[k][r];
		}
		GetFullSolution(Ab,solution,r);
		for(i=0;i<n;i++){
			real_solution[loc[i]]=solution[i];
		}
		printf("非齐次线性方程组的一个特解为:\n");
		OutputSolution(real_solution,n);
	}else if(r==n){
		GetFullSolution(Ab,solution,n);
		printf("该方程组有唯一解:\n");
		OutputSolution(solution,n);
	}
}

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
void GetEigenValue(double***orth,double***up_tri,double***vector,double**value,int dim){
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

//操作函数
void opreate(){
	char ch;
	double**a,**gauss,*b,**ni,**tmp;
	int m,n,r,t;
	double**vector,**orth,**up_tri,*value;int dim;
	printf("请输入进行操作需要的字母代号:\nA/高斯消元 B/求矩阵的秩 C/求齐次方程的解 D/求非齐次线性方程的解 E/QR分解 F/求矩阵特征值 G/求行列式的值 H/矩阵求逆 I/求伴随矩阵 J/矩阵乘法 Q/退出\n");
	while((ch=getchar())!='Q'){
		switch(ch){		
		case 'A':
			GetMatrixSize(&m,&n);
			a=InputMatrix(m,n);
			gauss=Gauss(a,m,n);
			printf("高斯消元后的矩阵:\n");
			OutputMatrix(gauss,m,n);
			break;
		case 'B':
			GetMatrixSize(&m,&n);
			a=InputMatrix(m,n);
			printf("矩阵的秩:%d\n",(r=GetRank(a,m,n)));
			break;
		case 'C':
			GetMatrixSize(&m,&n);
			a=InputMatrix(m,n);
			//齐次方程
			GetSolution(a,m,n);
			break;
		case 'D':
			GetMatrixSize(&m,&n);
			a=InputMatrix(m,n);
			b=InputVector(m);
			//非齐次线性方程组
			GetNonHomoSolution(a,b,m,n);
			break;
		case 'E':
			input(&vector,&dim);
			QR(vector,&orth,&up_tri,dim);
			output(orth,up_tri,dim);
			myfree(&vector,dim);
			myfree(&orth,dim);
			myfree(&up_tri,dim);
			break;
		case 'F':
			input(&vector,&dim);
			QR(vector,&orth,&up_tri,dim);
			output(orth,up_tri,dim);
			GetEigenValue(&orth,&up_tri,&vector,&value,dim);
			myfree(&vector,dim);
			myfree(&orth,dim);
			myfree(&up_tri,dim);
			break;
		case 'G':
			GetMatrixSize(&m,&n);
			a=InputMatrix(m,n);
			printf("行列式值=%.2f\n",GetDatValue(a,n));
			break;
		case 'H':
			GetMatrixSize(&m,&n);
			a=InputMatrix(n,n);
			tmp=CreatMatrix(n,n);
			CopyMatrix(tmp,a,n,n);
			if(JudgeZero(GetDatValue(tmp,n))){
				printf("该矩阵不可逆！\n");
				break;
			}
			ni=GetNi(a,n);
			OutputMatrix(ni,n,n);
			break;
		case 'I':
			GetMatrixSize(&m,&n);
			a=InputMatrix(n,n);
			OutputMatrix(GetBansui(a,n),n,n);
			break;
		case 'J':
			printf("请输入矩阵大小m n t:\n");
			scanf_s("%d%d%d",&m,&n,&t);
			a=InputMatrix(m,n);
			tmp=InputMatrix(m,n);
			ni=CreatMatrix(m,t);
			matrix_multi(&ni,a,tmp,m,n,t);
			OutputMatrix(ni,m,t);
			break;
		default:break;
		}
		getchar();
	}
	return;
}

//主函数调用
int main(){
	system("color F0");
	opreate();
	return 0;
}
