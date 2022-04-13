#pragma once
#include "Queue.h"
#include "PriorityQueue.h"
#include "Truck.h"
#include "Event.h"
class Company
{

	Queue<Event*> Event;
	Queue<Truck*> Ready[3];
	Queue<Truck*> Maintained[3]; 
	Queue<Truck*> In_Trip[3];
	Queue<Truck*> Special;
	Queue<Truck*> Normal;

	PriorityQueue<Truck*> VIP;

};

