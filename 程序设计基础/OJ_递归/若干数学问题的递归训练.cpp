//¥����n(100 > n > 0)��̨��,��¥ʱ����һ����1��,Ҳ����һ����2��,Ҳ����һ����3�ף�
//��̼��㹲�ж����ֲ�ͬ���߷���
#include<stdio.h>
#include<math.h>
/*int run(int n){
	if(n==1)return 1;else if(n==2)return 2;else if(n==3)return 4;
	else return run(n-1)+run(n-2)+run(n-3);
}
int main(){
	int n;
	printf("please input n:\n");scanf_s("%d",&n);
	printf("%d\n",run(n));
	return 0;
}*/

//��������
/*void zuhe(int n,int m,int begin,int count){
	int i;
	if(count==m)putchar(10);
	else{
		for(i=begin;i-count<=n-m+1;i++){
			if(i!=begin)
				for(int j=0;j<count;j++)printf("   ");
			printf("%d  ",i);
			zuhe(n,m,i+1,count+1);
		}
	}
}
int main()
{
	int m,n;
	scanf_s("%d",&n);scanf_s("%d",&m);
	zuhe(n,m,1,0);
}*/
//���ֵ���Ҫ���Ǽ򵥵ģ���Ϊ�����ǵ�һλ��ʱ��ֻ��Ҫ��ȫ�ո�Ȼ��Ϳ��Խ�����һ��ݹ�
//�������ÿһ�ж�����������������ô����Ҫ��¼��һ��ݹ������ϼ���ݹ���������
//����˵�������ȵݹ���������������ݣ�Ȼ���ڴﵽ�ݹ�߽��ʱ��һ���������
void  swap(int*a,int*b){int tmp=*a;*a=*b;*b=tmp;}
void pailie(int a[],int sum,int count,int b[])
{
	int i;
	if(count<sum){
		for(i=count;i<sum;i++){
			b[count]=a[i];
			//ͬ��Ϊ���������ÿһ�����еĽ�����Ƚ����н���������飬���һ�����
			swap(&a[i],&a[count]);
			pailie(a,sum,count+1,b);
			swap(&a[i],&a[count]);
			//ÿ�ξ��Ե�һ�ε�����˳��Ϊ��׼���н��������Խ�����֮��Ҫ�ٻ���ȥ
		}
	}else if(count==sum){
		for(i=0;i<sum;i++)printf("%d  ",b[i]);
		putchar(10);
	}
}
//�ڼ����������Ľ������ʱ�����÷ֲ��˷����ԶԵݹ������ô��������жϣ�ѭ������*�ݹ������,
//���ԽϺõ��ж�����ݹ�����Ƿ���ȷ��
void zuhe(int n,int m,int a[],int begin,int count){
	int i,b[100];
	if(count<m){
		for(i=begin;i-count<=n-m+1;i++){
			a[count]=i;
			zuhe(n,m,a,i+1,count+1);
		}
	}else if(count==m){
		/*for(i=0;i<m;i++)printf("%d  ",a[i]);*///�˴�������������
		pailie(a,m,0,b);//�˴������������
		/*putchar(10);*/
	}
}
int main()
{
	int n,m,a[100];
	scanf_s("%d",&n);scanf_s("%d",&m);
	zuhe(n,m,a,1,0);
	return 0;
}
//��װ�ŷ�����
/* ��A��B��C������ʾд�ţ�λ�������ֵ��ŷ⣬a��b��c������ʾ�����Ӧ��д�õ���ֽ���Ѵ�װ������Ϊ����D(n)������ѣ��װ�������ˣ���������������һ�д�װ�������ࣺ
(1)bװ������ʱÿ�ִ�װ�����ಿ�ֶ���A��B��a��b�޹أ�Ӧ��D(n��2)�ִ�װ������������
(2)��װ��A��B֮���һ���ŷ⣬��ʱ��װ�Ź���ʵ���ǰѣ���a֮��ģ�n��1����ֽ�⡢�㡭��װ�루��B����ģ�n��1���ŷ�A��C��������Ȼ��ʱװ��ķ�����D(n��1)�֡�
��֮�ڣ�װ��B�Ĵ���֮�£����д�װ��D(n��2)��D(n��1)�֡�
aװ��C��װ��D������n��2�ִ���֮�£�ͬ������D(n��1)��D(n��2)�ִ�װ�������D(n)��(n��1)[D(n��1)��D(n��2)]*/
/*int xinfeng(int n){
	if(n==1)return 0;
	else if(n==2)return 1;
	else return (n-1)*(xinfeng(n-1)+xinfeng(n-2));
}
int main()
{
	int n;
	scanf_s("%d",&n);
	printf("%d\n",xinfeng(n));
	return 0;
}*/
//����һ������n��������������ֵĿ�������������
//���統n=4ʱ������5�����֣�{4}��{3,1}��{2,2}��{2,1,1}��{1,1,1,1}��
//ע�⣺4=1+3��4=3+1����Ϊ��ͬһ�����֡�
/*����n��m�Ĺ�ϵ���������漸�������
��1����n=1ʱ������m��ֵΪ���٣�m>0����ֻ��һ�ֻ��֣���{1}��
��2����m=1ʱ������n��ֵΪ���٣�n>0����ֻ��һ�ֻ��֣���{1,1,....1,1,1}��
��3����n=mʱ�����ݻ������Ƿ����n�����Է�Ϊ���������
        ��a�������а���n�������ֻ��һ������{n}��
        ��b�������в�����n���������ʱ��������������Ҳһ����nС����n�����У�n-1�����֣�
        ��ˣ�f(n,n) = 1 + f(n, n - 1)��
��4����n<mʱ�����ڻ����в����ܳ��ָ�������˾��൱��f(n,n)��< span="">
��5����n>mʱ�����ݻ������Ƿ����m�����Է�Ϊ���������
        ��a�������а���m���������{m,{x1,x2,x3,...,xi}}������{x1,x2,x3,...,xi}�ĺ�Ϊn-m�������ٴγ���m������ǣ�n-m����m���֣�������ֻ��ָ���Ϊf(n-m, m)��
        ��b�������в�����m��������򻮷�������ֵ����mС����n�ģ�m-1�����֣�����Ϊf(n, m - 1)��
        ��ˣ�f(n,m) = f(n - m,m) + f(n, m - 1)��*/
/*int huafen(int n,int m){
	if(n==1||m==1)return 1;
	else if(n==m)return 1+huafen(n,n-1);
	else if(n<m)return huafen(n,n);
	else if(n>m)return huafen(n,m-1)+huafen(n-m,m);
}
int main()
{
	int n;
	scanf_s("%d",&n);
	printf("%d\n",huafen(n,n));//�Ľ�Ϊ������һ��ֻ��Ҫ��-1����
	return 0;
}*/
