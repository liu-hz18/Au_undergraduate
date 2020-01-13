#include "my_head.h"

/*
*         ★★★ATTENTION★★★
* 士兵的id和它在vector里的索引（index）不一样！！！
*
* 经验：struct可以直接复制，复制时内部的struct同样复制，但pointer指向空间并不改变。
*
* 经验：用形参pointer传输数据时，用引用，且在函数体内为引用分配空间
* 
* 目前还需要：
* 副塔防卫升级为副塔+主塔防卫
* 修改士兵移动后的点occupied情况【否则有些移动会绕路】
* 中塔-副塔核心策略完善
* 在主塔生成的兵要尽早到副塔来(防守任务时的站位很重要)
*/

/**********************************基础算法*************************************/

//欧氏距离
float euler_distance(int x1, int x2, int y1, int y2)
{
	return sqrt(pow((x1 - x2), 2.) + pow((y1 - y2), 2.));
}

//曼哈顿距离
int manhattan_distance(int x1, int x2, int y1, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

/**********************************底层功能*************************************/
//Tpoint打印函数
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

//TSoldier打印函数
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

//打印任务分配结果
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


/**********************************基本命令*************************************/

//生成士兵命令(类型1-7)
void c_produce_soldier(Info& info, int tower, int soldierType )
{
	info.myCommandList.addCommand(Produce, tower, soldierType);
}

//移动士兵命令
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

//升级塔命令
void c_upgrade(Info& info, int towerId)
{
	info.myCommandList.addCommand(Upgrade, towerId);
}

//攻击命令
void c_attack(Info& info, int so_id, int x, int y)
{
	info.myCommandList.addCommand(Attack, so_id, x, y);
}

/*******************************操作·判断**********************************/

/*****搜索*****/

//搜索走向某点的最优下一步_s
bool search_step(Info& info, Node* startPos, Node* endPos, Node*& res, int id, int index)
{
	Astar astar;
	TSoldier* temp;

	//获得士兵移动力
	int movedis = 0;
	if (get_soldier_by_id(info, id, temp))
		movedis = temp->move_left;
	astar.CreateMap(info, startPos->x, startPos->y, movedis);		//地图预处理,传入当前坐标和士兵移动力

	Node* finalPos;											//最终决策走兵的坐标
	if ((finalPos = astar.search(info, startPos, endPos, movedis)) != NULL)
	{
		res = finalPos;
		return true;
	}
	else return false;				//未找到合适路径
}

//根据士兵id搜索信息
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

//根据士兵id搜索下标
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


/*****操作*****/

//士兵移动至某点_s,so_info:<so_index,so_id>
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

		//寻找最优落脚点
		Node* result = NULL;
		if (search_step(info, start, end, result, so_id, so_index))
		{
			printf("next step:(%d, %d)\n", result->x, result->y);
			int x_dis = result->x - x;
			int y_dis = result->y - y;

			//x方向
			if (x_dis > 0)
			{
				c_move_soldier(info, so_id, RIGHT, min(abs(x_dis), max_move));
			}
			else if (x_dis < 0)
			{
				c_move_soldier(info, so_id, LEFT, min(abs(x_dis), max_move));
			}

			//y方向
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

/*****判断*****/

//士兵在某范围
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

// 士兵在某点
bool soldier_at(Info& info, int so_index, int x, int y)
{
	if ((info.soldierInfo[so_index].x_position == x)
		&& (info.soldierInfo[so_index].y_position == y)){
		return true;
	}

	else
		return false;
}

//搜索某位置某范围内特定格子_s(欧拉距离)(仅返回第一个搜索结果)
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


/*******************************攻击**********************************/


/*****攻击塔*****/

//士兵可以攻击某塔_s
bool soldier_can_attack_tow(Info& info, int so_index, int to_id, set<pair<int, int>>& result)
{
	int tow_x = tw_position[to_id][0];			//获取该塔位置
	int tow_y = tw_position[to_id][1];
	
	int so_x = info.soldierInfo[so_index].x_position;		//我方位置
	int so_y = info.soldierInfo[so_index].y_position;
	int range = info.soldierInfo[so_index].range;			//攻击范围
	int move = info.soldierInfo[so_index].move_left;		//剩余移动力

	bool can_attack = false;
	result.clear();

	//外层循环：找到士兵可能移动到的点
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

			//内层循环：找到士兵可能攻击到的点
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
						if (euler_distance(x,tow_x,y,tow_y)<1.5)	//欧氏距离小于5说明是塔上的点
						{
							pair<int, int> p(i, j);
							result.insert(p);
							can_attack = true;
							break;
						}
					}
				}
			}
			//内层循环结束
		}
	}
	return can_attack;
}

