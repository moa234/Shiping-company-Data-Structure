#include "Cargo.h"


Cargo::Cargo(Itemtype t,int ID, int Dis, int Lt, int cost, Time time)
{
	type = t;
	this->ID = ID;
	deldis = Dis;
	this->Lt = Lt;
	this->cost = cost;
	Pt = time;
}

Cargo::Cargo()
{
}

int Cargo::getid()
{
	return ID;
}

Itemtype Cargo::gettype()
{
	return type;
}

Time Cargo::getprept()
{
	return Pt;
}

int Cargo::getloadt()
{
	return Lt;
}




int Cargo::getdeldis()
{
	return deldis;
}

int Cargo::getcost()
{
	return cost;
}

ostream& operator<<(ostream& f, const Cargo& C)
{
	f  << C.ID ;
	return f;
}
