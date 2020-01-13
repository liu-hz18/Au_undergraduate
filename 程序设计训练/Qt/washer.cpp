#include "washer.h"

Washer::Washer()
{
    washdropNum = 0;
}

bool Washer::iniPath(int m[][18][18], int temp[][5],int r,int c)
{
    //初始化污染事件列表
    for(int i = 1;i < 20;i ++){
        if(temp[i][0] != 0 && temp[i][1] != 0){
            pollutionEvent p(temp[i][0],temp[i][1],temp[i][2],temp[i][3]);
            this->pollutionList.append(p);
        }
    }
    int pollutionSize = pollutionList.size();

    //为每个清洗液滴规划路径
    Position beg(1,1);
    Position end(c,r);
    for(int i = 1;i <= pollutionSize;i++){
        Position pos(temp[i][0],temp[i][1]);
        int starttime = temp[i][3] - 2;//在污染事件发生前2s出发
        Washdrop drop;
        bool flag = false;
        if((flag = drop.getPath(beg,end,pos,m[starttime],c,r)) == true){
            washdropNum ++;
            drop.setStartTime(starttime);
            this->washdropList.append(drop);
        }
    }
    return true;
}

void Washer::reset()
{
    pollutionList.clear();
    washdropList.clear();
}

QList<Washdrop>::Iterator Washer::getOnMove(int cur_time)
{
    QList<Washdrop>::Iterator iter;
    for(iter = this->washdropList.begin();iter != this->washdropList.end();iter++){
        if(cur_time >= iter->starttime && cur_time <= iter->totTime + iter->starttime)break;
    }
    return iter;
}
