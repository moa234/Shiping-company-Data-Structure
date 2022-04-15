#pragma once
#include "Event.h"
class Preparation :
    public Event
{
    int Dis;
    int Lt;
    int cost;
    Itemtype type;
public:
    Preparation(Itemtype type, Time time, int ID, int Dis, int Lt, int cost);
    virtual void excute();
};

