#include "Promotion.h"


void Promotion::SetAutoP(int T)
{
	AutoP = T;
}

int Promotion::GetAutoP()
{
	return AutoP;
}

bool Promotion:: toPromote(Queue<Cargo>& normalWaitingList)
{
	Cargo C(Normal);
	bool x=normalWaitingList.peek(C);
	if (C.getpreptd()> AutoP)
	{
		return true;
	}
	return false;
}

void Promotion::excute(Queue<Cargo>& normalWaitingList,Queue<Cargo>& VipWaitingList)
{
	if (toPromote(normalWaitingList))
	{
		Cargo C(Normal);
		normalWaitingList.dequeue(C);
		VipWaitingList.enqueue(C);
		
	}
	
}
