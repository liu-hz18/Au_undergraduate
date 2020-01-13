
//CopyRight@LiuHongzun
//Created by LiuHongzun at Tsinghua University.
// 2019/1/21

//Basic Operations of <Linear Algebra>.

#include<stdio.h>
#include<math.h>
#include<malloc.h>
#include<Windows.h>

double multiply(double*a,double*b,int dim);
void matrix_multi(double***result,double**a,double**b,int m,int n,int r);
double**CreatMatrix(int m,int n);
double GetVectorLen(double*Vector,int n);
double GetAngle(double*Vector1,double*Vector2,int n);
double*GetNonHomoSolution(double**a,double*b,int m,int n);
double GetDatValue(double**a,int n);
void OutputMatrix(double**a,int m,int n);

//ŷʽ�ռ�ֱ�߲���
struct Line{
	double point[3];
	double direction[3];
};

//ŷʽ�ռ�ƽ�����
struct Plane{
	double NormalVector[3];//����������
	double d;//������
};

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

//����������������ֵ
void SwapVector(double**a,double**b,int n){
	int i;double tmp;
	for(i=0;i<n;i++){
		tmp=(*a)[i];
		(*a)[i]=(*b)[i];
		(*b)[i]=tmp;
	}
}

//��������
double*GetVector(int*n){
	int i;double*Vector;
	printf("����������ά��:\n");
	scanf_s("%d",n);
	Vector=(double*)malloc(*n*sizeof(double));
	for(i=0;i<*n;i++){
		scanf_s("%lf",Vector[i]);
	}
	return Vector;
}

//������ά����
double*GetSanVector(){
	int i;double*p;
	p=(double*)malloc(3*sizeof(double));
	printf("��������ά����:\n");
	for(i=0;i<3;i++){
		scanf_s("%lf",&p[i]);
	}
	return p;
}

//�����ά����
void OutputSanVector(double*p){
	int i;
	for(i=0;i<3;i++){
		printf("%.2f ",p[i]);
	}
	putchar(10);
	return ;
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

//����һ��ƽ��ĸ�����
struct Plane InputPlane(){
	Plane plane;
	printf("������ƽ�������(һ�㷽��A B C D):\n");
	scanf_s("%lf%lf%lf%lf",&plane.NormalVector[0],&plane.NormalVector[1],&plane.NormalVector[2],&plane.d);
	return plane;
}

//����һ��ֱ�߸�����
struct Line InputLine(){
	Line line;
	printf("������ֱ����������:\n");
	scanf_s("%lf%lf%lf",&line.point[0],&line.point[1],&line.point[2]);
	printf("������ֱ�ߵķ�������\n");
	scanf_s("%lf%lf%lf",&line.direction[0],&line.direction[1],&line.direction[2]);
	return line;
}

//�����潻��
void GetInterPiont(Line line,Plane plane){
	int i;double p[3];double t,tmp1,tmp2;
	tmp1=multiply(line.point,plane.NormalVector,3);
	tmp2=multiply(line.direction,plane.NormalVector,3);
	if(!JudgeZero(tmp2)){
		t=-(tmp1+plane.d)/tmp2;
		for(i=0;i<3;i++){
			p[i]=line.point[i]+line.direction[i]*t;
		}
		printf("���潻��Ϊ:\n");
		for(i=0;i<3;i++){
			printf("%.2f ",p[i]);
		}
		putchar(10);
	}else if((!JudgeZero(tmp1))&&JudgeZero(tmp2)){
		printf("����ƽ��!\n");
	}else{
		printf("�����غ�!\n");
	}
}

//������֮�����
void GetPointsDis(){
	double tmp[3];int i;
	double*p1;double*p2;
	p1=(double*)malloc(3*sizeof(double));
	p2=(double*)malloc(3*sizeof(double));
	printf("���������������:\n");
	for(i=0;i<3;i++){
		scanf_s("%lf",&p1[i]);
	}
	for(i=0;i<3;i++){
		scanf_s("%lf",&p2[i]);
	}
	for(i=0;i<3;i++){
		tmp[i]=p1[i]-p2[i];
	}
	printf("������룺%.3f\n",sqrt(tmp[0]*tmp[0]+tmp[1]*tmp[1]+tmp[2]*tmp[2]));
	return ;
}

//������
void  GetP_PDis(){
	double tmp1=0.0,tmp2=0.0,result;int i;double p[3];Plane plane;
	printf("������������:\n");
	for(i=0;i<3;i++){
		scanf_s("%lf",&p[i]);
	}
	plane=InputPlane();
	for(i=0;i<3;i++){
		tmp1+=plane.NormalVector[i]*p[i];
	}
	tmp1+=plane.d;
	for(i=0;i<3;i++){
		tmp2+=plane.NormalVector[i]*plane.NormalVector[i];
	}
	printf("�����=%.3f\n",(result=abs(tmp1)/sqrt(tmp2)));
	return ;
}

//��������ϵ�µ������˻�
void Get_Fangshe_Multi(){
	double **e,**A,**x,**y,**tmp1,**tmp2;
	int i,j;
	e=CreatMatrix(3,3);
	A=CreatMatrix(3,3);
	x=CreatMatrix(1,3);
	y=CreatMatrix(3,1);
	printf("��������������������:\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			scanf_s("%lf",&e[i][j]);
		}
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			A[i][j]=multiply(e[i],e[j],3);
		}
	}
	
	printf("��������������:\n");
	for(i=0;i<3;i++)scanf_s("%lf",&x[0][i]);
	for(i=0;i<3;i++)scanf_s("%lf",&y[i][0]);
	printf("������µĶ�������AΪ:\n");
	OutputMatrix(A,3,3);
	matrix_multi(&tmp1,x,A,1,3,3);
	matrix_multi(&tmp2,tmp1,y,1,3,1);
	printf("�÷�������ϵ�µ������˻�Ϊ:%.3f\n",tmp2[0][0]);
	return ;
}