//士兵可以直接攻击某塔_s
bool soldier_can_straightly_attack_tow(Info& info, int so_index, int to_id, pair<int, int>& p)
{
	int tow_x = tw_position[to_id][0];			//获取该塔位置
	int tow_y = tw_position[to_id][1];

	int so_x = info.soldierInfo[so_index].x_position;		//我方位置
	int so_y = info.soldierInfo[so_index].y_position;
	int range = info.soldierInfo[so_index].range;			//攻击范围

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
				euler_distance(x, tow_x, y, tow_y)<1.5)	//欧氏距离小于5说明是塔上的点
			{
				p = pair<int, int>(x,y);
				return true;
			}
		}
	}
	return false;
}


//搜索某士兵攻击某塔的最优位置(待改进)
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


//事件：调用某一num士兵进攻某塔直到完成
void soldier_occupy_tower(Info& info, int so_id, int to_id)
{
	int index;
	get_index_by_id(info, so_id, index);						//获取士兵索引
	int id = so_id;						//获取士兵id
	printf("so_id = %d, spo_index = %d #soldier_occupy_tower \n",id,index);
	int x_pos = info.soldierInfo[index].x_position;			//获取该士兵当前位置
	int y_pos = info.soldierInfo[index].y_position;
	int range = info.soldierInfo[index].range;

	int tow_x = tw_position[to_id][0];						//获取该塔位置
	int tow_y = tw_position[to_id][1];

	set<pair<int, int>> result;								//保存可能攻击点的搜索结果
	if (!soldier_can_attack_tow(info, index, to_id, result))
	{
		soldier_march_to(info, pair<int,int>(index,id), tow_x, tow_y);
	}
	else
	{
		pair<int, int> tarp;								//最佳攻击点
		if (soldier_can_straightly_attack_tow(info, index, to_id, tarp))
		{
			printf("Attack!!(tow)\n");
			c_attack(info, id, tarp.first, tarp.second);
		}
		else if (get_attack_tow_point(info,to_id,index,result,tarp))
		{
			//移动
			soldier_march_to(info, pair<int, int>(index, id), tarp.first, tarp.second);

			//★★更新位置
			x_pos = info.soldierInfo[index].x_position;	
			y_pos = info.soldierInfo[index].y_position;

			//获取攻击目标点
			pair<int, int> tara;
			if (search_type_around(info, tower, x_pos, y_pos, range, tara))
			{
				//攻击
				printf("Attack!!(tow)\n");
				c_attack(info, id, tara.first, tara.second);
			}
		}
	}
}



/*****攻击兵*****/

//搜索某塔周围所有敌方士兵_s
bool search_invader_around(Info& info, int to_id,int range, vector<int>& invader)
{
	int tow_x = tw_position[to_id][0];
	int tow_y = tw_position[to_id][1];

	//加入所有新发现的士兵
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
					if (it == invader.end())			//如果vector里没有，就把该id加入
						invader.push_back(id);
				}
			}
		}
	}
	TSoldier* temp;
	//清除所有不在范围内的士兵
	for (vector<int>::iterator it = invader.begin();
		it != invader.end(); it++)
	{
		if (!get_soldier_by_id(info, *it, temp))
			invader.erase(it);
	}

	return !(invader.empty());
}

//获取某塔周围第一个敌方士兵id
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

//士兵可以攻击某士兵_s
bool soldier_can_attack_sol(Info& info, int so_index, int enm_id, set<pair<int, int>>& result)
{
	TSoldier *enm;
	get_soldier_by_id(info, enm_id, enm);
	int enm_x = enm->x_position;					//敌方位置
	int enm_y = enm->y_position;

	int so_x = info.soldierInfo[so_index].x_position;		//我方位置
	int so_y = info.soldierInfo[so_index].y_position;
	int range = info.soldierInfo[so_index].range;		//攻击范围
	int move = info.soldierInfo[so_index].move_left;	//剩余移动力

	bool can_attack = false;
	result.clear();

	//外层循环：找到士兵可能移动到的点(含不动)
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

			//内层循环：找到士兵可能攻击到的点
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
			//内层循环结束
		}
	}
	return can_attack;
}

