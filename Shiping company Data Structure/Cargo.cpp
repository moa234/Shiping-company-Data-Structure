#include "Cargo.h"

Cargo::Cargo(Itemtype t)
{
	type = t;
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
