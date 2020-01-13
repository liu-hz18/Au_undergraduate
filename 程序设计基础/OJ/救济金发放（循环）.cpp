//救济金发放，循环
#include <stdio.h>
int go(int p, int q, int t,int n,int a[]){
	while(t--){
		do{
			p=(p+q+n-1)%n+1;
		}
		while(a[p] == 0);
	}
	return p;
}
int main()
{
	int n,k,m,p1,p2,left,a[25];
	while(scanf("%d %d %d",&n,&k,&m) == 3 && n){
		left = n, p1 = n, p2 = 1; 
		for(int i = 1; i <= n; i++) a[i] = i;
		while(left){
			p1=go(p1,1,k,n,a);
			p2=go(p2,-1,m,n,a);
			printf("%d",p1);
			left--;
			a[p1]=0;
			if(p1!=p2){
				printf(" %d", p2);
				left--;
				a[p2] = 0;
			}
			if(left)printf(",");
		}
		printf("\n");	
	}
	return 0;
}