#include "Truck.h"

Truck::Truck(int tc)
{
	TCap = tc;
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
