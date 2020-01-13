
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

//欧式空间直线参数
struct Line{
	double point[3];
	double direction[3];
};

//欧式空间平面参数
struct Plane{
	double NormalVector[3];//法向量方向
	double d;//常数项
};

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

//交换两个行向量的值
void SwapVector(double**a,double**b,int n){
	int i;double tmp;
	for(i=0;i<n;i++){
		tmp=(*a)[i];
		(*a)[i]=(*b)[i];
		(*b)[i]=tmp;
	}
}

//输入向量
double*GetVector(int*n){
	int i;double*Vector;
	printf("请输入向量维数:\n");
	scanf_s("%d",n);
	Vector=(double*)malloc(*n*sizeof(double));
	for(i=0;i<*n;i++){
		scanf_s("%lf",Vector[i]);
	}
	return Vector;
}

//输入三维向量
double*GetSanVector(){
	int i;double*p;
	p=(double*)malloc(3*sizeof(double));
	printf("请输入三维向量:\n");
	for(i=0;i<3;i++){
		scanf_s("%lf",&p[i]);
	}
	return p;
}

//输出三维向量
void OutputSanVector(double*p){
	int i;
	for(i=0;i<3;i++){
		printf("%.2f ",p[i]);
	}
	putchar(10);
	return ;
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

//输入一个平面的各参数
struct Plane InputPlane(){
	Plane plane;
	printf("请输入平面各参数(一般方程A B C D):\n");
	scanf_s("%lf%lf%lf%lf",&plane.NormalVector[0],&plane.NormalVector[1],&plane.NormalVector[2],&plane.d);
	return plane;
}

//输入一个直线各参数
struct Line InputLine(){
	Line line;
	printf("请输入直线所过定点:\n");
	scanf_s("%lf%lf%lf",&line.point[0],&line.point[1],&line.point[2]);
	printf("请输入直线的方向向量\n");
	scanf_s("%lf%lf%lf",&line.direction[0],&line.direction[1],&line.direction[2]);
	return line;
}

//求线面交点
void GetInterPiont(Line line,Plane plane){
	int i;double p[3];double t,tmp1,tmp2;
	tmp1=multiply(line.point,plane.NormalVector,3);
	tmp2=multiply(line.direction,plane.NormalVector,3);
	if(!JudgeZero(tmp2)){
		t=-(tmp1+plane.d)/tmp2;
		for(i=0;i<3;i++){
			p[i]=line.point[i]+line.direction[i]*t;
		}
		printf("线面交点为:\n");
		for(i=0;i<3;i++){
			printf("%.2f ",p[i]);
		}
		putchar(10);
	}else if((!JudgeZero(tmp1))&&JudgeZero(tmp2)){
		printf("线面平行!\n");
	}else{
		printf("线面重合!\n");
	}
}

//求两点之间距离
void GetPointsDis(){
	double tmp[3];int i;
	double*p1;double*p2;
	p1=(double*)malloc(3*sizeof(double));
	p2=(double*)malloc(3*sizeof(double));
	printf("请输入两点的坐标:\n");
	for(i=0;i<3;i++){
		scanf_s("%lf",&p1[i]);
	}
	for(i=0;i<3;i++){
		scanf_s("%lf",&p2[i]);
	}
	for(i=0;i<3;i++){
		tmp[i]=p1[i]-p2[i];
	}
	printf("两点距离：%.3f\n",sqrt(tmp[0]*tmp[0]+tmp[1]*tmp[1]+tmp[2]*tmp[2]));
	return ;
}

//求点面距
void  GetP_PDis(){
	double tmp1=0.0,tmp2=0.0,result;int i;double p[3];Plane plane;
	printf("请输入点的坐标:\n");
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
	printf("点面距=%.3f\n",(result=abs(tmp1)/sqrt(tmp2)));
	return ;
}

//仿射坐标系下的向量乘积
void Get_Fangshe_Multi(){
	double **e,**A,**x,**y,**tmp1,**tmp2;
	int i,j;
	e=CreatMatrix(3,3);
	A=CreatMatrix(3,3);
	x=CreatMatrix(1,3);
	y=CreatMatrix(3,1);
	printf("请依次输入三个基向量:\n");
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
	
	printf("请输入两个向量:\n");
	for(i=0;i<3;i++)scanf_s("%lf",&x[0][i]);
	for(i=0;i<3;i++)scanf_s("%lf",&y[i][0]);
	printf("这组基下的度量矩阵A为:\n");
	OutputMatrix(A,3,3);
	matrix_multi(&tmp1,x,A,1,3,3);
	matrix_multi(&tmp2,tmp1,y,1,3,1);
	printf("该仿射坐标系下的向量乘积为:%.3f\n",tmp2[0][0]);
	return ;
}

//求叉积
double*GetCrossProduct(double*Vector1,double*Vector2){
	double*result;
	result=(double*)malloc(3*sizeof(double));
	result[0]=Vector1[1]*Vector2[2]-Vector1[2]*Vector2[1];
	result[1]=-(Vector1[0]*Vector2[2]-Vector1[2]*Vector2[0]);
	result[2]=Vector1[0]*Vector2[1]-Vector1[1]*Vector2[0];
	return result;
}

//求混合积
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

//求点线距
void GetP_LDis(){
	double p[3],dis;int i;Line line;
	printf("请输入点坐标:\n");
	for(i=0;i<3;i++){
		scanf_s("%lf",&p[i]);
	}
	line=InputLine();
	for(i=0;i<3;i++){
		p[i]=p[i]-line.point[i];
	}
	dis=GetVectorLen(GetCrossProduct(p,line.direction),3)/GetVectorLen(line.direction,3);
	printf("点线距为:%.3f\n",dis);
	return ;
}

//求异面直线距离
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
		printf("线线距为d=%.3f\n",tmp1/tmp2);
	else if(abs(GetAngle(p,line1.direction,3)-1.0)<1e-6)
		printf("两线重合!\n");
	else printf("两线平行!\n");
	return ;
}

