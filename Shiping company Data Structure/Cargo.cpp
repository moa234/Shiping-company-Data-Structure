#include "Cargo.h"

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
