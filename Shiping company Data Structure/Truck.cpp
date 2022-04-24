#include "Truck.h"

Truck::Truck( int speed, int Tcap, int Mjourney, Itemtype type,int ID)
{
	this->TCap = Tcap;
	this->speed = speed;
	this->Mjourney = Mjourney;
	this->type = type;
	Currjourney = 0;
	this->ID = ID;
}

Truck::Truck()
{
}

int Truck::getcap() const
{
	return TCap;
}

void Truck::updateDI()
{
	DI = 2 * (DDFC / speed) + tl;
}

bool Truck::loadC(Cargo*& c)
{
	bool canadd = MovingC.enqueue(c, -c->getdeldis());
	if (canadd)
	{
		if (c->getdeldis() > DDFC)
			DDFC = c->getdeldis();
		tl = tl + c->getloadt();
		this->updateDI();
	}
	return canadd;
}

int Truck::getspeed() const
{
	return speed;
}

int Truck::getid() const
{
	return ID;
}

void Truck::setDI(int DeliveryT)
{
	DI = DeliveryT;
}

void Truck::IncementJ()
{
	Currjourney = 0;
}

std::ostream& operator<<(std::ostream& f, const Truck* C)
{
	f << C->getid();
	return f;
}