//����
double*GetCrossProduct(double*Vector1,double*Vector2){
	double*result;
	result=(double*)malloc(3*sizeof(double));
	result[0]=Vector1[1]*Vector2[2]-Vector1[2]*Vector2[1];
	result[1]=-(Vector1[0]*Vector2[2]-Vector1[2]*Vector2[0]);
	result[2]=Vector1[0]*Vector2[1]-Vector1[1]*Vector2[0];
	return result;
}

//���ϻ�
double GetMixProduct(double*Vector1,double*Vector2,double*Vector3){
	int i;
	double**A;
	A=CreatMatrix(3,3);
	for(i=0;i<3;i++){
		A[0][i]=Vector1[i];
	}
	for(i=0;i<3;i++){
		A[1][i]=Vector2[i];
	}
	for(i=0;i<3;i++){
		A[2][i]=Vector3[i];
	}
	return GetDatValue(A,3);
}

//����߾�
void GetP_LDis(){
	double p[3],dis;int i;Line line;
	printf("�����������:\n");
	for(i=0;i<3;i++){
		scanf_s("%lf",&p[i]);
	}
	line=InputLine();
	for(i=0;i<3;i++){
		p[i]=p[i]-line.point[i];
	}
	dis=GetVectorLen(GetCrossProduct(p,line.direction),3)/GetVectorLen(line.direction,3);
	printf("���߾�Ϊ:%.3f\n",dis);
	return ;
}

//������ֱ�߾���
void GetL_LDis(){
	double p[3],tmp1,tmp2;int i;Line line1,line2;
	line1=InputLine();
	line2=InputLine();
	for(i=0;i<3;i++){
		p[i]=line1.point[i]-line2.point[i];
	}
	tmp1=GetMixProduct(p,line1.direction,line2.direction);
	tmp2=GetVectorLen(GetCrossProduct(line1.direction,line2.direction),3);
	if(!JudgeZero(tmp2))
		printf("���߾�Ϊd=%.3f\n",tmp1/tmp2);
	else if(abs(GetAngle(p,line1.direction,3)-1.0)<1e-6)
		printf("�����غ�!\n");
	else printf("����ƽ��!\n");
	return ;
}

