#include<stdio.h>
#include<malloc.h>

void input(int*m,int*n,int***a){
	int i,j; 
	printf("������m��n��ֵ:");
	scanf_s("%d%d",m,n);
	*a=(int**)malloc(*m*sizeof(int*));
	for(i=0;i<*m;i++){
		*((*a)+i)=(int*)malloc(*n*sizeof(int));
	}
	printf("������������Ԫ��ֵ��\n");
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
	printf("�����ľ���:\n");
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<n;j++){
			printf("%4d",a[i][j]);
		}
	}
}
//�������ڵݼ�ð������
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
//�Ծ����к�����
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
				//������Ԫ�����ν���
				/*for(k=0;k<n;k++){
					t=(*a)[j][k];(*a)[j][k]=(*a)[j+1][k];(*a)[j+1][k]=t;
				}*/
				//ʹ����ָ����н���
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
		printf("�Ƿ��������@��������\n");
	}
	return 0;
}
