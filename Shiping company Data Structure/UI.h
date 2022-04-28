#pragma once
#include "DEFS.h"
#include"Company.h"
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

class UI
{
	Modetype mode;
	Company* ptr;
public:
	UI(Company* ptr);
	int readnumber();
	string readfilename();
	void displayTime(Time t);
	void displayline();
	void displaytext(string c);
	void displayNum(int n);
	void readmode();
	void PrintBracketStart(Itemtype t);
	void PrintBracketEnd(Itemtype t);
	void PrintQC(Queue<Cargo*>& q,Itemtype t);
	void PrintLC(CargoList& q, Itemtype t);
	void PrintPQC(PriorityQueue<Cargo*>& q, Itemtype t);
	void PrintEQT(Queue<Truck*>& q, Itemtype t);
	void PrintEPQT(Queue<Truck*>& q, Itemtype t);
	void PrintQT(Queue<Truck*>& q);
	void PrintPQT(PriorityQueue<Truck*>& q);
	void WaitOption();
	void save(ofstream &s);
	void Interface();
};