//��������ƽ��һ�㷽��
void GetPlaneFunc(){
	int i,j;double p[3][3],v1[3],v2[3];Plane plane;
	printf("�����벻���ߵ�����:\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			scanf_s("%lf",&p[i][j]);
		}
	}
	for(i=0;i<3;i++){
		v1[i]=p[0][i]-p[1][i];
	}
	for(i=0;i<3;i++){
		v2[i]=p[0][i]-p[2][i];
	}
	plane.NormalVector[0]=v1[1]*v2[2]-v1[2]*v2[1];
	plane.NormalVector[1]=-(v1[0]*v2[2]-v1[2]*v2[0]);
	plane.NormalVector[2]=v1[0]*v2[1]-v1[1]*v2[0];
	plane.d=-(p[0][0]*plane.NormalVector[0]+p[0][1]*plane.NormalVector[1]+p[0][2]*plane.NormalVector[2]);
	printf("ֱ�ߵ�һ�㷽��Ϊ:\n");
	printf("(%.2f)X+(%.2f)Y+(%.2f)Z+(%.2f)=0\n",plane.NormalVector[0],plane.NormalVector[1],plane.NormalVector[2],plane.d);
	return ;
}

//����ƽ��Ľ��߷���
void GetLineFunc(Plane plane1,Plane plane2){
	double**A,*v,*p,*b;int i;Line line;
	A=CreatMatrix(2,3);
	b=(double*)malloc(2*sizeof(double));
	if(abs(GetAngle(plane1.NormalVector,plane2.NormalVector,3)-1.0)<1e-6){
		printf("��ƽ��ƽ�л��غϣ�\n");
	}else{
		v=GetCrossProduct(plane1.NormalVector,plane2.NormalVector);
		for(i=0;i<3;i++){
			A[0][i]=plane1.NormalVector[i];
		}
		for(i=0;i<3;i++){
			A[1][i]=plane2.NormalVector[i];
		}
		b[0]=-plane1.d;b[1]=-plane2.d;
		p=GetNonHomoSolution(A,b,2,3);
		for(i=0;i<3;i++){
			line.point[i]=p[i];
			line.direction[i]=v[i];
		}
		printf("ֱ�ߵĶԳƷ���Ϊ:\n");
		printf("X-(%.2f) Y-(%.2f) Z-(%.2f)\n",p[0],p[1],p[2]);
		printf("--------=---------=------- = 0\n");
		printf("  %.2lf    %.2lf    %.2lf\n",v[0],v[1],v[2]);
	}
	return ;
}

//��������ֱ�߷���
void GetLineFuncP(){
	int i;double p1[3],p2[3];
	printf("������ֱ�߾���������:\n");
	for(i=0;i<3;i++){
		scanf_s("%lf",&p1[i]);
	}
	for(i=0;i<3;i++){
		scanf_s("%lf",&p2[i]);
	}
	printf("ֱ�ߵĶԳƷ���Ϊ:\n");
	printf("X-%.2f Y-%.2f Z-%.2f\n",p1[0],p1[1],p1[2]);
	printf("------=------=------ = 0\n");
	printf(" %.2lf  %.2lf  %.2lf\n",p1[0]-p2[0],p1[1]-p2[1],p1[2]-p2[2]);
	return ;
}

