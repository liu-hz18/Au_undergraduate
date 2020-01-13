#include<stdio.h>
#include<malloc.h>

void input(int***a,int***b,int*na,int*nb){
	int i,j;
	*a=(int**)malloc(2*sizeof(int*));
	for(i=0;i<2;i++){
		*((*a)+i)=(int*)malloc(10000*sizeof(int));
	}
	*b=(int**)malloc(2*sizeof(int*));
	for(i=0;i<2;i++){
		*((*b)+i)=(int*)malloc(10000*sizeof(int));
	}
	printf("please input elements of matrix a:\n");
	for(j=0;;j++){
		for(i=0;i<2;i++){
			scanf_s("%d",&(*a)[i][j]);
		}
		if((*a)[0][j]==0)break;
	}
	*na=j;
	printf("please input elements of matrix b:\n");
	for(j=0;;j++){
		for(i=0;i<2;i++){
			scanf_s("%d",&(*b)[i][j]);
		}
		if((*b)[0][j]==0)break;
	}
	*nb=j;
}

void sort(int***a,int n){
	int i,j,tmp;
	for(i=n-1;i>=0;i--){
		for(j=0;j<i;j++){
			if((*a)[0][j]>(*a)[0][j+1]){
				tmp=(*a)[0][j];(*a)[0][j]=(*a)[0][j+1];(*a)[0][j+1]=tmp;
				tmp=(*a)[1][j];(*a)[1][j]=(*a)[1][j+1];(*a)[1][j+1]=tmp;
			}
		}
	}
}
void merge(int**a,int na,int**b,int nb,int***c,int*nc){
	int i,j,k=0;
	*c=(int**)malloc(2*sizeof(int*));
	for(i=0;i<2;i++){
		*((*c)+i)=(int*)malloc((na+nb+5)*sizeof(int));
	}
	for(i=0,j=0;i<na||j<nb;){
		if(i<na&&j<nb){
			if(a[0][i]<b[0][j]){
				(*c)[0][k]=a[0][i];
				(*c)[1][k++]=a[1][i];
				i++;
			}else if(a[0][i]>b[0][j]){
				(*c)[0][k]=b[0][j];
				(*c)[1][k++]=b[1][j];
				j++;
			}else if(a[0][i]==b[0][j]){
				(*c)[0][k]=a[0][i];
				(*c)[1][k++]=(a[1][i]+b[1][i])/2;
				i++;j++;
			}
		}else{
			if(i==na&&j<nb){(*c)[0][k]=b[0][j];(*c)[1][k++]=b[1][j++];}
			else if(j==nb&&i<na){(*c)[0][k]=a[0][i];(*c)[1][k++]=b[1][i++];}
		}
		if(i==na&&j==nb)break;
	}
	*nc=k;
}
void peak(int**c,int nc,int**loc,int*count){
	int i,max=c[1][0];
	*count=0;
	*loc=(int*)malloc(nc*sizeof(int));
	for(i=0;i<nc;i++){
		if(max<c[1][i])max=c[1][i];
	}
	for(i=0;i<nc;i++){
		if(max==c[1][i])(*loc)[(*count)++]=i;
	}
}
void print(int**c,int nc,int *loc,int count){
	int i,j;
	printf("合并运算之后的数组:\n");
	for(i=0;i<2;i++,putchar(10)){
		for(j=0;j<nc;j++){
			printf("%4d",c[i][j]);
		}
	}
	printf("数组C的峰值有%d个，分别为:\n",count);
	for(i=0;i<count;i++){
		printf("(%d,%d) ",c[0][loc[i]],c[1][loc[i]]);
	}
}
void myfree(int***a){
	int i;
	for(i=0;i<2;i++)free(*((*a)+i));
	free(*a);
}
int main(){
	int **a,na,**b,nb,**c,nc,*loc,count;
	input(&a,&b,&na,&nb);
	sort(&a,na);sort(&b,nb);
	merge(a,na,b,nb,&c,&nc);
	peak(c,nc,&loc,&count);
	print(c,nc,loc,count);
	myfree(&a);myfree(&b);myfree(&c);free(loc);
	return 0;
}
