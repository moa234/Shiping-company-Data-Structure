#include "Promotion.h"
#include "DEFS.h"

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
	//Cargo C(Normal);
	//bool x=normalWaitingList.peek(C);
	//if (C.getpreptd()> AutoP)
	//{
	//	return true;
	//}
	return false;
}

Promotion::Promotion(Time et, int id, int extra)
{
	time = et;
	ID = id;
	extracost = extra;
}

void Promotion::excute(Queue<Cargo>& normalWaitingList,Queue<Cargo>& VipWaitingList)
{
	if (toPromote(normalWaitingList))
	{
		//Cargo C(Normal);
		//normalWaitingList.dequeue(C);
		//VipWaitingList.enqueue(C);
		//C.setitemtype(VIP);
	}
	
}

void Promotion::excute(Company* MainPtr)
{
}

