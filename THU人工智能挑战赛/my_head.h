
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

int tw_position[9][2] = { 0 };		//��λ��
vector<pair<int, int>> my_soldier;	//����ʿ����Ϣ,��һ��Ϊ�������ڶ���Ϊid
int my_so_num = 0;					//����ʿ������

vector<TowerInfo> my_tower;			//����������Ϣ
int main_tow,						//����
sec_tow,							//����
mid_tow = 8;

int my_id;							//�Լ�id
vector<int> defend_id;				//���ظ���ʿ��id
vector<int> mid_id;					//��������ʿ��id

struct Commandinfo
{
	int so_produce_sequence[50];		//ʿ������˳��
	int res[7];							//������������Դ��
	int pop[7];							//�����������˿���
	int tow_upg_res[3];					//��������Ҫ��Դ��
	int towers[4][2];					//�������Ļ�����
}commandinfo;

enum Soldiermission
{
	NoMission = 0,
	AttackMid = 1,
};

bool can_produce = true;			//���غ��ܷ����

bool have_sec_tow = false;
bool occupy_secondary_tower_on = false;
bool middle_tower_on = false;
bool place_soldier_mid1_on = false;
bool place_soldier_mid0_on = false;
bool mobile_wolfare_on = false;


/**********************************�����㷨*************************************/


/**********************************��������*************************************/
//����ʿ��(ʿ�����Ͷ����defini.h)
void c_produce_soldier(Info& info, int tower_id, int soldierType);
//�ƶ�ʿ��
void c_move_soldier(Info& info, int so_id, int direction, int distance);
//������
void c_upgrade(Info& info, int towerId);
//����(�����)
void c_attack(Info& info, int so_id, int x, int y);


/*******************************�������ж�**********************************/

//ʿ���ƶ���ĳ��
void soldier_march_to(Info& info, pair<int, int> so_info, int tar_x, int tar_y);

//�ж�ʿ����ĳ��Χ��(>= <=)
bool soldier_at(Info& info, int so_index, int x_L, int y_D, int x_R, int y_U);

//�ж�ʿ����ĳ��
bool soldier_at(Info& info, int so_index, int x, int y);

//����ĳλ����Χĳ��Χ���ض����͸���(�����ص�һ���������)
bool search_type_around(Info& info, TOccupiedType type, int x, int y, int range, pair<int, int>& p);

//����ʿ��id������Ϣ
bool get_soldier_by_id(Info& info, int id, TSoldier*& res);

//����id�����±�
bool get_index_by_id(Info& info, int so_id, int& index);

/*************************************�¼�****************************************/




//************************************************************

//·������
typedef struct Node
{
	int x, y;//����
	int g;//��ʼ�㵽��ǰ��ʵ�ʴ���
	int h;//��ǰ�ڵ㵽Ŀ��ڵ����·���Ĺ��ƴ���
	int f;//����ֵ f = g + h
	Node* father;//���ڵ�

	//���캯�����أ�������Ĭ�Ϲ��캯��
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

//Astar��
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
	void CreateMap(Info& info, int x, int y, int movedis);//������ͼ
	vector<Node*> openList;//�����б�
	vector<Node*> closeList;//����б���Ų���Ҫ�ٽ��п��ǵĽڵ�
	Node *startPos;
	Node *endPos;
	//���ۺ����Ĺ��۷Ŵ�ϵ��
private:
	static const int WeightW = 10;// ����������
	static const int row = 50;//��ͼ����
	static const int col = 50;//��ͼ����
};


//����map,���ڴ����Ұ�ڵ�����Ϣ��Ԥ��Ϊ0,���11*11
int temp_map[70][70];
TLandForm LF_map[70][70];
int countNode(Node*current);


//************************************************************