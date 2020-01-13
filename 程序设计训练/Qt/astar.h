#ifndef ASTAR_H
#define ASTAR_H

//提供接口 QList<Position> getPath(Position start,Position end,int m[][18],int r,int c);

#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>
#include <QList>
#include <QDebug>
#include "point.h"
using namespace std;

//路径存储在链表里
typedef struct Node
{
    int x, y;   //坐标
    int g;      //起始点到当前点实际代价
    int h;      //当前节点到目标节点最佳路径的估计代价
    int f;      //估计值 f = g + h
    Node* father;//父节点

    Node(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->g = 0;
        this->h = 0;
        this->f = 0;
        this->father = nullptr;
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

class Astar{
public:
    Astar();
    ~Astar();
    Node* search(Node* startPos, Node* endPos);
    void checkPoit(int x, int y, Node* father, int g);
    void NextStep(Node* currentPoint);
    int isContains(vector<Node*>* Nodelist, int x, int y);
    void countGHF(Node* sNode, Node* eNode, int g);
    static bool compare(Node* n1, Node* n2);
    bool unWalk(int x, int y);
    void getPathCur(Node* current);
    QList<Position> getPath(Position start,Position end,int m[][18],int r,int c);
    void iniMatrix(int m[][18]);
    vector<Node*> openList;//开放列表
    vector<Node*> closeList;//封闭列表，存放不需要再进行考虑的节点
    Node *startPos;
    Node *endPos;
    //估价函数的估价放大系数
    int WeightW = 10;// 正方向消耗
    int row;//地图行数
    int col;//地图列数
    int map[18][18];
    QList<Position> path;

};

#endif
