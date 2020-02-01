
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

//前16个素数
unsigned long long p[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

void release(long long** a, int n){
	for(int i = 0; i < n; i++)delete[] a[i];
	delete[] a;
}

//方阵乘法
void matMulti(long long** a, long long** b, int n){
	long long** temp = new long long*[n];
	for(int i = 0; i < n; i++)temp[i] = new long long[n];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			temp[i][j] = 0;
			for(int k = 0; k < n; k++){
				temp[i][j] += a[i][k] * b[k][j];	
			}
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			a[i][j] = temp[i][j];
		}
	}
	release(temp, n);
}


//快速幂O(logn)可以应用在任何具有结合律的运算中，显然的是它可以应用于模意义下取幂、矩阵幂等运算
//将取幂的任务按照 (指数的二进制表示) 来分割成更小的任务。

//快速幂递归
long long binpowRe(long long a, long long b){
	if(b == 0)return 1;
	long long result = binpowRe(a, b>>1);
	return (b & 2) ? (result*result*a) : (result*result);
}

//快速幂迭代
long long binpow(long long a, long long b){
	long long result = 1;
	while(b > 0){
		if(b & 1)result *= a;
		a *= a;
		b >>= 1;
	}
	return result;
}

//快速幂迭代
double binpow(double a, long long b){
	double result = 1.0;
	while(b > 0){
		if(b & 1)result *= a;
		a *= a;
		b >>= 1;
	}
	return result;
}

//矩阵快速幂, n是矩阵大小，O(logb * n^3)
long long** matBinPow(long long** a, int b, int n){
	long long** res = new long long*[n];
	for(int i = 0; i < n; i++){
		res[i] = new long long[n];
		for(int j = 0; j < n; j++)res[i][j] = 0;
		res[i][i] = 1;//单位阵
	}
	while(b > 0){
		if(b & 1)matMulti(res, a, n);
		matMulti(a, a, n);
		b >>= 1;
	}
	return res;
}

//打印矩阵
void printMat(int** a, int n){
	for(int i = 0; i < n; i++, putchar(10)){
		for(int j = 0; j < n; j++){
			printf("%5d", a[i][j]);
		}
	}
}

//第n项Fib(1, 1, 2, 3...)
//但由于幂运算不是每次+1，所以只适用于求单个fib的值，求出前n项还是需要 记忆化dp,均摊O(1)
long long fib(int b){
	int n = 2;
	long long** mat = new long long*[n];
	for(int i = 0; i < n; i++)mat[i] = new long long[n];
	mat[0][0] = 1, mat[0][1] = 1, mat[1][0] = 1, mat[1][1] = 0;//Fib矩阵
	long long** res = matBinPow(mat, b, n);
	//printMat(res, n);
	long long re = res[0][1];
	release(res, n);
	return re;
}

//公式法Fib, 因为要计算幂, 依然是O(2logn),常数小一些
long long Fib(int n){
	double num = (sqrt(5.0) + 1.0) / 2.0;
	return 1+(long long)((binpow(num, n) - binpow(-(num - 1.0), n)) / sqrt(5.0));
}

//Fib(n)%p的计算:
//斐波那契数列在模一个数时会出现循环，而这个周期的长度就称为斐波那契循环节。
//我们需要先求出斐波那契循环节m，然后用矩阵快速幂计算F(n mod m) mod p就行了。

//我们把该图的邻接矩阵M取k次幂，那么M_ij就表示从i到j长度为k的路径的数目。
//该算法的复杂度O(n^3logk)。

//数论相关板子
//欧几里得算法(Euclidean algorithm)GCD，即辗转相除法
//一般重要的是 类欧几里得，即将 某种求和问题 通过等价变换 转化为 辗转相除 的形式进行求解。
int gcd(int a, int b){//O( log(min(a, b) )
	if(b == 0)return a;
	return gcd(b, a % b);
}
//多个数的最大公约数
//显然答案一定是每个数的约数，那么也一定是每相邻两个数的约数。我们采用归纳法，可以证明，每次取出两个数求出答案后再放回去，不会对所需要的答案造成影响。

//求解最小公倍数
//gcd 一定是 lcm 的因数
int lcm(int a, int b){//O( log(min(a, b) )
	return a * b / gcd(a, b);
}

