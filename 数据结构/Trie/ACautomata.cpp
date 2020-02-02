
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
using namespace std;

//字典树(前缀树):哈希树的一种
//假设只有英文字母26个
//trie中的键通常是字符串，但也可以是其它的结构。trie的算法可以很容易地修改为处理其它结构的有序序列，比如一串数字或者形状的排列。比如，bitwise trie中的键是一串位元，可以用于表示整数或者内存地址

//1.根节点不包含字符，除根节点意外每个节点只包含一个字符。
//2.从根节点到某一个节点，路径上经过的字符连接起来，为该节点对应的字符串。
//3.每个节点的所有子节点包含的字符串不相同

//可以最大限度地减少无谓的字符串比较，故可以用于词频统计和大量字符串排序。
//没有冲突，自带排序(类似Radix Sort)
//trie是一个以空间换时间的算法。其每一个字符都可能包含至多字符集大小数目的指针

//可以进一步改成AC自动机，添加失配指针(Trie + KMP)，BFS即可
//暴力去跳fail的最坏时间复杂度是O(模式串长度 · 文本串长度)，可以 拓扑排序 建图优化

//以01串为例，可以根据需要 修改 字典大小 和 字符集的起始字符
const int SIZE = 26;
const int BASE = 'a';

inline int dice(int n){return rand() % n;}

//树节点,每个节点size = 4+1+SIZE*4个字节，内存开销很大
struct trieNode{
	int num;//记录途径的字符串个数，每次加入新字符串沿路就+1
	int isend;//是否是某个字符串的结尾,并统计结尾个数
	trieNode* fail;//失配指针, 用于AC自动机
	trieNode* child[SIZE];//Size个指针

	trieNode():num(1), isend(0), fail(NULL){//除了根节点，其余节点只要创建就说明有一个字符串经过了
		for(int i = 0; i < SIZE; i++)child[i] = NULL;
	}

};

//字典树(AC自动机)，单次插入、删除都是O(len)--O(1)的。以空间换时间，方便前缀匹配查询
//可以进一步修改为 哈希树 ，即多次哈希，每一层代表不同的哈希值，在叶子节点存储哈希结果
//如设置哈希模数2,3,5，则哈希树的第一层分支为mod2的余数，第二层分支为mod3的余数...直到最后一个模数。
//实验发现随机串下，串长度几乎不影响复杂度！！！一直是O(1)的
class Trie{
	int size;//节点个数
	int maxlen;//树中字符串的最大长度
	trieNode* root;//根节点
	

public:
	Trie():size(1), root(new trieNode){
		maxlen = -1;
	}
	~Trie(){ /*release(root);*/ }
	//递归删除有问题，会出现无穷递归，尚未修改
	void release(trieNode* node){//字符串过长的情况下会出现StackOverflow,可以考虑改成迭代写法。。。
		if(!node)return;
		for(int i = 0; i < SIZE; i++){
			if(node->child[i] && node->child[i] != node){
				release(node->child[i]);
				node->child[i] = NULL;//及时置空
			}
		}
		delete node;
		node = NULL;
	}
	//AC自动机，设置失配指针，采用BFS
	void buildFail(){
		queue<trieNode*> Q;
		for(int i = 0; i < SIZE; i++){//先处理第二层的指针
			if(root->child[i]){
				root->child[i]->fail = root;//指向根节点
				Q.push(root->child[i]);//入队
			}
		}
		while(!Q.empty()){//BFS
			trieNode* temp = Q.front(); Q.pop();
			for(int i = 0; i < SIZE; i++){
				if(temp->child[i]){//存在这个子节点
					temp->child[i]->fail = temp->fail->child[i];
					Q.push(temp->child[i]);
				}else{//不存在这个子节点
					temp->child[i] = temp->fail->child[i];//当前节点的这个子节点指向当前节点fail指针的这个子节点
				}
			}
		}
	}
	//AC自动机的查询
	//给定n个串加入字典，再给定文本串s, 判断s中包含字典中多少个串
	int acQuery(char* s){
		int len = strlen(s);
		trieNode* cur = root;
		int ans = 0;
		for(int i = 0; i < len; i++){
			int rank = s[i] - BASE;
			cur = cur->child[rank];//深入
			for(trieNode* temp = cur; temp && temp->isend; temp = temp->fail){//状态转移
				ans += temp->isend;
				temp->isend = 0;//加过了就不再加了
			}
		}
		return ans;
	}
	void insert(char* s){
		size++;
		int len = strlen(s);
		if(maxlen < len)maxlen = len;
		trieNode* cur = root;
		cur->num++;
		for(int i = 0; i < len; i++){
			int rank = s[i] - BASE;
			if(cur->child[rank]) cur->child[rank]->num++;
			else cur->child[rank] = new trieNode;
			cur = cur->child[rank];
		}
		cur->isend++;//只有到达isend才叫有该字符串，但注意isend不一定是叶子节点！！！
	}
	bool remove(char* str){
		int len = strlen(str);
		trieNode* cur = root;
		if(!find(str))return false;//确保有此字符串
		size--;
		for(int i = 0; i < len; i++){
			int rank = str[i] - BASE;
			cur->num --;
			if(cur->child[rank]){
				if(cur->child[rank]->num == 1){//释放以下的节点
					release(cur->child[rank]);//及时释放内存
					cur->child[rank] = NULL;
					break;
				}
				cur = cur->child[rank];
			}else break;
		}
		return true;
	}
	bool find(char* s){
		int len = strlen(s);
		trieNode* cur = root;
		for(int i = 0; i < len; i++){
			int rank = s[i] - BASE;
			if(cur->child[rank]){
				cur = cur->child[rank];
			}else return false;
		}
		if(cur->isend)return true;//只有到达isend才叫有该字符串，但注意isend不一定是叶子节点！！！
		else return false;
	}
	void findPrefix(char* s){//查找公共前缀
		printf("Find prefix of %s\n", s);
		int len = strlen(s), i;
		trieNode* cur = root;
		for(i = 0; i < len; i++){
			int rank = s[i] - BASE;
			if(cur->child[rank])cur = cur->child[rank];
		}
		//此时cur以下的所有节点就是以s为前缀的字符串,打印。也可以选择用栈保存，到达叶子节点后输出
		for(int i = 0; i < len; i++){putchar(' ');putchar(' ');putchar(s[i]);}
		_print_(cur, len);
	}
	//打印保存的所有字符串, 截止条件是物理上没有孩子，而不是isend
	void _print_(trieNode* node, int depth){
		bool flag = false;
		for(int i = 0; i < SIZE; i++){
			if(node->child[i]){
				putchar(' ');putchar(' ');putchar(BASE + i);
				_print_(node->child[i], depth+1);
				putchar('\r');//回退到行首
				for(int j = 0; j < depth; j++){putchar(' ');putchar(' ');putchar(' ');}//表示分支
				flag = true;
			}
		}
		if(!flag)putchar(10);
	}
	//打印字典树结构
	void print(){
		printf("Print Trie Structure...\n");
		_print_(root, 0);
		putchar('\r');for(int i = 0; i <= maxlen<<2; i++)putchar(' ');
		putchar('\n');
	}
};

