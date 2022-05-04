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
	Currjourney++;
}

bool Truck::peekTopC(Cargo* c)
{
	MovingC.peek(c);
	if (c)
	{
		return true;
	}
	return false;
}

Time Truck::getStartLoading() const
{
	return StartLoading;
}

Time Truck::getMaxCLT() const 
{
	return maxCargoLT;
}

bool Truck::dequeuetop(Cargo* & c)
{
	MovingC.dequeue(c);
	if (!c)
	{
		return false;
	}
	return true ;

}

int Truck::getCurrj() const
{
	return Currjourney;
}

int Truck::getMj() const
{
	return Mjourney;
}

std::ostream& operator<<(std::ostream& f, Truck* C)
{
	if (!C->MovingC.isempty())
		f << " ";
	f << C->getid();
	if (!C->MovingC.isempty())
	{
		Cargo* type;
		C->MovingC.peek(type);
		Itemtype t = type->gettype();
		if (t == Normal)
		{
			f << "[";
			C->MovingC.print();
			f << "]";
		}
		else if (t == VIP)
		{
			f << "{";
			C->MovingC.print();
			f << "}";
		}
		else if (t == Special)
		{
			f << "(";
			C->MovingC.print();
			f << ")";
		}
	}
	
	return f;
}