//扩展欧几里得算法Extended Euclidean algorithm (EXGCD)
//用于求 ax + by = gcd(a, b)(裴蜀定理)的可行解
//有一个直接的应用就是 如果ax+by=1有解，那么gcd(a,b)=1；gcd是a,b两个数线性组合的最小值
int exgcd(int a, int b, int& x, int& y){//函数返回的值为 GCD，在这个过程中计算x, y
	if(!b){x = 1, y = 0; return a;}
	int d = exgcd(b, a % b, x, y);//用欧几里得算法，递归直到b == 0,这时对x, y赋值，回溯过程对x, y进行运算，最终求出x, y
	int t = x;
	x = y;//回溯过程对x, y进行运算，最终求出x, y
	y = t - (a / b) * y;
	return d;
}

//用扩展欧几里得算法求逆元 a*x (mod m) == 1
int calInverse(int a, int m){//单个数O(log(min(a, m)))
	int x, y;
	int gcd = exgcd(a, m, x, y);
	if(1 % gcd != 0)return -1;
	x *= 1 / gcd;
	m = abs(m);
	int ans = x % m;
	if(ans <= 0) ans += m;
	return ans;
}

//线性求逆元O(n), 均摊O(1)
//实际上是 群(模p剩余系) 的每个数的逆元。那么必有 n < p。对于n > p，可以先计算n = n % p < p. 再进行求逆元
void inverse(int p, int n){//p是素数
	assert(n < p);//保证在群内.群外元素可以通过取模得到，即 inv[n] = inv[n%p]
	int* inv = new int[n];
	inv[1] = 1;//1的逆元是自己
	for(int i = 2; i <= n ;i++){
		inv[i] = (long long)(p - p / i) * inv[p % i] % p;//(p - p / i)加上p是为了防止出现素数
	}
	printf("逆元:\n");
	for(int i = 1; i <= n; i++){
		printf("%d  ", inv[i]);
	}
	putchar(10);
}

//欧拉函数 ：小于等于n和n互质的数的个数。
//质因数分解的同时求
int euler_phi(int n){
	int m = int(sqrt(n + 0.5));//问题上界
	int ans = n;//初始化，将n看成一个素数
	for(int i = 2; i <= m; i++){//进行质因数分解O()
		if(n % i == 0){
			ans = (ans / i) * (i-1);
			while(n % i == 0)n /= i;
		}
	}
	if(n > 1)ans /= n*(n-1);
	return ans;
}
//相关定理：欧拉定理，扩展欧拉定理, 费马小定理

//线性筛求欧拉函数O(n)
//实际上 积性函数 都可以 用线性筛O(n)，比如筛法求 约数个数，求约数的和 等
void phi_table(int n){
	int* phi = new int[n+1];
	memset(phi, 0, (n + 1) * sizeof(int));
	phi[1] = 1;
	for(int i = 2; i <= n; i++){
		if(!phi[i]){//i是素数
			for(int j = i; j <= n; j += i){//对i的所有倍数
				if(!phi[j])phi[j] = j;//初始化为自身
				phi[j] = (phi[j] / i) * (i - 1);//使用欧拉函数的定义
			}
		}
	}
	//输出欧拉函数值
	printf("欧拉函数值：\n");
	for(int i = 1; i <= n; i++){
		printf("%d  ", phi[i]);
	}
	putchar(10);
}

//筛法求素数(<=n的所有素数)
//埃拉托色尼筛法：如果x是合数，那么x的倍数也一定是合数。
//返回 素数计数函数 pi(x) 值
//注意到筛法求素数的同时也得到了每个数的最小质因子
int eratosthenes(int n){//O(n loglogn)
	int pcount = 0;//素数个数
	bool* isPrime = new bool[n+1];
	memset(isPrime, true, (n+1)*sizeof(bool));
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= n; i++){//从2开始
		if(isPrime[i]){
			pcount++;//可以开辟空间同时记录素数
			for(int j = i*i; j <= n; j += i){ // 因为从 2 到 i - 1 的倍数我们之前筛过了，这里直接从 i的倍数开始，提高了运行速度
				isPrime[j] = false;
			}
		}
	}
	delete[] isPrime;
	return pcount;
}

