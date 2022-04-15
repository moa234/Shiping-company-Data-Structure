#include "Cargo.h"

Cargo::Cargo(Itemtype t)
{
	type = t;
}

Cargo::Cargo(Itemtype t, int id, int dis, int load, int c)
{
	ID = id;
	deldis = dis;
	loadt = load;
	cost = c;
}

Cargo::Cargo()
{
}

void Cargo::setprepth(int pt)
{
	prepth = pt;
}

void Cargo::setpreptd(int pt)
{
	preptd = pt;
}

void Cargo::setloadt(int lt)
{
	loadt = lt;
}

void Cargo::setunloadt(int ult)
{
	unloadt = ult;
}

void Cargo::setdeldis(int ds)
{
	deldis = ds;
}

void Cargo::setcost(int c)
{
	cost = c;
}

void Cargo::setitemtype(int it_type)
{
	type = static_cast<Itemtype>(it_type);
}

void Cargo::setid(int id)
{
	ID = id;
}

int Cargo::getid()
{
	return ID;
}

int Cargo::getprepth()
{
	return prepth;
}

int Cargo::getpreptd()
{
	return preptd;
}

int Cargo::getload()
{
	return loadt;
}

int Cargo::getunload()
{
	return unloadt;
}

int Cargo::getdeldis()
{
	return deldis;
}

int Cargo::getcost()
{
	return cost;
}
