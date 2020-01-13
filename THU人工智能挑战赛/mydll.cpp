#include "my_head.h"

/*
*         ����ATTENTION����
* ʿ����id������vector���������index����һ��������
*
* ���飺struct����ֱ�Ӹ��ƣ�����ʱ�ڲ���structͬ�����ƣ���pointerָ��ռ䲢���ı䡣
*
* ���飺���β�pointer��������ʱ�������ã����ں�������Ϊ���÷���ռ�
* 
* Ŀǰ����Ҫ��
* ������������Ϊ����+��������
* �޸�ʿ���ƶ���ĵ�occupied�����������Щ�ƶ�����·��
* ����-�������Ĳ�������
* ���������ɵı�Ҫ���絽������(��������ʱ��վλ����Ҫ)
*/

/**********************************�����㷨*************************************/

//ŷ�Ͼ���
float euler_distance(int x1, int x2, int y1, int y2)
{
	return sqrt(pow((x1 - x2), 2.) + pow((y1 - y2), 2.));
}

//�����پ���
int manhattan_distance(int x1, int x2, int y1, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

/**********************************�ײ㹦��*************************************/
//Tpoint��ӡ����
bool print_point(TPoint* po)
{
	if (po == NULL)
		return false;
	else
	{
		printf("	position:(%d, %d)\n", po->x, po->y);
		cout << "	landform:" << po->land << endl;

		cout << "	visible:" << po->visible << endl;
		if (po->visible)
		{
			cout << "	occupied:" << po->occupied << endl;
			if (po->occupied)
			{
				cout << "	occupied_type:" << po->occupied_type << endl;
				if (po->occupied_type == soldier)
					cout << "	soldierID:" << po->soldier << endl;
				else if (po->occupied_type == tower)
					cout << "	towerID:" << po->tower << endl;
			}
		}
		return true;
	}
}

//TSoldier��ӡ����
bool print_soldier(TSoldier* so)
{
	if (so == NULL)
		return false;
	else
	{
		printf("*********\n");
		cout << "id:" << so->id << endl;
		cout << "owner:" << so->owner << endl;
		cout << "type:" << so->type << endl<<endl;
		cout << "range:" << so->range << endl;
		cout << "move_ability:" << so->move_ability << endl;
		cout << "attack:" << so->attack << endl;
		cout << "armor:" << so->armor << endl;
		cout << "blood:" << so->blood << endl;
		cout << "experience:" << so->experience << endl;
		cout << "level:" << so->level << endl;
		cout << "move_left:" << so->move_left << endl;
		cout << "attackable:" << so->attackable << endl;

		cout << "point information:" << endl;
		print_point(&(so->position));
		printf("*********\n");

		return true;
	}
}

//��ӡ���������
void show_assign_result(Info& info)
{
	printf("After:all = %d defend = %d mid = %d\n", my_soldier.size(), defend_id.size(), mid_id.size());

	printf("All soldier ids:\n");
	for (vector<pair<int, int>>::iterator it = my_soldier.begin();
		it != my_soldier.end(); it++)
	{
		printf("%d ", (*it).second);
	}
	printf("\n");

	printf("All defend ids:\n");
	for (vector<int>::iterator it = defend_id.begin();
		it != defend_id.end(); it++)
	{
		printf("%d ", *it);
	}
	printf("\n");

	printf("All mid ids:\n");
	for (vector<int>::iterator it = mid_id.begin();
		it != mid_id.end(); it++)
	{
		printf("%d ", *it);
	}
	printf("\n");
}


/**********************************��������*************************************/

//����ʿ������(����1-7)
void c_produce_soldier(Info& info, int tower, int soldierType )
{
	info.myCommandList.addCommand(Produce, tower, soldierType);
}

//�ƶ�ʿ������
void c_move_soldier(Info& info, int so_id, int direction, int distance)
{
	info.myCommandList.addCommand(Move, so_id, direction, distance);
	int index;
	if (get_index_by_id(info, so_id, index))
	{
		switch (direction)
		{
		case UP:
			info.soldierInfo[index].y_position += distance;
			break;
		case DOWN:
			info.soldierInfo[index].y_position -= distance;
			break;
		case LEFT:
			info.soldierInfo[index].x_position -= distance;
			break;
		case RIGHT:
			info.soldierInfo[index].x_position += distance;
			break;
		default:
			break;
		}
	}
		
}

//����������
void c_upgrade(Info& info, int towerId)
{
	info.myCommandList.addCommand(Upgrade, towerId);
}

//��������
void c_attack(Info& info, int so_id, int x, int y)
{
	info.myCommandList.addCommand(Attack, so_id, x, y);
}

/*******************************�������ж�**********************************/

/*****����*****/

//��������ĳ���������һ��_s
bool search_step(Info& info, Node* startPos, Node* endPos, Node*& res, int id, int index)
{
	Astar astar;
	TSoldier* temp;

	//���ʿ���ƶ���
	int movedis = 0;
	if (get_soldier_by_id(info, id, temp))
		movedis = temp->move_left;
	astar.CreateMap(info, startPos->x, startPos->y, movedis);		//��ͼԤ����,���뵱ǰ�����ʿ���ƶ���

	Node* finalPos;											//���վ����߱�������
	if ((finalPos = astar.search(info, startPos, endPos, movedis)) != NULL)
	{
		res = finalPos;
		return true;
	}
	else return false;				//δ�ҵ�����·��
}

//����ʿ��id������Ϣ
bool get_soldier_by_id(Info& info, int id, TSoldier*& res)
{
	int size = info.soldierInfo.size();
	if (size == 0)
	{
		return false;
	}
	for (int i = 0; i < size; i++)
	{
		if (info.soldierInfo[i].id == id)
		{
			res = new TSoldier;
			memcpy(res, &(info.soldierInfo[i]), sizeof(TSoldier));
			return true;
		}
	}
	return false;
}

//����ʿ��id�����±�
bool get_index_by_id(Info& info, int so_id, int& index)
{
	for (int i = 0; i < info.soldierInfo.size(); i++)
	{
		if (info.soldierInfo[i].id == so_id)
		{
			index = i;
			return true;
		}
	}
	return false;
}


/*****����*****/

//ʿ���ƶ���ĳ��_s,so_info:<so_index,so_id>
void soldier_march_to(Info& info, pair<int, int> so_info, int tar_x, int tar_y)
{
	int so_id = so_info.second;
	int so_index = so_info.first;

	int max_move = info.soldierInfo[so_index].move_left;
	if (max_move > 0)
	{
		int x = info.soldierInfo[so_index].x_position;
		int y = info.soldierInfo[so_index].y_position;
		Node* start = new Node(x, y);
		Node* end = new Node(tar_x, tar_y);

		//Ѱ��������ŵ�
		Node* result = NULL;
		if (search_step(info, start, end, result, so_id, so_index))
		{
			printf("next step:(%d, %d)\n", result->x, result->y);
			int x_dis = result->x - x;
			int y_dis = result->y - y;

			//x����
			if (x_dis > 0)
			{
				c_move_soldier(info, so_id, RIGHT, min(abs(x_dis), max_move));
			}
			else if (x_dis < 0)
			{
				c_move_soldier(info, so_id, LEFT, min(abs(x_dis), max_move));
			}

			//y����
			if (y_dis>0)
			{
				c_move_soldier(info, so_id, UP, min(abs(y_dis), max_move));
			}
			else if (y_dis < 0)
			{
				c_move_soldier(info, so_id, DOWN, min(abs(y_dis), max_move));
			}
		}
	}
}

/*****�ж�*****/

//ʿ����ĳ��Χ
bool soldier_at(Info& info, int so_index, int x_L, int y_D, int x_R, int y_U)
{
	if (info.soldierInfo[so_index].x_position >= x_L
		&& info.soldierInfo[so_index].y_position >= y_D
		&& info.soldierInfo[so_index].x_position <= x_R
		&& info.soldierInfo[so_index].y_position <= y_U)
		return true;
	else
		return false;
}

// ʿ����ĳ��
bool soldier_at(Info& info, int so_index, int x, int y)
{
	if ((info.soldierInfo[so_index].x_position == x)
		&& (info.soldierInfo[so_index].y_position == y)){
		return true;
	}

	else
		return false;
}

//����ĳλ��ĳ��Χ���ض�����_s(ŷ������)(�����ص�һ���������)
bool search_type_around(Info& info, TOccupiedType type, int x, int y, int range, pair<int, int>& p)
{
	printf("searching_type_around\n");
	for (int i = x - range; i <= x + range; i++)
	{
		for (int j = y - range; j <= y + range; j++)
		{
			if (i == x&&j == y)
				continue;
			if (i<0 || i>49 || j<0 || j>49)
				continue;
			if (euler_distance(x, i, y, j) > range)
				continue;
			if (!info.pointInfo[i][j].visible)
				continue;
			if (info.pointInfo[i][j].occupied_type == type)
			{
				p = pair<int, int>(i, j);
				return true;
			}
		}
	}

	return false;
}


/*******************************����**********************************/


/*****������*****/

//ʿ�����Թ���ĳ��_s
bool soldier_can_attack_tow(Info& info, int so_index, int to_id, set<pair<int, int>>& result)
{
	int tow_x = tw_position[to_id][0];			//��ȡ����λ��
	int tow_y = tw_position[to_id][1];
	
	int so_x = info.soldierInfo[so_index].x_position;		//�ҷ�λ��
	int so_y = info.soldierInfo[so_index].y_position;
	int range = info.soldierInfo[so_index].range;			//������Χ
	int move = info.soldierInfo[so_index].move_left;		//ʣ���ƶ���

	bool can_attack = false;
	result.clear();

	//���ѭ�����ҵ�ʿ�������ƶ����ĵ�
	for (int i = so_x - move; i <= so_x + move; i++)
	{
		for (int j = so_y - move; j <= so_y + move; j++)
		{
			if (i<0 || i>49 || j<0 || j>49)
				continue;
			if (manhattan_distance(i, so_x, j, so_y) > move)
				continue;
			if (info.pointInfo[i][j].occupied)
				continue;
			if (info.pointInfo[i][j].land == TowerLand ||
				(info.pointInfo[i][j].land == River))
				continue;
			//printf("	psb point: (%d, %d)\n", i, j);

			//�ڲ�ѭ�����ҵ�ʿ�����ܹ������ĵ�
			for (int x = i - range; x <= i + range; x++)
			{
				for (int y = j - range; y <= j + range; y++)
				{
					if (x<0 || x>49 || y<0 || y>49)
						continue;
					if (!info.pointInfo[x][y].visible)
						continue;
					if (info.pointInfo[x][y].occupied_type == soldier)
						continue;
					//printf("		psb attack:(%d, %d)\n", x, y);
					if (euler_distance(x, i, y, j) <= range)
					{
						if (euler_distance(x,tow_x,y,tow_y)<1.5)	//ŷ�Ͼ���С��5˵�������ϵĵ�
						{
							pair<int, int> p(i, j);
							result.insert(p);
							can_attack = true;
							break;
						}
					}
				}
			}
			//�ڲ�ѭ������
		}
	}
	return can_attack;
}

//ʿ������ֱ�ӹ���ĳ��_s
bool soldier_can_straightly_attack_tow(Info& info, int so_index, int to_id, pair<int, int>& p)
{
	int tow_x = tw_position[to_id][0];			//��ȡ����λ��
	int tow_y = tw_position[to_id][1];

	int so_x = info.soldierInfo[so_index].x_position;		//�ҷ�λ��
	int so_y = info.soldierInfo[so_index].y_position;
	int range = info.soldierInfo[so_index].range;			//������Χ

	for (int x = so_x - range; x <= so_x + range; x++)
	{
		for (int y = so_y - range; y <= so_y + range; y++)
		{
			if (x<0 || x>49 || y<0 || y>49)
				continue;
			if (!info.pointInfo[x][y].visible)
				continue;
			if (info.pointInfo[x][y].occupied_type == soldier)
				continue;
			if (euler_distance(x, so_x, y, so_y) <= range &&
				euler_distance(x, tow_x, y, tow_y)<1.5)	//ŷ�Ͼ���С��5˵�������ϵĵ�
			{
				p = pair<int, int>(x,y);
				return true;
			}
		}
	}
	return false;
}


//����ĳʿ������ĳ��������λ��(���Ľ�)
bool get_attack_tow_point(Info& info, int to_id, int so_index, set<pair<int, int>> result, pair<int, int>& p)
{
	if (!result.empty())
	{
		set<pair<int, int>>::iterator iter = result.begin();
		p = *iter;
		return true;
	}
	else return false;
}


//�¼�������ĳһnumʿ������ĳ��ֱ�����
void soldier_occupy_tower(Info& info, int so_id, int to_id)
{
	int index;
	get_index_by_id(info, so_id, index);						//��ȡʿ������
	int id = so_id;						//��ȡʿ��id
	printf("so_id = %d, spo_index = %d #soldier_occupy_tower \n",id,index);
	int x_pos = info.soldierInfo[index].x_position;			//��ȡ��ʿ����ǰλ��
	int y_pos = info.soldierInfo[index].y_position;
	int range = info.soldierInfo[index].range;

	int tow_x = tw_position[to_id][0];						//��ȡ����λ��
	int tow_y = tw_position[to_id][1];

	set<pair<int, int>> result;								//������ܹ�������������
	if (!soldier_can_attack_tow(info, index, to_id, result))
	{
		soldier_march_to(info, pair<int,int>(index,id), tow_x, tow_y);
	}
	else
	{
		pair<int, int> tarp;								//��ѹ�����
		if (soldier_can_straightly_attack_tow(info, index, to_id, tarp))
		{
			printf("Attack!!(tow)\n");
			c_attack(info, id, tarp.first, tarp.second);
		}
		else if (get_attack_tow_point(info,to_id,index,result,tarp))
		{
			//�ƶ�
			soldier_march_to(info, pair<int, int>(index, id), tarp.first, tarp.second);

			//������λ��
			x_pos = info.soldierInfo[index].x_position;	
			y_pos = info.soldierInfo[index].y_position;

			//��ȡ����Ŀ���
			pair<int, int> tara;
			if (search_type_around(info, tower, x_pos, y_pos, range, tara))
			{
				//����
				printf("Attack!!(tow)\n");
				c_attack(info, id, tara.first, tara.second);
			}
		}
	}
}



/*****������*****/

//����ĳ����Χ���ез�ʿ��_s
bool search_invader_around(Info& info, int to_id,int range, vector<int>& invader)
{
	int tow_x = tw_position[to_id][0];
	int tow_y = tw_position[to_id][1];

	//���������·��ֵ�ʿ��
	for (int i = tow_x - range; i <= tow_x + range; i++)
	{
		for (int j = tow_y - range; j <= tow_y + range; j++)
		{
			TPoint po = info.pointInfo[i][j];
			if (po.occupied_type != soldier)
				continue;
			int id = po.soldier;
			TSoldier *so;
			if (get_soldier_by_id(info, id, so))
			{
				if (so->owner != my_id)
				{
					vector<int>::iterator it =
						find(invader.begin(), invader.end(), id);
					if (it == invader.end())			//���vector��û�У��ͰѸ�id����
						invader.push_back(id);
				}
			}
		}
	}
	TSoldier* temp;
	//������в��ڷ�Χ�ڵ�ʿ��
	for (vector<int>::iterator it = invader.begin();
		it != invader.end(); it++)
	{
		if (!get_soldier_by_id(info, *it, temp))
			invader.erase(it);
	}

	return !(invader.empty());
}

//��ȡĳ����Χ��һ���з�ʿ��id
bool get_invader_around(Info& info, int to_id, vector<int>& invader, int& enm_id)
{
	if (invader.empty())
	{
		printf("get_invader_around_false!!!\n");
		return false;
	}
	else
	{
		enm_id = *invader.begin();
		return true;
	}
}

//ʿ�����Թ���ĳʿ��_s
bool soldier_can_attack_sol(Info& info, int so_index, int enm_id, set<pair<int, int>>& result)
{
	TSoldier *enm;
	get_soldier_by_id(info, enm_id, enm);
	int enm_x = enm->x_position;					//�з�λ��
	int enm_y = enm->y_position;

	int so_x = info.soldierInfo[so_index].x_position;		//�ҷ�λ��
	int so_y = info.soldierInfo[so_index].y_position;
	int range = info.soldierInfo[so_index].range;		//������Χ
	int move = info.soldierInfo[so_index].move_left;	//ʣ���ƶ���

	bool can_attack = false;
	result.clear();

	//���ѭ�����ҵ�ʿ�������ƶ����ĵ�(������)
	for (int i = so_x - move; i <= so_x + move; i++)
	{
		for (int j = so_y - move; j <= so_y + move; j++)
		{
			if (i<0 || i>49 || j<0 || j>49)
				continue;
			if (manhattan_distance(i, so_x, j, so_y) > move)
				continue;
			if (info.pointInfo[i][j].occupied && !(i==so_x&&j==so_y))
				continue;
			if (info.pointInfo[i][j].land == TowerLand ||
				(info.pointInfo[i][j].land == River))
				continue;

			//�ڲ�ѭ�����ҵ�ʿ�����ܹ������ĵ�
			for (int x = i - range; x <= i + range; x++)
			{
				for (int y = j - range; y <= j + range; y++)
				{
					if (x<0 || x>49 || y<0 || y>49)
						continue;
					if (!info.pointInfo[x][y].visible)
						continue;
					if (info.pointInfo[x][y].occupied_type != soldier)
						continue;
					if (euler_distance(x, i, y, j) <= range)
					{
						if (x == enm_x && (y == enm_y))
						{
							pair<int, int> p(i, j);
							result.insert(p);
							can_attack = true;
							break;
						}
					}
				}
			}
			//�ڲ�ѭ������
		}
	}
	return can_attack;
}

//ʿ������ֱ�ӹ���ĳ��_s
bool soldier_can_straightly_attack_sol(Info& info, int so_index, int enm_id, pair<int, int>& p)
{
	TSoldier *enm;
	get_soldier_by_id(info, enm_id, enm);
	int enm_x = enm->x_position;					//�з�λ��
	int enm_y = enm->y_position;

	int so_x = info.soldierInfo[so_index].x_position;		//�ҷ�λ��
	int so_y = info.soldierInfo[so_index].y_position;
	int range = info.soldierInfo[so_index].range;			//������Χ

	for (int x = so_x - range; x <= so_x + range; x++)
	{
		for (int y = so_y - range; y <= so_y + range; y++)
		{
			if (x<0 || x>49 || y<0 || y>49)
				continue;
			if (!info.pointInfo[x][y].visible)
				continue;
			if (info.pointInfo[x][y].occupied_type != soldier)
				continue;
			if (euler_distance(x, so_x, y, so_y) <= range &&
				(x == enm_x) && (y == enm_y))	
			{
				p = pair<int, int>(enm_x, enm_y);
				return true;
			}
		}
	}
	return false;
}


//����ĳʿ������ĳʿ��������λ��(���Ľ�)
bool get_attack_sol_point(Info& info, int enm_id, int so_index, set<pair<int, int>> result, pair<int, int>& p)
{
	if (!result.empty())
	{
		float min_dis = 50;
		int so_x = info.soldierInfo[so_index].x_position;
		int so_y = info.soldierInfo[so_index].y_position;

		auto iter = result.begin();
		for (; iter != result.end(); iter++)
		{
			float dis= euler_distance(so_x, iter->first, so_y, iter->second);
			if (dis < min_dis)
				min_dis = dis;
		}

		for (iter = result.begin(); iter != result.end(); iter++)
		{
			float dis = euler_distance(so_x, iter->first, so_y, iter->second);
			if (dis == min_dis)
			{
				p = *iter;
				return true;
			}
		}
		return false;
	}
	else return false;
}


//�¼�������ĳһʿ����ĳid�����߷�������_s
void offensive_against_soldier(Info& info, int so_id, int inv_id)
{
	TSoldier *temp;
	if (get_soldier_by_id(info, inv_id, temp))					//�����ѵ�����Ŀ��ʿ�����
	{
		int index ;	
		get_index_by_id(info, so_id, index);					//�ҷ�ʿ������
		int id = so_id;											//�ҷ�ʿ��id
		int x_pos = info.soldierInfo[index].x_position;			//�ҷ�ʿ����ǰλ��
		int y_pos = info.soldierInfo[index].y_position;
		int range = info.soldierInfo[index].range;				//�ҷ�ʿ��������Χ

		//printf("position: (%d, %d)\n", x_pos, y_pos);

		int enm_index ;
		get_index_by_id(info, inv_id, enm_index);				//�з�ʿ������
		int enm_x = info.soldierInfo[enm_index].x_position;		//�з�ʿ����ǰλ��
		int enm_y = info.soldierInfo[enm_index].y_position;

		set<pair<int, int>> result;								//������ܹ�������������
		if (!soldier_can_attack_sol(info,index,inv_id,result))
		{
			soldier_march_to(info, pair<int,int>(index,id), enm_x, enm_y);
		}

		else
		{
			pair<int, int> tarp;								//��ѹ�����
			if (soldier_can_straightly_attack_sol(info,index,inv_id,tarp))
			{
				printf("Straightly Attack!!!\n");
				c_attack(info, id, tarp.first, tarp.second);
			}
			else if (get_attack_sol_point(info,inv_id,index,result,tarp))
			{
				//�ƶ�
				soldier_march_to(info, pair<int, int>(index, id), tarp.first, tarp.second);
				//����
				printf("Attack!!!\n");
				c_attack(info, id, enm_x, enm_y);
			}
		}
	}
}



/*************************************�¼�****************************************/

//���ĳ�������ĵз���в_s��ids,����ʿ��id;so_num,�μ�����ʿ������
void clear_around_tower(Info& info, int to_id, const int* ids, int so_num, vector<int>& invader)
{
	printf("clear_around_on\n");
	int invd_id = -1;
	//��ȡ�׸��з�ʿ��id
	if (get_invader_around(info, to_id, invader,invd_id))
	{		
		//���вμ������ʿ�������з�ʿ��
		for (int i = 0; i < so_num; i++)
		{
			printf("Soldier id:%d offensive_against_soldier\n", ids[i]);
			offensive_against_soldier(info, ids[i], invd_id);
		}
	}
}


/**********************************����***********************************/

//����+��������_s
void produce(Info& info)
{
	if (info.round <= 100)
	{
		int i = my_so_num;
		int type = commandinfo.so_produce_sequence[i];
		int required_res = commandinfo.res[type];
		int current_res = info.playerInfo[my_id].resource;

		int required_pop = commandinfo.pop[type];
		int current_pop = info.playerInfo[my_id].population;
		int max_pop = info.playerInfo[my_id].max_population;

		//�����Ƿ�������
		can_produce = !((current_pop + required_pop) > max_pop);
		
		//���������ȿ�������
		if (can_produce)
		{
			//����ûռ��ǰ�����������ɱ�
			if (!have_sec_tow && (current_res > required_res))
			{
				c_produce_soldier(info, main_tow, type);
			}

			//����ռ����ø������ɱ�
			else if (have_sec_tow && (current_res > required_res))
			{
				c_produce_soldier(info, sec_tow, type);
			}
		}
		
		//����������������
		else if (!can_produce)
		{
			printf("	Ready to Upgrade!\n");
			//�ȿ��Ǹ���
			int sec_level = info.towerInfo[sec_tow].level;
			int main_level = info.towerInfo[main_tow].level;
			if (sec_level<3 && 
				current_res > commandinfo.tow_upg_res[sec_level - 1])
			{
				printf("	Upgrade sec_tow!!\n");
				c_upgrade(info, sec_tow);
			}
			else if (main_level<3 &&
				current_res > commandinfo.tow_upg_res[main_level - 1])
			{
				printf("	Upgrade main_tow!!\n");
				c_upgrade(info, main_tow);
			}
			
		}


		//����:ռ�츱��

		int num = defend_id.size();
		int* ids = new int[num];
		for (int i = 0; i < num; i++)
		{
			ids[i] = defend_id[i];
		}
		
		if (occupy_secondary_tower_on)
		{
			for (int i = 0; i < num; i++)			//������0-2ʿ��ռ�츱��
			{
				printf("soldier id:%d occupy_second_tower\n", ids[i]);
				soldier_occupy_tower(info, ids[i], sec_tow);
			}
		}
	}
}


//�������ԡ���
void middle_tower(Info& info)
{
	printf("middle_tower_on\n");
	//��ȡ������������ʿ��
	int num = mid_id.size();
	int* ids = new int[num];
	for (int i = 0; i < num; i++)
	{
		ids[i] = mid_id[i];
	}

	//û�������м���
	for (int i = 0; i < num; i++)
	{
		int index;
		get_index_by_id(info, ids[i], index);
		int tar_x = tw_position[8][0];
		int tar_y = tw_position[8][1];
		if (!soldier_at(info, index, tar_x - 4, tar_y - 4, tar_x + 4, tar_y + 4))
		{
			soldier_march_to(info, pair<int, int>(index, ids[i]), tar_x, tar_y);
		}
	}

	//�ȸ���
	if(info.towerInfo[8].owner != my_id)
	{
		printf("occupy_middle_tower!\n");
		for (int i = 0; i < mid_id.size(); i++)
		{
			soldier_occupy_tower(info, ids[i], 8);
		}
	}
	//�ٸɱ�
	else if(info.towerInfo[8].owner == my_id)
	{
		printf("defend_middle_tower!\n");
		vector<int> invader;
		if (search_invader_around(info, mid_tow, 4, invader))
		{
			clear_around_tower(info, mid_tow, ids, num, invader);
		}
	}
}


//��-������������
void defend_second_tower(Info& info)
{
	//��̬�滮����ʿ������
	int defender_num = defend_id.size();
		
	int *ids = new int[defender_num];
	for (int i = 0; i < defender_num; i++)
	{
		ids[i] = defend_id[i];
	}

	vector<int> invader;							//���ڱ���������id
	if (search_invader_around(info, sec_tow,5, invader))
	{
		printf("invader around sec tow!!!\n");
		for (auto it = invader.begin(); it != invader.end(); it++)
		{
			int tempid = *it;
			cout << "num: " << *it ;
			TSoldier* enm;
			get_soldier_by_id(info, tempid, enm);
			printf("position: (%d, %d)", enm->x_position, enm->y_position);
			cout << endl;
		}	
		clear_around_tower(info, sec_tow, ids, defender_num,invader);
	}
}


//���Ĳ��ԡ���
void core_strategy(Info& info)
{
	//����-��������
	if (have_sec_tow)
	{
		defend_second_tower(info);
	}

	//����-��������
	if (middle_tower_on)
	{
		printf("middle_tower_on!\n");
		middle_tower(info);
	}
}


/**********************************���ܺ���*************************************/
//��ͼ��ʼ��_s
void map_init(Info& info)
{
	for (int i = 0; i <= 49; i++)
	{
		for (int j = 0; j <= 49; j++)
		{
			LF_map[i][j] = info.pointInfo[i][j].land;
		}
	}
}


//�������_s
void task_assign(Info& info)
{
	//��˼·��ɾ���������䡪���ط���
	
	//����ɾ��defend����ʿ��
	TSoldier *temps;
	auto it = defend_id.cbegin();
	while(it != defend_id.cend())
	{
		if (!get_soldier_by_id(info, *it, temps))
		{
			it = defend_id.erase(it);
		}
		else
		{
			it++;
		}
	}

	//����ɾ��mid����ʿ��
	it = mid_id.cbegin();
	while (it != mid_id.cend())
	{
		if (!get_soldier_by_id(info, *it, temps))
		{
			it = mid_id.erase(it);
		}
		else
		{
			it++;
		}
	}

	//�������������ʿ�� my_so_num<=5��defend��>=6��mid
	if (0 < my_so_num && my_so_num <= 5)
	{
		for (auto it = my_soldier.cbegin(); it != my_soldier.cend(); it++)
		{
			int id = it->second;
			//���ң����defend��mid�ﶼû�У��ͰѸ�id����defend
			auto it2 = find(defend_id.begin(), defend_id.end(), id);
			auto it3 = find(mid_id.begin(), mid_id.end(), id);
			if (it2 == defend_id.end() && (it3 == mid_id.end())){
				defend_id.push_back(id);
			}
		}
	}
	else if (my_so_num >= 6)
	{
		for (auto it = my_soldier.cbegin(); it != my_soldier.cend(); it++)
		{
			//���ң����defend��mid�ﶼû�У��ͰѸ�id����mid
			int id = it->second;
			auto it2 = find(mid_id.begin(), mid_id.end(), id);
			auto it3 = find(defend_id.begin(), defend_id.end(), id);
			if (it2 == mid_id.end() && (it3 == defend_id.end())){
				mid_id.push_back(id);
			}
		}
	}
	
	//�ط���
	if (my_so_num == 4 && !mid_id.empty())
	{
		//��������5�����б����ط�
		mid_id.clear();
		defend_id.clear();
		for (int i = my_so_num - 1; i >= 0; i--)
		{
			defend_id.push_back(my_soldier[i].second);
		}
	}
	else if (my_so_num == 5 && mid_id.empty())
	{
		defend_id.clear();
		for (int i = my_so_num - 1; i >= 0; i--)
		{
			if (i >= my_so_num - 3)
				mid_id.push_back(my_soldier[i].second);
			else if (i < my_so_num - 3)
				defend_id.push_back(my_soldier[i].second);
		}
	}
	else if (my_so_num >= 6 && (defend_id.size()<3))
	{
		auto temp = mid_id.back();
		mid_id.pop_back();
		defend_id.push_back(temp);
	}

	show_assign_result(info);
}

//��Ϣ��ʼ��
void info_init(Info& info)
{
	//��ʼ����ͼ
	map_init(info);

	//��ȡ����id��
	my_id = info.myID;

	//��ȡ���������
	for (int i = 0; i < 9; i++)
	{
		tw_position[i][0] = info.towerInfo[i].x_position;
		tw_position[i][1] = info.towerInfo[i].y_position;
	}

	//��ȡ��������ʿ����	
	if (!my_soldier.empty())
	{
		my_soldier.clear();
	}
	my_so_num = 0;
	for (int num = 0; num < (int)info.soldierInfo.size(); num++)
	{
		if (info.soldierInfo[num].owner == info.myID)
		{
			pair<int, int> index_and_id = pair<int, int>(num, info.soldierInfo[num].id);
			my_soldier.push_back(index_and_id);
			my_so_num++;
		}
	}

	//�������
	task_assign(info);
}

//��������ʼ��
void comd_init(Info& info)
{
	int so_pro_seq[40] = {
		HeavyInfantry, HeavyArcher, 
		HeavyInfantry, HeavyArcher, 
		HeavyInfantry, HeavyArcher, 
		HeavyInfantry, HeavyArcher, 
		HeavyInfantry, HeavyArcher, 
		HeavyInfantry, HeavyArcher, 
		HeavyInfantry, HeavyArcher,
		HeavyInfantry, HeavyArcher,
		HeavyInfantry, HeavyArcher,
		HeavyInfantry, HeavyArcher,
		HeavyInfantry, HeavyArcher,
		HeavyInfantry, HeavyArcher,
		HeavyInfantry, HeavyArcher,
		HeavyInfantry, HeavyArcher,
		HeavyInfantry, HeavyArcher,
		HeavyInfantry, HeavyArcher,
		1, 1, 1, 1, 1, 1, 1, 1, };
	memcpy(commandinfo.so_produce_sequence, so_pro_seq, sizeof(int)* 36);
	
	int rscs[7] = { 40, 40, 50, 70, 55, 60, 70, };
	memcpy(commandinfo.res, rscs, sizeof(int)* 7);

	int popu[7] = { 2, 3, 5, 8, 5, 8, 8 };
	memcpy(commandinfo.pop, popu, sizeof(int)* 7);

	int upg_res[3] = { 80, 150, 99999 };
	memcpy(commandinfo.tow_upg_res, upg_res, sizeof(int)* 3);
	
	int tows[4][2] = { { 0, 1 }, { 6, 7 }, { 4, 5 }, { 2, 3 } };
	memcpy(commandinfo.towers, tows, sizeof(int)* 8);

	main_tow = commandinfo.towers[my_id][0];
	sec_tow = commandinfo.towers[my_id][1];

}

//�¼�״̬��ʼ��
void event_init(Info& info)
{
	have_sec_tow = info.towerInfo[sec_tow].owner == info.myID;

	occupy_secondary_tower_on = !have_sec_tow && (my_so_num >= 1) ;

	middle_tower_on = !mid_id.empty();

}


//��ʼ��
void init(Info& info)
{
	//��Ϣ��ʼ��
	info_init(info);
	
	//��������ʼ��
	comd_init(info);

	//���������
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	long millis = (sys.wMinute * 60 + sys.wSecond) * 1000 + sys.wMilliseconds;
	srand((unsigned)millis);
	
	//��ʼ���¼�״̬
	event_init(info);

	//��ʾ�ؼ���Ϣ
	printf("Round: %d\n", info.round);
	printf("my_id = %d\n", info.myID);
}

//����
void debug(Info& info)
{
	if (info.round >= 40)
	{
		printf("\n\n");
		system("pause");
	}	
}

/************************************������***************************************/

void player_ai(Info& info)
{
	init(info);					//���г�ʼ������
	
	produce(info);				//����+����

	core_strategy(info);		//���Ĳ���

	debug(info);
}




/************************************Astar��ʵ��***************************************/

//����Ԥ������,����Ұ��Χ�ڵĵ��ν���Ԥ���������������Լ��Ѿ�ռ�ݵ�λ����Ϊ�ϰ�
void Astar::CreateMap(Info& info,int x, int y, int movedis)//����Ϊ��ǰʿ������,ʿ���ƶ���
{
	int i, j;
	memset(&temp_map, 0, sizeof(int)* 4900);
	for (i = x - movedis; i <= x + movedis; i++)
	{
		for (j = y - movedis; j <= y + movedis; j++)
		{
			if (i<0 || i>49 || j<0 || j>49)
			{
				continue;
			}
			TOccupiedType grid_o = info.pointInfo[i][j].occupied_type;
			TLandForm grid_f = LF_map[i][j];

			if (grid_o == soldier || grid_o == tower )
			{
				temp_map[i][j] = 1;
			}
			else if(grid_0 == river)//��������ֵ��Ϊ2
			{
				temp_map[i][j] = 2;
			}
			else
			{
				temp_map[i][j] = 0;
			}
		}
	}
}

//�����㷨:�����ʼ�ڵ�����սڵ㣬�Լ�ʿ���ƶ���
Node* Astar::search(Info& info, Node* startPos, Node* endPos, int movedis = 5)//Ĭ����Ϊ�������5
{
	//������ͼ��Χ�Ĵ���
	if (startPos->x < 0 || startPos->x > row || startPos->y < 0 || startPos->y >col ||
		endPos->x < 0 || endPos->x > row || endPos->y < 0 || endPos->y > col)
		return NULL;

	Node* current;//��ǰ�ڵ�
	this->startPos = startPos;
	this->endPos = endPos;
	openList.push_back(startPos);

	//�ѿ�ʼ�Ľڵ����openlist��ʼ�����������ҵ�4���ڵ㣬������곬����Χ����closelist��return 
	//����Ѿ�����openlist�ͶԱȵ�ǰ�ڵ㵽���������Ǹ��ڵ��Gֵ�͵�ǰ�ڵ㵽ԭ�����ڵ��Gֵ ���ԭ����Gֵ�Ƚϴ� ���ù� 
	//�������¸�ֵGֵ ���ڵ� ��f ������½ڵ� ���뵽openlist ֱ��opellistΪ�ջ��ҵ��յ�

	while (openList.size() > 0)
	{

		current = openList[0];//���еĵ�һ���ǵ�ǰ�ڵ�

		if ((current->x == endPos->x && (current->y == endPos->y)) 
			|| (countNode(current) >= movedis))//�ж��Ƿ񵽴�Ŀ�꣬���߳�����Ұ
		{

			openList.clear();
			closeList.clear();
			return current;//������һ������Ҫ�ߵĽڵ�
		}
		else if (countNode(current) >= movedis)
		{
			return NULL;
		}

		NextStep(info,current);//��һ��

		closeList.push_back(current);//����һ��������������б�����Ҫ�ٽ��п���
		openList.erase(openList.begin());//�������б�ĵ�һ������һ�����������
		std::sort(openList.begin(), openList.end(), compare);//����

	}
}

//·�����ȼ��������ݹ飬���ؿ���·���Ľڵ����
int countNode(Node*current)
{
	if (current->father != NULL)
		return countNode(current->father) + 1;
	else return 0;
}

//�������꣬���ص�ǰ��Ĵ���ϵ��
int PosWeight(Info& info, int x, int y)
{
	int Weight = 10;							    //Ĭ��ֵΪ10
	TLandForm Pos = info.pointInfo[x][y].land;
	if (Pos==Mountain)								//ɽ�ص�����Ϊ20,�Ծ����ܱܿ�ɽ��
		Weight = 20;
	
	return Weight;
}

//������������ӽڵ�֮��ļ̳�
void Astar::checkPoit(int x, int y, Node* father, int g)//g���ۻ���
{
	if (x < 0 || x > row || y < 0 || y > col)
		return;
	if (this->unWalk(x, y))
		return;
	if (isContains(&closeList, x, y) != -1)//�� ����б��У�ʲô������
		return;
	int index;
	if ((index = isContains(&openList, x, y)) != -1)//��������Ľڵ��Ѿ��ڿ����б��У��ͱȽ�Gֵ
	{
		Node *point = openList[index];
		//�� G ֵΪ�ο�����µ�·���Ƿ����, ���͵�Gֵ��ζ�Ÿ��õ�·�������µĽڵ�̳и��ڵ㣬����ʲô������
		if (point->g > father->g + g)
		{
			point->father = father;//���ĵ�ǰ�ڵ�ĸ��ڵ�
			point->g = father->g + g;
			point->f = point->g + point->h;
		}
	}
	else//���ڿ����б���
	{
		Node * point = new Node(x, y, father);//�����µĽڵ㣬���뿪���б�
		countGHF(point, endPos, g);
		openList.push_back(point);
	}
}

//�����ΧһȦ�Ƿ��к���
bool CheckRiver()
{


}

//ֻ�������������߱�
void Astar::NextStep(Info &info, Node* current)
{

	//���������ҵ�ÿһ�ֿ��ܽ�����̽�����η��뿪���б�
	checkPoit(current->x - 1, current->y, current, PosWeight(info,current->x - 1, current->y));//��
	checkPoit(current->x + 1, current->y, current, PosWeight(info, current->x + 1, current->y));//��
	checkPoit(current->x, current->y + 1, current, PosWeight(info, current->x, current->y + 1));//��
	checkPoit(current->x, current->y - 1, current, PosWeight(info, current->x, current->y - 1));//��

	/*������б��
	checkPoit(current->x - 1, current->y + 1, current, WeightWH);//����
	checkPoit(current->x - 1, current->y - 1, current, WeightWH);//����
	checkPoit(current->x + 1, current->y - 1, current, WeightWH);//����
	checkPoit(current->x + 1, current->y + 1, current, WeightWH);//����
	*/
}

//��������б��д��ڵ�ǰ�ڵ㣬�ͷ��������б��е�λ�ã����򷵻�-1
int Astar::isContains(vector<Node*>* Nodelist, int x, int y)
{
	for (int i = 0; i <(int)(Nodelist->size()); i++)
	{
		if (Nodelist->at(i)->x == x && Nodelist->at(i)->y == y)
		{
			return i;
		}
	}
	return -1;//���ڿ����б���
}

//������ۺ���f
void Astar::countGHF(Node* sNode, Node* eNode, int g)
{
	//h��g�ļ��㷽ʽ���ᱻ���ۺ���ȡ����������
	int h = (abs(sNode->x - eNode->x) + abs(sNode->y - eNode->y)) * WeightW;//���ƺ�����Ȩ��ȡ�����������*10
	int currentg = sNode->father->g + g;//�Դ��ۺ������ۼ�
	int f = currentg + h;//���ƴ��ۺ���
	sNode->f = f;
	sNode->h = h;
	sNode->g = currentg;
}

bool Astar::compare(Node* n1, Node* n2)
{
	return n1->f < n2->f;
}

//����õ��β����ߣ��ͷ���true
bool Astar::unWalk(int x, int y)
{
	if (temp_map[x][y] == 1)
		return true;
	return false;
}

Astar::Astar() {    }
Astar::~Astar(){    }