#pragma once
#include <fstream>
#include "Queue.h"
#include "PriorityQueue.h"
#include "Truck.h"
#include "Cargo.h"
#include "DEFS.h"
#include "Time.h"
#include <string>

class Event;
class Preparation;
class Promotion;
class Cancellation;
class Company
{
	Time AutoP;
	Time timer;
	int counter;
	Queue<Event*> Events;
	Queue<Truck*> ReadyT[3];
	Queue<Truck*> MaintainedT[3]; 
	Queue<Truck*> In_TripT[3];
	Queue<Cargo*> NWaitingC;
	Queue<Cargo*> SWaitingC;
	PriorityQueue<Cargo*> VWaitingC;
	Queue<Cargo*> NMovingC;
	Queue<Cargo*> SMovingC;
	Queue<Cargo*> VMovingC;
	Queue<Cargo*> NDeliveredC;
	Queue<Cargo*> SDeliveredC;
	Queue<Cargo*> VDeliveredC;
	void ReadTrucks(ifstream& fin);
	void ReadEvents(ifstream& fin);
public:
	Company();
	Time GetTime();
	void Timer();
	void ReadFile(ifstream& fin);
	Cargo* removenormal(int id);
	//void PrintAllData();
	//void PrintCargo(Queue<Cargo*> &q);
	//void PrintCargoPQ(PriorityQueue<Cargo*>&q);
	Queue<int>* AccessCargoIds(ListType L, Itemtype T);
	Queue<int>* CargoData(Queue<Cargo*>& q);
	Queue<int>* CargoDataPQ(PriorityQueue<Cargo*>& q);
	void AddNormList(Cargo* ptr);
	void AddSpeList(Cargo* ptr);
	void AddVIPList(Cargo* ptr);
	void deletecargo(Cargo* c);
	void simulate();
};

