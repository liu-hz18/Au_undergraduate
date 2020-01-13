#include <iostream>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//注意先保存再编译再运行；
 
int main() {
	int i,j,sum = 0;
	cin>>j;
	for(i = 1;i <= j;i ++){
		sum += i;
	} 
	cout<<sum;
	return 0;
}
