#include<iostream>
#include"link.h"
using namespace std;
int main()
{
	LinkedList<int> A;
	LinkedList<int> B;
	for (int i = 0; i < 5; i++)
	{
		int item;
		cin >> item;
		A.InsertRear(item);
	}
	for (int i = 0; i < 5; i++)
	{
		int item;
		cin >> item;
		B.InsertRear(item);
	}
	while(!B.EndOfList())
	{
		int item;
		item = B.Data();
		A.InsertRear(item);
		B.Next();
	}
	while (!A.EndOfList())
	{
		cout<< A.Data()<<" ";
		A.Next();
	}
	return 0;
}