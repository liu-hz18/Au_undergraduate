#ifndef WASHDROP_H
#define WASHDROP_H

#include "astar.h"
#include "point.h"

class Washdrop
{
public:
    Washdrop();
    int starttime;//出发时间
    int totTime;//总时间
    int midtime;//到达中间点的时间
    bool havePath;//当前是否存在路径
    Position midPosition;//中间点
    QList<Position> pathList;//路径列表
    Astar astar;
    //获取清洗路径，如果没有可行路径则返回false
    bool getPath(Position start_pos, Position end_pos, Position mid_pos, int m[][18], int r, int c);
    void setStartTime(int t);
    int getStarttime();
    int getTottime();
    Position getPositionAtTime(int time);
    void reset();
    bool isToEnd(int t);
    int gettimeAtMid();
    Position getMidPosition();
    bool changePath(int m[][18], int cur_time, int r, int c);
};


#endif // WASHDROP_H
