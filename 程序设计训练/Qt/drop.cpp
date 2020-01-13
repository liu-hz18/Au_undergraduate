#include "drop.h"

Drop::Drop(int x, int y, BioChip *par):
    parent(par),
    point_x(x),
    point_y(y),
    exist(true)
{
    dropCount ++;
    dropOnBoardCount ++;
}

Drop::~Drop()
{
    if(isExist()){
        dropCount --;
        dropOnBoardCount --;
    }else{
        dropCount --;
    }
}

//静态变量在类外初始化
int Drop::dropCount = 0;
int Drop::dropOnBoardCount = 0;

bool Drop::isExist()
{
    return exist;
}

void Drop::setExist(bool state)
{
    exist = state;
    if(exist == false){
        dropOnBoardCount --;
    }
}

int Drop::getPoint_x()
{
    return point_x;
}

int Drop::getPoint_y()
{
    return point_y;
}

void Drop::setPoint_y(int y)
{
    point_y = y;
}

void Drop::setPoint_x(int x)
{
    point_x = x;
}

int Drop::getDropOnBoardNum()
{
    return dropOnBoardCount;
}

int Drop::getDropTotalNum()
{
    return dropCount;
}