//����ֱ�߹�����
void GetComLine(){
	Line line1,line2;double*v1v2;
	Plane plane1,plane2;
	line1=InputLine();
	line2=InputLine();
	v1v2=GetCrossProduct(line1.direction,line2.direction);

	plane1.NormalVector[0]=line1.direction[1]*v1v2[2]-line1.direction[2]*v1v2[1];
	plane1.NormalVector[1]=-(line1.direction[0]*v1v2[2]-line1.direction[2]*v1v2[0]);
	plane1.NormalVector[2]=line1.direction[0]*v1v2[1]-line1.direction[1]*v1v2[0];
	plane1.d=-(line1.point[0]*plane1.NormalVector[0]+line1.point[1]*plane1.NormalVector[1]+line1.point[2]*plane1.NormalVector[2]);

	plane2.NormalVector[0]=line2.direction[1]*v1v2[2]-line2.direction[2]*v1v2[1];
	plane2.NormalVector[1]=-(line2.direction[0]*v1v2[2]-line2.direction[2]*v1v2[0]);
	plane2.NormalVector[2]=line2.direction[0]*v1v2[1]-line2.direction[1]*v1v2[0];
	plane2.d=-(line2.point[0]*plane2.NormalVector[0]+line2.point[1]*plane2.NormalVector[1]+line2.point[2]*plane2.NormalVector[2]);

	GetLineFunc(plane1,plane2);
	return;
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
					tmp=loc[i];
					loc[i]=loc[j];
					loc[j]=tmp;
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
double*GetNonHomoSolution(double**a,double*b,int m,int n){
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
			return NULL;
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
	return real_solution;
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

//����������
double GetVectorLen(double*Vector,int n){
	return sqrt(multiply(Vector,Vector,n));
}

//�����������ļн�����
double GetAngle(double*Vector1,double*Vector2,int n){
	double len1,len2,multi;
	multi=multiply(Vector1,Vector2,n);
	len1=GetVectorLen(Vector1,n);
	len2=GetVectorLen(Vector2,n);
	if((!JudgeZero(len1))&&(!JudgeZero(len2)))return multi/(len1*len2);
	else return -1.0;
}

//�����ǵ�����
void  GetPlaneAngle(Plane plane1,Plane plane2){
	printf("�����cos<>=%.2f\n",GetAngle(plane1.NormalVector,plane2.NormalVector,3));
}

//������ǵ�����
void GetP_LAngle(Plane plane,Line line){
	printf("�����sin<>=%.2f\n",GetAngle(plane.NormalVector,line.direction,3));
}

//����
void input(double***a,int*dim){
	int i,j;
	printf("������ռ�ά����");
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

//�������֮��Ĺ��ɾ���
double**GetTransition(double**a,double**b,int n){
	int i,j;double**c,**tmp;
	a=CreatMatrix(n,n);
	b=CreatMatrix(n,n);
	printf("�������Ե�һ���������������:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf_s("%lf",&a[i][j]);
		}
	}
	printf("�������Եڶ����������������:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf_s("%lf",&b[i][j]);
		}
	}
	c=GetNi(a,n);
	matrix_multi(&tmp,c,b,n,n,n);
	printf("�ӵ�һ������ڶ�����Ĺ��ɾ���Ϊ:\n");
	OutputMatrix(tmp,n,n);
	return tmp;
}

//�����n����
double**GetMi(){
	int i,n,mi;
	double**a,**tmp;
	printf("���������Ľ���:\n");
	scanf_s("%d",&n);
	a=InputMatrix(n,n);
	printf("�������ݴ�:");
	scanf_s("%d",&mi);
	for(i=0;i<mi-1;i++){
		matrix_multi(&tmp,a,a,n,n,n);
		a=tmp;
	}
	OutputMatrix(a,n,n);
	return a;
}

//���Ա任�ڲ�ͬ���µľ���
double**GetTransMatrix(){
	double**result,**c,**tmp,**tmp1,**a,**b,**tmp2=NULL,**yuan;int n;
	printf("������������:\n");
	scanf_s("%d",&n);
	printf("���������Ա任�ڵ�һ����µľ���:\n");
	a=b=NULL;
	tmp2=CreatMatrix(n,n);
	yuan=InputMatrix(n,n);
	c=GetTransition(a,b,n);
	CopyMatrix(tmp2,c,n,n);
	tmp=GetNi(tmp2,n);
	matrix_multi(&tmp1,tmp,yuan,n,n,n);
	matrix_multi(&result,tmp1,c,n,n,n);
	printf("���Ա任�ڵڶ�����µľ���Ϊ:\n");
	OutputMatrix(result,n,n);
	return result;
}

//���Ա任�ľ������ռ�ͺ˿ռ�Ļ���ά��
void GetDimAndBasic(){
	double**a,**tmp;int i,j,n,r=0,*loc;
	printf("���������Ľ���:\n");
	scanf_s("%d",&n);
	a=InputMatrix(n,n);
	tmp=CreatMatrix(n,n);
	CopyMatrix(tmp,a,n,n);
	tmp=Gauss(tmp,n,n);
	loc=AdjustMatrix(tmp,n,n);
	for(i=0;i<n;i++){
		if(!JudgeZero(tmp[i][i]))r++;
	}
	printf("��ռ��ά��:%d\n",r);
	printf("��Ӧ�������:\n");
	for(i=0;i<r;i++){
		printf("[%d]: ",loc[i]);
		for(j=0;j<n;j++){
			printf("%.3f ",a[j][i]);
		}
		printf("\n\n");
	}
	printf("�˿ռ��ά��:%d\n",n-r);
	printf("�˿ռ�Ļ�Ϊ:\n");
	GetSolution(a,n,n);
	return ;
}

//��������ĺ�ͬ�Խǻ�,�Ⱥ���������ָ��
double**CongruenceMatrix(double**a,int n){
	int i,j,flag,k,count1=0,count2=0,r=0;double**tmp,**I,coe;
	tmp=CreatMatrix(n,n);
	I=CreatMatrix(n,n);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j)I[i][j]=1.0;
			else I[i][j]=0.0;
		}
	}
	CopyMatrix(tmp,a,n,n);
	for(j=0;j<n;j++){
		if(JudgeZero(tmp[j][j])){
			flag=0;
			for(i=j+1;i<n;i++){
				if(!JudgeZero(tmp[i][j])){
					SwapVector(&tmp[i],&tmp[j],n);
					SwapCol(tmp,i,j,n);
					SwapVector(&I[i],&I[j],n);
					SwapCol(tmp,i,j,n);
					flag=1;break;
				}
				if(flag==0)continue;
			}
		}
		for(i=j+1;i<n;i++){
			if(!JudgeZero(tmp[j][j])){
				coe=tmp[i][j]/tmp[j][j];
				for(k=j;k<n;k++){
					tmp[i][k]-=coe*tmp[j][k];
					I[i][k]-=coe*I[j][k];
				}
				for(k=j;k<n;k++){
					tmp[k][i]-=coe*tmp[k][j];
					I[k][i]-=coe*I[k][j];
				}
			}
		}
	}
	for(i=0;i<n;i++){
		if(!JudgeZero(tmp[i][i])){
			r++;
			if(tmp[i][i]>0.0)count1++;
			else if(tmp[i][i]<0.0)count2++;
		}
	}
	printf("��ͬ����Ϊ:\n");
	OutputMatrix(tmp,n,n);
	printf("���������滻:\n");
	OutputMatrix(I,n,n);
	printf("�������:%d\n",r);
	printf("������ָ��:%d\n",count1);
	printf("������ָ��:%d\n",count2);
	return a;
}

