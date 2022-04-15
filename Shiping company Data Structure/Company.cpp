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
				Ready[type].enqueue(ptr);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		Truck *T;
		Ready[i].peek(T);
		cout << T << endl;
		cout << T->getcap() << endl;
	}
}

void Company::ReadEvents(ifstream& fin)
{
}
