#ifndef DROP_H
#define DROP_H

#include <QPaintEvent>
#include <QPainter>

class BioChip;

class Drop
{
public:
    Drop(int x,int y, BioChip* par = nullptr);
    ~Drop();
    bool isExist();
    void setExist(bool);
    int getPoint_x();
    int getPoint_y();
    void setPoint_x(int);
    void setPoint_y(int);
    int getDropOnBoardNum();
    int getDropTotalNum();
    void setState(int t,int x,int y);

private:
    BioChip* parent;
    int point_x;
    int point_y;
    bool exist;
    static int dropCount;
    static int dropOnBoardCount;

};

#endif // DROP_H
