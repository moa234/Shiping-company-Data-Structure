#pragma once
#include "Event.h"
#include"Queue.h"
#include "Cargo.h"
#include "Company.h"

class Promotion :
    public Event
{
    int extracost;
public:
    Promotion(Time et, int id, int extra);
    Promotion(int id, int extra);
    virtual void excute(Company* MainPtr);
};

