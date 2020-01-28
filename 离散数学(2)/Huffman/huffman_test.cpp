
#include <iostream>
#include <stdio.h>
#include "huffman.h"


int main(){
	//注意此处要输入字符串长度
	int n;
	scanf("%d", &n);
	//也可以修改为不限制字符串长度的版本
	char* str = new char[n+1];
	scanf("%s", str);
	
	huffman* H = new huffman(str);
	H->initForest(H->statistic());
	H->generateTable(H->generateTree());
	string huffstr = H->gethuffcode();
	cout<<"huffman code:"<<huffstr<<endl;
	cout<<"length:"<<huffstr.length()<<endl;

	delete[] str;
	delete H;
	return 0;
}