//士兵可以直接攻击某兵_s
bool soldier_can_straightly_attack_sol(Info& info, int so_index, int enm_id, pair<int, int>& p)
{
	TSoldier *enm;
	get_soldier_by_id(info, enm_id, enm);
	int enm_x = enm->x_position;					//敌方位置
	int enm_y = enm->y_position;

	int so_x = info.soldierInfo[so_index].x_position;		//我方位置
	int so_y = info.soldierInfo[so_index].y_position;
	int range = info.soldierInfo[so_index].range;			//攻击范围

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


//搜索某士兵攻击某士兵的最优位置(待改进)
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


//事件：调用某一士兵对某id侵略者发动攻势_s
void offensive_against_soldier(Info& info, int so_id, int inv_id)
{
	TSoldier *temp;
	if (get_soldier_by_id(info, inv_id, temp))					//若能搜到表明目标士兵存活
	{
		int index ;	
		get_index_by_id(info, so_id, index);					//我方士兵索引
		int id = so_id;											//我方士兵id
		int x_pos = info.soldierInfo[index].x_position;			//我方士兵当前位置
		int y_pos = info.soldierInfo[index].y_position;
		int range = info.soldierInfo[index].range;				//我方士兵攻击范围

		//printf("position: (%d, %d)\n", x_pos, y_pos);

		int enm_index ;
		get_index_by_id(info, inv_id, enm_index);				//敌方士兵索引
		int enm_x = info.soldierInfo[enm_index].x_position;		//敌方士兵当前位置
		int enm_y = info.soldierInfo[enm_index].y_position;

		set<pair<int, int>> result;								//保存可能攻击点的搜索结果
		if (!soldier_can_attack_sol(info,index,inv_id,result))
		{
			soldier_march_to(info, pair<int,int>(index,id), enm_x, enm_y);
		}

		else
		{
			pair<int, int> tarp;								//最佳攻击点
			if (soldier_can_straightly_attack_sol(info,index,inv_id,tarp))
			{
				printf("Straightly Attack!!!\n");
				c_attack(info, id, tarp.first, tarp.second);
			}
			else if (get_attack_sol_point(info,inv_id,index,result,tarp))
			{
				//移动
				soldier_march_to(info, pair<int, int>(index, id), tarp.first, tarp.second);
				//攻击
				printf("Attack!!!\n");
				c_attack(info, id, enm_x, enm_y);
			}
		}
	}
}



/*************************************事件****************************************/

//清除某塔附近的敌方威胁_s：ids,己方士兵id;so_num,参加任务士兵个数
void clear_around_tower(Info& info, int to_id, const int* ids, int so_num, vector<int>& invader)
{
	printf("clear_around_on\n");
	int invd_id = -1;
	//获取首个敌方士兵id
	if (get_invader_around(info, to_id, invader,invd_id))
	{		
		//所有参加任务的士兵攻击敌方士兵
		for (int i = 0; i < so_num; i++)
		{
			printf("Soldier id:%d offensive_against_soldier\n", ids[i]);
			offensive_against_soldier(info, ids[i], invd_id);
		}
	}
}


/**********************************策略***********************************/

//生产+升级策略_s
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

		//更新是否能生产
		can_produce = !((current_pop + required_pop) > max_pop);
		
		//能生产，先考虑生产
		if (can_produce)
		{
			//副塔没占领前，用主塔生成兵
			if (!have_sec_tow && (current_res > required_res))
			{
				c_produce_soldier(info, main_tow, type);
			}

			//副塔占领后，用副塔生成兵
			else if (have_sec_tow && (current_res > required_res))
			{
				c_produce_soldier(info, sec_tow, type);
			}
		}
		
		//不能生产考虑升级
		else if (!can_produce)
		{
			printf("	Ready to Upgrade!\n");
			//先考虑副塔
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


		//任务:占领副塔

		int num = defend_id.size();
		int* ids = new int[num];
		for (int i = 0; i < num; i++)
		{
			ids[i] = defend_id[i];
		}
		
		if (occupy_secondary_tower_on)
		{
			for (int i = 0; i < num; i++)			//开局用0-2士兵占领副塔
			{
				printf("soldier id:%d occupy_second_tower\n", ids[i]);
				soldier_occupy_tower(info, ids[i], sec_tow);
			}
		}
	}
}


