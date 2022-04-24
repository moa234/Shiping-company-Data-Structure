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

bool Company::IsRemainingEvents()
{
	return Events.GetSize() + NWaitingC.GetSize() + VWaitingC.GetSize() + SWaitingC.GetSize() != 0;
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


Cargo* Company::getNCargo(int id)
{
	return NWaitingC.remRet(id);
}

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

void Company::Timer()
{
	
		Event* nxt;
		while (Events.peek(nxt) && nxt->GetTime() == timer)
		{
			Events.dequeue(nxt);
			nxt->excute(this);
			delete nxt;
		}
		counter++;
		if (counter == 5)
		{
			Cargo* ptr = NWaitingC.remRet1();
			if (ptr)
				NDeliveredC.enqueue(ptr);
			if (SWaitingC.dequeue(ptr))
				SDeliveredC.enqueue(ptr);
			if (VWaitingC.dequeue(ptr))
				VDeliveredC.enqueue(ptr);
			counter = 0;
		}

}


/*void Company::autopromote()
{
	Cargo* c;
	int count = NWaitingC.GetSize();
	for (int i = 0; i < count; i++)
	{
		NWaitingC.dequeue(c);
		if (c->getWT().tohours() >= AutoP)
		{
			Time t;
			Event* promote = new Promotion(t,c->getid(), 0);
			promote->excute(this);
			delete promote;
		}
		else
		{
			NWaitingC.enqueue(c);
		}
		
	}
}*/

void Company::CurrData()
{
	PUI->displayTime(timer);
	PUI->displayNum(NWaitingC.GetSize()+SWaitingC.GetSize()+VWaitingC.GetSize());
	PUI->displaytext(" Waiting Cargos: ");
	PUI->PrintLC(NWaitingC,Normal);
	PUI->displaytext(" ");
	PUI->PrintQC(SWaitingC, Special);
	PUI->displaytext(" ");
	PUI->PrintPQC(VWaitingC, VIP);
	PUI->displayline();

	PUI->displayNum(LoadingT[0].GetSize() + LoadingT[1].GetSize() + LoadingT[2].GetSize());
	PUI->displaytext(" Loading Trucks: ");
	PUI->PrintQT(LoadingT[0]);
	PUI->displaytext(" ");
	PUI->PrintQT(LoadingT[1]);
	PUI->displaytext(" ");
	PUI->PrintQT(LoadingT[2]);
	PUI->displayline();

	PUI->displayNum(ReadyT[0].GetSize() + ReadyT[1].GetSize() + ReadyT[2].GetSize());
	PUI->displaytext(" Empty Trucks: ");
	PUI->PrintQT(ReadyT[0]);
	PUI->displaytext(",");
	PUI->PrintQT(ReadyT[1]);
	PUI->displaytext(",");
	PUI->PrintQT(ReadyT[2]);
	PUI->displayline();

	PUI->displayNum(In_TripT[0].GetSize() + In_TripT[1].GetSize() + In_TripT[2].GetSize());
	PUI->displaytext(" Moving Cargos: ");
	PUI->PrintPQT(In_TripT[0]);
	PUI->displaytext(" ");
	PUI->PrintPQT(In_TripT[1]);
	PUI->displaytext(" ");
	PUI->PrintPQT(In_TripT[2]);
	PUI->displayline();

	PUI->displayNum(MaintainedT[0].GetSize() + MaintainedT[1].GetSize() + MaintainedT[2].GetSize());
	PUI->displaytext(" In-Checkup Trucks: ");
	PUI->PrintQT(MaintainedT[0]);
	PUI->displaytext(" ");
	PUI->PrintQT(MaintainedT[1]);
	PUI->displaytext(" ");
	PUI->PrintQT(MaintainedT[2]);
	PUI->displayline();

	PUI->displayNum(NDeliveredC.GetSize() + SDeliveredC.GetSize() + VDeliveredC.GetSize());
	PUI->displaytext(" Delivered Cargos: ");
	PUI->PrintQC(NDeliveredC, Normal);
	PUI->displaytext(" ");
	PUI->PrintQC(SDeliveredC, Special);
	PUI->displaytext(" ");
	PUI->PrintQC(VDeliveredC, VIP);
	PUI->displayline();

	timer.hour_incr();

}

void Company::simulate()
{
	PUI->Interface();
}
