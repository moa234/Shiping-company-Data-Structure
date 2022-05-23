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
	LoadingN = nullptr; LoadingS = nullptr; LoadingV = nullptr;
	for (int i = 0; i < 3; i++)
	{
		loadflag[i] = 0;
	}
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
	bool cond1 = (LoadingN ? 1 : 0) || (LoadingS ? 1 : 0) || (LoadingV ? 1 : 0) || MaintainedT[VIP].GetSize() || MaintainedT[Special].GetSize() || MaintainedT[Normal].GetSize();
	bool cond2 = In_TripT.GetSize() || Events.GetSize() || NWaitingC.GetSize() || SWaitingC.GetSize();
	return cond1 || cond2;
}

void Company::savefile(ofstream& fout)
{
	fout << "CDT" << "\tID" << "\tPT" << "\tWT" << "\tTID" << endl;
	int count = DeliveredC.GetSize();
	Cargo* c;
	int countND = 0;
	int countVD = 0;
	int countSD = 0;
	int totalnor = 0;
	Time totalwait(0, 0);
	int totalautoP = 0;
	for (int i = 0; i < count; i++)
	{
		DeliveredC.dequeue(c);
		if (c->gettype() == Normal)
			countND += 1;
		if (c->gettype() == VIP)
		{
			countVD += 1;
			if (c->getautop())
				totalautoP += 1;
			if (c->getprom())
				totalnor += 1;
		}
		if (c->gettype() == Special)
			countSD += 1;
		totalwait = totalwait + c->getWT();
		fout << c->getCDT().GetDay() << ":" << c->getCDT().GetHour() << "\t" << c->getid() << "\t" << c->getprept().GetDay() << ":"
			<< c->getprept().GetHour() << "\t" << c->getWT().GetDay() << ":" << c->getWT().GetHour() << "\t" << c->getTID() << endl;
	}
	fout << "...................................." << endl;
	fout << "...................................." << endl;

	fout << "Cargos: " << count << " [N: " << countND << ", S: " << countSD << ", V: " << countVD << "]" << endl;

	totalwait.toTime(totalwait.tohours() / count);
	fout << "Cargo Avg Wait: " << totalwait.GetDay() << ":" << totalwait.GetHour() << endl;

	totalnor += countND;
	fout << "Auto-promoted Cargos: " << ((totalnor > 0) ? ((float)totalautoP / totalnor * 100) : 0) << "% from total " << totalnor << endl;

	int countt = ReadyT[Normal].GetSize() + ReadyT[VIP].GetSize() + ReadyT[Special].GetSize();
	fout << "Trucks: " << countt << " [N: " << ReadyT[Normal].GetSize() << ", S: " << ReadyT[Special].GetSize() << ", V: " << ReadyT[VIP].GetSize() << "]" << endl;


}

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
	float cost = ptr->getcost();
	VWaitingC.enqueue(ptr, cost/(ptr->getdeldis() * ptr->getprept().tohours()));
	if (loadflag[VIP])
	{
		Cargo* c;
		VWaitingC.peek(c);
		if (ptr == c)
		{
			MapTruckToCargo(VIP)->SetPrevLoad(timer);
		}
	}
}


