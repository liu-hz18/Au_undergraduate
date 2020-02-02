
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//�ֵ���(ǰ׺��):��ϣ����һ��
//����ֻ��Ӣ����ĸ26��
//trie�еļ�ͨ�����ַ�������Ҳ�����������Ľṹ��trie���㷨���Ժ����׵��޸�Ϊ���������ṹ���������У�����һ�����ֻ�����״�����С����磬bitwise trie�еļ���һ��λԪ���������ڱ�ʾ���������ڴ��ַ

//1.���ڵ㲻�����ַ��������ڵ�����ÿ���ڵ�ֻ����һ���ַ���
//2.�Ӹ��ڵ㵽ĳһ���ڵ㣬·���Ͼ������ַ�����������Ϊ�ýڵ��Ӧ���ַ�����
//3.ÿ���ڵ�������ӽڵ�������ַ�������ͬ

//��������޶ȵؼ�����ν���ַ����Ƚϣ��ʿ������ڴ�Ƶͳ�ƺʹ����ַ�������
//û�г�ͻ���Դ�����(����Radix Sort)
//trie��һ���Կռ任ʱ����㷨����ÿһ���ַ������ܰ��������ַ�����С��Ŀ��ָ��

//��01��Ϊ�������Ը�����Ҫ �޸� �ֵ��С �� �ַ�������ʼ�ַ�
const int SIZE = 2;
const int BASE = '0';

inline int dice(int n){return rand() % n;}

//���ڵ�,ÿ���ڵ�size = 4+1+SIZE*4���ֽڣ��ڴ濪���ܴ�
struct trieNode{
	int num;//��¼;�����ַ���������ÿ�μ������ַ�����·��+1
	bool isend;//�Ƿ���ĳ���ַ����Ľ�β
	trieNode* child[SIZE];//Size��ָ��

	trieNode():num(1), isend(false){//���˸��ڵ㣬����ڵ�ֻҪ������˵����һ���ַ���������
		for(int i = 0; i < SIZE; i++)child[i] = NULL;
	}

};

//�ֵ��������β��롢ɾ������O(len)--O(1)�ġ��Կռ任ʱ�䣬����ǰ׺ƥ���ѯ
//���Խ�һ���޸�Ϊ ��ϣ�� ������ι�ϣ��ÿһ�����ͬ�Ĺ�ϣֵ����Ҷ�ӽڵ�洢��ϣ���
//�����ù�ϣģ��2,3,5�����ϣ���ĵ�һ���֧Ϊmod2���������ڶ����֧Ϊmod3������...ֱ�����һ��ģ����
//ʵ�鷢��������£������ȼ�����Ӱ�츴�Ӷȣ�����һֱ��O(1)��
class Trie{
	int size;//�ڵ����
	int maxlen;//�����ַ�������󳤶�
	trieNode* root;//���ڵ�

public:
	Trie():size(1), root(new trieNode){
		maxlen = -1;
	}
	~Trie(){ release(root); }
	void release(trieNode* node){//�ַ�������������»����StackOverflow,���Կ��Ǹĳɵ���д��������
		for(int i = 0; i < SIZE; i++){
			if(node->child[i])release(node->child[i]);
		}
		delete node;
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
			cur->isend = false;
			cur = cur->child[rank];
		}
		cur->isend = true;//ֻ�е���isend�Ž��и��ַ�������ע��isend��һ����Ҷ�ӽڵ㣡����
	}
	bool remove(char* str){
		int len = strlen(str);
		trieNode* cur = root;
		if(!find(str))return false;//ȷ���д��ַ���
		size--;
		for(int i = 0; i < len; i++){
			int rank = str[i] - BASE;
			cur->num --;
			if(cur->child[rank]){
				if(cur->child[rank]->num == 1){//�ͷ����µĽڵ�
					release(cur->child[rank]);//��ʱ�ͷ��ڴ�
					cur->isend = true;
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
		if(cur->isend)return true;//ֻ�е���isend�Ž��и��ַ�������ע��isend��һ����Ҷ�ӽڵ㣡����
		else return false;
	}
	void findPrefix(char* s){//���ҹ���ǰ׺
		printf("Find prefix of %s\n", s);
		int len = strlen(s), i;
		trieNode* cur = root;
		for(i = 0; i < len; i++){
			int rank = s[i] - BASE;
			if(cur->child[rank])cur = cur->child[rank];
		}
		//��ʱcur���µ����нڵ������sΪǰ׺���ַ���,��ӡ��Ҳ����ѡ����ջ���棬����Ҷ�ӽڵ�����
		for(int i = 0; i < len; i++){putchar(' ');putchar(' ');putchar(s[i]);}
		_print_(cur, len);
	}
	//��ӡ����������ַ���, ��ֹ������������û�к��ӣ�������isend
	void _print_(trieNode* node, int depth){
		bool flag = false;
		for(int i = 0; i < SIZE; i++){
			if(node->child[i]){
				putchar(' ');putchar(' ');putchar(BASE + i);
				_print_(node->child[i], depth+1);
				putchar('\r');//���˵�����
				for(int j = 0; j < depth; j++){putchar(' ');putchar(' ');putchar(' ');}//��ʾ��֧
				flag = true;
			}
		}
		if(!flag)putchar(10);
	}
	//��ӡ�ֵ����ṹ
	void print(){
		printf("Print Trie Structure...\n");
		_print_(root, 0);
		putchar('\r');for(int i = 0; i <= maxlen<<2; i++)putchar(' ');
		putchar('\n');
	}
};

//���س���Ϊn������ַ������ֵ�Ϊ26��Ӣ����ĸ
char* randomString(int n){
	char* str = new char[n+1];
	for(int i = 0; i < n; i++)str[i] = dice(SIZE) + BASE;
	str[n] = '\0';
	return str;
}	

void randomTrieTest(int n, int len){//n�������� ���볤������Ϊlen���ַ���
	int count = 0;
	Trie trie;
	while(count++ < n){
		char* str = randomString(len/2+1 + dice(len/2+1));//���ɳ�������Ϊ5���ַ���
		switch(dice(3)){
			case 0://ѯ��
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

int main(){
	srand((unsigned)time(NULL));
	int n = 10000, m = 100;
	//�ӱ������Կ���������ɵ��ַ���ƥ��ɹ��ĸ��ʼ���Ϊ0��
	clock_t start, finish;
	start = clock();
	randomTrieTest(n, m);
	finish = clock();
	//���Կ�����ͳ��������, �ﵽ���ȶ���O(1)���Ӷ�
	printf("\n%d operations finished...tot time:%f s\n\n", \
		n, (double)(finish - start) / CLOCKS_PER_SEC);
	return 0;
}
