#include<stdio.h>
int main(){
	long a,b,i,j,k,N=10005,e[10005],c[10005];
	for(*c=1;++i,k<N;c[k]?0:++k)
		for(b=0,j=k-1;++j<N;b=a%i)e[j]+=(c[j]=(a=b*10+c[j])/i);
	for(;--j;e[j]%=10)e[j-1]+=e[j]/10;
	for(printf("2.");++j<N-5;)printf("%ld",e[j]);
	return 0;
}