//���ӿռ佻��͵Ļ���ά��
void GetSubSpace(){
	double**a,**b,**c,**tmp;int m1,m2,n,i,j,r=0,r1,r2,*loc;
	printf("������ȫ�ռ�ά��������Ԫ�ظ�����:");
	scanf_s("%d",&n);
	printf("�������һ���ӿռ��������������:\n");
	scanf_s("%d",&m1);
	printf("�������һ���ӿռ����������:\n");
	a=InputMatrix(n,m1);
	printf("������ڶ����ӿռ��������������:\n");
	scanf_s("%d",&m2);
	printf("������ڶ����ӿռ����������:\n");
	b=InputMatrix(n,m2);
	c=CreatMatrix(n,m1+m2);
	for(i=0;i<n;i++){
		for(j=0;j<m1+m2;j++){
			if(j<m1){
				c[i][j]=a[i][j];
			}else if(j>=m1){
				c[i][j]=b[i][j-m1];
			}
		}
	}
	r1=GetRank(a,n,m1);
	r2=GetRank(b,n,m2);
	printf("\n���������ĺϲ������� :\n");
	OutputMatrix(c,n,m1+m2);
	tmp=CreatMatrix(n,m1+m2);
	CopyMatrix(tmp,c,n,m1+m2);
	c=Gauss(c,n,m1+m2);
	loc=AdjustMatrix(c,n,m1+m2);
	for(i=0;i<n;i++){
		if(!JudgeZero(c[i][i]))r++;
	}
	printf("�ӿռ�� W1+W2 ��ά��:%d\n",r);
	printf("�ӿռ�� W1+W2 �Ļ�Ϊ:\n");
	for(i=0;i<r;i++){
		if(loc[i]<m1)printf("��[%d] ",loc[i]);
		else printf("��[%d] ",loc[i]-m1);
	}
	printf("\n�ӿռ佻 W1��W2 ��ά��:%d\n",r1+r2-r);//ά����ʽ
	printf("\n�ӿռ佻 W1��W2 �Ļ�����:\n");
	GetSolution(tmp,n,m1+m2);
	printf("������η��̽���ǰ%d��ϵ������Ӧ��������ɵĺ�����ΪW1��W2 �Ļ�����\n",m1);
	return ;
}

