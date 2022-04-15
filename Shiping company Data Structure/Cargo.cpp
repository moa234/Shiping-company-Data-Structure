#include "Cargo.h"


Cargo::Cargo(int ID, int Dis, int Lt, int cost)
{
	this->ID = ID;
	deldis = Dis;
	this->Lt = Lt;
	this->cost = cost;

}

Cargo::Cargo()
{
}

int Cargo::getid()
{
	return ID;
}

int Cargo::getprept()
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
	f << " " << C.ID <<" "  << endl;
	return f;
}
