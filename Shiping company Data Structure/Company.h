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
class UI;
class Preparation;
class Promotion;
class Cancellation;
class Company
{
	UI* PUI;
	Time AutoP;
	Time timer;
	int counter;
	Queue<Event*> Events;
	Queue<Truck*> ReadyT[3];
	Queue<Truck*> MaintainedT[3]; 
	PriorityQueue<Truck*> In_TripT;
	Queue<Cargo*> NWaitingC;
	Queue<Cargo*> SWaitingC;
	PriorityQueue<Cargo*> VWaitingC;
	PriorityQueue<Cargo*> MovingC;
	Queue<Cargo*> DeliveredC;
	//Queue<Cargo*> SDeliveredC;
	//Queue<Cargo*> VDeliveredC;
	void ReadTrucks(ifstream& fin);
	void ReadEvents(ifstream& fin);
public:
	Company();
	Time GetTime();
	void Timer();
	void ReadFile(ifstream& fin);
	void savefile(ofstream& fout);
	Cargo* removenormal(int id);
	//void PrintAllData();
	//void PrintCargo(Queue<Cargo*> &q);
	//void PrintCargoPQ(PriorityQueue<Cargo*>&q);
	//Queue<int>* AccessCargoIds(ListType L, Itemtype T);
	//Queue<int>* CargoData(Queue<Cargo*>& q);
	void printwaiting();
	void printdelivered();
	//Queue<int>* CargoDataPQ(PriorityQueue<Cargo*>& q);
	void AddNormList(Cargo* ptr);
	void AddSpeList(Cargo* ptr);
	void AddVIPList(Cargo* ptr);
	void deletecargo(Cargo* c);
	void simulate();
};

