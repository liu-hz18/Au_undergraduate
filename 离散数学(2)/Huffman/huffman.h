
#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "bitmap.h"
#include "minHeap.h"
#include "binTree.h"
#include "huffChar.h"

#define HuffTree BinTree<HuffChar>
#define HuffNode BinNode<HuffChar>
#define CHARNUM (0x80 - 0x20) //仅统计可打印字符

//堆维护，O(nlogn)
class huffman{
	char* str;
	MinHeap< HuffTree* >* forest;
	hash_map<char, string> charmap;
	int _size;//字符种类数
	int _len;//输入字符串的长度

public:
	huffman(char *s):_size(0), _len(strlen(s)){
		str = new char[_len+1];
		strcpy(str, s);
		forest = new MinHeap< HuffTree* >(CHARNUM);
	}
	~huffman(){
		delete forest;
		delete str;
	}
	int* statistic(){
		int* freq = new int[CHARNUM];
		memset(freq, 0, CHARNUM * sizeof(int));
		for(int i = 0; i < _len; i++){
			if(str[i] >= 0x20)freq[str[i] - 0x20]++;
		}
		return freq;
	}
	void initForest(int* freq){
		for(int i = 0; i < CHARNUM; i++){
			if(freq[i] > 0){
				forest->push(new HuffTree(HuffChar(0x20 + i, freq[i])));
			}
		}
	}
	//由森林生成树
	HuffTree* generateTree(){
		while(1 < forest->size()){
			HuffTree* t1 = forest->pop();
			HuffTree* t2 = forest->pop();
			HuffTree* S = new HuffTree(HuffChar('^', (t1->root()->data).weight + (t2->root()->data).weight));
			S->attachAsLT(t1);
			S->attachAsRT(t2);
			forest->push(S);
		}
		return forest->top();
	}
	//递归生成某一字符的编码
	void generateCode(Bitmap* code, int length, HuffNode* node){
		if(node->isleaf()){
			charmap[node->data.ch] = code->bit2string(length);
			return;
		}
		if(node->lc){
			code->clear(length);
			generateCode(code, length + 1, node->lc);
		}
		if(node->rc){
			code->set(length);
			generateCode(code, length + 1, node->rc);
		}
	}
	//生成hash表(char:huffmancode)
	void generateTable(HuffTree* tree){
		Bitmap* code = new Bitmap(tree->root()->height + 1);
		generateCode(code, 0, tree->root());
	}
	string gethuffcode(){
		string huffstr;
		for(int i = 0; i < _len; i++){
			huffstr += charmap[str[i]];
		}
		return huffstr;
	}
};

#endif
