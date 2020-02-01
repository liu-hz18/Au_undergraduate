
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

//ǰ16������
unsigned long long p[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};

void release(long long** a, int n){
	for(int i = 0; i < n; i++)delete[] a[i];
	delete[] a;
}

//����˷�
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


//������O(logn)����Ӧ�����κξ��н���ɵ������У���Ȼ����������Ӧ����ģ������ȡ�ݡ������ݵ�����
//��ȡ�ݵ������� (ָ���Ķ����Ʊ�ʾ) ���ָ�ɸ�С������

//�����ݵݹ�
long long binpowRe(long long a, long long b){
	if(b == 0)return 1;
	long long result = binpowRe(a, b>>1);
	return (b & 2) ? (result*result*a) : (result*result);
}

//�����ݵ���
long long binpow(long long a, long long b){
	long long result = 1;
	while(b > 0){
		if(b & 1)result *= a;
		a *= a;
		b >>= 1;
	}
	return result;
}

//�����ݵ���
double binpow(double a, long long b){
	double result = 1.0;
	while(b > 0){
		if(b & 1)result *= a;
		a *= a;
		b >>= 1;
	}
	return result;
}

//���������, n�Ǿ����С��O(logb * n^3)
long long** matBinPow(long long** a, int b, int n){
	long long** res = new long long*[n];
	for(int i = 0; i < n; i++){
		res[i] = new long long[n];
		for(int j = 0; j < n; j++)res[i][j] = 0;
		res[i][i] = 1;//��λ��
	}
	while(b > 0){
		if(b & 1)matMulti(res, a, n);
		matMulti(a, a, n);
		b >>= 1;
	}
	return res;
}

//��ӡ����
void printMat(int** a, int n){
	for(int i = 0; i < n; i++, putchar(10)){
		for(int j = 0; j < n; j++){
			printf("%5d", a[i][j]);
		}
	}
}

//��n��Fib(1, 1, 2, 3...)
//�����������㲻��ÿ��+1������ֻ�������󵥸�fib��ֵ�����ǰn�����Ҫ ���仯dp,��̯O(1)
long long fib(int b){
	int n = 2;
	long long** mat = new long long*[n];
	for(int i = 0; i < n; i++)mat[i] = new long long[n];
	mat[0][0] = 1, mat[0][1] = 1, mat[1][0] = 1, mat[1][1] = 0;//Fib����
	long long** res = matBinPow(mat, b, n);
	//printMat(res, n);
	long long re = res[0][1];
	release(res, n);
	return re;
}

//��ʽ��Fib, ��ΪҪ������, ��Ȼ��O(2logn),����СһЩ
long long Fib(int n){
	double num = (sqrt(5.0) + 1.0) / 2.0;
	return 1+(long long)((binpow(num, n) - binpow(-(num - 1.0), n)) / sqrt(5.0));
}

//Fib(n)%p�ļ���:
//쳲�����������ģһ����ʱ�����ѭ������������ڵĳ��Ⱦͳ�Ϊ쳲�����ѭ���ڡ�
//������Ҫ�����쳲�����ѭ����m��Ȼ���þ�������ݼ���F(n mod m) mod p�����ˡ�

//���ǰѸ�ͼ���ڽӾ���Mȡk���ݣ���ôM_ij�ͱ�ʾ��i��j����Ϊk��·������Ŀ��
//���㷨�ĸ��Ӷ�O(n^3logk)��

//������ذ���
//ŷ������㷨(Euclidean algorithm)GCD����շת�����
//һ����Ҫ���� ��ŷ����ã����� ĳ��������� ͨ���ȼ۱任 ת��Ϊ շת��� ����ʽ������⡣
int gcd(int a, int b){//O( log(min(a, b) )
	if(b == 0)return a;
	return gcd(b, a % b);
}
//����������Լ��
//��Ȼ��һ����ÿ������Լ������ôҲһ����ÿ������������Լ�������ǲ��ù��ɷ�������֤����ÿ��ȡ������������𰸺��ٷŻ�ȥ�����������Ҫ�Ĵ����Ӱ�졣

//�����С������
//gcd һ���� lcm ������
int lcm(int a, int b){//O( log(min(a, b) )
	return a * b / gcd(a, b);
}

