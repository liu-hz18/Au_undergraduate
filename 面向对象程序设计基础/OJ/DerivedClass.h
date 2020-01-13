#ifndef DERIVEDCLASS_H
#define DERIVEDCLASS_H
#include"BaseClass.h"
class DerivedClass:public BaseClass{
public:
	void fn1(){
		cout<<"DerivedClass fn1 run!\n";
	}
	void fn2(){
		cout<<"DerivedClass fn2 run!\n";
	}
};
#endif