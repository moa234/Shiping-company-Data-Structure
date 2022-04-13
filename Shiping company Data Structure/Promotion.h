#pragma once
#include "Event.h"
#include"Queue.h"
#include "Cargo.h"
class Promotion :
    public Event
{
    int AutoP; //max unloaded time

public:
    virtual void excute(Queue<Cargo>& normalWaitingList, Queue<Cargo>& VipWaitingList);
    void SetAutoP(int T);
    int GetAutoP();
    bool toPromote(Queue<Cargo>& WaitingList);
};

