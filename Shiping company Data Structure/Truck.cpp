#include "Truck.h"

Truck::Truck(int speed, int Tcap, int CheckUpDuration, Itemtype type, int ID)
{
	this->TCap = Tcap;
	this->speed = speed;
	this->CheckUpDuration = CheckUpDuration;
	this->type = type;
	Currjourney = 0;
	this->ID = ID;
	Ctype = {};
	DI = 0;
	DDFC = 0;
	loading = 0;
	tl = 0;
	util = 0;
	PreviousLoadC.SetDay(0);
	PreviousLoadC.SetHour(0);
	maxCargoLT.SetDay(0); maxCargoLT.SetHour(0);
	tDC = 0;
	TActive.toTime(0);
}


int Truck::getcap() const
{
	return TCap;
}

int Truck::getCurrj() const
{
	return Currjourney;
}

int Truck::get_DDFC()
{
	return DDFC;
}

int Truck::getid() const
{
	return ID;
}

int Truck::getMj() const
{
	return CheckUpDuration;
}

int Truck::getspeed() const
{
	return speed;
}

Itemtype Truck::GetCargoType()
{
	return Ctype;
}

Itemtype Truck::GetType()
{
	return type;
}

Time Truck::getMaxCLT() const
{
	return maxCargoLT;
}

Time Truck::getReturn_time() const
{
	return Returntime;
}

Time Truck::getStartLoading() const
{
	return StartLoading;
}

void Truck::SetPrevLoad(Time T)
{
	PreviousLoadC = T;
}

Time Truck::GetPrevLoad()
{
	return PreviousLoadC;
}

Time Truck::getTActive()
{
	return TActive;
}

void Truck::SetCargoType(Itemtype type)
{
	Ctype = type;
}

void Truck::setDI(int DeliveryT)
{
	DI = DeliveryT;
}

void Truck::SetMTime(Time T)
{
	MTime = T;
}

void Truck::SetStartLoading(const Time& T, Itemtype ctype)
{
	StartLoading = T;
	SetCargoType(ctype);
	SetPrevLoad(T);
	loading = 1;
}




void Truck::inc_tDC()
{
	tDC++;
}

void Truck::IncementJ()
{
	Currjourney++;
}

void Truck::updateCDT(Time& currTime)
{
	PriorityQueue<Cargo*>* temp=new PriorityQueue<Cargo*>;
	Cargo* c;
	int tload = 0;
	int size = MovingC.GetSize();
	for (int i = 0; i < size; i++)
	{
		MovingC.dequeue(c);
		tload += c->getloadt();
		c->setCDT(currTime.tohours() + (c->getdeldis() / speed) + tload);
		temp->enqueue(c, -c->getCDT().tohours());
	}
	for (int i = 0; i < size; i++)
	{
		temp->dequeue(c);
		MovingC.enqueue(c, -c->getCDT().tohours());
		if (i == size - 1)
		{
			maxCDT = c->getCDT();
			TActive = TActive + maxCDT - currTime;
		}
	}
	delete temp;
}

void Truck::updateDI()
{
	DI = 2 * (DDFC / speed) + tl;
}

void Truck::updateReturn_time()
{
	Returntime = maxCDT + (DDFC / speed);
}

int Truck::GetCargoSize()
{
	return MovingC.GetSize();
}




bool Truck::dequeuetop(Cargo*& c)
{

	if (MovingC.dequeue(c))
	{
		return true;
	}
	return false;

}

bool Truck::InMaintainence(const Time& T)
{
	if (T == (MTime + CheckUpDuration))
	{
		return false;
	}
	return true;
}

bool Truck::loadC(Cargo*& c, Time& t)
{
	bool canadd = MovingC.enqueue(c, -c->getdeldis());
	if (canadd)
	{
		if (c->getdeldis() > DDFC)
			DDFC = c->getdeldis();
		tl = tl + c->getloadt();
		if (c->getloadt() > maxCargoLT.tohours())
		{
			maxCargoLT.toTime(c->getloadt());
		}

		this->updateDI();
		c->setWT(t);
		c->setTID(ID);
	}
	return canadd;
}

bool Truck::peekTopC(Cargo*& c)
{
	if (MovingC.peek(c))
	{
		return true;
	}
	return false;
}

bool Truck::FullCapacity()
{
	return (MovingC.GetSize() == TCap);
}

void Truck::EndMaitainence()
{
	MTime.SetDay(0);
	MTime.SetHour(0);
}

void Truck::EndLoading(Time& currTime)
{
	TActive = TActive + currTime - StartLoading;
	loading = 0;
	StartLoading.SetDay(0);
	StartLoading.SetHour(0);
	PreviousLoadC.SetDay(0);
	PreviousLoadC.SetHour(0);
	if (GetCargoSize() != 0)
	{
		updateCDT(currTime);
		updateReturn_time();
	}
}

float Truck::calcUtil(Time& timer)
{
	if (Currjourney == 0)
		util = 0;
	else
		util = (float)tDC / (TCap * Currjourney) * ((float)TActive.tohours() / timer.tohours());
	return util;
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
	else
	{
		if (C->loading && (C->GetCargoSize() == 0))
		{
			if (C->GetCargoType() == Normal)
				f << "[]";
			if (C->GetCargoType() == Special)
				f << "()";
			if (C->GetCargoType() == VIP)
				f << "{}";
		}
	}

	return f;
}
