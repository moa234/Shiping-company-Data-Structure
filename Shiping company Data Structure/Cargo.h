#pragma once
#include "DEFS.h"
#include "Time.h"
#include <ostream>
class Cargo
{
	int cost;		//cost of delivering
	int deldis;		//delivery distance in km
	int ID;			//unique id
	int TID;		//truck id when loaded
	int Lt;			//Load time

	Time CDT;		//delivery time 
	Time Pt;		//Preparation time
	Time WT;		//waiting time
	
	Itemtype type;	//type of cargo (normal, vip, special)

	bool autop;
	bool delivered;

public:
//Constructor
	Cargo(Itemtype t, int ID, int Dis, int Lt, int cost, Time time);
	Cargo();

//Getters
	int getcost();
	int getdeldis();
	int getid() const;
	int getloadt();
	int getTID() const;

	Time getCDT();
	Time getprept();
	Time getWT();

	Itemtype gettype();

	bool getautop();

//Setters
	void setautop(bool t);
	void setCDT(int t);
	void setdelivered(bool t);
	void setTID(int id);
	void settype(Itemtype t);
	void setWT(Time& t);

	void inccost(int c);
	
	friend std::ostream& operator <<(std::ostream& f, const Cargo* C);
};
