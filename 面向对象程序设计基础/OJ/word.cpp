#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
class Ch{
	char ch;
	int num;
public:
	Ch(char ch,int num);
	void show();
	void add();
	char getch();
};
Ch::Ch(char c,int n):ch(c),num(n){ }
void Ch::show(){cout<<ch<<' '<<num<<'\n';}
void Ch::add(){num++;}
char Ch::getch(){return ch;}

//自定义类的判断函数
class Find{
public:
	char cha;
	Find(char c):cha(c){ }
	bool operator()(Ch p){//函数运算符()重载，使得对象看上去像一个函数，但这不是构造函数！！也称函数对象
		return (cha == p.getch());
	}
};
bool compare(Ch &a,Ch &b){ return a.getch() < b.getch(); }
int main(){
	string str;
	getline(cin,str);
	vector<Ch> array;
	vector<Ch>::iterator it;
	str.erase(remove(str.begin(),str.end(),' '),str.end());//删除字符串中的所有空格。
	//c.erase()从c中删除迭代器p指定的元素，p必须指向c中的一个真实元素，不能等于c.end()
	//（1）string& erase ( size_t pos = 0, size_t n = npos );删除从pos开始的n个字符，比如erase(0,1)就是删除第一个字符
	//（2）iterator erase ( iterator position );删除position处的一个字符(position是个string类型的迭代器)
	//（3）iterator erase ( iterator first, iterator last );删除从first到last之间的字符（first和last都是迭代器）
	//remove函数将str中所有搜索字符向前覆盖（平移字符串）最终返回新字符串尾部的迭代器it1，此时不符合要求的字符全部位于it1和str.end()之间，用erase把他们删除！
	for(string::iterator iter = str.begin();iter != str.end();iter ++){
		Find find(*iter);//调用构造函数初始化
		it = find_if(array.begin(),array.end(),find);
		//第三个参数是一个函数对象find，find_if函数自动把array中的元素作为参数传入find()中，实际上等于find.operator()(*iter);
		//泛型算法比循环算法的效率高
		//find()函数只能处理简单类型的内容，也就是缺省类型，如果你想用一个自定义类型的数据作为查找依据则会出错！
		if(it == array.end()){
			Ch temp((*iter),1);
			array.push_back(temp);
		}else{
			(*it).add();
		}
	}
	sort(array.begin(),array.end(),compare);
	for(it = array.begin();it != array.end();it ++){
		(*it).show();
	}
	return 0;
}
