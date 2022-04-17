#pragma once
#include "DEFS.h"
#include "Time.h"
#include <iostream>
using namespace std;
class Cargo
{
	int Lt;	//Load time
	Time Pt;    //Preparation time
	int deldis;	 //delivery distance in km
	int cost;	 //cost of delivering truck
	int ID;
	Time CDT;
	Time WT;
	Itemtype type;
	int TID;

public:
	Cargo(Itemtype t, int ID, int Dis, int Lt, int cost, Time time);
	Cargo();
	int getid();
	int getTID();
	void setTID(int id);
	Itemtype gettype();
	Time getprept();
	Time getCDT();
	Time getWT();
	void setWT(Time& t);
	void setCDT(Time &t);
	int getloadt();
	int getdeldis();
	int getcost();
	
	friend ostream& operator <<(ostream& f,const Cargo& C);
};

