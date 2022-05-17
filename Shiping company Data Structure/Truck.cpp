#include "Truck.h"

Truck::Truck( int speed, int Tcap, int Mjourney, Itemtype type,int ID)
{
	this->TCap = Tcap;
	this->speed = speed;
	this->CheckUpDuration = CheckUpDuration;
	this->type = type;
	Currjourney = 0;
	this->ID = ID;
	maxCargoLT.SetDay(0); maxCargoLT.SetHour(0);
}

/*Truck::Truck()
{
}*/

int Truck::getcap() const
{
	return TCap;
}

Itemtype Truck::GetType()
{
	return type;
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
		if (c->getCDT() > maxCargoLT)
			maxCargoLT = c->getCDT();
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
	if (MovingC.peek(c))
	{
		return true;
	}
	return false;
}

void Truck::SetStartLoading(const Time& T)
{
	StartLoading = T;
}

Time Truck::getStartLoading() const
{
	return StartLoading;
}

void Truck::EndLoading()
{
	StartLoading.SetDay(0);
	StartLoading.SetHour(0);
	maxCargoLT.SetDay(0);
	maxCargoLT.SetHour(0);
}

Time Truck::getMaxCLT() const
{
	return maxCargoLT;
}

bool Truck::dequeuetop(Cargo*& c)
{

	if (MovingC.dequeue(c))
	{
		return true;
	}
	return false;

}

int Truck::getCurrj() const
{
	return Currjourney;
}

int Truck::getMj() const
{
	return CheckUpDuration;
}

void Truck::SetMTime(Time T)
{
	MTime = T;
}


bool Truck::InMaintainence(const Time& T)
{
	if (T == (MTime+CheckUpDuration))
	{
		return false;
	}
	return true;
}

void Truck::EndMaitainence()
{
	MTime.SetDay(0);
	MTime.SetHour(0);
}

int Truck::get_DDFC()
{
	return DDFC;
}

Time Truck::getReturn_time() const
{
	return Returntime;
}

void Truck::setReturn_time(const Time& T)
{
	Returntime = T + (DDFC / speed);
}

void Truck::inc_tDC() 
{
	tDC++;
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



