
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <vector>

using namespace std;

//����ʹ��C++11���ԣ�����
//B���ڵ�
template<typename T> struct BTNode{
	BTNode<T>* parent;//���ڵ�
	vector<T> key;//�ؼ�������
	vector< BTNode<T>* > child;//�����������䳤���ܱ�key��һ��
	BTNode(): parent(NULL){//BTNodeֻ����Ϊ���ڵ㴴�������ҳ�ʼʱ��0���ؼ����1���պ���ָ��
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

//B��
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
	int order()const{return _order;}//B������
	int size()const{return _size;}
	BTNode<T>*& root(){return _root;}
	bool empty()const{return !root;}
	BTNode<T>* search(const T& e);//����
	bool insert(const T& e);//����
	bool remove(const T& e);//ɾ��
};

template<typename T>
BTNode<T>* BTree<T>::search(const T& e){
	BTNode<T>* v = _root, _hot = NULL;//�Ӹ��ڵ����
	while(v){
		int r = v->key.search(e);//�ڵ�ǰ�ڵ��У��ҵ�������e�����ؼ���
		if(0 <= r && e == v->key[r])return v;//�ɹ����ڵ�ǰ�ڵ�������Ŀ��ؼ���
		_hot = v;
		v = v->child[r+1];//����ת���Ӧ������_hotָ���丸������ ����I/O�����ʱ��
	}
	return NULL;
}

template<typename T>
bool BTree<T>::remove(const T& e){
	BTNode<T>* v = search(e);
	if(!v)return false;//ȷ��Ŀ��ڵ㲻����
	int r = v->key.search(e);//ȷ��Ŀ��ؼ����ڽڵ�v�е���
	if(v->child[0]){//��v��Ҷ�ӣ���e�ĺ�̱�����ĳҶ�ڵ�
		BTNode<T>* u = v->child[r+1];//����������һֱ���󣬼���
		while(u->child[0])u = u->child[0];//�ҳ�e�ĺ��
		v->key[r] = u->key[0];//����֮ ����λ��
		v = u;
		r = 0;
	}//���ˣ�v��Ȼλ����ײ㣬�����е�r���ؼ�����Ǵ�ɾ����
	v->key.remove(r);
	v->child.remove(r+1);//ɾ��e���Լ����� �����ⲿ�ڵ�֮һ
	_size--;
	solveUnderFlow(v);//���б�Ҫ��������ת��ϲ�
	return true;
}

template <typename T> 
bool BTree<T>::insert ( const T& e ) { //���ؼ���e����B����
	BTNode<T>* v = search(e); 
	if(v) return false; //ȷ��Ŀ��ڵ㲻����
	int r = _hot->key.search(e); //�ڽڵ�_hot������ؼ��������в��Һ��ʵĲ���λ��
	_hot->key.insert(r + 1, e); //���¹ؼ��������Ӧ��λ��
	_hot->child.insert(r + 2, NULL); //����һ��������ָ��
	_size++; //����ȫ����ģ
	solveOverFlow(_hot); //���б�Ҫ����������
	return true; //����ɹ�
}

template <typename T> //�ؼ����������ڵ����磬�����ڵ���Ѵ���
void BTree<T>::solveOverFlow(BTNode<T>* v){
	if( _order >= v->child.size()) return; //�ݹ������ǰ�ڵ㲢δ����
	int s = _order / 2; //��㣨��ʱӦ��_order = key.size() = child.size() - 1��
	//ֻ��Ҫ�´���һ���½ڵ㣬��Ϊ�м�ڵ����ƣ��������ڵ�����һ����ԭ���Ľڵ㣬��һ���ֵ����´�����
	BTNode<T>* u = new BTNode<T>(); //ע�⣺�½ڵ�����һ���պ���
	for(int j = 0; j < _order - s - 1; j++) { //v�Ҳ�_order-s-1������ �� �ؼ��� ����Ϊ�Ҳ�ڵ�u
		u->child.insert(j, v->child.remove(s + 1) ); //����ƶ�Ч�ʵ�
		u->key.insert(j, v->key.remove(s + 1)); //�˲��ԿɸĽ�
	}
	u->child[_order - s - 1] = v->child.remove(s + 1);//�ƶ�v��ҵĺ���
	if(u->child[0]){//��u�ĺ����Ƿǿգ���
		for(int j = 0; j < _order - s; j++) //�����ǵĸ��ڵ�ͳһ
			u->child[j]->parent = u; //ָ��u
	}  
	BTNode<T>* p = v->parent; //v��ǰ�ĸ��ڵ�p
	if(!p){
		_root = p = new BTNode<T>();
		p->child[0] = v; 
		v->parent = p; 
	} //��p���򴴽�֮
	int r = 1 + p->key.search(v->key[0]); //p��ָ��u��ָ�����
	p->key.insert(r, v->key.remove(s)); //���ؼ�������
	p->child.insert(r + 1, u);  
	u->parent = p; //�½ڵ�u�븸�ڵ�p����
	solveOverflow(p); //����һ�㣬���б�Ҫ��������ѡ�������ݹ�O(logn)��
}

template<typename T>////�ؼ���ɾ�������ڵ����磬�����ڵ���ת��ϲ�����
void BTree<T>::solveUnderFlow(BTNode<T>* v){
	if((_order + 1) / 2 <= v->child.size())return;//�ݹ������ǰ�ڵ㲢δ����
	BTNode<T>* p = v->parent;
	if(!p){//�ݹ�����ѵ����ڵ㣬û�к��ӵ�����
		if(!v->key.size() && v->child[0]){//����Ϊ������v�Ѳ����ؼ��룬ȴ�У�Ψһ�ģ��ǿպ���
			_root = v->child[0];//����ڵ�ɱ�����
			_root->parent = NULL;
			v->child[0] = NULL;
			release(v);//���������ö�������
		}//�����߶Ƚ���һ��
		return;
	}
	int r = 0;
	while(p->child[r] != v)r++;
	//ȷ��v��p�ĵ�r�����ӡ�����ʱv���ܲ����ؼ��룬�ʲ���ͨ���ؼ������
	
	// ���1�������ֵܽ�ؼ���
	if(0 < r){//��v����p�ĵ�һ������
		BTNode<T>* ls = p->child[r - 1];//���ֵܱش���
		if((_order + 1) / 2 < ls->child.size()){//�����ֵ��㹻���֡�
			v->key.insert(0, p->key[r - 1]);//p���һ���ؼ����v����Ϊ��С�ؼ��룩
			p->key[r - 1] = ls->key.remove(ls->key.size() - 1);//ls�����ؼ���ת��p
			v->child.insert(0, ls->child.remove(ls->child.size() - 1));
			if(v->child[0]) v->child[0]->parent = v;//ͬʱls�����Ҳຢ�ӹ��̸�v,��Ϊv������ຢ��
			return;//���ˣ�ͨ����������ɵ�ǰ�㣨�Լ����в㣩�����紦��
		}
	}//���ˣ����ֵ�ҪôΪ�գ�Ҫô̫���ݡ�

	//���2�������ֵܽ�ؼ���
	if(p->child.size() - 1 > r){//��v����p�����һ������
		BTNode<T>* rs = p->child[r + 1]; //���ֵܱش���
		if((_order + 1) / 2 < rs->child.size()){//�����ֵ��㹻���֡�
			v->key.insert(v->key.size(), p->key[r]); //p���һ���ؼ����v����Ϊ���ؼ��룩
			p->key[r] = rs->key.remove(0);//ls����С�ؼ���ת��p
			v->child.insert(v->child.size(), rs->child.remove(0));
			if(v->child[v->child.size() - 1]){//ͬʱrs������ຢ�ӹ��̸�v
				v->child[v->child.size() - 1]->parent = v;//��Ϊv�����Ҳຢ��
			}
			return;//���ˣ�ͨ����������ɵ�ǰ�㣨�Լ����в㣩�����紦��
		}
	}//���ˣ����ֵ�ҪôΪ�գ�Ҫô̫���ݡ�
	
	//���3�������ֵ�ҪôΪ�գ���������ͬʱ����Ҫô��̫���ݡ������ϲ�
	if(0 < r){//�����ֵܺϲ�
		BTNode<T>* ls = p->child[r - 1];//���ֵܱش���
		//p�ĵ�r - 1���ؼ���ת��ls��v������p�ĵ�r������
		ls->key.insert(ls->key.size(), p->key.remove(r - 1));
		p->child.remove(r);
		ls->child.insert(ls->child.size(), v->child.remove(0));
		if(ls->child[ls->child.size() - 1]){//v������ຢ�ӹ��̸�ls�����Ҳຢ��
			ls->child[ls->child.size() - 1] = ls;
		}
		while( !v->key.empty() ){//vʣ��Ĺؼ���ͺ��ӣ�����ת��ls
			ls->key.insert(ls->key.size(), v->key.remove(0));
			ls->child.insert(ls->child.size(), v->child.remove(0));
			if(ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;
		}
		release(v);//�ͷ�v
	}
	else{//�����ֵܺϲ�
		BTNode<T>* rs = p->child[r + 1];//���ֶȱش���
		rs->key.insert(0, p->key.remove(r)); p->child.remove(r);
		//p�ĵ�r���ؼ���ת��rs��v������p�ĵ�r������
		rs->child.insert(0, v->child.remove(v->child.size() - 1 ));
		if(rs->child[0]){
			rs->child[0]->parent = rs; //v������ຢ�ӹ��̸�ls�����Ҳຢ��
		}
		while(!v->key.empty()){ //vʣ��Ĺؼ���ͺ��ӣ�����ת��rs
			rs->key.insert(0, v->key.remove(v->key.size() - 1));
			rs->child.insert(0, v->child.remove(v->child.size() - 1));
			if(rs->child[0]){
				rs->child[0]->parent = rs;
			}
		}
		release(v); //�ͷ�v
	}

	solveUnderFlow(p);//����һ�㣬���б�Ҫ��������ѡ�������ݹ�O(logn)��
	return;
}


//����n���������(���ң����룬ɾ��)��������ݷ�ΧΪ[0, m)
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
	//���Կ�����ͳ��������, �ﵽ���ȶ���nlogm���Ӷ�, ����splay���ĳ����Ƚϴ󣡣���
	printf("\n%d operations finished...tot time:%f...nlogm = %.2f\n\n", \
		n, (double)(finish - start) / CLOCKS_PER_SEC, double(n) * log(double(n)) / log(ord));
	return 0;
}
