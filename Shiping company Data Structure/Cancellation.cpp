#include "Cancellation.h"

Cancellation::Cancellation(Time et, int id)
{
	ID = id;
	time = et;
}

void Cancellation::excute(Company* MainPtr)
{
	Cargo* cancelled /*= MainPtr->removenormal(ID)*/ = nullptr;
	if (cancelled)
	{
		MainPtr->deletecargo(cancelled);
	}
}
