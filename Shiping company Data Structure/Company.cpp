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
	PUI = new UI();
}


Time Company::GetTime()
{
	return timer;
}

void Company::ReadFile(ifstream& fin)
{

	ReadTrucks(fin);
	int d, h;
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
	int ids = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			fin >> data[i][j];
	fin >> MaintainenceLimit;
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

			Truck* ptr = new Truck(data[1][i], data[2][i], data[3][i], type, ++ids);
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
	AssignmentVIP();
	AssignmentSpecial();
	AssignmentNormal();
	Event* nxt;
	while (Events.peek(nxt) && nxt->GetTime() == timer)
	{
		Events.dequeue(nxt);
		nxt->excute(this);
		delete nxt;
	}
	/*counter++;
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
	}*/

}

bool Company::Assignment()
{
	while (!ReadyT[0].isempty() || !ReadyT[1].isempty() || !ReadyT[2].isempty())
	{
		//there is no need for while loop here as this conditions are handeled inside each
		//assignment
		AssignmentVIP();
		AssignmentNormal();
		AssignmentSpecial();
		return true;
	}
	return false;
}


void Company::AssignmentVIP()
{

	Cargo* C;
	Truck* T;
	int AvailableCargos = VWaitingC.GetSize();
	if (!ReadyT[2].isempty())//you have two conditions, think of it deeply 
	{
		ReadyT[2].peek(T);
		if (AvailableCargos >= T->getcap())
			ReadyT[2].dequeue(T);
	}
	else if (!ReadyT[0].isempty())
	{
		ReadyT[0].peek(T);
		if (AvailableCargos >= T->getcap())
			ReadyT[0].dequeue(T);
	}
	else
	{
		ReadyT[1].peek(T);
		if (AvailableCargos >= T->getcap())
			ReadyT[1].dequeue(T);
	}

	if (AvailableCargos >= T->getcap())
	{
		//is equivilent to previous condition replace
		//shoof ani truck fadya mn al 3 3la asas al criteria
		//w 7ot fl fadya

		T->SetStartLoading(timer);// bnset an al truck bd2t amta t load
		for (int i = 0; i < T->getcap(); i++)
		{
			VWaitingC.dequeue(C);
			T->loadC(C);
		}
		LoadingT[T->GetType()].enqueue(T, -T->getMaxCLT().tohours());
		//al satr dh mohem gdn fakrni ashrholk f vn
		//b5tsar b7ot al truck fl loading
	}

}

void Company::AssignmentSpecial()
{
	Truck* T;
	int AvailableCargos = SWaitingC.GetSize();
	Cargo* C;

	ReadyT[1].peek(T);

	if (AvailableCargos >= T->getcap())
	{
		ReadyT[1].dequeue(T);
		T->SetStartLoading(timer);
		for (int i = 0; i < T->getcap(); i++)
		{
			SWaitingC.dequeue(C);
			T->loadC(C);
		}
		LoadingT[T->GetType()].enqueue(T, -T->getMaxCLT().tohours());
	}

}

void Company::AssignmentNormal()
{
	Truck* T = nullptr;
	int AvailableCargos = NWaitingC.GetSize();
	Cargo* C;

	if (!ReadyT[0].isempty())
	{
		ReadyT[0].peek(T);
		if (AvailableCargos >= T->getcap())
		{
			ReadyT[0].dequeue(T);
			T->SetStartLoading(timer);
			for (int i = 0; i < T->getcap(); i++)
			{

				C = NWaitingC.remRet1();
				T->loadC(C);



			}
			LoadingT[T->GetType()].enqueue(T, -T->getMaxCLT().tohours());

		}

	}
	else if (!ReadyT[2].isempty())
	{
		ReadyT[2].peek(T);
		if (AvailableCargos >= T->getcap())
		{
			ReadyT[2].dequeue(T);
			T->SetStartLoading(timer);
			for (int i = 0; i < T->getcap(); i++)
			{
				C = NWaitingC.remRet1();
				T->loadC(C);

			}
			LoadingT[T->GetType()].enqueue(T, -T->getMaxCLT().tohours());
		}

	}

}

void Company::autopromote()
{
	Cargo* c;
	int count = NWaitingC.GetSize();
	c = NWaitingC.getEntry1();
	while (c->getWT().tohours() >= AutoP * 24)
	{
		c = NWaitingC.remRet1();
		Time t;
		Event* promote = new Promotion(c->getid(), 0);
		promote->excute(this);
		delete promote;
		c = NWaitingC.getEntry1();
	}
}
void Company::LoadFile()
{
	ifstream fin(PUI->readfilename());
	this->ReadFile(fin);
}

