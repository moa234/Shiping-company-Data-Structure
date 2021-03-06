#pragma once
#include "DEFS.h"
#include <iostream>
#include <windows.h>
#include "Time.h"
#include "Cargo.h"
#include "Queue.h"
#include "CargoList.h"
#include "PriorityQueue.h"
#include "Truck.h"
using namespace std;

class UI
{
	Modetype mode; 
public:
	UI(); //constructor so that UI point to class to access functions
	int readnumber(); //read number from the console
	string readfilename(); //get the file name so company class can load this file 
	void displayTime(Time t); //display format for time on console
	void displayline(); 
	void displaytext(string c);
	void displayNum(int n);
	void readmode(); //Get the mode number from user and intialize mode variable
	void PrintBracketStart(Itemtype t); //print the suitable bracket openeing for item
	void PrintBracketEnd(Itemtype t); //print the suitable bracket closing for item
	void PrintQC(Queue<Cargo*>& q,Itemtype t); //calls print function of List
	void PrintDQC(Queue<Cargo*>& q);
	void PrintLC(CargoList& q, Itemtype t);  //calls print function of List
	void PrintPQC(PriorityQueue<Cargo*>& q, Itemtype t);  //calls print function of List
	void PrintEQT(Queue<Truck*>& q, Itemtype t);  //calls print function of List
	void PrintPQT(PriorityQueue<Truck*>& q);  //calls print function of List
	void PrintT(Truck* T);
	Modetype getmode();
	void WaitOption(); //checks the interface mode to use correct 
					   // wait option either delay 1 second or enter key 
	//void Interface(); //function responsible for coordinating 
					//between UI class and Company class for simulation
};

