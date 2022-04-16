#include "Cancellation.h"

Cancellation::Cancellation(Time et, int id)
{
}

void Cancellation::excute(Company* MainPtr)
{
	Cargo* cancelled = nullptr;
	if (MainPtr->removenormal(cancelled, ID))
	{
		MainPtr->deletecargo(cancelled);
	}
}
