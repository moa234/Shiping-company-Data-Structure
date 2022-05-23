#include "Promotion.h"
#include "DEFS.h"

Promotion::Promotion(Time et, int id, int extra)
{
	time = et;
	ID = id;
	extracost = extra;
}
Promotion::Promotion(int id, int extra)
{
	ID = id;
	extracost = extra;
}

void Promotion::excute(Company* MainPtr)
{
	Cargo* promoted = MainPtr->getNCargo(ID);
	if (promoted)
	{
		promoted->inccost(extracost);
		promoted->settype(VIP);
		promoted->setprom(1);
		MainPtr->AddVIPList(promoted);
	}
}

