#pragma once
#include "Event.h"
#include"Queue.h"
#include "Cargo.h"
#include "Company.h"

class Promotion :
    public Event
{
    int AutoP; //max unloaded time
    int extracost;
public:
    Promotion(Time et, int id, int extra);
    virtual void excute(Queue<Cargo>& normalWaitingList, Queue<Cargo>& VipWaitingList);
    virtual void excute(Company* MainPtr);
    void SetAutoP(int T);
    int GetAutoP();
    bool toPromote(Queue<Cargo>& WaitingList);
};

