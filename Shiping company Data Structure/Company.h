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
	Truck* LoadingN;
	Truck* LoadingS;
	Truck* LoadingV;
	PriorityQueue<Truck*> In_TripT;	   					 //three PriorityQueues for Moving trucks grouped in array

	CargoList NWaitingC;									 //Linked List for Normal Waiting Cargo
	Queue<Cargo*> SWaitingC;								 //List for Special Waiting Cargos
	PriorityQueue<Cargo*> VWaitingC;						 //List for VIP Waiting Cargo

	Queue<Cargo*> DeliveredC;								 //List for Delivered Cargos

	void ReadTrucks(ifstream& fin);							 //utility function to read trucks info from file
	void ReadEvents(ifstream& fin);							 //utility function to read events info from file
	void savefile();										 //utility function to save parameters of simulation to file
public:
	Company();
	void Timer(); //function responsible for executing events corresponding to current hour
				  // and Checking for assignment status

	void ReadFile(ifstream& fin);
	void LoadFile();

	bool IsRemainingEvents();	//Checking whether the program finishes or not 
								//by checking empety conditions for reponsible lists
	
	void autopromote();

	Cargo* getNCargo(int id); //gets the cargo with specific id from 

	void AddNormList(Cargo* ptr); //adds a cargo to Normal Cargo List
	void AddSpeList(Cargo* ptr); //adds a cargo to Special Cargo List
	void AddVIPList(Cargo* ptr); //adds a cargo to VIP Cargo List
	void CurrData(); //Function to be called to send current data to UI to be printed on screen
	void simulate(); //to start simulation
	void IncrementHour(); //increment the current hour
	void Assignment();
	void AssignmentVIP(); //Assign a vip truck to start loading cargos on it
	void AssignmentNormal(bool maxw = 0); //Assign a Normal truck to start loading cargos on it
	void AssignmentSpecial(bool maxw = 0);//Assign a Special truck to start loading cargos on it
	bool MaxWaitCheck(Itemtype ctype);  //checks for a ceartin type whether there a cargo ecxeeded max wait time
	void MaxWaitAssign(Itemtype ctype);  //Assign A truck for a cargo that exceeded max wait
	bool MaxWaitExceed(Cargo* C); //utility function for MaxWaitCheck
	void LoadingCargo(Itemtype ctype); //A genaralized funtion for loading cargo onto truck and checking maxWait for front cargos
	void CheckEndLoading(Truck*& T, bool maxw = 0);
	Cargo* DequeueTopCargo(Itemtype ctype);//dequeues the top cargo from a list of type ctype
	Cargo* PeekTopCargo(Itemtype ctype);//gets the top cargo of a list from the cargo type send
	Truck*& MapTruckToCargo(Itemtype ctype); //Maps the truck that is currently loading a specific type of cargo
	void Maintenance(); //function responsible for checking maintenance status of truck
	void cargodeliver(Truck*& t, bool& moretrucks, Cargo*& c);//deliver cargo and rearange the truck position in IN_Trip
	void addtomaintain(Truck*& t);//adds a truck to maintenance List
	void addtoready(Truck*& t); //adds a truck to Ready List
	void returnTruck(Truck*& t, bool& morecargos);//Checks if the truck finished the trip then adds it to Maint. or ready list
	void TruckControl();//manages the trucks' cargos delevery
};

