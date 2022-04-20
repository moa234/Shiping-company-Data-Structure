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
	void displayTime(Time t);
	void displayline();
	void displaytext(string c);
	void displayNum(int n);
	void readmode();
	void PrintBracketStart(Itemtype t);
	void PrintBracketEnd(Itemtype t);
	void PrintQC(Queue<Cargo*>& q,Itemtype t);
	void PrintPQC(PriorityQueue<Cargo*>& q, Itemtype t);
	void PrintListC(List<Cargo*>& q, Itemtype t);
	void PrintQT(Queue<Truck*>& q, Itemtype t);
	void PrintPQT(PriorityQueue<Truck*>& q, Itemtype t);
	void WaitOption();
	void save(ofstream &s);
	void Interface();
};

