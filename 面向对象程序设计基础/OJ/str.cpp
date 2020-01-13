#include<iostream>
#include<string>
#include<cstring>
using namespace std;



int main(){
	string str1,str2;
	cin>>str1>>str2;
	cout<<str1 + str2<<endl;
	
	//构造函数内部的参数可以是string对象，也可以是char[]对象
	string str3(str1);//调用拷贝构造函数生成str3,内容相同
	cout<<str3<<endl;

	string str4(str1,3);//从第3位及其之后的位置拷贝给str4
	cout<<str4<<endl;

	string str5(5,'A');//生成一个字符串，均为A且长度为5
	cout<<str5<<endl;

	string str6(str1.begin(),str1.begin()+2);//将这个区间内的字符串拷贝给str6
	cout<<str6<<endl;


	/*
	int capacity()const;    //返回当前容量（即string中不必增加内存即可存放的元素个数）
	int max_size()const;    //返回string对象中可存放的最大字符串的长度
	int size()const;        //返回当前字符串的大小
	int length()const;       //返回当前字符串的长度
	bool empty()const;        //当前字符串是否为空
	void resize(int len,char c);  //把字符串当前大小置为len，多去少补，多出的字符c填充不足的部分
	*/

	/*
	注意找不到返回string::npos！！！
	//static const size_type npos = -1
	str.find( const basic_string &str, size_type index );  //返回str在字符串中第一次出现的位置（从index开始查找），如果没找到则返回string::npos
	str.find( const char *str, size_type index );  // 同上
	str.find( const char *str, size_type index, size_type length );  //返回str在字符串中第一次出现的位置（从index开始查找，长度为length），如果没找到就返回string::npos
	str.find( char ch, size_type index );  // 返回字符ch在字符串中第一次出现的位置（从index开始查找），如果没找到就返回string::npos
	//示例：
	if(str.find(str2) != string::npos){
		cout<<"find a substring\n"
	}
	*/

	/*
	str.insert(int p,const string &s);  //在p位置插入字符串s
	str.replace(int p, int n,const char *s); //删除从p开始的n个字符，然后在p处插入串s
	str.erase(int p, int n);  //删除p开始的n个字符，返回修改后的字符串
	str.substr(int pos = 0,int n = npos) const;  //返回pos开始的n个字符组成的字符串
	void swap(string &s2);    //交换当前字符串与s2的值
	str.append(const char *s);   //把字符串s连接到当前字符串结尾
	void push_back(char c)   //当前字符串尾部加一个字符c
	const char *data()const;   //返回一个非null终止的c字符数组，data():与c_str()类似，用于string转const char*其中它返回的数组是不以空字符终止,
	const char *c_str()const;  //返回一个以null终止的c字符串，即c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同,用于string转const char*
	*/

	return 0;
}