#pragma once
#include "Event.h"
class Cancellation :
    public Event
{
public:
    virtual void excute();
};