void Company::CurrData()
{

	PUI->displayTime(timer);
	PUI->displayNum(NWaitingC.GetSize() + SWaitingC.GetSize() + VWaitingC.GetSize());
	PUI->displaytext(" Waiting Cargos: ");
	PUI->PrintLC(NWaitingC, Normal);
	PUI->displaytext(" ");
	PUI->PrintQC(SWaitingC, Special);
	PUI->displaytext(" ");
	PUI->PrintPQC(VWaitingC, VIP);
	PUI->displayline();

	PUI->displayNum(LoadingT[0].GetSize() + LoadingT[1].GetSize() + LoadingT[2].GetSize());
	PUI->displaytext(" Loading Trucks: ");
	PUI->PrintPQT(LoadingT[0]);
	PUI->displaytext(" ");
	PUI->PrintPQT(LoadingT[1]);
	PUI->displaytext(" ");
	PUI->PrintPQT(LoadingT[2]);

	if (LoadingT[0].isempty() && LoadingT[1].isempty() && LoadingT[2].isempty())
	{
		PUI->PrintBracketStart(Normal);
		PUI->PrintBracketEnd(Normal);
		PUI->displaytext(", ");
		PUI->PrintBracketStart(Special);
		PUI->PrintBracketEnd(Special);
		PUI->displaytext(", ");
		PUI->PrintBracketStart(VIP);
		PUI->PrintBracketEnd(VIP);
	}

	PUI->displayline();

	PUI->displayNum(ReadyT[0].GetSize() + ReadyT[1].GetSize() + ReadyT[2].GetSize());
	PUI->displaytext(" Empty Trucks: ");
	PUI->PrintEQT(ReadyT[0], Normal);
	PUI->displaytext(", ");
	PUI->PrintEQT(ReadyT[1], Special);
	PUI->displaytext(", ");
	PUI->PrintEQT(ReadyT[2], VIP);
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
	PUI->PrintEQT(MaintainedT[0], Normal);
	PUI->displaytext(", ");
	PUI->PrintEQT(MaintainedT[1], Special);
	PUI->displaytext(", ");
	PUI->PrintEQT(MaintainedT[2], VIP);
	PUI->displayline();

	PUI->displayNum(NDeliveredC.GetSize() + SDeliveredC.GetSize() + VDeliveredC.GetSize());
	PUI->displaytext(" Delivered Cargos: ");
	PUI->PrintQC(NDeliveredC, Normal);
	PUI->displaytext(" ");
	PUI->PrintQC(SDeliveredC, Special);
	PUI->displaytext(" ");
	PUI->PrintQC(VDeliveredC, VIP);
	PUI->displayline();



}

void Company::simulate()
{
	PUI->readmode();
	while (IsRemainingEvents())
	{
		if (GetTime().CompInRangeH(5, 23))//checks current hour is in range of working hours
		{
			PUI->WaitOption();
			Timer();
			CurrData();
		}
		IncrementHour();
	}
}

void Company::IncrementHour()
{
	timer.hour_incr();
}
void Company::Maintenance()
{
	for (int i = 0; i < 3; i++)
	{
		if (!MaintainedT[i].isempty())
		{
			Truck* ptr;
			bool itemfound = MaintainedT[i].peek(ptr);
			while (itemfound && !ptr->InMaintainence(timer))
			{
				MaintainedT[i].dequeue(ptr);
				ptr->EndMaitainence();
				ReadyT[i].enqueue(ptr);
				itemfound = MaintainedT[i].peek(ptr);
			}
		}
	}
}

void Company::TruckControl()
{
	for (int i = 0; i < 3; i++)
	{
		//loading->in_trip

		Truck* x = nullptr;
		LoadingT[i].peek(x);

		if (!x)
			continue;

		while (x)
		{
			//Truck* x2 = x;  no need for x2

			Time Cargos_are_loaded = x->getMaxCLT() + x->getStartLoading();

			if (Cargos_are_loaded == timer)
			{
				Cargo* c = nullptr;
				x->peekTopC(c);

				LoadingT[i].dequeue(x);
				In_TripT[i].enqueue(x, -(c->getdeldis())); //they are 3 intrip not one
			}
			bool existmore = LoadingT[i].peek(x);
			if (!existmore)  //x2 == x old but you should check whether it returned true or false see implementation of peek
				break;

		}
	}

	for (int i = 0; i < 3; i++)
	{
		Truck* t = nullptr;
		Cargo* c = nullptr;

		In_TripT[i].peek(t);

		if (t->peekTopC(c))
		{
			while (c->getCDT() == timer)
			{
				t->dequeuetop(c);

				if (i == 0)
					NDeliveredC.enqueue(c);
				else if (i == 1)
					VDeliveredC.enqueue(c);
				else
					SDeliveredC.enqueue(c);

				t->inc_tDC();

				In_TripT[i].dequeue(t);
				if (t->peekTopC(c))
					In_TripT[i].enqueue(t, -(c->getCDT().tohours()));
				else
				{
					t->setReturn_time(timer);

					In_TripT[i].enqueue(t, -(t->getReturn_time().tohours()));
				}
				In_TripT[i].peek(t);
				if (!t->peekTopC(c))
					break;
			}

		}
	}

	//if (t->Check_endtrip(timer))
	//{
	//	t->IncementJ();
	//	t->SetMTime(timer);
	//	In_TripT[i].dequeue(t);

	//	if (t->getCurrj() == MaintainenceLimit)
	//		MaintainedT[i].enqueue(t);

	//	else
	//		ReadyT[i].enqueue(t);

	//}

}