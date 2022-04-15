#pragma once
#include "DEFS.h"
#include <iostream>
using namespace std;
class Cargo
{
	int Lt;	//Load time
	int Pt;    //Preparation time
	int deldis;	 //delivery distance in km
	int cost;	 //cost of delivering truck
	int ID;
	Itemtype type;

public:
	Cargo(int ID, int Dis, int Lt, int cost);
	Cargo();
	int getid();
	int getprept();
	int getloadt();
	int getdeldis();
	int getcost();
	
	friend ostream& operator <<(ostream& f,const Cargo& C);
};