void Company::Timer()
{
	/*if (timer.GetDay() == 6 && timer.GetHour() == 20)
	{
		int x;
		cin >> x;
	}*/
	Assignment();
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

void Company::Assignment()
{

	Maintenance();
	if (GetTime().CompInRangeH(5, 23))//checks current hour is in range of working hours
	{
		AssignmentVIP();
		AssignmentSpecial();
		AssignmentNormal();
		AssignmentCargo(VIP);
		AssignmentCargo(Normal);
		AssignmentCargo(Special);
		autopromote();
	}
	TruckControl();
}


void Company::AssignmentVIP()
{
	Truck* T = nullptr;
	int AvailableCargos = VWaitingC.GetSize();
	if (loadflag[VIP] == 0)
	{
		if (!ReadyT[VIP].isempty() && !LoadingV)//you have two conditions, think of it deeply 
		{
			ReadyT[VIP].peek(T);
			if (AvailableCargos >= T->getcap())
			{
				ReadyT[VIP].dequeue(T);
				LoadingV = T;
				LoadingV->SetStartLoading(timer, VIP);
				loadflag[VIP] = 1;
			}

		}
		else if (!ReadyT[Normal].isempty() && !LoadingN)
		{
			ReadyT[Normal].peek(T);
			if (AvailableCargos >= T->getcap())
			{
				ReadyT[Normal].dequeue(T);
				LoadingN = T;
				LoadingN->SetStartLoading(timer, VIP);
				loadflag[VIP] = 1;
			}
		}
		else if (!ReadyT[Special].isempty() && !LoadingS)
		{
			ReadyT[Special].peek(T);
			if (AvailableCargos >= T->getcap())
			{
				ReadyT[Special].dequeue(T);
				LoadingS = T;
				LoadingS->SetStartLoading(timer, VIP);
				loadflag[VIP] = 1;
			}
		}

	}
}

void Company::AssignmentSpecial(bool maxw)
{
	Truck* T;
	int AvailableCargos = SWaitingC.GetSize();

	if (ReadyT[Special].peek(T) && loadflag[Special] == 0)
	{
		if ((AvailableCargos >= T->getcap() || maxw) && !LoadingS)
		{
			ReadyT[Special].dequeue(T);
			LoadingS = T;
			T->SetStartLoading(timer, Special);
			loadflag[Special] = 1;
		}
	}
}
void Company::MaxWaitAssign(Itemtype ctype)
{
	if (ctype == Normal)
		AssignmentNormal(1);
	if (ctype == Special)
		AssignmentSpecial(1);
}
bool Company::MaxWaitCheck(Itemtype ctype)
{
	if (ctype == VIP)
		return 0;
	if (ctype == Normal)
	{
		Cargo* C = NWaitingC.getEntry1();
		if (!C) return 0;
		return MaxWaitExceed(C);
	}
	if (ctype == Special)
	{
		Cargo* C;
		if (SWaitingC.peek(C))
			return MaxWaitExceed(C);
		else
			return 0;
	}
}
bool Company::MaxWaitExceed(Cargo* C)
{
	return ((timer - C->getprept()).tohours() >= maxW);
}
void Company::AssignmentCargo(Itemtype ctype)
{
	bool isMaxW = MaxWaitCheck(ctype);
	if (loadflag[ctype] == 0)
	{
		if (isMaxW)
		{
			MaxWaitAssign(ctype);
			return;
		}
		else
			return;
	}
	Truck*& Tcargo = MapTruckToCargo(ctype);
	Cargo* C = PeekTopCargo(ctype);

	bool isloaded = 0;
	if (C && (C->getloadt() <= (timer - Tcargo->GetPrevLoad()).tohours()))
	{
		C = DequeueTopCargo(ctype);
		Tcargo->loadC(C, timer);
		Tcargo->SetPrevLoad(timer);
		isloaded = 1;
	}
	CheckEndLoading(Tcargo, isMaxW && isloaded);
}
void Company::CheckEndLoading(Truck*& T, bool maxw)
{
	if (T->FullCapacity() || maxw)
	{
		T->EndLoading(timer);
		Cargo* c = nullptr;
		T->peekTopC(c);
		In_TripT.enqueue(T, -(c->getCDT().tohours())); //they are 3 intrip not one
		loadflag[T->GetCargoType()] = 0;
		T = nullptr;
	}
	else
	{ //Handling Case of Promotion or Cancelling during loading
		if (T->GetCargoType() == Normal && NWaitingC.GetSize() == 0)
		{

			if (T->GetCargoSize() == 0)
			{
				T->EndLoading(timer);
				ReadyT[T->GetType()].enqueue(T);
				loadflag[Normal] = 0;
				T = nullptr;
			}
			else
			{
				T->EndLoading(timer);
				Cargo* c = nullptr;
				T->peekTopC(c);
				In_TripT.enqueue(T, -(c->getCDT().tohours())); //they are 3 intrip not one
				loadflag[T->GetCargoType()] = 0;
				T = nullptr;
			}

		}
	}
}
Cargo* Company::DequeueTopCargo(Itemtype ctype)
{
	Cargo* C = nullptr;
	if (ctype == Normal)
	{
		C = NWaitingC.remRet1();
	}
	if (ctype == Special)
	{
		SWaitingC.dequeue(C);
	}
	if (ctype == VIP)
	{
		VWaitingC.dequeue(C);
	}
	return C;
}
Cargo* Company::PeekTopCargo(Itemtype ctype)
{
	Cargo* C = nullptr;
	if (ctype == Normal)
	{
		C = NWaitingC.getEntry1();
	}
	if (ctype == Special)
	{
		SWaitingC.peek(C);
	}
	if (ctype == VIP)
	{
		VWaitingC.peek(C);
	}
	return C;
}
Truck*& Company::MapTruckToCargo(Itemtype ctype)
{
	if (LoadingN && LoadingN->GetCargoType() == ctype)
		return LoadingN;
	if (LoadingS && LoadingS->GetCargoType() == ctype)
		return LoadingS;
	if (LoadingV && LoadingV->GetCargoType() == ctype)
		return LoadingV;
}
void Company::AssignmentNormal(bool maxw)
{
	Truck* T = nullptr;
	int AvailableCargos = NWaitingC.GetSize();
	if (loadflag[Normal] == 0)
	{
		if (!ReadyT[Normal].isempty() && !LoadingN)
		{
			ReadyT[Normal].peek(T);
			if (AvailableCargos >= T->getcap() || maxw)
			{
				ReadyT[Normal].dequeue(T);
				T->SetStartLoading(timer, Normal);
				LoadingN = T;
				loadflag[Normal] = 1;

			}

		}
		else if (!ReadyT[VIP].isempty() && !LoadingV)
		{
			ReadyT[VIP].peek(T);
			if (AvailableCargos >= T->getcap() || maxw)
			{
				ReadyT[VIP].dequeue(T);
				T->SetStartLoading(timer, Normal);
				loadflag[Normal] = 1;
				LoadingV = T;
			}

		}
	}

}

void Company::autopromote()
{
	if (loadflag[Normal] == 1)
		return;
	Cargo* c;
	c = NWaitingC.getEntry1();
	if (c)
	{
		while ((timer.tohours() - c->getprept().tohours()) >= AutoP * 24)
		{
			//(c->getprept() + timer).tohours() >= AutoP   shoof kda ya moaaz?salah.
			Time t;
			Event* promote = new Promotion(c->getid(), 0);
			promote->excute(this);
			c->setautop(1);
			delete promote;
			c = NWaitingC.getEntry1();
			if (!c)
			{
				break;
			}
		}
	}
}
void Company::LoadFile()
{
	ifstream fin(PUI->readfilename());
	this->ReadFile(fin);
}

void Company::CurrData()
{
	if (PUI->getmode() == silent)
	{
		if (timer.tohours() <= 25)
		{
			PUI->displaytext("Simulation starts...");
		}
		if (!IsRemainingEvents())
		{
			PUI->displaytext("Simulation ends, output file generated.");
		}
		return;
	}
	PUI->displayTime(timer);
	PUI->displayNum(NWaitingC.GetSize() + SWaitingC.GetSize() + VWaitingC.GetSize());
	PUI->displaytext(" Waiting Cargos: ");
	PUI->PrintLC(NWaitingC, Normal);
	PUI->displaytext(" ");
	PUI->PrintQC(SWaitingC, Special);
	PUI->displaytext(" ");
	PUI->PrintPQC(VWaitingC, VIP);
	PUI->displayline();
	PUI->displayNum((LoadingN ? 1 : 0) + (LoadingS ? 1 : 0) + (LoadingV ? 1 : 0));
	PUI->displaytext(" Loading Trucks: ");
	PUI->PrintT(LoadingN);
	PUI->displaytext(" ");
	PUI->PrintT(LoadingS);
	PUI->displaytext(" ");
	PUI->PrintT(LoadingV);

	/*if (LoadingT[0].isempty() && LoadingT[1].isempty() && LoadingT[2].isempty())
	{
		PUI->PrintBracketStart(Normal);
		PUI->PrintBracketEnd(Normal);
		PUI->displaytext(", ");
		PUI->PrintBracketStart(Special);
		PUI->PrintBracketEnd(Special);
		PUI->displaytext(", ");
		PUI->PrintBracketStart(VIP);
		PUI->PrintBracketEnd(VIP);
	}*/

	PUI->displayline();

	PUI->displayNum(ReadyT[0].GetSize() + ReadyT[1].GetSize() + ReadyT[2].GetSize());
	PUI->displaytext(" Empty Trucks: ");
	PUI->PrintEQT(ReadyT[0], Normal);
	PUI->displaytext(", ");
	PUI->PrintEQT(ReadyT[1], Special);
	PUI->displaytext(", ");
	PUI->PrintEQT(ReadyT[2], VIP);
	PUI->displayline();

	PUI->displayNum(In_TripT.GetSize());
	PUI->displaytext(" Moving Cargos: ");
	PUI->PrintPQT(In_TripT);
	PUI->displayline();

	PUI->displayNum(MaintainedT[0].GetSize() + MaintainedT[1].GetSize() + MaintainedT[2].GetSize());
	PUI->displaytext(" In-Checkup Trucks: ");
	PUI->PrintEQT(MaintainedT[0], Normal);
	PUI->displaytext(", ");
	PUI->PrintEQT(MaintainedT[1], Special);
	PUI->displaytext(", ");
	PUI->PrintEQT(MaintainedT[2], VIP);
	PUI->displayline();

	PUI->displayNum(DeliveredC.GetSize());
	PUI->displaytext(" Delivered Cargos: ");
	PUI->PrintDQC(DeliveredC);
	PUI->displayline();



}

void Company::simulate()
{
	PUI->readmode();
	while (IsRemainingEvents())
	{

		PUI->WaitOption();
		Timer();
		CurrData();
		IncrementHour();
	}
	ofstream fout("save.txt");
	savefile(fout);
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
				addtoready(ptr);
				itemfound = MaintainedT[i].peek(ptr);
			}
		}
	}
}
void Company::cargodeliver(Truck*& t, bool& moretrucks, Cargo*& c)
{
	while (t->peekTopC(c) && c->getCDT() == timer)
	{
		moretrucks = 1;
		t->dequeuetop(c);
		c->setdelivered(1);
		DeliveredC.enqueue(c);
		t->inc_tDC();

	}
	if (moretrucks == 1)
	{
		In_TripT.dequeue(t);
		if (t->peekTopC(c))
			In_TripT.enqueue(t, -(c->getCDT().tohours()));
		else
		{
			In_TripT.enqueue(t, -(t->getReturn_time().tohours()));
		}
	}
}

