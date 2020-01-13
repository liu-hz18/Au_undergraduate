//楼梯有n(100 > n > 0)阶台阶,上楼时可以一步上1阶,也可以一步上2阶,也可以一步上3阶，
//编程计算共有多少种不同的走法。
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

//输出组合数
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
//这种递推要求是简单的，因为当不是第一位的时候，只需要补全空格，然后就可以进入下一层递归
//但是如果每一行都完整地输出结果，那么就需要记录上一层递归乃至上几层递归的输出数据
//或者说，可以先递归向数组中填充数据，然后在达到递归边界的时候一并输出数据
void  swap(int*a,int*b){int tmp=*a;*a=*b;*b=tmp;}
void pailie(int a[],int sum,int count,int b[])
{
	int i;
	if(count<sum){
		for(i=count;i<sum;i++){
			b[count]=a[i];
			//同样为了完整输出每一次排列的结果，先将排列结果存入数组，最后一并输出
			swap(&a[i],&a[count]);
			pailie(a,sum,count+1,b);
			swap(&a[i],&a[count]);
			//每次均以第一次的排列顺序为基准进行交换，所以交换完之后要再换回去
		}
	}else if(count==sum){
		for(i=0;i<sum;i++)printf("%d  ",b[i]);
		putchar(10);
	}
}
//在计算可能输出的结果总数时，采用分布乘法策略对递归程序调用次数进行判断（循环次数*递归次数）,
//可以较好地判断所编递归程序是否正确！
void zuhe(int n,int m,int a[],int begin,int count){
	int i,b[100];
	if(count<m){
		for(i=begin;i-count<=n-m+1;i++){
			a[count]=i;
			zuhe(n,m,a,i+1,count+1);
		}
	}else if(count==m){
		/*for(i=0;i<m;i++)printf("%d  ",a[i]);*///此处仅用于输出组合
		pailie(a,m,0,b);//此处用于输出排列
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
//错装信封问题
/* 用A、B、C……表示写着ｎ位友人名字的信封，a、b、c……表示ｎ份相应的写好的信纸。把错装的总数为记作D(n)。假设把ａ错装进Ｂ里了，包含着这个错误的一切错装法分两类：
(1)b装入Ａ里，这时每种错装的其余部分都与A、B、a、b无关，应有D(n－2)种错装法。　　　　
(2)ｂ装入A、B之外的一个信封，这时的装信工作实际是把（除a之外的）n－1份信纸ｂ、ｃ……装入（除B以外的）n－1个信封A、C……，显然这时装错的方法有D(n－1)种。
总之在ａ装入B的错误之下，共有错装法D(n－2)＋D(n－1)种。
a装入C，装入D……的n－2种错误之下，同样都有D(n－1)＋D(n－2)种错装法，因此D(n)＝(n－1)[D(n－1)＋D(n－2)]*/
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
//给定一个整数n，输出这个整数拆分的可能总数？？？
//例如当n=4时，它有5个划分：{4}、{3,1}、{2,2}、{2,1,1}、{1,1,1,1}；
//注意：4=1+3和4=3+1被认为是同一个划分。
/*根据n和m的关系，考虑下面几种情况：
（1）当n=1时，不论m的值为多少（m>0），只有一种划分，即{1}；
（2）当m=1时，不论n的值为多少（n>0），只有一种划分，即{1,1,....1,1,1}；
（3）当n=m时，根据划分中是否包含n，可以分为两种情况：
        （a）划分中包含n的情况，只有一个，即{n}；
        （b）划分中不包含n的情况，这时划分中最大的数字也一定比n小，即n的所有（n-1）划分；
        因此，f(n,n) = 1 + f(n, n - 1)。
（4）当n<m时，由于划分中不可能出现负数，因此就相当于f(n,n)；< span="">
（5）当n>m时，根据划分中是否包含m，可以分为两种情况：
        （a）划分中包含m的情况，即{m,{x1,x2,x3,...,xi}}，其中{x1,x2,x3,...,xi}的和为n-m，可能再次出现m，因此是（n-m）的m划分，因此这种划分个数为f(n-m, m)；
        （b）划分中不包含m的情况，则划分中所有值都比m小，即n的（m-1）划分，个数为f(n, m - 1)；
        因此，f(n,m) = f(n - m,m) + f(n, m - 1)。*/
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
	printf("%d\n",huafen(n,n));//改进为至少切一刀只需要再-1即可
	return 0;
}*/
