
#include <stdio.h>
#include <string.h>

//数字转格雷码
//可以发现，如果Gray的二进制第i位为1，仅当n的二进制(第i位为1，第i+1位为0)或者(第i位为0，第i+1位为1)。
//于是我们可以当成一个异或的运算
unsigned long long num2Gray(unsigned long long k){
	return k ^ (k >> 1);
}

//格雷码转数字
unsigned long long gray2Num(unsigned long long k){
	unsigned long long n = 0;
	for(; g; g >>= 1)n ^= g;
	return n;
}

int main(){
	int n;
	unsigned long long k;
	//数字k的格雷码输出成n位格雷二进制表示
	scanf("%d%lu", &n, &k);
	k = num2Gray(k);//得到格雷码表示
	while(~--n)printf("%d", (k>>n)&1);
	return 0;
}
