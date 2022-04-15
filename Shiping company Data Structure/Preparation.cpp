#include "Preparation.h"


Preparation::Preparation(Itemtype type, Time time, int ID, int Dis, int Lt, int cost)
{
	this->type = type;
	this->ID = ID;
	this->Dis = Dis;
	this->cost = cost;
	this->Lt = Lt;
	this->time = time;
	MainPtr = nullptr;
}

void Preparation::excute(Company* MainPtr)
{
	Cargo* ptr = new Cargo(ID, Dis, Lt, cost);
	if (type == Normal)
	{
		
	}
}

