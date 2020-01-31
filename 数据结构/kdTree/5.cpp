
//g++ 5.cpp temperature_lib.cpp -std=c++11 -O2 -Wall -o 5.exe
#include <stdio.h>
#include <stdlib.h>
#include "temperature.h"


inline int max(int& a,int& b){
	return a > b ? a : b;
}

inline int min(int& a,int& b){
	return a < b ? a : b;
}

int comparex(const void* a, const void* b);
int comparey(const void* a, const void* b);

//KD-Tree
//问询部分思路与 课程讲义kd-tree一节09-B5 相同，但加入了剪枝
class KDTree{
	
	int _size;
	int* tmin;//最大值
	int* tmax;//最小值
	int* leftbound;//左边界
	int* rightbound;//右边界
	int* ceiling;//上边界
	int* floor;//下边界
	int* rank;//原数组排序后的rank
	//rank数组在这里的作用是建树时对x或y进行排序，由于原始数据排序不能同时移动，所以对rank数组按不同规则排序可以达到比较好的效果
	
public:
	const int* x;//用于rank数组的排序
	const int* y;
	const int* t;

	int _x1, _y1, _x2, _y2;//用类变量标记查询量，简化了递归函数传参
	int _tmin, _tmax;

	KDTree(int n, const int* _x, const int* _y, const int* _t):_size(n<<2), tmin(new int[_size]), tmax(new int[_size]), leftbound(new int[_size]), rightbound(new int[_size]){
		ceiling = new int[_size];
		floor = new int[_size];
		rank = new int[n];
		for(int i = 0; i < n; i++)rank[i] = i;//初始化rank
		t = _t; x = _x; y = _y;
	}

	~KDTree(){
		delete[] tmin;
		delete[] tmax;
		delete[] leftbound;
		delete[] rightbound;
		delete[] ceiling;
		delete[] floor;
		delete[] rank;
	}
	
	//递归建树,flag为1就对x维排序，否则对y排序
	void _build(int root, int begin, int size, bool flag){
		if(flag){
			if(size > 1){
				floor[root] = y[rank[begin]];
				ceiling[root] = y[rank[begin + size - 1]];
				//排序后获得最大的x范围
				qsort(rank + begin, size, sizeof(int), comparex);
				leftbound[root] = x[rank[begin]];
				rightbound[root] = x[rank[begin + size - 1]];
				//递归建左右子树
				_build(root<<1, begin, size>>1, !flag);
				_build(root<<1|1, begin + (size>>1), size - (size>>1), !flag);
				//回溯时给温度赋值
				tmin[root] = min(tmin[root<<1], tmin[root<<1|1]);
				tmax[root] = max(tmax[root<<1], tmax[root<<1|1]);
			}else{
				//到达叶子节点
				leftbound[root] = rightbound[root] = x[rank[begin]];
				ceiling[root] = floor[root] = y[rank[begin]];
				tmin[root] = tmax[root] = t[rank[begin]];
			}
		}else{
			if(size > 1){
				leftbound[root] = x[rank[begin]];
				rightbound[root] = x[rank[begin + size - 1]];
				//排序后获得最大的y范围
				qsort(rank + begin, size, sizeof(int), comparey);
				floor[root] = y[rank[begin]];
				ceiling[root] = y[rank[begin + size - 1]];
				//递归建左右子树
				_build(root<<1, begin, size>>1, !flag);
				_build(root<<1|1, begin + (size>>1), size - (size>>1), !flag);
				//回溯时给温度赋值
				tmin[root] = min(tmin[root<<1], tmin[root<<1|1]);
				tmax[root] = max(tmax[root<<1], tmax[root<<1|1]);
			}else{
				//到达叶子节点
				leftbound[root] = rightbound[root] = x[rank[begin]];
				ceiling[root] = floor[root] = y[rank[begin]];
				tmin[root] = tmax[root] = t[rank[begin]];
			}
		}
	}
	//判断是否是叶子节点
	bool isleaf(int i){
		return leftbound[i] == rightbound[i] && ceiling[i] == floor[i];
	}
	//属于问询区间
	bool isinArea(int root){
		return leftbound[root] >= _x1 && rightbound[root] <= _x2 && ceiling[root] <= _y2 && floor[root] >= _y1;
	}
	//有交集
	bool hasCross(int root){
		if(leftbound[root] > _x2 || rightbound[root] < _x1)return false;
		if(ceiling[root] < _y1 || floor[root] > _y2)return false;
		return true;
	}

	//查询，递归
	void _query(int root){
		//完全落在查询区域中，赋值并返回
		if(isinArea(root)){
			if(_tmin > tmin[root])_tmin = tmin[root];
			if(_tmax < tmax[root])_tmax = tmax[root];
			return;
		}
		if(isleaf(root))return;
		//剪枝：如果有交集并且 最低温度小于当前标记值 或 最高温度大于当前标记值，说明有修改的必要。否则剪枝
		if(hasCross(root<<1) && (tmin[root<<1] < _tmin || tmax[root<<1] > _tmax))_query(root<<1);
		if(hasCross(root<<1|1) && (tmin[root<<1|1] < _tmin || tmax[root<<1|1] > _tmax))_query(root<<1|1);
	}

	//查询
	void query(int x1, int x2, int y1, int y2, int* __tmin, int* __tmax){
		_tmin = 2147483647;
		_tmax = -1;
		_x1 = x1, _x2 = x2, _y1 = y1, _y2 = y2;//初始化查询变量
		_query(1);
		//对类变量_tmin和_tmax赋值后给结果赋值
		if(_tmax == -1)_tmin = -1;//没有找到点
		*__tmin = _tmin;
		*__tmax = _tmax;
	}

	//建树
	void build(int n){
		//先建立根节点
		qsort(rank, n, sizeof(int), comparey);
		floor[1] = y[rank[0]];
		ceiling[1] = y[rank[n - 1]];
		qsort(rank, n, sizeof(int), comparex);
		leftbound[1] = x[rank[0]];
		rightbound[1] = x[rank[n - 1]];
		//建立子节点
		if(n > 1){
			_build(2, 0, n>>1, 0);
			_build(3, n>>1, n - (n>>1), 0);
			tmin[1] = min(tmin[2], tmin[3]);
			tmax[1] = max(tmax[2], tmax[3]);
		}else{
			tmin[1] = tmax[1] = t[rank[0]];
		}
	}

};

KDTree* kdtree;

//两个大范围的int相减会爆int，因此使用条件判断
inline int comparey(const void* a, const void* b){
	return kdtree->y[*(int*)a] < kdtree->y[*(int*)b] ? -1 : kdtree->y[*(int*)a] > kdtree->y[*(int*)b] ? 1 : 0;
}

inline int comparex(const void* a, const void* b){
	return kdtree->x[*(int*)a] < kdtree->x[*(int*)b] ? -1 : kdtree->x[*(int*)a] > kdtree->x[*(int*)b] ? 1 : 0;
}

void init(int n, const int *x, const int* y, const int *temp){
	kdtree = new KDTree(n, x, y, temp);
	kdtree->build(n);
}

void query(int x1, int x2, int y1, int y2, int* tmin, int *tmax){
	kdtree->query(x1, x2, y1, y2, tmin, tmax);
}
