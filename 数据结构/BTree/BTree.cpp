
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <algorithm>

using namespace std;

inline int max(int a, int b){return a > b ? a : b;}
inline int min(int a, int b){return a > b ? b : a;}
inline void swap(int& a, int& b){int temp = a; a = b; b = temp;}
inline int dice(int n){return rand() % n;}

//尽量使用C++11特性！！！
//B树节点
template<typename T> struct BTNode{
	BTNode<T>* parent;//父节点
	vector<T> key;//关键码向量
	vector< BTNode<T>* > child;//孩子向量（其长度总比key多一）
	BTNode(): parent(NULL){//BTNode只能作为根节点创建，而且初始时有0个关键码和1个空孩子指针
		child.insert(0, NULL);
	}
	BTNode(T e, BTNode<T>* lc = NULL, BTNode<T>* rc = NULL){
		parent = NULL;
		key.insert(0, e);
		child.insert(0, lc);
		child.insert(0, rc);
		if(lc)lc->parent = this;
		if(rc)rc->parent = this;
	}
};

//B树
template<typename T> class BTree{
protected:
	int _size;
	int _order;
	BTNode<T>* _root;
	BTNode<T>* _hot;
	void solveOverFlow(BTNode<T>*);
	void solveUnderFlow(BTNode<T>*);

public:
	BTree(int order = 3): _order(order), _size(0){
		_root = new BTNode<T>();
	}
	~BTree(){
		//if(_root)release(_root);
	}
	int order()const{return _order;}//B树阶数
	int size()const{return _size;}
	BTNode<T>*& root(){return _root;}
	bool empty()const{return !root;}
	BTNode<T>* search(const T& e);//查找
	bool insert(const T& e);//插入
	bool remove(const T& e);//删除
};

template<typename T>
BTNode<T>* BTree<T>::search(const T& e){
	BTNode<T>* v = _root, _hot = NULL;//从根节点出发
	while(v){
		int r = v->key.search(e);//在当前节点中，找到不大于e的最大关键码
		if(0 <= r && e == v->key[r])return v;//成功：在当前节点中命中目标关键码
		_hot = v;
		v = v->child[r+1];//否则，转入对应子树（_hot指向其父）—— 需做I/O，最费时间
	}
	return NULL;
}

template<typename T>
bool BTree<T>::remove(const T& e){
	BTNode<T>* v = search(e);
	if(!v)return false;//确认目标节点不存在
	int r = v->key.search(e);//确定目标关键码在节点v中的秩
	if(v->child[0]){//若v非叶子，则e的后继必属于某叶节点
		BTNode<T>* u = v->child[r+1];//在右子树中一直向左，即可
		while(u->child[0])u = u->child[0];//找出e的后继
		v->key[r] = u->key[0];//并与之 交换位置
		v = u;
		r = 0;
	}//至此，v必然位于最底层，且其中第r个关键码就是待删除者
	v->key.remove(r);
	v->child.remove(r+1);//删除e，以及其下 两个外部节点之一
	_size--;
	solveUnderFlow(v);//如有必要，需做旋转或合并
	return true;
}

template <typename T> 
bool BTree<T>::insert ( const T& e ) { //将关键码e插入B树中
	BTNode<T>* v = search(e); 
	if(v) return false; //确认目标节点不存在
	int r = _hot->key.search(e); //在节点_hot的有序关键码向量中查找合适的插入位置
	_hot->key.insert(r + 1, e); //将新关键码插至对应的位置
	_hot->child.insert(r + 2, NULL); //创建一个空子树指针
	_size++; //更新全树规模
	solveOverFlow(_hot); //如有必要，需做分裂
	return true; //插入成功
}

template <typename T> //关键码插入后若节点上溢，则做节点分裂处理
void BTree<T>::solveOverFlow(BTNode<T>* v){
	if( _order >= v->child.size()) return; //递归基：当前节点并未上溢
	int s = _order / 2; //轴点（此时应有_order = key.size() = child.size() - 1）
	//只需要新创建一个新节点，因为中间节点上移，左右两节点其中一个是原来的节点，另一个兄弟是新创建的
	BTNode<T>* u = new BTNode<T>(); //注意：新节点已有一个空孩子
	for(int j = 0; j < _order - s - 1; j++) { //v右侧_order-s-1个孩子 及 关键码 分裂为右侧节点u
		u->child.insert(j, v->child.remove(s + 1) ); //逐个移动效率低
		u->key.insert(j, v->key.remove(s + 1)); //此策略可改进
	}
	u->child[_order - s - 1] = v->child.remove(s + 1);//移动v最靠右的孩子
	if(u->child[0]){//若u的孩子们非空，则
		for(int j = 0; j < _order - s; j++) //令它们的父节点统一
			u->child[j]->parent = u; //指向u
	}  
	BTNode<T>* p = v->parent; //v当前的父节点p
	if(!p){
		_root = p = new BTNode<T>();
		p->child[0] = v; 
		v->parent = p; 
	} //若p空则创建之
	int r = 1 + p->key.search(v->key[0]); //p中指向u的指针的秩
	p->key.insert(r, v->key.remove(s)); //轴点关键码上升
	p->child.insert(r + 1, u);  
	u->parent = p; //新节点u与父节点p互联
	solveOverflow(p); //上升一层，如有必要则继续分裂——至多递归O(logn)层
}

