
#ifndef _BITMAP_H_
#define _BITMAP_H_

#include "util.h"

//位图
//Bitmap数据结构比较基础，参考了课程讲义02-XA1的代码
class Bitmap{
	int _len;
	char *m;

public:
	Bitmap(int n):_len(n){
		m = new char[(_len+7)>>3];
	}
	~Bitmap(){
		delete[] m;
	}
	void set(int k){
		m[k>>3] |= (0x80 >> (k & 0x07));
	}
	void clear(int k){
		m[k>>3] &= ~(0x80 >> (k & 0x07));
	}
	bool get(int k){
		return bool(m[k>>3] & (0x80 >> (k & 0x07)));
	}
	void init(int len){
		memset(m, 0, (len+7)>>3);
	}
	string bit2string(int len){
		char* str = new char[len];
		for(int i = 0; i < len; i++){
			str[i] = (char)(get(i) + '0');
		}
		str[len] = '\0';
		return string(str);
	}
};

#endif
