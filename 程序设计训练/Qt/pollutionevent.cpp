#include "pollutionevent.h"

pollutionEvent::pollutionEvent(int _x, int _y, int _t1, int _t2):
    x(_x),y(_y),t1(_t1),t2(_t2)
{}

int pollutionEvent::gett1()
{
    return this->t1;
}

int pollutionEvent::gett2()
{
    return this->t2;
}
