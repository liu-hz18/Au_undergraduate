//�����¶������㣬��̬�����ڴ沢�ͷš�
#include<stdio.h>
#include<malloc.h>

//���ĵݹ麯��
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
	scanf_s("%d%d%d",m,n,t);//����m,n,t�Ѿ������˶�Ӧ�����ĵ�ַ���������ﲻ��Ҫ���н��ַ����Ȼ���Ƕ�ָ�븳ֵ
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
//����a�ļ�����int***������Ϊ�˶�Ӧ��Ӧ����(*a)[i][j]�����ܶ�Ӧ�Ӻ����е�a[i][j]�������a������ָ�룬ָ��������a�ĵ�ַ
//���ʱ��֤һһ��Ӧ�ͺ�
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
	//�������ĵ�ַ����Ȼmain�ռ��������ǵ�ַ���ݣ����Ǵ˴���Ҫ���Ӻ����ж�̬�����ڴ棬������Ȼ��Ҫ����ַ
	multily(0,0,0,0,a,b,c,m,n,t);
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<t;j++){
			printf("%4d",c[i][j]);
		}
	}
	myfree(&a,m);myfree(&b,n);myfree(&c,m);
	return 0;
}
