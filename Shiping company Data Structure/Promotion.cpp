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
	promoted->inccost(extracost);
	if (promoted)
	{
		promoted->settype(VIP);
		MainPtr->AddVIPList(promoted);
	}
}