//��չŷ������㷨Extended Euclidean algorithm (EXGCD)
//������ ax + by = gcd(a, b)(������)�Ŀ��н�
//��һ��ֱ�ӵ�Ӧ�þ��� ���ax+by=1�н⣬��ôgcd(a,b)=1��gcd��a,b������������ϵ���Сֵ
int exgcd(int a, int b, int& x, int& y){//�������ص�ֵΪ GCD������������м���x, y
	if(!b){x = 1, y = 0; return a;}
	int d = exgcd(b, a % b, x, y);//��ŷ������㷨���ݹ�ֱ��b == 0,��ʱ��x, y��ֵ�����ݹ��̶�x, y�������㣬�������x, y
	int t = x;
	x = y;//���ݹ��̶�x, y�������㣬�������x, y
	y = t - (a / b) * y;
	return d;
}

//����չŷ������㷨����Ԫ a*x (mod m) == 1
int calInverse(int a, int m){//������O(log(min(a, m)))
	int x, y;
	int gcd = exgcd(a, m, x, y);
	if(1 % gcd != 0)return -1;
	x *= 1 / gcd;
	m = abs(m);
	int ans = x % m;
	if(ans <= 0) ans += m;
	return ans;
}

//��������ԪO(n), ��̯O(1)
//ʵ������ Ⱥ(ģpʣ��ϵ) ��ÿ��������Ԫ����ô���� n < p������n > p�������ȼ���n = n % p < p. �ٽ�������Ԫ
void inverse(int p, int n){//p������
	assert(n < p);//��֤��Ⱥ��.Ⱥ��Ԫ�ؿ���ͨ��ȡģ�õ����� inv[n] = inv[n%p]
	int* inv = new int[n];
	inv[1] = 1;//1����Ԫ���Լ�
	for(int i = 2; i <= n ;i++){
		inv[i] = (long long)(p - p / i) * inv[p % i] % p;//(p - p / i)����p��Ϊ�˷�ֹ��������
	}
	printf("��Ԫ:\n");
	for(int i = 1; i <= n; i++){
		printf("%d  ", inv[i]);
	}
	putchar(10);
}

//ŷ������ ��С�ڵ���n��n���ʵ����ĸ�����
//�������ֽ��ͬʱ��
int euler_phi(int n){
	int m = int(sqrt(n + 0.5));//�����Ͻ�
	int ans = n;//��ʼ������n����һ������
	for(int i = 2; i <= m; i++){//�����������ֽ�O()
		if(n % i == 0){
			ans = (ans / i) * (i-1);
			while(n % i == 0)n /= i;
		}
	}
	if(n > 1)ans /= n*(n-1);
	return ans;
}
//��ض���ŷ��������չŷ������, ����С����

//����ɸ��ŷ������O(n)
//ʵ���� ���Ժ��� ������ ������ɸO(n)������ɸ���� Լ����������Լ���ĺ� ��
void phi_table(int n){
	int* phi = new int[n+1];
	memset(phi, 0, (n + 1) * sizeof(int));
	phi[1] = 1;
	for(int i = 2; i <= n; i++){
		if(!phi[i]){//i������
			for(int j = i; j <= n; j += i){//��i�����б���
				if(!phi[j])phi[j] = j;//��ʼ��Ϊ����
				phi[j] = (phi[j] / i) * (i - 1);//ʹ��ŷ�������Ķ���
			}
		}
	}
	//���ŷ������ֵ
	printf("ŷ������ֵ��\n");
	for(int i = 1; i <= n; i++){
		printf("%d  ", phi[i]);
	}
	putchar(10);
}

//ɸ��������(<=n����������)
//������ɫ��ɸ�������x�Ǻ�������ôx�ı���Ҳһ���Ǻ�����
//���� ������������ pi(x) ֵ
//ע�⵽ɸ����������ͬʱҲ�õ���ÿ��������С������
int eratosthenes(int n){//O(n loglogn)
	int pcount = 0;//��������
	bool* isPrime = new bool[n+1];
	memset(isPrime, true, (n+1)*sizeof(bool));
	isPrime[0] = isPrime[1] = false;
	for(int i = 2; i <= n; i++){//��2��ʼ
		if(isPrime[i]){
			pcount++;//���Կ��ٿռ�ͬʱ��¼����
			for(int j = i*i; j <= n; j += i){ // ��Ϊ�� 2 �� i - 1 �ı�������֮ǰɸ���ˣ�����ֱ�Ӵ� i�ı�����ʼ������������ٶ�
				isPrime[j] = false;
			}
		}
	}
	delete[] isPrime;
	return pcount;
}

