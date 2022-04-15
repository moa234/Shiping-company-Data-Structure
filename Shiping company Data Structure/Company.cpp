#include "Company.h"

Company::Company()
{
}

void Company::ReadFile(ifstream& fin)
{
	ReadTrucks(fin);
	int d, h;
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
		for (int j = 0; j < data[0][j]; j++)
		{
			
			Truck* ptr = new Truck(data[1][i],data[2][i],data[3][0],type);
				ReadyT[type].enqueue(ptr);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		Truck *T;
		ReadyT[i].peek(T);
		cout << T << endl;
		cout << T->getcap() << endl;
	}
}

void Company::ReadEvents(ifstream& fin)
{
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
	for (int i = 0; i < 3; i++)
	{
		string s;
		if (i == 0)
			s = "Normal";
		if (i == 1)
			s = "Special";
		if (i == 2)
			s = "VIP";
		cout << s << " size: " << ReadyT[i].GetSize() << endl;
		
	}
}

void Company::PrintCargo(Queue<Cargo*>& q)
{
	int sz = q.GetSize();
	for (int i = 0; i < sz; i++)
	{
		Cargo* t;
		q.dequeue(t);
		cout<<t->
	}
}
