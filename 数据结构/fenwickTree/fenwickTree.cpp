
//Fenwick Tree 树状数组模板（区间和，异或和，最大值，最小值）
//动态维护前缀和
//单点修改，区间查询
//区间修改，单点查询（差分数组b，用树状数组维护b的前缀和，即a中每个元素的增量）
//区间修改，区间查询（差分数组b,以及差分数字）

#include <stdio.h>
#include <string.h>

inline int lowbit(int x){ return x & -x; }

class fenwickTree{
	int* t;
	int len;

public:
	//O(n)建树
	fenwickTree(int* a, int n):t(new int[n+1]), len(n){
		memset(t, 0, (n+1) * sizeof(int));
		for(int i = 1; i <= n; i ++){//维护前缀和
			t[i] += a[i];
			int j = i + lowbit(i);
			if(j <= n)t[j] += t[i];
		}
	}
	~fenwickTree(){
		delete[] t;
	}
	void add(int x, int k){//O(logn)
		for(; x <= len; x += lowbit(x))t[x] += k;
	}
	int ask(int x){//O(logn)
		int ans = 0;
		for(; x; x -= lowbit(x))ans += t[x];
		return ans;
	}
};


int main(){
	int n, q;
	scanf("%d%d", &n, &q);
	int* a = new int[n+1]; a[0] = 0;//其实有了b数组，a数组在此刻不需要显式记录，滚动即可
	int* b = new int[n+1];//b是差分数组
	int* c = new int[n+1];
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		b[i] = a[i] - a[i-1];
		c[i] = i * b[i];
	}
	fenwickTree* tree = new fenwickTree(b, n);
	fenwickTree* tree2 = new fenwickTree(c, n);
	int i = 0, op = 0, l, r, k;
	while(i ++ < q){
		//单点修改，区间查询
		
		scanf("%d%d%d", &op, &l, &r);
		if(op == 1)tree->add(l, r);
		else printf("%d\n", tree->ask(r) - tree->ask(l-1));
		
		//区间修改，单点查询
		/*
		scanf("%d", &op);
		if(op == 1){
			scanf("%d%d%d", &l, &r, &k);
			tree->add(l, k);
			tree->add(r+1, -k);
		}else{
			scanf("%d", &l);
			printf("%d\n", tree->ask(l));
		}
		*/
		//区间修改，区间查询
		/*
		scanf("%d", &op);
		if(op == 1){
			scanf("%d%d%d", &l, &r, &k);
			tree->add(l, k);
			tree->add(r+1, -k);
			tree2->add(l, l*k);
			tree2->add(r+1, -(r+1)*k);
		}else{
			scanf("%d%d", &l, &r);
			printf("%d\n", (r+1)*tree->ask(r) - l * tree->ask(l-1) - (tree2->ask(r) - tree2->ask(l-1)));
		}
		*/
	}
	delete[] a;
	delete[] b;
	delete[] c;
	return 0;
}
