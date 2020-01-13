#ifndef WASHER_H
#define WASHER_H

#include <QDebug>
#include "washdrop.h"
#include "pollutionevent.h"

class Washer
{
public:
    Washer();
    int washdropNum;
    QList<pollutionEvent> pollutionList;//污染点列表
    QList<Washdrop> washdropList;//清洗液滴列表
    bool iniPath(int m[][18][18], int temp[][5], int r, int c);
    void reset();
    QList<Washdrop>::Iterator getOnMove(int cur_time);
};

#endif // WASHER_H
