
#pragma once
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <queue>
#include <set>
#include <vector>
#include <algorithm>
#include "mydll.h"
#include "definition.h"

using namespace std;

int tw_position[9][2] = { 0 };		//塔位置
vector<pair<int, int>> my_soldier;	//己方士兵信息,第一项为索引，第二项为id
int my_so_num = 0;					//己方士兵总数

vector<TowerInfo> my_tower;			//己方兵塔信息
int main_tow,						//主塔
sec_tow,							//副塔
mid_tow = 8;

int my_id;							//自己id
vector<int> defend_id;				//防守副塔士兵id
vector<int> mid_id;					//中塔任务士兵id

struct Commandinfo
{
	int so_produce_sequence[50];		//士兵生产顺序
	int res[7];							//各兵种消耗资源数
	int pop[7];							//各兵种消耗人口数
	int tow_upg_res[3];					//升级塔需要资源数
	int towers[4][2];					//各势力的基本塔
}commandinfo;

enum Soldiermission
{
	NoMission = 0,
	AttackMid = 1,
};

bool can_produce = true;			//本回合能否造兵

bool have_sec_tow = false;
bool occupy_secondary_tower_on = false;
bool middle_tower_on = false;
bool place_soldier_mid1_on = false;
bool place_soldier_mid0_on = false;
bool mobile_wolfare_on = false;


/**********************************基础算法*************************************/


/**********************************基本命令*************************************/
//生产士兵(士兵类型定义见defini.h)
void c_produce_soldier(Info& info, int tower_id, int soldierType);
//移动士兵
void c_move_soldier(Info& info, int so_id, int direction, int distance);
//升级塔
void c_upgrade(Info& info, int towerId);
//攻击(塔或兵)
void c_attack(Info& info, int so_id, int x, int y);


/*******************************操作·判断**********************************/

//士兵移动至某点
void soldier_march_to(Info& info, pair<int, int> so_info, int tar_x, int tar_y);

//判断士兵在某范围中(>= <=)
bool soldier_at(Info& info, int so_index, int x_L, int y_D, int x_R, int y_U);

//判断士兵在某点
bool soldier_at(Info& info, int so_index, int x, int y);

//搜索某位置周围某范围内特定类型格子(仅返回第一个搜索结果)
bool search_type_around(Info& info, TOccupiedType type, int x, int y, int range, pair<int, int>& p);

//根据士兵id搜索信息
bool get_soldier_by_id(Info& info, int id, TSoldier*& res);

//根据id查找下标
bool get_index_by_id(Info& info, int so_id, int& index);

/*************************************事件****************************************/




//************************************************************

//路径链表
typedef struct Node
{
	int x, y;//坐标
	int g;//起始点到当前点实际代价
	int h;//当前节点到目标节点最佳路径的估计代价
	int f;//估计值 f = g + h
	Node* father;//父节点

	//构造函数重载，不存在默认构造函数
	Node()	{	};
	~Node()	{	};

	Node(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->g = 0;
		this->h = 0;
		this->f = 0;
		this->father = NULL;
	}
	Node(int x, int y, Node* father)
	{
		this->x = x;
		this->y = y;
		this->g = 0;
		this->h = 0;
		this->f = 0;
		this->father = father;
	}

}Node;

//Astar类
class Astar{
public:
	Astar();
	~Astar();
	Node* search(Info& info, Node* startPos, Node* endPos, int movedis);
	void checkPoit(int x, int y, Node* father, int g);
	void NextStep(Info& info, Node* currentPoint);
	int isContains(vector<Node*>* Nodelist, int x, int y);
	void countGHF(Node* sNode, Node* eNode, int g);
	static bool compare(Node* n1, Node* n2);
	bool unWalk(int x, int y);
	void printPath(Node* current);
	void printMap();
	void CreateMap(Info& info, int x, int y, int movedis);//创建地图
	vector<Node*> openList;//开放列表
	vector<Node*> closeList;//封闭列表，存放不需要再进行考虑的节点
	Node *startPos;
	Node *endPos;
	//估价函数的估价放大系数
private:
	static const int WeightW = 10;// 正方向消耗
	static const int row = 50;//地图行数
	static const int col = 50;//地图列数
};


//地形map,用于存放视野内地形信息，预设为0,最大11*11
int temp_map[70][70];
TLandForm LF_map[70][70];
int countNode(Node*current);


//************************************************************