
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stack>
#include <queue>
using namespace std;

//n�ʺ����⣬ֻ�� n>=4 ʱ �н�

//�ʺ�����
const int QUEEN_NUM = 10000;//10000�ʺ� Լ600s
int queen[QUEEN_NUM];//�ʺ����
int solunum = 0;

inline int max(int a, int b){return a > b ? a : b;}
inline int min(int a, int b){return a > b ? b : a;}
inline void swap(int& a, int& b){int temp = a; a = b; b = temp;}
inline int dice(int n){return rand() % n;}

//n�ʺ����⣬�ֲ������㷨������������ģ���˻�
//ֻ��Ҫ��ÿ���ʺ� ���� һ�У���queen[i] = j ��ʾ��i���ʺ��ڵ�j��

//�����㷨����n��ѭ�����������Ӷ�O(n^5)
//��Ȼ�����ڽ���ÿ��ѭ��֮ǰ��֦�������������Ĺ�ģ

//���鴫ͳ�ⷨ�ⲻ����25�����⣬�����˹�ģ��ʱ�伱������
//����ͳ�ⷨ�����ҳ����еĽ⣡
//���������������ķ�������Ϊn�ʺ�����Ľ�ܶ࣬���Ƕ���ĳЩ���н�Ƚ��ٵ����ӣ�����󲿷ֵ�TSP���⣬���������Ч�ʲ�����
inline bool collide(int k){//�ж��Ƿ��ͻ
	for(int i = 0; i < k; i++){
		if(queen[k] == queen[i])return true;
		if(abs(queen[k] - queen[i]) == k - i)return true;
	}
	return false;
}

void display(){//�����
	for(int i = 0; i < QUEEN_NUM; i++, putchar(10)){
		for(int j = 0; j < QUEEN_NUM; j++){
			printf ( ( j == queen[i] ) ? "��" : "[]" );
		}
	}
}

//�����㷨����

//�����㷨���ݹ飨������������еĽ⣩O(n!)
void palceQueens_Recurse(int nQueen, int k){//����n���ʺ��еĵ�k��������0��k-1���Ѿ�λ��
	if(nQueen <= k){
		solunum++;
		printf("Solution: %d :\n", solunum);
		display();
	}else{
		for(int i = 0; i < nQueen; i++){
			queen[k] = i;
			if(!collide(k)){//�ʵ���֦
				palceQueens_Recurse(nQueen, k+1);
			}
		}
	}
}

//���ݣ������� O(n!)
void placeQueens_iter(int n){
	int k = 0;
	queen[k] = -1;//��ԭ�����
	while(k >= 0){
		queen[k]++;
		for(; queen[k] < n && collide(k); queen[k]++);//���õ�k���ʺ�,ֱ���ҵ����н�
		//ע�⻻�з�֮�������κ��ַ���
		if(queen[k] >= n){
			k--;//����
		}else{
			if(k == n - 1){/*�ҵ���*/
				printf("Solution: %d :\n", ++solunum);/*�����*/
				display();
				break;
			}else{
				queen[++k] = -1;/*��ʼ������һ��*/
			}
		}
	}
}

//����ҵ���ͬ�в�ͬ�е��Ų�����ʵ����1-n��������У�����knuth��ϴ���㷨��
void shuffle(int n){//O(n)
	for(int i = 0; i < n; i++)queen[i] = i;
	//Knuthϴ��
	for(int i = n-1; i > 0; i--){
		swap(queen[i], queen[dice(i+1)]);
	}
	//for(int i = 0; i < n; i ++)printf("%d ", queen[i]);
}

//�����ͻ������Ϊ����ϴ�ƻ�����������֮���Ա�֤��ͬ��ͬ�У�����ֻ��Ҫ�ж�б��
int conflictNum(int n){//O(n^2)
	int num = 0;
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(abs(queen[i] - queen[j]) == j - i)num++;
		}
	}
	return num;
}

//���仯��ʽ ʵ��O(n)����ͻ���������2n-1�� ����-���º� 2n-1������-���ϵĶԽ��ߣ����ͳ�Ƴ�ͻ��
//�Ƽ����ô˷�������ʹ���ʱ�����̽� 10 ����
int conflictNum_Memo(int n){//O(n)
	int d1[QUEEN_NUM<<1] = {0};//����-����
	int d2[QUEEN_NUM<<1] = {0};//����-����
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

//�ֲ����� �㷨(ֻ��֤�ҵ�һ����н�)
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
			for(int x = 0; x < n; x ++){//�������еĽ���
				for(int y = x+1; y < n; y++){
					swap(queen[x], queen[y]);
					if((temp = conflictNum_Memo(n)) < connum){//O(n) //�������Ž⣬�ڴ˻����ϼ������н����������Ǵ�ͷ��ʼ����
						connum = temp;
						flag = true;
						if(!connum){
							printf("Solution: %d :\n", ++solunum);
							//display();
							return;
						}
					}
					else swap(queen[x], queen[y]);//���ԭ��
				}
			}
			if(!flag)break;//�������н���������ʹ��ͻ����С��������ϴ��
		}
	}
}


//���Ժ���
void run(){
	clock_t start, finish1, finish2;
	start = clock();
	//���ݺ͵ݹ����û�в��
	//palceQueens_Recurse(QUEEN_NUM, 0);
	//placeQueens_iter(QUEEN_NUM);//ֻ��һ����
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
