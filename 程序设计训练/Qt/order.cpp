#include "order.h"

Order::Order()
{

}

Order::~Order()
{

}

//读取文件，将命令读入内存
bool Order::readFile(const QString &FileName)
{
    order.clear();
    QFile aFile(FileName);
    if(!aFile.exists())return false;
    if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text))return false;
    QTextStream aStream(&aFile);
    aStream.setAutoDetectUnicode(true);
    QString str,_order;//order存放关键词
    QList<int> numlist;//存放数字，第一个为时间，后面偶数个为坐标
    while(!aStream.atEnd()){
        numlist.clear();
        str = aStream.readLine();
        QStringList strlist = str.split(" ");
        _order = strlist.first();
        QStringList arguments = strlist.last().split(";").first().split(",");
        for(QList<QString>::Iterator iter = arguments.begin();iter != arguments.end(); ++iter){
            numlist.push_back(iter->toInt());
        }
        Step temp(_order,numlist);
        this->order.append(temp);
    }
    return true;
}

QString Order::getCurOrder()
{
    if(!order.isEmpty()){
        return order.first().getSingleOrder();
    }
    return nullptr;
}

QList<int> Order::getCurArguments()
{
    return order.takeFirst().getSignleArguments();
}

bool Order::isEmpty()
{
    if(order.isEmpty())return true;
    else return false;
}

void Order::takefirst()
{
    if(!order.isEmpty()){
        curStep = order.takeFirst();
    }
}

Step &Order::getcurStep()
{
    return curStep;
}





