#pragma once
#include <fstream>
#include "Queue.h"
#include "PriorityQueue.h"
#include "Truck.h"
#include "Event.h"
#include "Cargo.h"
#include "DEFS.h"
#include "Time.h"
#include <string>
class Company
{
	Time AutoP;
	Time timer;
	Queue<Event* > Event;
	Queue<Truck* > ReadyT[3];
	Queue<Truck* > MaintainedT[3]; 
	Queue<Truck* > In_TripT[3];
	Queue<Cargo* > NWaitingC;
	Queue<Cargo* > SWaitingC;
	PriorityQueue<Cargo*> VWaitingC;
	Queue<Cargo* > NMovingC;
	Queue<Cargo* > SMovingC;
	Queue<Cargo* > VMovingC;
public:
	Company();
	void ReadFile(ifstream &fin);
	void ReadTrucks(ifstream &fin);
	void ReadEvents(ifstream& fin);
	void PrintAllData();
	void PrintCargo(Queue<Cargo*> &q);

};

