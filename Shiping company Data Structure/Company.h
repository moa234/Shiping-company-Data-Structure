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
	UI* PUI;												 //pointer to User interface
	int AutoP;												 //Auto Promotion Day limit
	int maxW;												 //Maximum Waiting time 
	Time timer;												 //Object of time class to deal with day and hour easily
	int counter;											 //counter for simulation function
	int MaintainenceLimit;                                   //Number of journies to do maintainence
	bool loadflag[3];
	Queue<Event*> Events;									 //list of events
	
	Queue<Truck*> ReadyT[3];								 //three Queues for ready trucks grouped in array
	Queue<Truck*> MaintainedT[3];							 //three Queues for Maintained trucks grouped in array
	PriorityQueue<Truck*> LoadingT[3];						 //three PriorityQueues for Loading trucks grouped in array
	PriorityQueue<Truck*> In_TripT;	   					 //three PriorityQueues for Moving trucks grouped in array
	
	CargoList NWaitingC;									 //Linked List for Normal Waiting Cargo
	Queue<Cargo*> SWaitingC;								 //List for Special Waiting Cargos
	PriorityQueue<Cargo*> VWaitingC;						 //List for VIP Waiting Cargo
	
	Queue<Cargo*> NDeliveredC;								 //List for Normal Delivered Cargos
	Queue<Cargo*> SDeliveredC;								 //List for Special Delivered Cargos
	Queue<Cargo*> VDeliveredC;								 //List for VIP Delivered Cargos
	
	void ReadTrucks(ifstream& fin);							 //utility function to read trucks info from file
	void ReadEvents(ifstream& fin);							 //utility function to read events info from file
public:
	Company();
	Time GetTime(); //getter for current time
	void Timer(); //function responsible for executing events corresponding to current hour

	void ReadFile(ifstream& fin); 
	void LoadFile();

	bool IsRemainingEvents(); //Checking whether the program finishes or not 
							  //by checking empety conditions for reponsible lists
	//void savefile(ofstream& fout);
	void autopromote();

	Cargo* getNCargo(int id); //gets the cargo with specific id from 
	
	void AddNormList(Cargo* ptr); //adds a cargo to Normal Cargo List
	void AddSpeList(Cargo* ptr); //adds a cargo to Special Cargo List
	void AddVIPList(Cargo* ptr); //adds a cargo to VIP Cargo List
	void MaxWAssignment();
	void CurrData(); //Function to be called to send current data to UI to be printed on screen
	void simulate(); //to start simulation
	void IncrementHour(); //increment the current hour
	void Assignment();
	void AssignmentVIP();
	void AssignmentNormal(bool MaxWA=0);
	void AssignmentSpecial(bool MaxWA=0);
	void Maintenance();
	void TruckControl();
};

