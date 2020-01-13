
//CopyRight@LiuHongzun
//Created by LiuHongzun at Tsinghua University.
// 2019/1/16

//Basic Operations of <Linear Algebra>.

#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<Windows.h>

//�жϸ������Ƿ�Ϊ0
int JudgeZero(double a){
	if(abs(a)<1e-7)return 1;
	else return 0;
};

//������������ֵ
void Swap(double&a,double&b){
	double tmp=a;
	a=b;
	b=tmp;
	return;
}

//��������������ֵ
void SwapVector(double**a,double**b,int n){
	int i;double tmp;
	for(i=0;i<n;i++){
		tmp=(*a)[i];
		(*a)[i]=(*b)[i];
		(*b)[i]=tmp;
	}
}

//��þ��������������
void GetMatrixSize(int*m,int*n){
	printf("�������������ֵ:\n");
	scanf_s("%d%d",m,n);
}

//��������Ԫ�ص�ֵ
double**InputMatrix(int m,int n){
	int i,j;
	double**a;
	a=(double**)malloc(m*sizeof(double*));
	for(i=0;i<m;i++){
		*(a+i)=(double*)malloc(n*sizeof(double));
	}
	printf("����������Ԫ��ֵ:\n");
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			scanf_s("%lf",&a[i][j]);
		}
	}
	return a;
}

//�����������ֵ
double*InputVector(int m){
	printf("������mά��������Ԫ�ص�ֵ:\n");
	int i;double*b;
	b=(double*)malloc(m*sizeof(double));
	for(i=0;i<m;i++){
		scanf_s("%lf",&b[i]);
	}
	return b;
}

//���ƾ���a��b
void CopyMatrix(double**b,double**a,int m,int n){
	int i,j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			b[i][j]=a[i][j];
		}
	}
}

//����һ������
double**CreatMatrix(int m,int n){
	int i;
	double**a;
	a=(double**)malloc(m*sizeof(double*));
	for(i=0;i<m;i++){
		*(a+i)=(double*)malloc(n*sizeof(double));
	}
	return a;
}

//���������
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

//Gauss��Ԫ
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

//������ʽ��ֵ
double GetDatValue(double**a,int n){
	double result=1.0;int i;
	a=Gauss(a,n,n);
	for(i=0;i<n;i++){
		result*=a[i][i];
	}
	return result;
}

//�����������
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

//ȡ��ʽ
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

//��-1��n�η�
double GetPow(int i){
	if(i%2==0)return 1.0;
	else return -1.0;
}

//��������
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

//��������
void SwapCol(double**a,int m,int t,int k){
	int i;double tmp;
	for(i=0;i<m;i++){
		tmp=a[i][t];
		a[i][t]=a[i][k];
		a[i][k]=tmp;
	}
}

//��������˳��Ϊ�н�����
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

//�������
void OutputMatrix(double**a,int m,int n){
	int i,j;
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<n;j++){
			printf("%9.5lf",a[i][j]);
		}
	}
	return ;
}

//��������
int GetRank(double**a,int m,int n){
	int i,rank=0;
	a=Gauss(a,m,n);
	AdjustMatrix(a,m,n);
	for(i=0;i<m&&i<n;i++){
		if(!JudgeZero(a[i][i]))rank++;
	}
	return rank;
}

//��Խǻ�֮������ȷ�����
void GetFullSolution(double**a,double*solution,int r){
	int i;
	for(i=0;i<r;i++){
		solution[i]=a[i][r]/a[i][i];
	}
}

//�����
void OutputSolution(double*b,int n){
	int i;
	for(i=0;i<n;i++){
		printf("%9.5lf ",b[i]);
	}
	putchar(10);
}

//��������Է�����
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
	printf("��˹��Ԫ���:\n");
	OutputMatrix(Ab,m,n+1);
	if(r==n){printf("��η���ֻ����⣡\n");return;}
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
	printf("��η��̽�ռ�ά��:%d\n��η��̵Ļ�����ϵΪ:\n",n-r);
	for(i=0;i<n-r;i++){
		OutputSolution(real_solu[i],n);
	}
	return ;
}

