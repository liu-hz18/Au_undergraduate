
#ifndef _HUFFCHAR_H_
#define _HUFFCHAR_H_

//huffman×Ö·û
struct HuffChar{
	char ch;
	int weight;
	HuffChar(char c = '^', int w = 0):ch(c), weight(w){}
	bool operator<(HuffChar const& hc){
		return weight < hc.weight;
	}
	bool operator==(HuffChar const& hc){
		return weight == hc.weight;
	}
};

#endif
