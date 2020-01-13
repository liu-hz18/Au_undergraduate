#include "washdrop.h"

Washdrop::Washdrop()
{

}

//每个液滴清洗一个点，形成路径
bool Washdrop::getPath(Position start_pos, Position end_pos, Position mid_pos,int m[][18],int r,int c)
{
    QList<Position> temp_path;
    temp_path = astar.getPath(start_pos,mid_pos,m,r,c);
    if(temp_path.size() == 0){
        havePath = false;
        return false;
    }
    this->pathList.append(temp_path);
    midPosition = mid_pos;
    midtime = temp_path.size();

    temp_path = astar.getPath(mid_pos,end_pos,m,r,c);
    if(temp_path.size() == 0){
        havePath = false;
        return false;
    }
    temp_path.pop_front();
    this->pathList.append(temp_path);

    this->totTime = pathList.size();

    for (QList<Position>::Iterator temp_iter = pathList.begin();temp_iter != pathList.end();temp_iter ++) {
        qDebug()<<"("<<(*temp_iter).x<<","<<(*temp_iter).y<<")";
    }

    havePath = true;
    return true;
}

void Washdrop::setStartTime(int t)
{
    this->starttime = t;
}

int Washdrop::getStarttime()
{
    return this->starttime;
}

int Washdrop::getTottime()
{
    return this->totTime;
}

Position Washdrop::getPositionAtTime(int time)
{
    int count;
    QList<Position>::Iterator iter = this->pathList.begin();
    for (count = 0;count < time && time <= totTime;count++,iter++) {}
    return (*iter);
}

void Washdrop::reset()
{
    pathList.clear();
}

bool Washdrop::isToEnd(int t)
{
    if(t - starttime >= midtime)return true;
    else return false;
}

int Washdrop::gettimeAtMid()
{
    return midtime;
}

Position Washdrop::getMidPosition()
{
    return midPosition;
}

bool Washdrop::changePath(int m[][18], int cur_time, int r, int c)
{
    if(havePath){
        QList<Position>::Iterator iter = pathList.begin();
        QList<Position> temp;
        int count = 0;
        for(;iter != pathList.end() && count < cur_time - starttime;iter++,count ++){
            temp.append(*iter);
        }
        Position cur_pos;
        if(count == cur_time - starttime)cur_pos = *iter;
        pathList.clear();
        pathList.append(temp);
        QList<Position> temp_path;
        Position end_pos(c,r);
        if(isToEnd(cur_time)){
            temp_path = astar.getPath(cur_pos,end_pos,m,c,r);
            if(temp_path.size() == 0){
                havePath = false;
                return false;
            }
            this->pathList.append(temp_path);
        }else{
            temp_path = astar.getPath(cur_pos,midPosition,m,c,r);
            if(temp_path.size() == 0){
                havePath = false;
                return false;
            }
            this->pathList.append(temp_path);
            midtime = pathList.size();
            temp_path = astar.getPath(midPosition,end_pos,m,c,r);
            if(temp_path.size() == 0){
                havePath = false;
                return false;
            }
            temp_path.pop_front();
            this->pathList.append(temp_path);
        }

        this->totTime = pathList.size();

        qDebug()<<"pathlist:\n";
        for (QList<Position>::Iterator temp_iter = pathList.begin();temp_iter != pathList.end();temp_iter ++) {
            qDebug()<<"("<<(*temp_iter).x<<","<<(*temp_iter).y<<")";
        }

        return true;
    }else {
        havePath = false;
        return false;
    }

}