//求过三点的平面一般方程
void GetPlaneFunc(){
	int i,j;double p[3][3],v1[3],v2[3];Plane plane;
	printf("请输入不共线的三点:\n");
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
	printf("直线的一般方程为:\n");
	printf("(%.2f)X+(%.2f)Y+(%.2f)Z+(%.2f)=0\n",plane.NormalVector[0],plane.NormalVector[1],plane.NormalVector[2],plane.d);
	return ;
}

//求两平面的交线方程
void GetLineFunc(Plane plane1,Plane plane2){
	double**A,*v,*p,*b;int i;Line line;
	A=CreatMatrix(2,3);
	b=(double*)malloc(2*sizeof(double));
	if(abs(GetAngle(plane1.NormalVector,plane2.NormalVector,3)-1.0)<1e-6){
		printf("两平面平行或重合！\n");
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
		printf("直线的对称方程为:\n");
		printf("X-(%.2f) Y-(%.2f) Z-(%.2f)\n",p[0],p[1],p[2]);
		printf("--------=---------=------- = 0\n");
		printf("  %.2lf    %.2lf    %.2lf\n",v[0],v[1],v[2]);
	}
	return ;
}

//求过两点的直线方程
void GetLineFuncP(){
	int i;double p1[3],p2[3];
	printf("请输入直线经过的两点:\n");
	for(i=0;i<3;i++){
		scanf_s("%lf",&p1[i]);
	}
	for(i=0;i<3;i++){
		scanf_s("%lf",&p2[i]);
	}
	printf("直线的对称方程为:\n");
	printf("X-%.2f Y-%.2f Z-%.2f\n",p1[0],p1[1],p1[2]);
	printf("------=------=------ = 0\n");
	printf(" %.2lf  %.2lf  %.2lf\n",p1[0]-p2[0],p1[1]-p2[1],p1[2]-p2[2]);
	return ;
}

//求两直线公垂线
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
double*GetNonHomoSolution(double**a,double*b,int m,int n){
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
		printf("非齐次线性方程组的一个特解为:\n");
		OutputSolution(real_solution,n);
	}else if(r==n){
		GetFullSolution(Ab,solution,n);
		printf("该方程组有唯一解:\n");
		OutputSolution(solution,n);
	}
	return real_solution;
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

//求向量长度
double GetVectorLen(double*Vector,int n){
	return sqrt(multiply(Vector,Vector,n));
}

//求两个向量的夹角余弦
double GetAngle(double*Vector1,double*Vector2,int n){
	double len1,len2,multi;
	multi=multiply(Vector1,Vector2,n);
	len1=GetVectorLen(Vector1,n);
	len2=GetVectorLen(Vector2,n);
	if((!JudgeZero(len1))&&(!JudgeZero(len2)))return multi/(len1*len2);
	else return -1.0;
}

