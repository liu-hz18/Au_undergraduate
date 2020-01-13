
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

inline void swap(int &a,int &b){
	int temp = a;a = b;b = temp;
}
//自己定义com标准，其排列与return语句中顺序相同,形参和排序的内容相同！！！
bool compare(vector<int> a,vector<int> b){//注意一维数组依然是vector,不可以认为 是指针
	//return a[0] < b[0];//此处是向量首元素比较，不是迭代器的比较，所以不是a.begin()<b.begin()!!!
	return *(a.begin()) < *(b.begin());//或者采用这种方式进行！！！需要对迭代器解引用！！！
}
//vector容器中的内存都是动态的
int main(){
	int N;
	//第二种方式开辟二维数组,不需要进行内存释放
	/*
	vector< vector<int> > array(num);
	for(int i = 0;i < N;i++ ){
    	array[i].resize(N);//resize 改变当前使用数据的大小，如果它比当前使用的大，者填充默认值 
	}
	*/
	//第三种方式开辟 二维向量
	cin>>N;
	vector< vector<int> > array( N , vector<int>(N) );//一行代码即可定义，默认为 0
	//使用index遍历数组
	for(int i = 0;i < array.size();i++){
		for(int j = 0;j < array[i].size();j++){
			cin>>array[i][j];
		}
	}
	//对数组行内排序
	//调用.begin()返回的是迭代器！！！
	
	for(vector< vector<int> >::iterator iter = array.begin();iter!=array.end();iter++){
		sort((*iter).begin(),(*iter).end(),compare);//排序前20个，只需要进行sort((*iter).begin(),(*iter).begin()+20);
	}
	
	//排序内容应与排序标准相一致，本例对于二维数组中每一行作为整体排序，则compare函数要针对一维数组划分标准
	sort(array.begin(),array.end(),compare);
	
	//使用迭代器 遍历二维数组！！推荐！！！对于所有容器都有迭代器！！但是不一定都支持下标访问！！！
	for(vector< vector<int> >::iterator iter = array.begin();iter != array.end();iter++,putchar(10)){//注意判断条件是不等于末尾！！！不是小于！！！
		for(vector<int>::iterator it = (*iter).begin();it != (*iter).end() ; it++){//注意*iter加括号！！！
			cout<<*it<<" ";
		}
	}

	return 0;
}
/*
//使用vector容器进行处理(方式一)
int main(){
	//括号之间要有个空格，不然无法区分输入流运算符！！！
	vector< vector<int> > array;
	vector<int> v;//临时存放一维数组
	int num,temp;
	cin>>num;
	array.clear();//清空数组内容
	for(int i = 0;i < num;i ++){
		v.clear();
		for(int j = 0;j < num;j ++){
			cin>>temp;
			v.push_back(temp);
		}
		array.push_back(v);
	}
	for(int i = 0;i < num; i++){
		for(int j = 0;j <= i ;j ++){
			swap(array[i][j],array[j][i]);
		}
	}
	for(int i = 0;i < num; i++,putchar(10)){
		for(int j = 0;j <= num ;j ++){
			cout<<array[i][j]<<' ';
		}
	}
	return 0;
}
*/


/*
//使用面向对象方法
class Matrix{
	int n;
	int **pm;
public:
	Matrix();
	~Matrix();
	void show();
	void trans();
	void swap(int&a,int&b);
};
//注意动态数组的申请和释放！！！
Matrix::Matrix(){
	cin>>n;
	pm = new int* [n];
	for(int i = 0;i < n;i ++){
		pm[i] = new int [n];
	}
	for(int i = 0;i < n;i ++){
		for(int j = 0;j < n;j ++){
			cin>>pm[i][j];
		}
	}
}
//注意析构函数的内存释放！！！
Matrix::~Matrix(){
	for(int i = 0;i < n;i ++){
		delete[] pm[i];
	}
	delete pm;
}
void Matrix::show(){
	int i,j;
	for(i = 0; i < n;i ++,putchar(10)){
		for(j = 0;j < n;j ++)
			cout<<pm[i][j]<<' ';
	}
}
//内联函数修饰在函数定义的时候！！！
inline void Matrix::swap(int& a,int& b){
	int temp;
	temp = a;a = b;b = temp;
}
void Matrix::trans(){
	int i,j;
	for(i = 0;i < n;i ++){
		for(j = 0;j <= i ;j ++){
			swap(pm[i][j],pm[j][i]);
		}
	}
}
int main(){
	Matrix ma;
	ma.trans();
	ma.show();
	return 0;
}
*/