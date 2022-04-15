#include "Company.h"

Company::Company()
{
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
		switch (evtype)
		{
		case 'R':
			fin >> type;
			int data[6];
			for (int i = 0; i < 5; i++)
			{
				if (i == 1)
				{
					char nullchar;
					fin >> nullchar;
				}
				fin >> data[i];
			}
			Time et;
			et.SetDay(data[0]);
			et.SetHour(data[1]);
			Event* prep = new Preparation(type, et, data[2], data[3], data[4], data[5]);
			Events.enqueue(prep);
			break;
		case 'X':
			int data[3];
			for (int i = 0; i < 3; i++)
			{
				if (i == 1)
				{
					char nullchar;
					fin >> nullchar;
				}
				fin >> data[i];
			}
			Time et;
			et.SetDay(data[0]);
			et.SetHour(data[1]);
			Event* cancel = new Cancellation(et, data[2]);
			Events.enqueue(cancel);
			break;

		case 'P':
			int data[4];
			for (int i = 0; i < 4; i++)
			{
				if (i == 1)
				{
					char nullchar;
					fin >> nullchar;
				}
				fin >> data[i];
			}
			Time et;
			et.SetDay(data[0]);
			et.SetHour(data[1]);
			Event* prom = new Promotion(et, data[2], data[3]);
			Events.enqueue(prom);
			break;
		}
	}

	cout << eventsnum;
}
void Company::PrintAllData()
{
	/*Queue<Event* > Event;
	Queue<Truck* > ReadyT[3];
	Queue<Truck* > MaintainedT[3];
	Queue<Truck* > In_TripT[3];
	Queue<Cargo* > NWaitingC;
	Queue<Cargo* > SWaitingC;
	PriorityQueue<Cargo*> VWaitingC;
	Queue<Cargo* > NMovingC;
	Queue<Cargo* > SMovingC;
	Queue<Cargo* > VMovingC;*/
	cout << "Normal Waiting Cargo:";
	PrintCargo()
	cout << "Special Waiting Cargo:";
	cout << "VIP Waiting Cargo:";
	cout << "Normal Moving Cargo:";
	cout << "Special Moving Cargo:";
	cout << "VIP Moving Cargo:";
	
}

void Company::PrintCargo(Queue<Cargo*>& q)
{
	int sz = q.GetSize();
	q.print();
	cout << endl;
}