//求二面角的余弦
void  GetPlaneAngle(Plane plane1,Plane plane2){
	printf("二面角cos<>=%.2f\n",GetAngle(plane1.NormalVector,plane2.NormalVector,3));
}

//求线面角的正弦
void GetP_LAngle(Plane plane,Line line){
	printf("线面角sin<>=%.2f\n",GetAngle(plane.NormalVector,line.direction,3));
}

//输入
void input(double***a,int*dim){
	int i,j;
	printf("请输入空间维数：");
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

//求两组基之间的过渡矩阵
double**GetTransition(double**a,double**b,int n){
	int i,j;double**c,**tmp;
	a=CreatMatrix(n,n);
	b=CreatMatrix(n,n);
	printf("请输入以第一组基，列向量排列:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf_s("%lf",&a[i][j]);
		}
	}
	printf("请输入以第二组基，列向量排列:\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf_s("%lf",&b[i][j]);
		}
	}
	c=GetNi(a,n);
	matrix_multi(&tmp,c,b,n,n,n);
	printf("从第一组基到第二组基的过渡矩阵为:\n");
	OutputMatrix(tmp,n,n);
	return tmp;
}

//方阵的n次幂
double**GetMi(){
	int i,n,mi;
	double**a,**tmp;
	printf("请输入矩阵的阶数:\n");
	scanf_s("%d",&n);
	a=InputMatrix(n,n);
	printf("请输入幂次:");
	scanf_s("%d",&mi);
	for(i=0;i<mi-1;i++){
		matrix_multi(&tmp,a,a,n,n,n);
		a=tmp;
	}
	OutputMatrix(a,n,n);
	return a;
}

//线性变换在不同基下的矩阵
double**GetTransMatrix(){
	double**result,**c,**tmp,**tmp1,**a,**b,**tmp2=NULL,**yuan;int n;
	printf("请输入矩阵阶数:\n");
	scanf_s("%d",&n);
	printf("请输入线性变换在第一组基下的矩阵:\n");
	a=b=NULL;
	tmp2=CreatMatrix(n,n);
	yuan=InputMatrix(n,n);
	c=GetTransition(a,b,n);
	CopyMatrix(tmp2,c,n,n);
	tmp=GetNi(tmp2,n);
	matrix_multi(&tmp1,tmp,yuan,n,n,n);
	matrix_multi(&result,tmp1,c,n,n,n);
	printf("线性变换在第二组基下的矩阵为:\n");
	OutputMatrix(result,n,n);
	return result;
}

//线性变换的矩阵的像空间和核空间的基与维数
void GetDimAndBasic(){
	double**a,**tmp;int i,j,n,r=0,*loc;
	printf("请输入矩阵的阶数:\n");
	scanf_s("%d",&n);
	a=InputMatrix(n,n);
	tmp=CreatMatrix(n,n);
	CopyMatrix(tmp,a,n,n);
	tmp=Gauss(tmp,n,n);
	loc=AdjustMatrix(tmp,n,n);
	for(i=0;i<n;i++){
		if(!JudgeZero(tmp[i][i]))r++;
	}
	printf("像空间的维数:%d\n",r);
	printf("对应向量编号:\n");
	for(i=0;i<r;i++){
		printf("[%d]: ",loc[i]);
		for(j=0;j<n;j++){
			printf("%.3f ",a[j][i]);
		}
		printf("\n\n");
	}
	printf("核空间的维数:%d\n",n-r);
	printf("核空间的基为:\n");
	GetSolution(a,n,n);
	return ;
}

//正定矩阵的合同对角化,秩和正负惯性指数
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
	printf("合同矩阵为:\n");
	OutputMatrix(tmp,n,n);
	printf("可逆线性替换:\n");
	OutputMatrix(I,n,n);
	printf("矩阵的秩:%d\n",r);
	printf("正惯性指数:%d\n",count1);
	printf("负惯性指数:%d\n",count2);
	return a;
}