//����ɸ
//ŷ��ɸ�����������ÿ��������ֻ�����һ�Σ���ôʱ�临�ӶȾͿ��Խ���O(n)��
//���������� Լ��������Լ���ͣ�ŷ��������������ȡ�
// ���Ժ��� ����������ɸ��ֻ�Ǹ�����Ҫ��Ʋ�ͬ�� �������� �� ת�Ʒ��̡����������� �� vis��prime ����ͬ��

//Ī����˹������ ����n���������ֽ�(������ȥ�ظ���Ϊk)�����ÿ�������ӵĴ�������1����mu(n) = (-1)^k, ����Ϊ0
//��������Ҫ�������ǻ��Ժ������� Ī����˹�任���������׾��(Ī����˹���ݣ����������) �����й�ϵ
int eulerPrime(int n){//O(n)
	int pcount = 0;
	//����ĺ���
	int* prime = new int[n+1];//������
	bool* vis = new bool[n+1];//�ж��Ƿ�ɸ��(��֦)
	memset(prime, 0, n * sizeof(n));
	memset(vis, false, n * sizeof(bool));

	//��ŷ������
	int* phi = new int[n+1];//ŷ������ֵ��
	//��Լ������
	int* num = new int[n+1];//�� i ����С�����ӳ��ִ���
	int* dnum = new int[n+1];//Լ������
	//��Ī����˹����
	int* mobius = new int[n+1];//Ī����˹����
	//��Լ����
	int* dsum = new int[n+1];//Լ����
	int* g = new int[n+1];//g[i]��ʾi����С�����ӵ�p + p^2 + p^3 + ......
	
	//���dpֵ��ʼ��
	phi[1] = 1; dnum[1] = 1; mobius[1] = 1; g[1] = dsum[1] = 1;
	
	for(int i = 2; i <= n; i++){
		if(!vis[i]){//������
			prime[pcount++] = i;//��¼����
			phi[i] = i - 1;//��¼ŷ������ֵ
			dnum[i] = 2;//��¼Լ������
			num[i] = 1;//��¼���Ӹ���
			mobius[i] = -1;//��¼Ī����˹����
			g[i] = dsum[i] = i + 1;//Լ������ ����+1
		}
		//�Ͱ���ɸ����ͬ��ŷ��ɸ������������������ɸ����������Ҳ���� �� �������������ĳ˻� ɸ��
		//��α�֤���ظ�ɸ�� ÿ��ֻ ɸ�� i*prime[pcount]!!, ��֤ÿ������ֻ��ɸһ�Σ� ÿһ���������Ǳ���С��������ɸ��
		for(int j = 0; j < pcount && i * prime[j] <= n; j++){
			vis[i * prime[j]] = 1;
			//�ɻ��Ժ��������ʵõ�ת�Ʒ���
			if(i % prime[j]){// i �� prime[j] ���ʣ� i ���� i*prime[j]��������
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);//ͬʱ�õ�ŷ������ֵ����˶������ŷ������ֵ����O(n)�������̯O(1)
				
				num[i * prime[j]] = 1;
				dnum[i * prime[j]] = dnum[i]<<1;
				
				mobius[i * prime[j]] = -mobius[i];
				
				dsum[i * prime[j]] = dsum[i] * dsum[prime[j]];
				g[i * prime[j]] = 1 + prime[j];
			}else{//����i��һ��������prime[j]�� i ������ i*prime[j] ������������(��Ϊ������Ӱ��������)
				phi[i * prime[j]] = phi[i] * prime[j];
				
				num[i * prime[j]] = num[i] + 1;
				dnum[i * prime[j]] = dnum[i] / num[i * prime[j]] * (num[i * prime[j]] + 1);
				
				mobius[i * prime[j]] = 0;
				
				g[i * prime[j]] = g[i] * prime[j] + 1;
				dsum[i * prime[j]] = dsum[i] / g[i] * g[i * prime[j]];
				break;
			}//ֻ��������������������� ��������������Լȥ ���ص�
		}
	}
	//���������
	printf("����:\n");
	for(int i = 0; i < pcount; i++){
		printf("%d  ", prime[i]);
	}
	//���ŷ������ֵ
	printf("\nŷ������ֵ��\n");
	for(int i = 1; i <= n; i ++){
		printf("%d  ", phi[i]);
	}
	printf("\nԼ��������\n");
	for(int i = 1; i <= n ;i++){
		printf("%d  ", dnum[i]);
	}
	printf("\nĪ����˹����ֵ��\n");
	for(int i = 1; i <= n ;i++){
		printf("%d  ", mobius[i]);
	}
	printf("\nԼ���ͣ�\n");
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