template<typename T>////关键码删除后若节点下溢，则做节点旋转或合并处理
void BTree<T>::solveUnderFlow(BTNode<T>* v){
	if((_order + 1) / 2 <= v->child.size())return;//递归基：当前节点并未下溢
	BTNode<T>* p = v->parent;
	if(!p){//递归基：已到根节点，没有孩子的下限
		if(!v->key.size() && v->child[0]){//若作为树根的v已不含关键码，却有（唯一的）非空孩子
			_root = v->child[0];//这个节点可被跳过
			_root->parent = NULL;
			v->child[0] = NULL;
			release(v);//并因不再有用而被销毁
		}//整树高度降低一层
		return;
	}
	int r = 0;
	while(p->child[r] != v)r++;
	//确定v是p的第r个孩子——此时v可能不含关键码，故不能通过关键码查找
	
	// 情况1：向左兄弟借关键码
	if(0 < r){//若v不是p的第一个孩子
		BTNode<T>* ls = p->child[r - 1];//左兄弟必存在
		if((_order + 1) / 2 < ls->child.size()){//若该兄弟足够“胖”
			v->key.insert(0, p->key[r - 1]);//p借出一个关键码给v（作为最小关键码）
			p->key[r - 1] = ls->key.remove(ls->key.size() - 1);//ls的最大关键码转入p
			v->child.insert(0, ls->child.remove(ls->child.size() - 1));
			if(v->child[0]) v->child[0]->parent = v;//同时ls的最右侧孩子过继给v,作为v的最左侧孩子
			return;//至此，通过右旋已完成当前层（以及所有层）的下溢处理
		}
	}//至此，左兄弟要么为空，要么太“瘦”

	//情况2：向右兄弟借关键码
	if(p->child.size() - 1 > r){//若v不是p的最后一个孩子
		BTNode<T>* rs = p->child[r + 1]; //右兄弟必存在
		if((_order + 1) / 2 < rs->child.size()){//若该兄弟足够“胖”
			v->key.insert(v->key.size(), p->key[r]); //p借出一个关键码给v（作为最大关键码）
			p->key[r] = rs->key.remove(0);//ls的最小关键码转入p
			v->child.insert(v->child.size(), rs->child.remove(0));
			if(v->child[v->child.size() - 1]){//同时rs的最左侧孩子过继给v
				v->child[v->child.size() - 1]->parent = v;//作为v的最右侧孩子
			}
			return;//至此，通过左旋已完成当前层（以及所有层）的下溢处理
		}
	}//至此，右兄弟要么为空，要么太“瘦”
	
	//情况3：左、右兄弟要么为空（但不可能同时），要么都太“瘦”——合并
	if(0 < r){//与左兄弟合并
		BTNode<T>* ls = p->child[r - 1];//左兄弟必存在
		//p的第r - 1个关键码转入ls，v不再是p的第r个孩子
		ls->key.insert(ls->key.size(), p->key.remove(r - 1));
		p->child.remove(r);
		ls->child.insert(ls->child.size(), v->child.remove(0));
		if(ls->child[ls->child.size() - 1]){//v的最左侧孩子过继给ls做最右侧孩子
			ls->child[ls->child.size() - 1] = ls;
		}
		while( !v->key.empty() ){//v剩余的关键码和孩子，依次转入ls
			ls->key.insert(ls->key.size(), v->key.remove(0));
			ls->child.insert(ls->child.size(), v->child.remove(0));
			if(ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
		}
		release(v);//释放v
	}
	else{//与右兄弟合并
		BTNode<T>* rs = p->child[r + 1];//右兄度必存在
		rs->key.insert(0, p->key.remove(r)); p->child.remove(r);
		//p的第r个关键码转入rs，v不再是p的第r个孩子
		rs->child.insert(0, v->child.remove(v->child.size() - 1 ));
		if(rs->child[0]){
			rs->child[0]->parent = rs; //v的最左侧孩子过继给ls做最右侧孩子
		}
		while(!v->key.empty()){ //v剩余的关键码和孩子，依次转入rs
			rs->key.insert(0, v->key.remove(v->key.size() - 1));
			rs->child.insert(0, v->child.remove(v->child.size() - 1));
			if(rs->child[0]){
				rs->child[0]->parent = rs;
			}
		}
		release(v); //释放v
	}

	solveUnderFlow(p);//上升一层，如有必要则继续分裂——至多递归O(logn)层
	return;
}


//进行n次随机操作(查找，插入，删除)，随机数据范围为[0, m)
void testBTreeRandom(int n, int m, int order){
	assert(order >= 3);
	BTree<int> bt(order);
	int count = 0;
	while(count++ < n){
		int data = dice(m);
		switch(dice(3)){
			case 0:
				printf("Searching %4d......", data);
				bt.search(data) ? printf("Found done with  %4d ", data) : printf("Data Not Found        ");
				break;
			case 1:
				printf("Inserting %4d......", data);
				bt.insert(data) ? printf("Insert done with %4d ", data) : printf("Data %d duplicate", data);
				break;
			default:
				printf("Removing  %4d......", data);
				bt.remove(data) ? printf("Remove done with %4d ", data) : printf("Data Not Found        ");
				break;
		}
		printf("...... size:%d\n", bt.size());
	}
}


int main(){
	srand((unsigned)time(NULL));
	int n = 30, m = 100, ord = 3;
	clock_t start, finish;
	start = clock();
	testBTreeRandom(n, m, ord);
	finish = clock();
	//可以看到在统计意义上, 达到了稳定的nlogm复杂度, 但是splay树的常数比较大！！！
	printf("\n%d operations finished...tot time:%f...nlogm = %.2f\n\n", \
		n, (double)(finish - start) / CLOCKS_PER_SEC, double(n) * log(double(n)) / log(ord));
	return 0;
}