//求子空间交与和的基和维数
void GetSubSpace(){
	double**a,**b,**c,**tmp;int m1,m2,n,i,j,r=0,r1,r2,*loc;
	printf("请输入全空间维数（向量元素个数）:");
	scanf_s("%d",&n);
	printf("请输入第一个子空间的生成向量个数:\n");
	scanf_s("%d",&m1);
	printf("请输入第一个子空间的生成向量:\n");
	a=InputMatrix(n,m1);
	printf("请输入第二个子空间的生成向量个数:\n");
	scanf_s("%d",&m2);
	printf("请输入第二个子空间的生成向量:\n");
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
	printf("\n两组向量的合并向量组 :\n");
	OutputMatrix(c,n,m1+m2);
	tmp=CreatMatrix(n,m1+m2);
	CopyMatrix(tmp,c,n,m1+m2);
	c=Gauss(c,n,m1+m2);
	loc=AdjustMatrix(c,n,m1+m2);
	for(i=0;i<n;i++){
		if(!JudgeZero(c[i][i]))r++;
	}
	printf("子空间和 W1+W2 的维数:%d\n",r);
	printf("子空间和 W1+W2 的基为:\n");
	for(i=0;i<r;i++){
		if(loc[i]<m1)printf("α[%d] ",loc[i]);
		else printf("β[%d] ",loc[i]-m1);
	}
	printf("\n子空间交 W1∩W2 的维数:%d\n",r1+r2-r);//维数公式
	printf("\n子空间交 W1∩W2 的基向量:\n");
	GetSolution(tmp,n,m1+m2);
	printf("上述齐次方程解中前%d个系数乘相应向量所组成的和向量为W1∩W2 的基向量\n",m1);
	return ;
}

//判断矩阵是否正定(未完成)
int isPositiveDefine(double**a,int n){
	int flag;


	return flag;
}

//判断矩阵是否半正定(未完成)
int isPositiveSemidefine(double**a,int n){
	int flag;


	return flag;
}

//操作函数
void opreate(){
	char ch;
	double**a=NULL,**gauss,*b,**ni,**tmp=NULL;
	int m,n,r,t;
	double**vector,**orth,**up_tri,*value;int dim;
	printf("请输入进行操作需要的字母代号:\nA/高斯消元 B/求矩阵的秩 C/求齐次方程的解 D/求非齐次线性方程的解 E/QR分解 F/求矩阵特征值 G/求行列式的值 H/矩阵求逆\nI/求伴随矩阵 J/矩阵乘法 K/求方阵的n次幂 L/两组基之间的过渡矩阵 \nM/线性变换在不同基下的矩阵 N/像空间和核空间的维数 O/子空间交与和的基与维数 P/二次型矩阵的合同对角化 Q/退出\n");
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
			/*output(orth,up_tri,dim);*/
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
		case 'K':
			GetMi();
			break;;
		case 'L':
			printf("请输入空间维数:\n");
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
			printf("请输入矩阵阶数:\n");
			scanf_s("%d",&n);
			a=InputMatrix(n,n);
			CongruenceMatrix(a,n);
			break;
		case 'Q':
			printf("程序结束!\n");
			break;
		default:
			printf("未能识别的字母，请重新输入!\n");
			break;
		}
		getchar();
	}
	return;
}

//第三章空间解析几何的函数
void operate_Three(){
	char ch;Plane plane1,plane2;Line line1;double*p1,*p2,*p;
	p1=(double*)malloc(3*sizeof(double));
	p2=(double*)malloc(3*sizeof(double));
	printf("请输入操作对应的字母代号:\n");
	printf(" A/线面交点 B/点点距 C/点面距 D/仿射坐标系下向量乘积 E/向量积 F/混合积 G/点线距 H/异面直线距离 I/已知三点求平面方程\n J/两平面交线方程 K/过两点直线方程 L/两直线公垂线 M/二面角余弦 N/线面角正弦 Q/退出\n");
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
		printf("叉积aXb的向量为:\n");
		OutputSanVector(p);
		break;
	case 'F':
		p1=GetSanVector();
		p2=GetSanVector();
		p=GetSanVector();
		printf("混合积为:%.3f\n",GetMixProduct(p1,p2,p));
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
		printf("该模块结束!\n");
		break;
	default: 
		printf("未能识别的字母，请重新输入!\n");
		break;
	}
	getchar();
	}
	return ;
}

//主函数调用
int main(){
	system("color F0");
	/*operate_Three();*/
	opreate();
	return 0;
}
