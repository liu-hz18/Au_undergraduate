#include<stdio.h>
#include<malloc.h>

//��ά����Ĵ���
void creat(int***a,int*m,int*n){
	int i,j;
	printf("����������Ĵ�Сm n:");
	scanf_s("%d%d",m,n);
	*a=(int**)malloc(*m*sizeof(int*));
	for(i=0;i<*m;i++){
		*((*a)+i)=(int*)malloc(*n*sizeof(int));
	}
	printf("�����������Ԫ�ص�ֵ:\n");
	for(i=0;i<*m;i++){
		for(j=0;j<*n;j++){
			scanf_s("%d",&(*a)[i][j]);
		}
	}
	getchar();
}

//��������Ԫ��
void print(int**a,int m,int n){
	int i,j;
	printf("����aΪ��\n");
	for(i=0;i<m;i++,putchar(10)){
		for(j=0;j<n;j++){
			printf("%5d ",a[i][j]);
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

//���� ���а��� ��������,ð��
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

//�ͷŶ�ά����
void FreeMatrix(int***a,int m){
	int i;
	for(i=0;i<m;i++){
		free((*a)[i]);
	}
	free(*a);
}

//����������
int main(){
	int**a,m,n;char ch;
	while((ch=getchar())!='@'){
		creat(&a,&m,&n);
		print(a,m,n);
		
		//���ڵݼ�����
		Rowsort(m,n,&a);
		printf("���ڵݼ�����:\n");
		print(a,m,n);

		//���к͵�������
		MatrixRowSort(m,n,&a);
		printf("���к͵�������:\n");
		print(a,m,n);

		//���а��еݼ�����
		MatrixSort(m,n,&a);
		printf("���а��е�������:\n");
		print(a,m,n);

		FreeMatrix(&a,m);
		
		printf("�Ƿ����?��@��������\n");
	};
	return 0;
}
