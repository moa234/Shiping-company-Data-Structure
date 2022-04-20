#include "Company.h"
#include "Event.h"
#include "Preparation.h"
#include "Cancellation.h"
#include "UI.h"
#include "Promotion.h"

Company::Company()
{
	timer.SetDay(1); timer.SetHour(1);
	counter = 0;
	PUI = new UI(this);
}


Time Company::GetTime()
{
	return timer;
}

void Company::ReadFile(ifstream& fin)
{
	ReadTrucks(fin);
	int d, h;
	int numjourn;
	fin >> numjourn;
	fin >> d >> h;
	AutoP = d;
	maxW = h;

	ReadEvents(fin);
}

//void Company::savefile(ofstream& fout)
//{
//	fout << "CDT" << "\tID" << "\tPT" << "\tWT" << "\tTID" << endl;
//	int count = DeliveredC.GetSize();
//	Cargo* c;
//	for (int i = 0; i < count; i++)
//	{
//		DeliveredC.dequeue(c);
//		fout << c->getCDT().GetDay() << ":" << c->getCDT().GetHour() << "\t" << c->getprept().GetDay() << ":"
//			<< c->getprept().GetHour() << "\t" << c->getWT().GetDay() << ":" << c->getWT().GetHour() << "\t" << c->getTID() << endl;
//		DeliveredC.enqueue(c);
//	}
//}

