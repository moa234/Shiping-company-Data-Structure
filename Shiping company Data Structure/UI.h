#pragma once
#include "DEFS.h"
#include"Company.h"
#include <iostream>
#include <fstream>

using namespace std;

class UI
{
	Modetype mode;
	Company* ptr;
public:
	UI(Company* ptr);
	int readnumber();
	void displaytext(string c);
	void readmode();
	void PrintCargoId(Queue<int>* n, Queue<int>* s, Queue<int>* v);
	void PrintQueue(Queue<int>* q);
	void PrintMode(Queue<int>* n, Queue<int>* s, Queue<int>* v,ListType l);
	void Print();
	void WaitOption();
	void save(ofstream &s);
	void simulate();
};

