#include "Cancellation.h"

Cancellation::Cancellation(Time et, int id)
{
	ID = id;
	time = et;
}

void Cancellation::excute(Company* MainPtr)
{
	Cargo* cancelled = MainPtr->getNCargo(ID);
	if (cancelled)
	{
		delete cancelled;
	}
}
