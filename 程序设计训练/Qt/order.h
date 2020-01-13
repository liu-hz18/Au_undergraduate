#ifndef ORDER_H
#define ORDER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QQueue>
#include <QDebug>
#include "step.h"

class BioChip;

class Order
{
public:
    Order();
    ~Order();
    bool readFile(const QString& FileName);
    //QTimer* globalTimer;//全局定时器
    QQueue<Step> order;//命令队列
    QString getCurOrder();//获取当前队列第一的任务
    QList<int> getCurArguments();//获取当前队列第一的任务参数
    bool isEmpty();
    Step curStep;
    void takefirst();
    Step& getcurStep();

};

#endif // ORDER_H
