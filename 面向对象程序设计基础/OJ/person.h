#ifndef PERSON_H
#define PERSON_H
#include<iostream>
using namespace std;
class Person{
	int hei;
	float wei;
public:
	Person();
	Person(const int& height,const float& weight);
	void showInfo();
};

#endif
