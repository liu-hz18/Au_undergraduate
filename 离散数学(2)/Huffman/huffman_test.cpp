
#include <iostream>
#include <stdio.h>
#include "huffman.h"


int main(){
	//ע��˴�Ҫ�����ַ�������
	int n;
	scanf("%d", &n);
	//Ҳ�����޸�Ϊ�������ַ������ȵİ汾
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