//返回长度为n的随机字符串，字典为26个英文字母
char* randomString(int n){
	char* str = new char[n+1];
	for(int i = 0; i < n; i++)str[i] = dice(SIZE) + BASE;
	str[n] = '\0';
	return str;
}	

void randomTrieTest(int n, int len){//n个操作， 插入长度至多为len的字符串
	int count = 0;
	Trie trie;
	while(count++ < n){
		char* str = randomString(len/2+1 + dice(len/2+1));//生成长度至少为5的字符串
		switch(dice(3)){
			case 0://询问
				//printf("Find str:%s ... ", str);
				trie.find(str) ? printf("Find Success!\n") : printf("Find Failed!\n");
				break;
			case 1:
				//printf("Insert str:%s ... \n", str);
				trie.insert(str);
			 	break;
			default:
				//printf("Remove str:%s ... ", str);
				trie.remove(str) ? printf("Remove Success!\n") : printf("Remove Failed!\n");
				break;
		}
		//trie.print();
		//trie.findPrefix("011");
	}
}

void testTrie(int n, int m){
	srand((unsigned)time(NULL));
	//从本例可以看到随机生成的字符串匹配成功的概率几乎为0！
	clock_t start, finish;
	start = clock();
	randomTrieTest(n, m);
	finish = clock();
	//可以看到在统计意义上, 达到了稳定的O(1)复杂度
	printf("\n%d operations finished...tot time:%f s\n\n", \
		n, (double)(finish - start) / CLOCKS_PER_SEC);
}

int main(){
	//testTrie(1000, 100);
	//AC自动机 测试
	int n;
	scanf("%d", &n);
	char str[1000010];
	Trie trie;
	for(int i = 0; i < n; i++){
		scanf("%s", str);
		trie.insert(str);
	}
	trie.buildFail();
	scanf("%s", str);
	printf("%d\n", trie.acQuery(str));
	return 0;
}
