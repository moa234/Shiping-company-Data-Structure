#pragma once
#include <fstream>
#include "Queue.h"
#include "PriorityQueue.h"
#include "Truck.h"
#include "Cargo.h"
#include "DEFS.h"
#include "Time.h"
#include <string>
#include "CargoList.h"
class Event;
class UI;
class Preparation;
class Promotion;
class Cancellation;
class Company
{
	UI* PUI;
	int AutoP;
	int maxW;
	Time timer;
	int counter;
	Queue<Event*> Events;
	Queue<Truck*> ReadyT[3];
	Queue<Truck*> MaintainedT[3];
	PriorityQueue<Truck*> LoadingT[3];
	PriorityQueue<Truck*> In_TripT[3];
	CargoList NWaitingC;
	Queue<Cargo*> SWaitingC;
	PriorityQueue<Cargo*> VWaitingC;
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
	bool IsRemainingEvents();
	//void savefile(ofstream& fout);
	Cargo* getNCargo(int id);
	void AddNormList(Cargo* ptr);
	void AddSpeList(Cargo* ptr);
	void AddVIPList(Cargo* ptr);
	//void autopromote();
	void CurrData();
	void simulate();
	void IncrementHour();
};

