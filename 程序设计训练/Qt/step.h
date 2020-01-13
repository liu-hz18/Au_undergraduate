#ifndef STEP_H
#define STEP_H

#include <QString>
#include <QList>
#include <QDebug>

class Step
{
public:
    Step();
    Step(QString single_order,QList<int> single_arguments);
    QString single_step_order;
    QList<int> single_step_arguments;
    QString getSingleOrder();
    QList<int> getSignleArguments();
    Step& operator=(const Step& cls);

};

#endif // STEP_H