void Company::ReadTrucks(ifstream& fin)
{
	int data[4][3]; // one row for count of vechiles,then another for speed,then another for capacity,then another for maintainence
					// one coloum contains complete data of a truck type
	int checkduration;
	int ids = 0;
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
			
			Truck* ptr = new Truck(data[1][i],data[2][i],data[3][i],type,++ids);
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
		
		if (evtype == 'R')
		{	
			char type;
			fin >> type;
			if (type == 'N') category = Normal;
			if (type == 'S') category = Special;
			if (type == 'V') category = VIP;
			int datar[6];
			for (int i = 0; i < 6; i++)
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
}
//void Company::PrintAllData()
//{
//	cout << "Normal Waiting Cargo:";
//	PrintCargo(NWaitingC);
//	cout << "Special Waiting Cargo:";
//	PrintCargo(SWaitingC);
//	cout << "VIP Waiting Cargo:";
//	PrintCargoPQ(VWaitingC);
//	cout << "Normal Delivered Cargo:";
//	PrintCargo(NDeliveredC);
//	cout << "Special Delivered Cargo:";
//	PrintCargo(SDeliveredC);
//	cout << "VIP Delivered Cargo:";
//	PrintCargo(VDeliveredC);
//}

//void Company::PrintCargo(Queue<Cargo*>& q)
//{
//	int sz = q.GetSize();
//	cout << " Size: " << sz << " " << endl;
//	for (int i = 0; i < sz ; i++)
//	{
//		Cargo* c;
//		q.dequeue(c);
//		cout << c->getid() << " ";
//		q.enqueue(c);
//	}
//	cout << endl;
//}
//
//void Company::PrintCargoPQ(PriorityQueue<Cargo*>& q)
//{
//	int sz = q.GetSize();
//	Queue<Cargo*> temp;
//	cout << " Size: " << sz << endl;
//	Cargo* ptr=nullptr;
//	while (!q.isempty())
//	{
//		q.dequeue(ptr);
//		cout << *ptr << " ";
//		temp.enqueue(ptr);
//	}
//	while (!temp.isempty())
//	{
//		temp.dequeue(ptr);
//		q.enqueue(ptr,ptr->getcost());
//	}
//	cout << endl;
//}

//Queue<int>* Company::AccessCargoIds(ListType L, Itemtype T)
//{
//	if (L == PCargoWaiting && T == Normal)
//		return CargoData(NWaitingC);
//	if (L == PCargoWaiting && T == Special)
//		return CargoData(SWaitingC);
//	if (L == PCargoWaiting && T == VIP)
//		return CargoDataPQ(VWaitingC);
//	if (L == PCargoMoving && T == Normal)
//		return CargoData(NMovingC);
//	if (L == PCargoMoving && T == Special)
//		return CargoData(SMovingC);
//	if (L == PCargoMoving && T == VIP)
//		return CargoData(VMovingC);
//	if (L == PCargoDelivered && T == Normal)
//		return CargoData(NDeliveredC);
//	if (L == PCargoDelivered && T == Special)
//		return CargoData(SDeliveredC);
//	if (L == PCargoDelivered && T == VIP)
//		return CargoData(VDeliveredC);
//}

//Queue<int>* Company::CargoData(Queue<Cargo*>& q)
//{
//	Queue<int>* ptr = new Queue<int>;
//	int sz = q.GetSize();
//	for (int i = 0; i < sz; i++)
//	{
//		Cargo* c;
//		q.dequeue(c);
//		ptr->enqueue(c->getid());
//		q.enqueue(c);
//	}
//	return ptr;
//	
//}
//void Company::printwaiting() 
//{
//	
//	Queue<int>* idn = new Queue<int>;
//	Queue<int>* idv = new Queue<int>;
//	Queue<int>* ids = new Queue<int>;
//	Cargo* c;
//
//	int count = NWaitingC.GetSize();
//	for (int i = 0; i < count; i++)
//	{
//		NWaitingC.dequeue(c);
//		idn->enqueue(c->getid());
//		NWaitingC.enqueue(c);
//	}
//	count = VWaitingC.GetSize();
//	Queue<Cargo*> temp;
//	/*for (int i = 0; i < count; i++)
//	{
//		VWaitingC.dequeue(c);
//		idv->enqueue(c->getid());
//		temp.enqueue(c);
//	}
//	for (int i = 0; i < count; i++)
//	{
//		temp.dequeue(c);
//		VWaitingC.enqueue(c, c->getcost()+c->getid()/100.0);
//	}*/
//	count = SWaitingC.GetSize();
//	for (int i = 0; i < count; i++)
//	{
//		SWaitingC.dequeue(c);
//		ids->enqueue(c->getid());
//		SWaitingC.enqueue(c);
//	}
//	PUI->PrintCargoId(idn, ids, idv);
//}
//
//void Company::printdelivered()
//{
//	Queue<int>* idn = new Queue<int>;
//	Queue<int>* idv = new Queue<int>;
//	Queue<int>* ids = new Queue<int>;
//	Cargo* c;
//
//	int count = DeliveredC.GetSize();
//	for (int i = 0; i < count; i++)
//	{
//		DeliveredC.dequeue(c);
//		if (c->gettype() == Normal)
//		{
//			idn->enqueue(c->getid());
//		}
//		else if (c->gettype() == VIP)
//		{
//			idv->enqueue(c->getid());
//		}
//		else
//		{
//			ids->enqueue(c->getid());
//		}
//		DeliveredC.enqueue(c);
//	}
//	PUI->PrintCargoId(idn, ids, idv);
//	delete idn, ids, idv;
//}

//Queue<int>* Company::CargoDataPQ(PriorityQueue<Cargo*>& q)
//{
//	Queue<int>* data = new Queue<int>;
//	int sz = q.GetSize();
//	Queue<Cargo*> temp;
//	Cargo* ptr = nullptr;
//	while (!q.isempty())
//	{
//		q.dequeue(ptr);
//		data->enqueue(ptr->getid());
//		temp.enqueue(ptr);
//	}
//	while (!temp.isempty())
//	{
//		temp.dequeue(ptr);
//		q.enqueue(ptr, ptr->getcost());
//	}
//	return data;
//}

void Company::AddNormList(Cargo* ptr)
{
	NWaitingC.insertend(ptr);
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

//void Company::Timer()
//{
//	
//		Event* nxt;
//		//PrintAllData();
//		//NWaitingC.print();
//		cout << "[";
//		NWaitingC.Print();
//		cout << "]" << endl;
//		while (Events.peek(nxt) && nxt->GetTime() == timer)
//		{
//			Events.dequeue(nxt);
//			nxt->excute(this);
//			delete nxt;
//		}
//		timer.hour_incr();
//		counter++;
//		if (counter == 5)
//		{
//			Cargo* ptr = nullptr;
//			if (NWaitingC.dequeue(ptr))
//				DeliveredC.enqueue(ptr);
//			if (SWaitingC.dequeue(ptr))
//				DeliveredC.enqueue(ptr);
//			if (VWaitingC.dequeue(ptr))
//				DeliveredC.enqueue(ptr);
//			counter = 0;
//		}
//
//}

void Company::deletecargo(Cargo* c)
{
	delete c;
}

void Company::simulate()
{
	PUI->simulate();
	//Timer();
}

void Company::autopromote()
{
	//Cargo* c;
	//int count = NWaitingC.GetSize();
	//for (int i = 0; i < count; i++)
	//{
	//	NWaitingC.dequeue(c);
	//	if (c->getWT().tohours() >= AutoP)
	//	{
	//		Time t;
	//		Event* promote = new Promotion(t,c->getid(), 0);
	//		promote->excute(this);
	//		delete promote;
	//	}
	//	else
	//	{
	//		NWaitingC.enqueue(c);
	//	}
	//	
	//}
}
