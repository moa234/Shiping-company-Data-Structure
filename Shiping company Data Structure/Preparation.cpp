#include "Preparation.h"


Preparation::Preparation(Itemtype type, Time time, int ID, int Dis, int Lt, int cost)
{
	this->type = type;
	this->ID = ID;
	this->Dis = Dis;
	this->cost = cost;
	this->Lt = Lt;
	this->time = time;
}

void Preparation::excute(Company* MainPtr)
{
	Cargo* ptr = new Cargo(ID, Dis, Lt, cost, time);
	if (type == Normal)
	{
		MainPtr->AddNormList(ptr);
	}
	if (type == Special)
	{
		MainPtr->AddSpeList(ptr);
	}
	if (type == VIP)
	{
		MainPtr->AddVIPList(ptr);
	}
}