//�жϾ����Ƿ�����(δ���)
int isPositiveDefine(double**a,int n){
	int flag;


	return flag;
}

//�жϾ����Ƿ������(δ���)
int isPositiveSemidefine(double**a,int n){
	int flag;


	return flag;
}

//��������
void opreate(){
	char ch;
	double**a=NULL,**gauss,*b,**ni,**tmp=NULL;
	int m,n,r,t;
	double**vector,**orth,**up_tri,*value;int dim;
	printf("��������в�����Ҫ����ĸ����:\nA/��˹��Ԫ B/�������� C/����η��̵Ľ� D/���������Է��̵Ľ� E/QR�ֽ� F/���������ֵ G/������ʽ��ֵ H/��������\nI/�������� J/����˷� K/�����n���� L/�����֮��Ĺ��ɾ��� \nM/���Ա任�ڲ�ͬ���µľ��� N/��ռ�ͺ˿ռ��ά�� O/�ӿռ佻��͵Ļ���ά�� P/�����;���ĺ�ͬ�Խǻ� Q/�˳�\n");
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
			/*output(orth,up_tri,dim);*/
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
		case 'K':
			GetMi();
			break;;
		case 'L':
			printf("������ռ�ά��:\n");
			scanf_s("%d",&n);
			GetTransition(a,tmp,n);
			break;
		case 'M':
			GetTransMatrix();
			break;
		case 'N':
			GetDimAndBasic();
			break;
		case 'O':
			GetSubSpace();
			break;
		case 'P':
			printf("������������:\n");
			scanf_s("%d",&n);
			a=InputMatrix(n,n);
			CongruenceMatrix(a,n);
			break;
		case 'Q':
			printf("�������!\n");
			break;
		default:
			printf("δ��ʶ�����ĸ������������!\n");
			break;
		}
		getchar();
	}
	return;
}

//�����¿ռ�������εĺ���
void operate_Three(){
	char ch;Plane plane1,plane2;Line line1;double*p1,*p2,*p;
	p1=(double*)malloc(3*sizeof(double));
	p2=(double*)malloc(3*sizeof(double));
	printf("�����������Ӧ����ĸ����:\n");
	printf(" A/���潻�� B/���� C/����� D/��������ϵ�������˻� E/������ F/��ϻ� G/���߾� H/����ֱ�߾��� I/��֪������ƽ�淽��\n J/��ƽ�潻�߷��� K/������ֱ�߷��� L/��ֱ�߹����� M/��������� N/��������� Q/�˳�\n");
	while((ch=getchar())!='Q'){
	switch(ch){
	case 'A':
		plane1=InputPlane();
		line1=InputLine();
		GetInterPiont(line1,plane1);
		break;
	case 'B':
		GetPointsDis();
		break;
	case 'C':
		GetP_PDis();
		break;
	case 'D':
		Get_Fangshe_Multi();
		break;
	case 'E':
		p1=GetSanVector();
		p2=GetSanVector();
		p=GetCrossProduct(p1,p2);
		printf("���aXb������Ϊ:\n");
		OutputSanVector(p);
		break;
	case 'F':
		p1=GetSanVector();
		p2=GetSanVector();
		p=GetSanVector();
		printf("��ϻ�Ϊ:%.3f\n",GetMixProduct(p1,p2,p));
		break;
	case 'G':
		GetP_LDis();
		break;
	case 'H':
		GetL_LDis();
		break;
	case 'I':
		GetPlaneFunc();
		break;
	case 'J':
		plane1=InputPlane();
		plane2=InputPlane();
		GetLineFunc(plane1,plane2);
		break;
	case 'K':
		GetLineFuncP();
		break;
	case 'L':
		GetComLine();
		break;
	case 'M':
		plane1=InputPlane();
		plane2=InputPlane();
		GetPlaneAngle(plane1,plane2);
		break;
	case 'N':
		line1=InputLine();
		plane1=InputPlane();
		GetP_LAngle(plane1,line1);
		break;
	case 'Q':
		printf("��ģ�����!\n");
		break;
	default: 
		printf("δ��ʶ�����ĸ������������!\n");
		break;
	}
	getchar();
	}
	return ;
}

//����������
int main(){
	system("color F0");
	/*operate_Three();*/
	opreate();
	return 0;
}
