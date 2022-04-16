#pragma once
#include "Event.h"
#include "Company.h"
#include "Time.h"
class Cancellation :
    public Event
{
public:
    Cancellation(Time et, int id);
    virtual void excute(Company* MainPtr);
};