void Company::addtomaintain(Truck*& t)
{
	if (t->GetType() == VIP)
	{
		MaintainedT[VIP].enqueue(t);
	}
	else if (t->GetType() == Normal)
	{
		MaintainedT[Normal].enqueue(t);
	}
	else
	{
		MaintainedT[Special].enqueue(t);
	}
	t->SetMTime(timer);
}

void Company::addtoready(Truck*& t)
{
	if (t->GetType() == VIP)
	{
		ReadyT[VIP].enqueue(t);
	}
	else if (t->GetType() == Normal)
	{
		ReadyT[Normal].enqueue(t);
	}
	else
	{
		ReadyT[Special].enqueue(t);
	}
}
void Company::returnTruck(Truck*& t, bool& moretrucks)
{
	if (t->getReturn_time() == timer)
	{
		moretrucks = 1;
		In_TripT.dequeue(t);
		t->IncementJ();
		if (t->getCurrj() % MaintainenceLimit == 0)
		{
			addtomaintain(t);
		}
		else
		{
			addtoready(t);
		}

	}
}
void Company::TruckControl()
{
	Truck* t = nullptr;
	Cargo* c = nullptr;
	bool moretrucks = 1;
	while (moretrucks && In_TripT.peek(t))
	{
		moretrucks = 0;
		if (t->peekTopC(c))
		{
			cargodeliver(t, moretrucks, c);
		}
		else
		{
			returnTruck(t, moretrucks);
		}
	}
}