#include "Company.h"
#include "Event.h"
#include "Preparation.h"
#include "Cancellation.h"
#include "Promotion.h"

Company::Company()
{
}

bool Company::removenormal(Cargo *&q, int id)
{
	Queue<Cargo*> temp;
	Cargo* t;
	bool found = 0;
	while (!NWaitingC.isempty())
	{
		NWaitingC.dequeue(t);
		
		if (t->getid() == id)
		{
			q = t;
			found = true;
		}
		temp.enqueue(t);
	}
	while (!temp.isempty())
	{
		temp.dequeue(t);
		NWaitingC.enqueue(t);
	}
	return found;
}

void Company::ReadFile(ifstream& fin)
{
	ReadTrucks(fin);
	int d, h;
	int numjourn;
	fin >> numjourn;
	fin >> d >> h;
	AutoP.SetDay(d); AutoP.SetHour(h);

	ReadEvents(fin);
}

void Company::ReadTrucks(ifstream& fin)
{
	int data[4][3]; // one row for count of vechiles,then another for speed,then another for capacity,then another for maintainence
					// one coloum contains complete data of a truck type
	int checkduration;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			fin >> data[i][j];
	for (int i = 0; i < 3; i++)
	{
		Itemtype type = Normal;
		if (i == 0)
			type = Normal;
		if (i == 1)
			type = Special;
		if (i == 2)
			type = VIP;
		for (int j = 0; j < data[0][i]; j++)
		{
			
			Truck* ptr = new Truck(data[1][i],data[2][i],data[3][i],type);
				ReadyT[type].enqueue(ptr);
		}
	}
	
}

void Company::ReadEvents(ifstream& fin)
{

	int eventsnum;
	fin >> eventsnum;
	char type;

	for (int i = 0; i < eventsnum; i++)
	{
		char evtype;
		fin >> evtype;
		Itemtype category;
		if (evtype == 'R') category = Normal;
		if (evtype == 'X') category = Special;
		if (evtype == 'P') category = VIP;
		if (evtype == 'R')
		{	
			int datar[6];
			for (int i = 0; i < 5; i++)
			{
				if (i == 1)
				{
					char nullchar;
					fin >> nullchar;
				}
				fin >> datar[i];
			}
			Time et;
			et.SetDay(datar[0]);
			et.SetHour(datar[1]);
			Event* prep = new Preparation(category, et, datar[2], datar[3], datar[4], datar[5]);
			Events.enqueue(prep);
		}
		else if (evtype == 'X')
		{
			int datax[3];
			for (int i = 0; i < 3; i++)
			{
				if (i == 1)
				{
					char nullchar;
					fin >> nullchar;
				}
				fin >> datax[i];
			}
			Time etx;
			etx.SetDay(datax[0]);
			etx.SetHour(datax[1]);
			Event* cancel = new Cancellation(etx, datax[2]);
			Events.enqueue(cancel);
		}
		else if (evtype == 'P')
		{
			int datap[4];
			for (int i = 0; i < 4; i++)
			{
				if (i == 1)
				{
					char nullchar;
					fin >> nullchar;
				}
				fin >> datap[i];
			}
			Time etp;
			etp.SetDay(datap[0]);
			etp.SetHour(datap[1]);
			Event* prom = new Promotion(etp, datap[2], datap[3]);
			
			Events.enqueue(prom);
		}
	}

	cout << eventsnum;
	Events.print();
}
void Company::PrintAllData()
{
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
	cout << "Normal Waiting Cargo:";
	PrintCargo(NWaitingC);
	cout << "Special Waiting Cargo:";
	PrintCargo(SWaitingC);
	cout << "VIP Waiting Cargo:";
	PrintCargoPQ(VWaitingC);
	cout << "Normal Moving Cargo:";
	PrintCargo(NMovingC);
	cout << "Special Moving Cargo:";
	PrintCargo(SMovingC);
	cout << "VIP Moving Cargo:";
	PrintCargo(VMovingC);
}

void Company::PrintCargo(Queue<Cargo*>& q)
{
	int sz = q.GetSize();
	cout << " Size: " << sz << " " << endl;
	for (int i = 0; i < sz ; i++)
	{
		Cargo* c;
		q.dequeue(c);
		cout << c->getid() << " ";
		q.enqueue(c);
	}
	cout << endl;
}

void Company::PrintCargoPQ(PriorityQueue<Cargo*>& q)
{
	int sz = q.GetSize();
	cout << " Size: " << sz << " " << endl;
	q.print();
	cout << endl;
}

void Company::AddNormList(Cargo* ptr)
{
	NWaitingC.enqueue(ptr);
}

void Company::AddSpeList(Cargo* ptr)
{
	SWaitingC.enqueue(ptr);
}

void Company::AddVIPList(Cargo* ptr)
{
	int cost = ptr->getcost();
	VWaitingC.enqueue(ptr, cost);
}
