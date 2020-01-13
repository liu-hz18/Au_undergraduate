#include<iostream>
#include<iomanip>
#include<string>
using namespace std;
//注意：sort,search,swap()等函数都在std的namespace里，自定义函数不要写这些名字，要么就只能std::cin,或者自己定义命名空间
class Birthday{
public:
	string year;
	string month;
	string day;
	//友元函数不是类的成员函数，不通过this指针访问数据，一些运算符重载需要友元函数是为了访问数据
	//但成员函数的运算符重载只能有一个参数，另一个参数是this指针，因此有些运算符不能作为成员函数
	friend istream& operator>>(istream& in,Birthday& dst){
		string temp;
		in>>temp;
		dst.year = temp.substr(0,4);
		dst.month = temp.substr(5,1);
		dst.day = temp.substr(7,1);
		return in;
	}
	friend ostream& operator<<(ostream& out,const Birthday& src){
		out<<src.year<<'-'<<src.month<<'-'<<src.day;
		return out;
	}
};

//不能定义为类的成员函数！！
class People{
	//string name;
	string num;
	string sex;
	Birthday birthday;//内嵌对象
	string id;
public:
	void setValue();
	void showValue()const;
	void show()const;
	string getnum()const;
	//友元函数，没有this参数
	friend bool operator==(People& src1,People& src2){
		return src1.id == src2.id;
	}
	//成员函数,默认左参数为this指针
	People& operator=(People& src){
	//	this->name =  src.name;
		//cout<<"operator="<<endl;
		this->num = src.num;
		this->sex = src.sex;
		this->birthday = src.birthday;
		this->id = src.id;
		return *this;
	}
};
string People::getnum()const{
	return num;
}
void People::setValue(){
	//cin>>name;
	cin>>num>>sex;
	cin>>birthday;
	cin>>id;
}
void People::showValue()const{
	if(id.substr(6,4) != birthday.year || id.substr(10,2) != birthday.month || id.substr(12,2) != birthday.day){
		cout<<"birthday mismatch!"<<endl;
	}
	//cout<<"Name: "<<name<<endl;
	cout<<"Number: "<<num<<endl;
	cout<<"Sex: "<<sex<<endl;
	cout<<"Birthday: "<<birthday<<endl;
	cout<<"ID: "<<id<<endl;
}
void People::show()const{
	cout<<num<<' '<<sex<<' '<<birthday<<' '<<id<<endl;
}
//使用函数模板 或 类模板
//算法实现与类型无关的时候，可以将参数抽象出来，得到函数模板
//函数模板调用时，编译器自动推导实际参数的类型（实例化），形式上调用一个函数模板 和 普通函数没有差别
//注意调用函数传参的时候，类型保持对应，
//使用模板特化进行编写
template<typename T>
inline void myswap(T& a,T& b){T temp = a;a = b;b = temp;}

//只有声明了模板函数，才能对其进行模板特化，不可直接进行特化！！
template <typename T> 
void mysort(T** array,const int& size){
	for(int i = 0;i < size;i ++)
		for(int j = 0;j < size;j ++)
			if((*array)[i] > (*array)[j])
				myswap((*array)[i],(*array)[j]);
}

template<typename T,typename T0>
int mysearch(T** array,const T0& val,const int& size){
	for(int i = 0;i < size;i ++){
		if((*array)[i] == val)return i;
	}
}

//模板特化
template<> void mysort<People>(People** peo,const int& size){
	//cout<<"mysort:people"<<endl;
	for(int i = 0;i < size;i++){
		for(int j = i + 1;j < size;j ++)
			if((*peo)[i].getnum() > (*peo)[j].getnum())
				myswap<People>((*peo)[i],(*peo)[j]);
	}
}
//注意多参数模板特化 形参列表要一一对应<People,string>
template<> int mysearch<People,string>(People** peo,const string& target,const int& size){
	for(int i = 0;i < size;i ++){
		if((*peo)[i].getnum() == target)return i;
	}
	return -1;
}

int main(){
	int num = 5;
	string target;
	People* people = new People[num];
	for(int i = 0;i < num;i ++){
		people[i].setValue();
	}
	cin>>target;
	mysort<People>(&people,num);
	for(int i = 0;i < num; i++){
		people[i].show();
	}
	int index = mysearch<People,string>(&people,target,num);
	if(index == -1)cout<<"null"<<endl;
	else people[index].show();
	delete[] people;
	/*
	People peo1,peo2;int num;
	cin>>num;
	if(num == 1){
		peo1.setValue();peo2.setValue();
		cout<<(peo1 == peo2);
	}else if(num == 2){
		peo1.setValue();
		peo2 = peo1;
		peo2.show();
	}*/
	//peo.showValue();
	return 0;
}
/*
重载操作符必须符合内建的模型，也就是说，重载操作符后的行为要与原来一致。
<< 操作符是一个二元操作符，它只接受二个参数，调用时的形式为：第一个参数<<第二个参数，如：
ostream& operator<< (ostream& os, const Point& pt);
的调用形式为： os<<pt （返回引用是为了可以连写：os << pt1 << pt2; )
而如果要将<<操作符定义为类的成员函数，那么你就只能给一个参数
（因为编译器展开类成员函数时将*this对象作为第一个参数），
如果你给两个参数，那最后<<操作就变成三元的了，
与原模型不符，所以编译器给出“overload.cpp:17: error: ‘std::ostream& Point::operator<<(std::ostream&, const Point&)’ must take exactly one argument”的错误。
如果你偏要定义成成员函数，并正确的只给出一个参数ostream&，那么最后的调用式就只能写成：
    pt << std::cout;
运算符重载一般具有以下原则：
（1）不可重载不存在的运算符，如重载**来表示平方等；
（2）重载后的运算符与原来的运算符优先级、结合性以及操作数数目相同，如双目运算符不能重载为单目；
（3）保留运算符本身的含义，如“+”号重载后应该保持其“求和”的自然含义；
（4）操作数中至少有一个为自定义类型，如重载运算符中参数都是int、double等类型是不允许的；

成员函数运算符重载时，运算符的左值为调用对象，右值为参数对象，举个例子，a,b均是类A的对象，
重载“+”实现a+b，可以将其认为是：a对象调用“+”函数，函数的参数为b对象；
而在事实上，a对象和b对象都是这个“+”函数的参数，只不过a对象被隐式调用，由this指针所绑定。
因此成员函数运算符重载的显式参数比实际运算参数少一个；
而在非成员函数运算符重载中，必须将操作数全部显式添加在参数列表中，
运算符左值为第一个参数，运算符右值为第二个参数。

this指针往往也是隐式存在的，因此在这里也可以省略掉this->；
非成员函数在进行运算符重载时，由于需要访问Stu类中的成员，
因此应当将该非成员函数声明为友元函数。因此，非成员函数运算符重载一般都是友元函数。

成员函数运算符重载时，运算符左值类型必须为所在类类型；而非成员函数运算符重载则不必。
“=”、“[]”、“->”和“（）”运算符之所以必须作为类成员函数进行重载，其原因是因为：
在成员函数重载时，会自动将this指针绑定到左值上，这样也就强制规定了运算符左值的类型
，如果不这样，而是通过非成员函数进行重载，那么很有可能会出现类似
“3=a”、“3[a]”、“3->a”以及“3(a)”的情况，单从运算符重载函数上说，这些似乎都是对的，但
是实际上这些在语法上都是错误的，是需要坚决避免的，为了避免出现这些情况，就
应当将这四种运算符重载限定在成员函数中。

*/