//���������Է������ؽ�
void GetNonHomoSolution(double**a,double*b,int m,int n){
	int i,k,r=0,*loc;double**tmp,**Ab,*solution,*real_solution;
	tmp=CreatMatrix(m,n);CopyMatrix(tmp,a,m,n);
	Ab=CombinMatrix(a,b,m,n);
	Gauss(Ab,m,n+1);
	loc=AdjustMatrix(Ab,m,n);
	printf("��˹��Ԫ���:\n");
	OutputMatrix(Ab,m,n+1);
	for(i=0;i<m&&i<n;i++){
		if(!JudgeZero(Ab[i][i]))r++;
	}
	for(i=r;i<m;i++){
		if(!JudgeZero(Ab[i][n])){
			printf("��������Է������޽�!\n");
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
		printf("��������Է������һ���ؽ�Ϊ:\n");
		OutputSolution(real_solution,n);
	}else if(r==n){
		GetFullSolution(Ab,solution,n);
		printf("�÷�������Ψһ��:\n");
		OutputSolution(solution,n);
	}
}

//������������������м����
void create(double***orth,double***tmp1,double***tmp2,int dim){
	int i,j;
	*orth=(double**)malloc((dim)*sizeof(double*));
	for(i=0;i<dim;i++){
		*((*orth)+i)=(double*)malloc((dim)*sizeof(double));
	}
	*tmp1=(double**)malloc((dim)*sizeof(double*));
	for(i=0;i<dim;i++){
		*((*tmp1)+i)=(double*)malloc((dim)*sizeof(double));
		for(j=0;j<i;j++)(*tmp1)[i][j]=0.0;//����ֵ��֤������Ϊ0
		(*tmp1)[i][i]=1.0;
	}
	*tmp2=(double**)malloc((dim)*sizeof(double*));
	for(i=0;i<dim;i++){
		*((*tmp2)+i)=(double*)malloc((dim)*sizeof(double));
		for(j=0;j<dim;j++)(*tmp2)[i][j]=0.0;//����ֵΪ0
	}
}

//����˷�
void matrix_multi(double***result,double**a,double**b,int m,int n,int r){
	int i,j,k;
	*result=(double**)malloc(m*sizeof(double*));
	for(i=0;i<m;i++){
		*((*result)+i)=(double*)malloc(r*sizeof(double));
		for(j=0;j<r;j++)(*result)[i][j]=0.0;//����ֵΪ0
	}
	for(i=0;i<m;i++){
		for(j=0;j<r;j++){
			for(k=0;k<n;k++){
				(*result)[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
}

//ת��
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

//�����˷�
double multiply(double*a,double*b,int dim){
	int i;double result=0.0;
	for(i=0;i<dim;i++){
		result+=a[i]*b[i];
	}
	return result;
}

//����
void input(double***a,int*dim){
	int i,j;
	printf("*********************\n    �����QR�ֽ�\n*********************\n\n������ռ�ά����");
	scanf_s("%d",dim);
	*a=(double**)malloc((*dim)*sizeof(double*));
	for(i=0;i<*dim;i++){
		*((*a)+i)=(double*)malloc((*dim)*sizeof(double));
	}
	printf("���������������ɵľ���A��\n");
	for(i=0;i<*dim;i++){
		for(j=0;j<*dim;j++){
			scanf_s("%lf",&(*a)[i][j]);
		}
	}
	return ;
}

//��������
void subtraction(double**a,double*b,int dim){
	int i;
	for(i=0;i<dim;i++){
		(*a)[i]-=b[i];
	}
}

//��������
double*num_multi(double*a,double coe,int dim){
	int i;double*result;
	result=(double*)malloc(dim*sizeof(double));
	for(i=0;i<dim;i++){
		result[i]=a[i]*coe;
	}
	return result;
}

//��λ��
void unitization(double***a,double***tmp2,int dim){
	for(int i=0;i<dim;i++){
		(*tmp2)[i][i]=sqrt(multiply((*a)[i],(*a)[i],dim));
		(*a)[i]=num_multi((*a)[i],1/(*tmp2)[i][i],dim);
	}
}

//������
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
	unitization(orth,tmp2,dim);//��λ��
	matrix_multi(up_tri,*tmp2,*tmp1,dim,dim,dim);
}

//���
void output(double**orth,double**up_tri,int dim){
	int i,j;
	printf("\n  �������� Q=\n");
	for(i=0;i<dim;i++,putchar(10)){
		for(j=0;j<dim;j++){
			printf("%11.6f ",orth[i][j]);
		}
	}
	printf("�����Ǿ��� R=\n");
	for(i=0;i<dim;i++,putchar(10)){
		for(j=0;j<dim;j++){
			printf("%11.6f ",up_tri[i][j]);
		}
	}
}

//�ͷ��ڴ�
void myfree(double***a,int m){
	int i;
	for(i=0;i<m;i++){free(*((*a)+i));}
	free(*a);
}

//QR�ֽ�
void QR(double**vector,double***orth,double***up_tri,int dim){
	double **tmp1,**tmp2;
	trans(&vector,dim);
	Schmidt(orth,vector,&tmp1,&tmp2,up_tri,dim);
	trans(orth,dim);
	myfree(&tmp1,dim);myfree(&tmp2,dim);
}

//�ж�������Ԫ���Ƿ�����
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

//���������ľ���
void print(double**vector,int dim){
	int i,j;
	printf("������ľ���\n");
	for(i=0;i<dim;i++,putchar(10)){
		for(j=0;j<dim;j++){
			printf("%11.6f ",vector[i][j]);
		}
	}
	return;
}

//QR���������������ֵ�������
void GetEigenValue(double***orth,double***up_tri,double***vector,double**value,int dim){
	int k=1;
	*value=(double*)malloc(dim*sizeof(double));
	const int end=100;//��������
	for(k=1;judge(*vector,dim)!=0;k++){
		matrix_multi(vector,*up_tri,*orth,dim,dim,dim);
		QR(*vector,orth,up_tri,dim);
		trans(vector,dim);
	}
	printf("����������%d\n",k);
	print(*vector,dim);
	for(k=0;k<dim;k++){
		(*value)[k]=(*vector)[k][k];
	}
	printf("����ֵΪ:\n");
	for(k=1;k<=dim;k++){
		if(k%4==0)putchar(10);
		printf("%11.6lf",(*value)[k-1]);
	}
	putchar(10);
}

//��������
void opreate(){
	char ch;
	double**a,**gauss,*b,**ni,**tmp;
	int m,n,r,t;
	double**vector,**orth,**up_tri,*value;int dim;
	printf("��������в�����Ҫ����ĸ����:\nA/��˹��Ԫ B/�������� C/����η��̵Ľ� D/���������Է��̵Ľ� E/QR�ֽ� F/���������ֵ G/������ʽ��ֵ H/�������� I/�������� J/����˷� Q/�˳�\n");
	while((ch=getchar())!='Q'){
		switch(ch){		
		case 'A':
			GetMatrixSize(&m,&n);
			a=InputMatrix(m,n);
			gauss=Gauss(a,m,n);
			printf("��˹��Ԫ��ľ���:\n");
			OutputMatrix(gauss,m,n);
			break;
		case 'B':
			GetMatrixSize(&m,&n);
			a=InputMatrix(m,n);
			printf("�������:%d\n",(r=GetRank(a,m,n)));
			break;
		case 'C':
			GetMatrixSize(&m,&n);
			a=InputMatrix(m,n);
			//��η���
			GetSolution(a,m,n);
			break;
		case 'D':
			GetMatrixSize(&m,&n);
			a=InputMatrix(m,n);
			b=InputVector(m);
			//��������Է�����
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
			printf("����ʽֵ=%.2f\n",GetDatValue(a,n));
			break;
		case 'H':
			GetMatrixSize(&m,&n);
			a=InputMatrix(n,n);
			tmp=CreatMatrix(n,n);
			CopyMatrix(tmp,a,n,n);
			if(JudgeZero(GetDatValue(tmp,n))){
				printf("�þ��󲻿��棡\n");
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
			printf("����������Сm n t:\n");
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

//����������
int main(){
	system("color F0");
	opreate();
	return 0;
}