//中塔策略【】
void middle_tower(Info& info)
{
	printf("middle_tower_on\n");
	//获取参与中塔任务士兵
	int num = mid_id.size();
	int* ids = new int[num];
	for (int i = 0; i < num; i++)
	{
		ids[i] = mid_id[i];
	}

	//没到先往中间走
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

	//先干塔
	if(info.towerInfo[8].owner != my_id)
	{
		printf("occupy_middle_tower!\n");
		for (int i = 0; i < mid_id.size(); i++)
		{
			soldier_occupy_tower(info, ids[i], 8);
		}
	}
	//再干兵
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


//主-副塔防卫策略
void defend_second_tower(Info& info)
{
	//动态规划防守士兵数量
	int defender_num = defend_id.size();
		
	int *ids = new int[defender_num];
	for (int i = 0; i < defender_num; i++)
	{
		ids[i] = defend_id[i];
	}

	vector<int> invader;							//用于保存侵略者id
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


//核心策略【】
void core_strategy(Info& info)
{
	//主塔-副塔部分
	if (have_sec_tow)
	{
		defend_second_tower(info);
	}

	//中塔-其他部分
	if (middle_tower_on)
	{
		printf("middle_tower_on!\n");
		middle_tower(info);
	}
}


/**********************************功能函数*************************************/
//地图初始化_s
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


//任务分配_s
void task_assign(Info& info)
{
	//大思路：删除——补充——重分配
	
	//遍历删除defend死亡士兵
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

	//遍历删除mid死亡士兵
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

	//获得所有新生成士兵 my_so_num<=5给defend，>=6给mid
	if (0 < my_so_num && my_so_num <= 5)
	{
		for (auto it = my_soldier.cbegin(); it != my_soldier.cend(); it++)
		{
			int id = it->second;
			//查找，如果defend和mid里都没有，就把该id加入defend
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
			//查找，如果defend和mid里都没有，就把该id加入mid
			int id = it->second;
			auto it2 = find(mid_id.begin(), mid_id.end(), id);
			auto it3 = find(defend_id.begin(), defend_id.end(), id);
			if (it2 == mid_id.end() && (it3 == defend_id.end())){
				mid_id.push_back(id);
			}
		}
	}
	
	//重分配
	if (my_so_num == 4 && !mid_id.empty())
	{
		//兵力不足5，所有兵力回防
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

//信息初始化
void info_init(Info& info)
{
	//初始化地图
	map_init(info);

	//获取己方id√
	my_id = info.myID;

	//获取兵塔坐标√
	for (int i = 0; i < 9; i++)
	{
		tw_position[i][0] = info.towerInfo[i].x_position;
		tw_position[i][1] = info.towerInfo[i].y_position;
	}

	//获取己方所有士兵√	
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

	//任务分配
	task_assign(info);
}

//控制量初始化
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

//事件状态初始化
void event_init(Info& info)
{
	have_sec_tow = info.towerInfo[sec_tow].owner == info.myID;

	occupy_secondary_tower_on = !have_sec_tow && (my_so_num >= 1) ;

	middle_tower_on = !mid_id.empty();

}


//初始化
void init(Info& info)
{
	//信息初始化
	info_init(info);
	
	//控制量初始化
	comd_init(info);

	//随机数种子
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	long millis = (sys.wMinute * 60 + sys.wSecond) * 1000 + sys.wMilliseconds;
	srand((unsigned)millis);
	
	//初始化事件状态
	event_init(info);

	//显示关键信息
	printf("Round: %d\n", info.round);
	printf("my_id = %d\n", info.myID);
}

//调试
void debug(Info& info)
{
	if (info.round >= 40)
	{
		printf("\n\n");
		system("pause");
	}	
}

/************************************主函数***************************************/

void player_ai(Info& info)
{
	init(info);					//所有初始化动作
	
	produce(info);				//生产+升级

	core_strategy(info);		//核心策略

	debug(info);
}




/************************************Astar类实现***************************************/

//地形预处理函数,对视野范围内的地形进行预处理，将河流和塔以及已经占据的位置设为障碍
void Astar::CreateMap(Info& info,int x, int y, int movedis)//参数为当前士兵坐标,士兵移动力
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
			else if(grid_0 == river)//河流代表值设为2
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

//核心算法:输入初始节点和最终节点，以及士兵移动力
Node* Astar::search(Info& info, Node* startPos, Node* endPos, int movedis = 5)//默认设为轻骑兵的5
{
	//超出地图范围的处理
	if (startPos->x < 0 || startPos->x > row || startPos->y < 0 || startPos->y >col ||
		endPos->x < 0 || endPos->x > row || endPos->y < 0 || endPos->y > col)
		return NULL;

	Node* current;//当前节点
	this->startPos = startPos;
	this->endPos = endPos;
	openList.push_back(startPos);

	//把开始的节点放入openlist后开始查找上下左右的4个节点，如果坐标超长范围或在closelist就return 
	//如果已经存在openlist就对比当前节点到遍历到的那个节点的G值和当前节点到原来父节点的G值 如果原来的G值比较大 不用管 
	//否则重新赋值G值 父节点 和f 如果是新节点 加入到openlist 直到opellist为空或找到终点

	while (openList.size() > 0)
	{

		current = openList[0];//队列的第一个是当前节点

		if ((current->x == endPos->x && (current->y == endPos->y)) 
			|| (countNode(current) >= movedis))//判断是否到达目标，或者超出视野
		{

			openList.clear();
			closeList.clear();
			return current;//返回这一步决策要走的节点
		}
		else if (countNode(current) >= movedis)
		{
			return NULL;
		}

		NextStep(info,current);//走一步

		closeList.push_back(current);//将上一步的坐标放入封闭列表，不需要再进行考虑
		openList.erase(openList.begin());//将开放列表的第一个即上一步的坐标清除
		std::sort(openList.begin(), openList.end(), compare);//排序

	}
}

//路径长度计数器，递归，返回可行路径的节点个数
int countNode(Node*current)
{
	if (current->father != NULL)
		return countNode(current->father) + 1;
	else return 0;
}

//输入坐标，返回当前点的代价系数
int PosWeight(Info& info, int x, int y)
{
	int Weight = 10;							    //默认值为10
	TLandForm Pos = info.pointInfo[x][y].land;
	if (Pos==Mountain)								//山地地形设为20,以尽可能避开山地
		Weight = 20;
	
	return Weight;
}

//这个函数负责父子节点之间的继承
void Astar::checkPoit(int x, int y, Node* father, int g)//g是累积量
{
	if (x < 0 || x > row || y < 0 || y > col)
		return;
	if (this->unWalk(x, y))
		return;
	if (isContains(&closeList, x, y) != -1)//在 封闭列表中，什么都不做
		return;
	int index;
	if ((index = isContains(&openList, x, y)) != -1)//如果待检查的节点已经在开放列表中，就比较G值
	{
		Node *point = openList[index];
		//用 G 值为参考检查新的路径是否更好, 更低的G值意味着更好的路径，用新的节点继承父节点，否则什么都不做
		if (point->g > father->g + g)
		{
			point->father = father;//更改当前节点的父节点
			point->g = father->g + g;
			point->f = point->g + point->h;
		}
	}
	else//不在开放列表中
	{
		Node * point = new Node(x, y, father);//创建新的节点，放入开放列表
		countGHF(point, endPos, g);
		openList.push_back(point);
	}
}

//检测周围一圈是否有河流
bool CheckRiver()
{


}

//只允许上下左右走兵
void Astar::NextStep(Info &info, Node* current)
{

	//对上下左右的每一种可能进行试探，依次放入开放列表
	checkPoit(current->x - 1, current->y, current, PosWeight(info,current->x - 1, current->y));//左
	checkPoit(current->x + 1, current->y, current, PosWeight(info, current->x + 1, current->y));//右
	checkPoit(current->x, current->y + 1, current, PosWeight(info, current->x, current->y + 1));//上
	checkPoit(current->x, current->y - 1, current, PosWeight(info, current->x, current->y - 1));//下

	/*不考虑斜向
	checkPoit(current->x - 1, current->y + 1, current, WeightWH);//左上
	checkPoit(current->x - 1, current->y - 1, current, WeightWH);//左下
	checkPoit(current->x + 1, current->y - 1, current, WeightWH);//右下
	checkPoit(current->x + 1, current->y + 1, current, WeightWH);//右上
	*/
}

//如果开放列表中存在当前节点，就返回其在列表中的位置，否则返回-1
int Astar::isContains(vector<Node*>* Nodelist, int x, int y)
{
	for (int i = 0; i <(int)(Nodelist->size()); i++)
	{
		if (Nodelist->at(i)->x == x && Nodelist->at(i)->y == y)
		{
			return i;
		}
	}
	return -1;//不在开放列表中
}

//计算估价函数f
void Astar::countGHF(Node* sNode, Node* eNode, int g)
{
	//h和g的计算方式将会被估价函数取代！！！！
	int h = (abs(sNode->x - eNode->x) + abs(sNode->y - eNode->y)) * WeightW;//估计函数，权重取距离的曼哈顿*10
	int currentg = sNode->father->g + g;//对代价函数的累加
	int f = currentg + h;//估计代价函数
	sNode->f = f;
	sNode->h = h;
	sNode->g = currentg;
}

bool Astar::compare(Node* n1, Node* n2)
{
	return n1->f < n2->f;
}

//如果该地形不能走，就返回true
bool Astar::unWalk(int x, int y)
{
	if (temp_map[x][y] == 1)
		return true;
	return false;
}

Astar::Astar() {    }
Astar::~Astar(){    }