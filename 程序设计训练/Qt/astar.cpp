#include "astar.h"

Astar::Astar() {    }
Astar::~Astar(){    }

//路径长度计数器，递归，返回可行路径的节点个数
int countNode(Node*current)
{
    if (current->father != nullptr)
        return countNode(current->father)+1;
    else return 0;
}

//核心算法
//输入初始节点和最终节点
Node* Astar::search(Node* startPos, Node* endPos)
{
    //超出地图范围的处理
    if (startPos->x < 0 || startPos->x > row || startPos->y < 0 || startPos->y >col ||
        endPos->x < 0 || endPos->x > row || endPos->y < 0 || endPos->y > col)
        return nullptr;
    Node* current;//当前节点
    this->startPos = startPos;
    this->endPos = endPos;
    openList.push_back(startPos);

    while (openList.size() > 0)
    {
        current = openList[0];//队列的第一个是当前节点
        if ((current->x == endPos->x && current->y == endPos->y))
        {
            openList.clear();
            closeList.clear();

            return current;//返回这一步决策要走的节点
        }
        else if(countNode(current) >= 100000)
        {
            return nullptr;
        }

        NextStep(current);
        closeList.push_back(current);   //将上一步的坐标放入封闭列表，不需要再进行考虑
        openList.erase(openList.begin());//将开放列表的第一个即上一步的坐标清除
        sort(openList.begin(), openList.end(), compare);//排序
    }
    return nullptr;
}

void Astar::checkPoit(int x, int y, Node* father, int g)//g是累积量
{
    if (x < 0 || x > row || y < 0 || y > col)
        return ;
    if (this->unWalk(x, y))
        return ;
    if (isContains(&closeList, x, y) != -1)
        return ;

    int index;
    if ((index = isContains(&openList, x, y)) != -1)//如果待检查的节点已经在开放列表中，比较G值
    {
        Node *point = openList[index];
        //用 G 值为参考检查新的路径是否更好, 用新的节点继承父节点
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

//只允许上下左右
void Astar::NextStep(Node* current)
{
    //对上下左右的每一种可能进行试探，依次放入开放列表
    checkPoit(current->x - 1, current->y, current, WeightW );//左
    checkPoit(current->x + 1, current->y, current, WeightW );//右
    checkPoit(current->x, current->y + 1, current, WeightW );//上
    checkPoit(current->x, current->y - 1, current, WeightW );//下
}

//如果开放列表中存在当前节点，就返回其在列表中的位置，否则返回-1
int Astar::isContains(vector<Node*>* Nodelist, int x, int y)
{
    for (int i = 0; i <int( Nodelist->size()); i++)
    {
        if (Nodelist->at(i)->x == x && Nodelist->at(i)->y == y)
        {
            return i;
        }
    }
    return -1;
}

//计算估价函数f
void Astar::countGHF(Node* sNode, Node* eNode, int g)
{
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

bool Astar::unWalk(int x, int y)
{
    if (map[x][y] == 1)
        return true;
    return false;
}

void Astar::getPathCur(Node *current)
{
    if(current->father != nullptr){
        getPathCur(current->father);
    }
    Position pos(current->x,current->y);
    path.push_back(pos);
}

QList<Position> Astar::getPath(Position start, Position end, int m[][18], int r, int c)
{
    QDebug out = qDebug();
    path.clear();

    this->row = r;
    this->col = c;
    Node* startPos = new Node(start.x,start.y);
    Node* endPos = new Node(end.x,end.y);
    Node* current;

    iniMatrix(m);

    if((current = search(startPos,endPos)) != nullptr){
        getPathCur(current);
    }

    for(int i = 0;i < 18;i ++,out<<"\n"){
        for(int j = 0;j < 18;j ++){
            out<<m[i][j];
        }
    }
    return path;
}

void Astar::iniMatrix(int m[][18])
{
    for(int i = 0;i < 18;i ++){
        for(int j = 0;j < 18;j ++){
            if(i == 0 || j == 0)map[i][j] = 1;
            else map[i][j] = m[i][j];
        }
    }
}


