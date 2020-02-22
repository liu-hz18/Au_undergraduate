
#include <iostream>
#include <stdio.h>
#include "huffman.h"

//支持所有可打印字符(ASCII:20-60),不支持空格的转换，如有空格请用下划线_代替

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
	auto huffstr = H->gethuffcode();
	cout<<"huffman code:"<<huffstr<<endl;
	cout<<"length:"<<huffstr.length()<<endl;

	delete[] str;
	delete H;
	return 0;
}
