#include"Tree.h"

Tree::Tree(int a):ages(a){ }
void Tree::grow(int year){
	ages += year;
}
int Tree::age(){
	return ages;
}
