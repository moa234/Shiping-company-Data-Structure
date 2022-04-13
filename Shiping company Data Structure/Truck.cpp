#include "Truck.h"

Truck::Truck(int tc, Itemtype t)
{
	TCap = tc;
	type = t;
}

Truck::Truck()
{
}

int Truck::getcap()
{
	return TCap;
}

int Truck::getspeed()
{
	return speed;
}

void Truck::setDI(int DeliveryT)
{
	DI = DeliveryT;
}
