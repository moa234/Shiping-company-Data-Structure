#pragma once
#include "DEFS.h"
#include <iostream>
using namespace std;
class Cargo
{
	int loadt;	 //load time in hours  
	int unloadt; //unload time in hours
	int preptd;	 //preparation time in (day:hour)
	int prepth;
	int deldis;	 //delivery distance in km
	int cost;	 //cost of delivering truck
	int ID;
	Itemtype type;

public:
	Cargo(Itemtype t);
	Cargo(Itemtype t,int id, int dis, int load, int c);
	Cargo();
	void setprepth(int pt);
	void setpreptd(int pt);
	void setloadt(int lt);
	void setunloadt(int ult);
	void setdeldis(int ds);
	void setcost(int cost);
	void setitemtype(int it_type);
	void setid(int id);
	int getid();
	int getprepth();
	int getpreptd();
	int getload();
	int getunload();
	int getdeldis();
	int getcost();
	
	friend ostream& operator <<(ostream& f,const Cargo& C);
	//virtual bool load() = 0;
	//virtual bool unload() = 0;
	//bool virtual assign() = 0;
};

