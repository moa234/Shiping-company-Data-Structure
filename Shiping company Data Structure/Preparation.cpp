#include "Preparation.h"

Preparation::Preparation(Itemtype &ty, Time &t, int &id, int &dis, int &lt, int &c)
{
	type = ty;
	ID = id;
	time = t;
	distance = dis;
	loadt = lt;
	cost = c;
}

void Preparation::excute()
{
	Cargo* carg = new Cargo(type, ID, distance, loadt, cost);
	
}
