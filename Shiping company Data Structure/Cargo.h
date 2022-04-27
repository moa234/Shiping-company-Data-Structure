#pragma once
#include "DEFS.h"
#include "Time.h"
#include <ostream>
class Cargo
{
	int Lt;			//Load time
	Time Pt;		//Preparation time
	int deldis;		//delivery distance in km
	int cost;		//cost of delivering
	int ID;			//unique id
	Time CDT;		//delivery time 
	Time WT;		//waiting time
	Itemtype type;	//type of cargo (normal, vip, special)
	int TID;		//truck id when loaded

public:
	Cargo(Itemtype t, int ID, int Dis, int Lt, int cost, Time time);
	Cargo();
	int getid() const;
	int getTID() const;
	void setTID(int id);
	Itemtype gettype();
	Time getprept();
	Time getCDT();
	Time getWT();
	void setWT(Time& t);
	void setCDT(Time& t);
	void settype(Itemtype t);
	int getloadt();
	int getdeldis();
	int getcost();
	void inccost(int c);
	friend std::ostream& operator <<(std::ostream& f, const Cargo* C);
};
