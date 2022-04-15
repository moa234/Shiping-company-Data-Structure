#include "Truck.h"


Truck::Truck(int Tcap, int speed, int Mjourney, Itemtype type)
{
	this->TCap = Tcap;
	this->speed = speed;
	this->Mjourney = Mjourney;
	this->type = type;
	int Currjourney = 0;
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

void Truck::IncementJ()
{
	Currjourney = 0;
}