//����ͬ�෽�� ax == c(mod b) �� ax + by == c ͬ�� �ȼ��� gcd(a, b) | c
//c = 1ʱ�˻�Ϊ�˷���Ԫ��ͬ��������չŷ������㷨
//ʹ����չŷ������㷨,�����Ƿ��н⣬�����x,y��
bool linearEquation(int a, int b, int c, int& x, int& y){
	int d = exgcd(a, b, x, y);
	if(c % d)return false;
	int k = c / d;
	x *= k;
	y *= k;
	x = (x + b) % b;//��֤������
	return true;
}

//�й�ʣ�ඨ��: һԪ����ͬ�෽���顣ģ����������
//�ȼ�������ģ���Ļ�n,���ڵ�i�����̣�����mi = n / ni(������)
//����mi��ģni�����µ���Ԫmi-1��֮�����ci = mi*mi-1(��ci��mod n������Ϊ1�����Կ�����һ����)
//��������Ψһ��\sum ai*ci (mod n)
//��������ȡһ��������������ղ�ֵ�ǵȼ۵ģ�����
int chinaResidual(){//O(n logp)
	int n = 3;
	int ans = 0;
	int* a = new int[n];
	int* p = new int[n];
	//���¸�ֵ���Ըĳɶ���
	a[0] = 2, p[0] = 3;//������֮ʣ��
	a[1] = 3, p[1] = 5;//������֮ʣ��
	a[2] = 2, p[2] = 7;//������֮ʣ��
	int multi = 1;
	for(int i = 0; i < n; i++)multi *= p[i];
	for(int i = 0; i < n; i++){
		int m = multi / p[i];
		int revm = calInverse(m, p[i]);//��չŷ�����O(logp[i])
		ans = (ans + a[i] * m * revm) % multi;
	}
	return ans;
}

//��ģn��ÿ��ʣ�����и�ȡһ�������õ�һ����n������ɵļ��ϣ�����ģn��һ����ȫʣ��ϵ����ȫʣ��ϵ�����������д�����֤����
//����n���������乹��ģn�� ��ȫʣ��ϵ �ȼ��������ģn������ͬ�ࣻ
//�������ǡ����ʡ����߳ɡ�����
//��Լʣ��ϵ����m����ȫʣ��ϵ����m���ص������ɵ��Ӽ������ģm��һ��ʣ����������������m���أ��Ͱ���������ģm���ص�ʣ���ࡣ
//ģ10��һ����Լʣ��ϵ��1��3��7��9

int main(){
	printf("%lld\n", binpow((long long)5, 10));//ע����λ���(long long: -2^63 ~ 2^63-1)
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
	
	//���۷ֿ�
	//���һ�� n/i ��ȡֵ���� �� ���ϴ�С(���2sqrt(n))
	for(int i = 1; i <= n/2+1; i++)printf("%4d ", n / i);
	putchar(10);
	//���۷ֿ�Ļ���[i, n / (n/i)]�����k�� n/k����ͬһ��ֵ��������˿�������һ����
	for(int i = 1; i <= n/2+1; i++)printf("%4d ", n / (n / i));//ʹn/i��ȵ�ֵ������i
	putchar(10);
	return 0;
}
