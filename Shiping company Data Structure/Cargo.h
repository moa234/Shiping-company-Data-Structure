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
	Itemtype type;

public:
	Cargo(int ID, int Dis, int Lt, int cost, Time time);
	Cargo();
	int getid();
	int getprept();
	int getloadt();
	int getdeldis();
	int getcost();
	
	friend ostream& operator <<(ostream& f,const Cargo& C);
};

