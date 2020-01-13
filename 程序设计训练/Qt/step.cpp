#include "step.h"

Step::Step()
{

}

Step::Step(QString single_order, QList<int> single_arguments):
    single_step_order(single_order),
    single_step_arguments(single_arguments)
{}

QString Step::getSingleOrder()
{
    return this->single_step_order;
}

QList<int> Step::getSignleArguments()
{
    return this->single_step_arguments;
}

Step &Step::operator=(const Step &cls)
{
    this->single_step_order = cls.single_step_order;
    this->single_step_arguments = cls.single_step_arguments;
    return *this;
}
