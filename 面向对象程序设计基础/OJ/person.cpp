#include"person.h"
void Person::showInfo(){
	printf("%d,%.2f",hei,wei);
}
Person::Person(){ }
Person::Person(const int& height,const float& weight){
	hei = height;
	wei = weight;
}