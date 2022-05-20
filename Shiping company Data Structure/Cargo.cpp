#include "Cargo.h"


Cargo::Cargo(Itemtype t,int ID, int Dis, int Lt, int cost, Time time)
{
	type = t;
	this->ID = ID;
	deldis = Dis;
	this->Lt = Lt;
	this->cost = cost;
	Pt = time;
	delivered = 0;
}

Cargo::Cargo()
{
}

int Cargo::getid() const
{
	return ID;
}

int Cargo::getTID() const
{
	return TID;
}

void Cargo::setTID(int id)
{
	TID = id;
}

Itemtype Cargo::gettype()
{
	return type;
}

Time Cargo::getprept()
{
	return Pt;
}

Time Cargo::getCDT()
{
	return CDT;
}

Time Cargo::getWT()
{
	return WT;
}

void Cargo::setWT(Time& t)
{
	WT = t - Pt;
}

void Cargo::setCDT(int t)
{
	CDT.toTime(t);
}

void Cargo::settype(Itemtype t)
{
	type = t;
}

void Cargo::setdelivered(bool t)
{
	delivered = t;
}

int Cargo::getloadt()
{
	return Lt;
}




int Cargo::getdeldis()
{
	return deldis;
}

void Cargo::inccost(int c)
{
	cost += c;
}

int Cargo::getcost()
{
	return cost;
}


std::ostream& operator<<(std::ostream& f, const Cargo* C)
{
	if (C->delivered)
	{
		f << " ";
		if (C->type == Normal)
			f << "[";
		if (C->type == Special)
			f << "(";
		if (C->type == VIP)
			f << "{";
	}
	f << C->getid();
	if (C->delivered)
	{
		if (C->type == Normal)
			f << "]";
		if (C->type == Special)
			f << ")";
		if (C->type == VIP)
			f << "}";
		
	}
	return f;
}


