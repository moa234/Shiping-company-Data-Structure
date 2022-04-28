#include "Promotion.h"
#include "DEFS.h"

Promotion::Promotion(Time et, int id, int extra)
{
	time = et;
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
		MainPtr->AddVIPList(promoted);
	}
}

