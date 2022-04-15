#pragma once
#include <fstream>
#include "Queue.h"
#include "PriorityQueue.h"
#include "Truck.h"
#include "Event.h"
#include "Preparation.h"
#include "Cancellation.h"
#include "Promotion.h"
#include "Cargo.h"
#include "DEFS.h"
#include "Time.h"
class Company
{
	Time AutoP;
	Time timer;
	Queue<Event* > Events;
	Queue<Truck* > Ready[3];
	Queue<Truck* > Maintained[3]; 
	Queue<Truck* > In_Trip[3];
	Queue<Cargo* > CNormal;
	Queue<Cargo* > CSpecial;
	PriorityQueue<Cargo*> CVIP;
public:
	Company();
	void ReadFile(ifstream &fin);
	void ReadTrucks(ifstream &fin);
	void ReadEvents(ifstream& fin);

};

