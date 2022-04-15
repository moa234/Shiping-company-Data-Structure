#pragma once
#include "Event.h"
#include "DEFS.h"

class Preparation :
    public Event
{
    Itemtype type;
    int distance;
    int loadt;
    int cost;

public:
    Preparation(Itemtype &ty, Time &t, int &id, int &dis, int &lt, int &c);
    virtual void excute();
};

