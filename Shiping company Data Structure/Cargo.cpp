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
	autop = 0;
	prom = 0;
}

Cargo::Cargo()
{
}

int Cargo::getcost()
{
	return cost;
}

int Cargo::getdeldis()
{
	return deldis;
}

int Cargo::getid() const
{
	return ID;
}

int Cargo::getloadt()
{
	return Lt;
}

int Cargo::getTID() const
{
	return TID;
}

Time Cargo::getCDT()
{
	return CDT;
}

Time Cargo::getWT()
{
	return WT;
}

Time Cargo::getprept()
{
	return Pt;
}

Itemtype Cargo::gettype()
{
	return type;
}

bool Cargo::getautop()
{
	return autop;
}

bool Cargo::getprom()
{
	return prom;
}

void Cargo::setautop(bool t)
{
	autop = t;
}

void Cargo::setprom(bool t)
{
	prom = t;
}

void Cargo::setCDT(int t)
{
	CDT.toTime(t);
}

void Cargo::setdelivered(bool t)
{
	delivered = t;
}

void Cargo::setTID(int id)
{
	TID = id;
}

void Cargo::settype(Itemtype t)
{
	type = t;
}

void Cargo::setWT(Time& t)
{
	WT = t - Pt;
}

void Cargo::inccost(int c)
{
	cost += c;
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