//线性筛
//欧拉筛法，如果能让每个合数都只被标记一次，那么时间复杂度就可以降到O(n)了
//可以用于求 约数个数，约数和，欧拉函数，素数表等。
// 积性函数 都可以线性筛，只是各自需要设计不同的 辅助数组 和 转移方程。但是总体框架 和 vis、prime 是相同的

//莫比乌斯函数： 对于n的质因数分解(质因子去重个数为k)，如果每个质因子的次数都是1，则mu(n) = (-1)^k, 否则为0
//数论中重要函数，是积性函数，和 莫比乌斯变换，狄利克雷卷积(莫比乌斯反演：卷积与逆卷积) 有密切关系
int eulerPrime(int n){//O(n)
	int pcount = 0;
	//必需的函数
	int* prime = new int[n+1];//素数表
	bool* vis = new bool[n+1];//判断是否筛过(剪枝)
	memset(prime, 0, n * sizeof(n));
	memset(vis, false, n * sizeof(bool));

	//求欧拉函数
	int* phi = new int[n+1];//欧拉函数值表
	//求约数个数
	int* num = new int[n+1];//数 i 的最小素因子出现次数
	int* dnum = new int[n+1];//约数个数
	//求莫比乌斯函数
	int* mobius = new int[n+1];//莫比乌斯函数
	//求约数和
	int* dsum = new int[n+1];//约数和
	int* g = new int[n+1];//g[i]表示i的最小质因子的p + p^2 + p^3 + ......
	
	//相关dp值初始化
	phi[1] = 1; dnum[1] = 1; mobius[1] = 1; g[1] = dsum[1] = 1;
	
	for(int i = 2; i <= n; i++){
		if(!vis[i]){//是素数
			prime[pcount++] = i;//记录素数
			phi[i] = i - 1;//记录欧拉函数值
			dnum[i] = 2;//记录约数个数
			num[i] = 1;//记录因子个数
			mobius[i] = -1;//记录莫比乌斯函数
			g[i] = dsum[i] = i + 1;//约数和是 自身+1
		}
		//和埃氏筛法不同，欧拉筛法不仅遇到素数进行筛，遇到合数也将其 与 遇到过的素数的乘积 筛掉
		//如何保证不重复筛？ 每次只 筛到 i*prime[pcount]!!, 保证每个合数只被筛一次， 每一个合数都是被最小的质因子筛掉
		for(int j = 0; j < pcount && i * prime[j] <= n; j++){
			vis[i * prime[j]] = 1;
			//由积性函数的性质得到转移方程
			if(i % prime[j]){// i 和 prime[j] 互质， i 不含 i*prime[j]的素因子
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);//同时得到欧拉函数值，因此多个数的欧拉函数值可以O(n)求出，均摊O(1)
				
				num[i * prime[j]] = 1;
				dnum[i * prime[j]] = dnum[i]<<1;
				
				mobius[i * prime[j]] = -mobius[i];
				
				dsum[i * prime[j]] = dsum[i] * dsum[prime[j]];
				g[i * prime[j]] = 1 + prime[j];
			}else{//发现i的一个素因子prime[j]， i 包含了 i*prime[j] 的所有素因子(因为素数不影响整除性)
				phi[i * prime[j]] = phi[i] * prime[j];
				
				num[i * prime[j]] = num[i] + 1;
				dnum[i * prime[j]] = dnum[i] / num[i * prime[j]] * (num[i * prime[j]] + 1);
				
				mobius[i * prime[j]] = 0;
				
				g[i * prime[j]] = g[i] * prime[j] + 1;
				dsum[i * prime[j]] = dsum[i] / g[i] * g[i * prime[j]];
				break;
			}//只有以上两种情况，这正是 素数可在整除中约去 的特点
		}
	}
	//输出素数表
	printf("素数:\n");
	for(int i = 0; i < pcount; i++){
		printf("%d  ", prime[i]);
	}
	//输出欧拉函数值
	printf("\n欧拉函数值：\n");
	for(int i = 1; i <= n; i ++){
		printf("%d  ", phi[i]);
	}
	printf("\n约数个数：\n");
	for(int i = 1; i <= n ;i++){
		printf("%d  ", dnum[i]);
	}
	printf("\n莫比乌斯函数值：\n");
	for(int i = 1; i <= n ;i++){
		printf("%d  ", mobius[i]);
	}
	printf("\n约数和：\n");
	for(int i = 1; i <= n ;i++){
		printf("%d  ", dsum[i]);
	}
	putchar(10);
	delete[] phi;
	delete[] num;
	delete[] dnum;
	delete[] dsum;
	delete[] g;
	delete[] prime;
	delete[] vis;
	delete[] mobius;
	return pcount;
}

