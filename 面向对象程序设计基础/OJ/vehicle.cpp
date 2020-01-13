
//虚基类主要解决多重继承中的基类多次拷贝问题
//否则基类就被拷贝了两次，构造函数和析构函数也会执行两次
#include<iostream>
using namespace std;
class Vehicle{
public:
	Vehicle(){cout<<"vehicle Construct\n";}
	~Vehicle(){cout<<"vehicle Destroy\n";}
};
class Bicycle:virtual public Vehicle{
public:
	Bicycle(){cout<<"bicycle Construct\n";}
	~Bicycle(){cout<<"bicycle Destroy\n";}
};
class Motorcar:virtual public Vehicle{
public:
	Motorcar(){cout<<"motorcar Construct\n";}
	~Motorcar(){cout<<"motorcar Destroy\n";}
};
//多重继承
//多重继承会有多个虚函数表，几重继承，就会有几个虚函数表。这些表按照派生的顺序依次排列
//如果子类改写了父类的虚函数，那么就会用子类自己的虚函数覆盖虚函数表的相应的位置，如果子类有新的虚函数，那么就添加到  第一个虚函数表(依继承时父类顺序而定）的末尾
//弊端：容易造成二义性（两个父类都有a)和数据冗余（虚继承可解决）
class Motorcycle:public Bicycle,public Motorcar{
public:
	Motorcycle(){cout<<"motorcycle Construct\n";}
	~Motorcycle(){cout<<"motorcycle Destroy\n";}
};
int main(){
	Motorcycle motorcycle;
	return 0;
}
/*当在多条继承路径上有一个公共的基类,在这些路径中的某几条汇合处，
这个公共的基类就会产生多个实例(或多个副本)，若只想保存这个基类的一个实例，
可以将这个公共基类说明为虚基类。
在继承中产生歧义的原因有可能是继承类继承了基类多次，子类Motorcycle最后会接受分别来自Motorcar和Bicycle的同一个或多个相同拷贝，
从而产生了多个拷贝,即不止一次的通过多个路径继承类在内存中创建了vehicle基类成员的多份拷贝。
而这些是Motorcar和Bicycle从父类继承而来，所以Motorcycle类该继承Motorcar还是Bocycle传下来的还是都接受呢？
这样就产生歧义，虚基类的基本原则是在内存中只有基类成员的一份拷贝。
这样，通过把基类继承声明为虚拟的，就只能继承基类的一份拷贝，从而消除歧义。
构造函数次序：
(1)虚基类的构造函数在非虚基类之前调用;
(2)若同一层次中包含多个虚基类，这些虚基类的构造函数按它们说明的次序调用;
(3)若虚基类由非虚基类派生而来，则仍先调用基类构造函数，再调用派生类的构造函数。
*/
/*
虚函数：
晚绑定(基类中的虚函数)只对指针和引用有效,否则为早绑定
对于被派生类重新定义的成员函数，若它在基类中被声明为虚函数，
则通过基类指针或引用调用该成员函数时，编译器将根据所指（或引用）对象的实际类型
决定是调用基类中的函数，还是调用派生类重写的函数。
若某成员函数在基类中声明为虚函数，当派生类重写覆盖(定义同名同参数函数)它时，
无论是否声明为虚函数，该成员函数都仍然是虚函数。
*/
