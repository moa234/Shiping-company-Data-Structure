#include "Cargo.h"

void Cargo::setprept(time pt)
{
	prept = pt;
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

Cargo::time Cargo::getprept()
{
	return prept;
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