//线性同余方程 ax == c(mod b) 和 ax + by == c 同解 等价于 gcd(a, b) | c
//c = 1时退化为乘法逆元，同样采用扩展欧几里得算法
//使用扩展欧几里得算法,返回是否有解，解放在x,y中
bool linearEquation(int a, int b, int c, int& x, int& y){
	int d = exgcd(a, b, x, y);
	if(c % d)return false;
	int k = c / d;
	x *= k;
	y *= k;
	x = (x + b) % b;//保证是正数
	return true;
}

//中国剩余定理: 一元线性同余方程组。模数两两互质
//先计算所有模数的积n,对于第i个方程，计算mi = n / ni(即补数)
//计算mi在模ni意义下的逆元mi-1，之后计算ci = mi*mi-1(即ci在mod n意义下为1，可以看做是一个基)
//方程组有唯一解\sum ai*ci (mod n)
//本质上是取一组基，和拉格朗日插值是等价的！！！
int chinaResidual(){//O(n logp)
	int n = 3;
	int ans = 0;
	int* a = new int[n];
	int* p = new int[n];
	//以下赋值可以改成读入
	a[0] = 2, p[0] = 3;//三三数之剩二
	a[1] = 3, p[1] = 5;//五五数之剩三
	a[2] = 2, p[2] = 7;//七七数之剩二
	int multi = 1;
	for(int i = 0; i < n; i++)multi *= p[i];
	for(int i = 0; i < n; i++){
		int m = multi / p[i];
		int revm = calInverse(m, p[i]);//扩展欧几里得O(logp[i])
		ans = (ans + a[i] * m * revm) % multi;
	}
	return ans;
}

//从模n的每个剩余类中各取一个数，得到一个由n个数组成的集合，叫做模n的一个完全剩余系。完全剩余系常用于数论中存在性证明。
//对于n个整数，其构成模n的 完全剩余系 等价于其关于模n两两不同余；
//质因数是“本质”或者成“基”
//既约剩余系，是m的完全剩余系中与m互素的数构成的子集，如果模m的一个剩余类里所有数都与m互素，就把它叫做与模m互素的剩余类。
//模10的一个既约剩余系是1，3，7，9

int main(){
	printf("%lld\n", binpow((long long)5, 10));//注意数位溢出(long long: -2^63 ~ 2^63-1)
	int n = 300;
	printf("Fib(%d): %lld\n", n, fib(n));
	printf("Fib(%d): %lld\n", n, Fib(n));
	int a = 11, b = 232, c;
	printf("gcd(%d, %d) = %d, lcm(%d, %d) = %d\n", a, b, gcd(a, b), a, b, lcm(a, b));
	printf("euler_phi(%d) = %d, eratos(%d) = %d, estimate: x/lnx = %d\n", n, euler_phi(n), n, eratosthenes(n), int(n / log(double(n))));
	
	eulerPrime(n);
	phi_table(n);
	inverse(/* p= */499, n);//n < p
	
	int x, y;
	a = 12, c = 20, b = 28;
	linearEquation(a, b, c, x, y);
	printf("%dx == %d (mod %d) solution:%d\n", a, c, b, x);
	printf("%d\n", chinaResidual());
	
	//数论分块
	//体会一下 n/i 的取值趋势 和 集合大小(最多2sqrt(n))
	for(int i = 1; i <= n/2+1; i++)printf("%4d ", n / i);
	putchar(10);
	//数论分块的基础[i, n / (n/i)]区域的k， n/k都是同一个值！！！因此可以缩成一个点
	for(int i = 1; i <= n/2+1; i++)printf("%4d ", n / (n / i));//使n/i相等的值的最大的i
	putchar(10);
	return 0;
}
