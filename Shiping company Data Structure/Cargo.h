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

	bool autop;		//Auto-Promoted from normal to vip
	bool prom;		//promoted either by auto-promotion or promotion event
	bool delivered;	//is the cargo delivered

public:
//Constructor
	Cargo(Itemtype t, int ID, int Dis, int Lt, int cost, Time time);

//Getters
	int getcost();				//return cost
	int getdeldis();			//return delivery distance in km
	int getid() const;			//returns cargo unique id
	int getloadt();				//return Load time
	int getTID() const;			//return truck id

	Time getCDT();				//return delivery time
	Time getprept();			//return Preparation time
	Time getWT();				//return waiting time

	Itemtype gettype();			//return type of cargo (normal, vip, special)

	bool getautop();			//return bool autop
	bool getprom();				//return bool prom

//Setters
	void setautop(bool t);		//sets bool autop
	void setCDT(int t);			//sets delivery time with hours
	void setdelivered(bool t);	//sets bool delivered
	void setprom(bool t);		//sets bool prom

	void setTID(int id);		//sets truck id

	void settype(Itemtype t);	//sets cargo type

	void setWT(Time& t);		//sets waiting time
	
	void inccost(int c);		//increrments cost

	friend std::ostream& operator <<(std::ostream& f, const Cargo* C);
};
