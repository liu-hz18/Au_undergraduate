
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

//n皇后问题，只有 n>=4 时 有解

//皇后数量
const int QUEEN_NUM = 10000;//10000皇后 约600s
int queen[QUEEN_NUM];//皇后的列
int solunum = 0;

inline int max(int a, int b){return a > b ? a : b;}
inline int min(int a, int b){return a > b ? b : a;}
inline void swap(int& a, int& b){int temp = a; a = b; b = temp;}
inline int dice(int n){return rand() % n;}

//n皇后问题，局部搜索算法，回溯搜索，模拟退火
//只需要给每个皇后 分配 一列，即queen[i] = j 表示第i个皇后处在第j列

//蛮力算法可以n重循环遍历，复杂度O(n^5)
//当然可以在进入每层循环之前剪枝，减少搜索树的规模

//建议传统解法解不超过25的问题，超过此规模则时间急剧上升
//但传统解法可以找出所有的解！
//这里采用随机重启的方法，因为n皇后问题的解很多，但是对于某些可行解比较少的例子，比如大部分的TSP问题，随机重启的效率并不高
inline bool collide(int k){//判断是否冲突
	for(int i = 0; i < k; i++){
		if(queen[k] == queen[i])return true;
		if(abs(queen[k] - queen[i]) == k - i)return true;
	}
	return false;
}

void display(){//输出解
	for(int i = 0; i < QUEEN_NUM; i++, putchar(10)){
		for(int j = 0; j < QUEEN_NUM; j++){
			printf ( ( j == queen[i] ) ? "█" : "[]" );
		}
	}
}

//各种算法汇总

//回溯算法：递归（适用于求解所有的解）O(n!)
void palceQueens_Recurse(int nQueen, int k){//放置n个皇后中的第k个（假设0至k-1均已就位）
	if(nQueen <= k){
		solunum++;
		printf("Solution: %d :\n", solunum);
		display();
	}else{
		for(int i = 0; i < nQueen; i++){
			queen[k] = i;
			if(!collide(k)){//适当剪枝
				palceQueens_Recurse(nQueen, k+1);
			}
		}
	}
}

//回溯：迭代版 O(n!)
void placeQueens_iter(int n){
	int k = 0;
	queen[k] = -1;//从原点出发
	while(k >= 0){
		queen[k]++;
		for(; queen[k] < n && collide(k); queen[k]++);//放置第k个皇后,直到找到可行解
		//注意换行符之后不能有任何字符！
		if(queen[k] >= n){
			k--;//回溯
		}else{
			if(k == n - 1){/*找到解*/
				printf("Solution: %d :\n", ++solunum);/*输出解*/
				display();
				break;
			}else{
				queen[++k] = -1;/*开始放置下一个*/
			}
		}
	}
}

//随机找到不同行不同列的排布（其实就是1-n的随机排列，采用knuth的洗牌算法）
void shuffle(int n){//O(n)
	for(int i = 0; i < n; i++)queen[i] = i;
	//Knuth洗牌
	for(int i = n-1; i > 0; i--){
		swap(queen[i], queen[dice(i+1)]);
	}
	//for(int i = 0; i < n; i ++)printf("%d ", queen[i]);
}

//计算冲突数，因为无论洗牌还是两两交换之后，仍保证不同行同列，所以只需要判断斜向
int conflictNum(int n){//O(n^2)
	int num = 0;
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(abs(queen[i] - queen[j]) == j - i)num++;
		}
	}
	return num;
}

//记忆化方式 实现O(n)求解冲突数，即标记2n-1条 左上-右下和 2n-1条左下-右上的对角线，最后统计冲突数
//推荐采用此方法，将使求解时间缩短近 10 倍！
int conflictNum_Memo(int n){//O(n)
	int d1[QUEEN_NUM<<1] = {0};//左上-右下
	int d2[QUEEN_NUM<<1] = {0};//左下-右上
	for(int i = 0; i < n; i++){
		d1[queen[i] - i + n - 1]++;
		d2[queen[i] + i]++;
	}
	int num = 0;
	for(int i = 0; i < (n<<1)-1; i++){
		if(d1[i] > 1)num += d1[i] - 1;
		if(d2[i] > 1)num += d2[i] - 1;
	}
	return num;
}

//局部搜索 算法(只保证找到一组可行解)
void localSearch(int n){
	while(1){
		shuffle(n);
		int connum, temp;
		if(!(connum = conflictNum_Memo(n))){//O(n)
			printf("Solution: %d :\n", ++solunum);
			//display();
			return;
		}
		while(1){
			bool flag = false;
			for(int x = 0; x < n; x ++){//尝试所有的交换
				for(int y = x+1; y < n; y++){
					swap(queen[x], queen[y]);
					if((temp = conflictNum_Memo(n)) < connum){//O(n) //更新最优解，在此基础上继续进行交换，而不是从头开始交换
						connum = temp;
						flag = true;
						if(!connum){
							printf("Solution: %d :\n", ++solunum);
							//display();
							return;
						}
					}
					else swap(queen[x], queen[y]);//变回原样
				}
			}
			if(!flag)break;//尝试所有交换都不能使冲突数减小，则重新洗牌
		}
	}
}


//测试函数
void run(){
	clock_t start, finish1, finish2;
	start = clock();
	//回溯和递归基本没有差别
	//palceQueens_Recurse(QUEEN_NUM, 0);
	//placeQueens_iter(QUEEN_NUM);//只找一个解
	finish1 = clock();
	localSearch(QUEEN_NUM);
	finish2 = clock();
	printf("\n%d queen solution...tot time:%f...\n\n", \
		QUEEN_NUM, (double)(finish1 - start) / CLOCKS_PER_SEC);
	printf("\n%d queen solution...tot time:%f...\n\n", \
		QUEEN_NUM, (double)(finish2 - finish1) / CLOCKS_PER_SEC);
}

int main(){
	srand((unsigned)time(NULL));
	run();
	return 0;
}
