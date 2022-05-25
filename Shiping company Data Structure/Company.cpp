#include "Company.h"
#include "Event.h"
#include "Preparation.h"
#include "Cancellation.h"
#include "UI.h"
#include "Promotion.h"

Company::Company()
{
	//initialize data member
	timer.SetDay(1); timer.SetHour(1);
	PUI = new UI();
	counter = 0;
	AutoP = 0;
	maxW = 0;
	MaintainenceLimit = 0;
	LoadingN = nullptr; LoadingS = nullptr; LoadingV = nullptr;
	for (int i = 0; i < 3; i++)
	{
		loadflag[i] = 0;
	}
}

void Company::ReadFile(ifstream& fin)
{
	//function responsible for reading parameters in input file

	//get all trucks parameters
	ReadTrucks(fin);

	//read autopromotion in days & maxwait in hours
	int d, h;
	fin >> d >> h;
	AutoP = d;
	maxW = h;

	//read prep, promotion, cancellation events parameters
	ReadEvents(fin);
}

bool Company::IsRemainingEvents()
{
	//checks if there is any more action to be done and return true if found

	//cond1 checks for loading cargos and trucks in maintainance
	bool cond1 = (LoadingN ? 1 : 0) || (LoadingS ? 1 : 0) || (LoadingV ? 1 : 0) || MaintainedT[VIP].GetSize() || MaintainedT[Special].GetSize() || MaintainedT[Normal].GetSize();

	//cond2 checks for any moving trucks and for waiting cargos
	bool cond2 = In_TripT.GetSize() || Events.GetSize() || NWaitingC.GetSize() || SWaitingC.GetSize();

	return cond1 || cond2;
}

void Company::savefile()
{
	// function generates output file and calculate parameters
	ofstream fout("save.txt");

	//calculate total simulation file
	Time simtime(1, 1);
	simtime = timer - simtime;

	//print cargo parameters
	fout << "CDT" << "\tID" << "\tPT" << "\tWT" << "\tTID" << endl;
	//initialize counts of cargos
	Cargo* c;
	int count = DeliveredC.GetSize();
	int countND = 0;
	int countVD = 0;
	int countSD = 0;
	int totalnor = 0;
	Time totalwait(0, 0);
	int totalautoP = 0;
	for (int i = 0; i < count; i++)
	{
		//dequeue every cargo then check type and increment count corresponding to its type
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
		//increment total waiting time for delivered cargo
		totalwait = totalwait + c->getWT();
		//print the parameters
		fout << c->getCDT().GetDay() << ":" << c->getCDT().GetHour() << "\t" << c->getid() << "\t" << c->getprept().GetDay() << ":"
			<< c->getprept().GetHour() << "\t" << c->getWT().GetDay() << ":" << c->getWT().GetHour() << "\t" << c->getTID() << endl;
		//deallocate cargo from memory as it is no longer needed
		delete c;
	}

	fout << "...................................." << endl;
	fout << "...................................." << endl;

	//print general paramters for all cargos and trucks

	//print total number of cargos
	fout << "Cargos: " << count << " [N: " << countND << ", S: " << countSD << ", V: " << countVD << "]" << endl;

	//prints average waiting time of cargos
	totalwait.toTime((count != 0) ? totalwait.tohours() / count : 0);
	fout << "Cargo Avg Wait: " << totalwait.GetDay() << ":" << totalwait.GetHour() << endl;

	//calculate percent of auto promoted cargos from total number
	totalnor += countND;
	fout << "Auto-promoted Cargos: " << ((totalnor > 0) ? ((float)totalautoP / totalnor * 100) : 0) << "% from total " << totalnor << endl;

	//save counts for each ready truck and total number then print count
	int countn = ReadyT[Normal].GetSize();
	int countv = ReadyT[VIP].GetSize();
	int counts = ReadyT[Special].GetSize();
	int countt = countn + countv + counts;
	fout << "Trucks: " << countt << " [N: " << countn << ", S: " << counts << ", V: " << countv << "]" << endl;

	Time tactive(0, 0);
	Truck* t;
	float util = 0;

	//deque every ready truck and increment total active time and utilisation
	for (int i = 0; i < countn; i++)
	{
		ReadyT[Normal].dequeue(t);
		tactive = tactive + t->getTActive();
		util = util + t->calcUtil(simtime);

		//deallocate truck as it is not needed anymore
		delete t;
	}
	for (int i = 0; i < countv; i++)
	{
		ReadyT[VIP].dequeue(t);
		tactive = tactive + t->getTActive();
		util = util + t->calcUtil(simtime);

		//deallocate truck as it is not needed anymore
		delete t;
	}
	for (int i = 0; i < counts; i++)
	{
		ReadyT[Special].dequeue(t);
		tactive = tactive + t->getTActive();
		util = util + t->calcUtil(simtime);

		//deallocate truck as it is not needed anymore
		delete t;
	}

	//print average active time as percent from total simulation
	fout << "Avg Active time: " << (tactive.tohours() / (float)countt) / simtime.tohours() * 100 << "% of total time " << simtime.GetDay() << ":" << simtime.GetHour() << endl;
	//print average utilization of truck
	fout << "Avg utilization: " << util / countt * 100 << "%" << endl;
}

void Company::ReadTrucks(ifstream& fin)
{
	int data[4][3]; // one row for count of vechiles,then another for speed,then another for capacity,then another for maintainence
					// one coloum contains complete data of a truck type
	int ids = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			fin >> data[i][j];
	fin >> MaintainenceLimit; // read no. of journeys to complete before entering maintainance
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
			//create truck from parameters given in save file and enque it in corresponding queue
			Truck* ptr = new Truck(data[1][i], data[2][i], data[3][i], type, ++ids);
			ReadyT[type].enqueue(ptr);
		}
	}

}

void Company::ReadEvents(ifstream& fin)
{
	//gets events number
	int eventsnum;
	fin >> eventsnum;

	for (int i = 0; i < eventsnum; i++)
	{
		char evtype;
		fin >> evtype;
		Itemtype category{};

		if (evtype == 'R')
		{
			//reads preparation events parameters
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

			//create preparation event and add it to events queue
			Event* prep = new Preparation(category, et, datar[2], datar[3], datar[4], datar[5]);
			Events.enqueue(prep);
		}
		else if (evtype == 'X')
		{
			//read cancellation events parameters
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

			//create cancellation event and add it to events queue
			Event* cancel = new Cancellation(etx, datax[2]);
			Events.enqueue(cancel);
		}
		else if (evtype == 'P')
		{
			//read promotion events
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

			//create cancellation event and add it to events queue
			Event* prom = new Promotion(etp, datap[2], datap[3]);
			Events.enqueue(prom);
		}
	}
}


Cargo* Company::getNCargo(int id)
{
	//remove cargo from ready list with certain id and returns it by pointer
	return NWaitingC.remRet(id);
}

void Company::AddNormList(Cargo* ptr)
{
	//add certain truck to end of ready cargos list
	NWaitingC.insertend(ptr);
}

void Company::AddSpeList(Cargo* ptr)
{
	//enque cargo to ready special queue
	SWaitingC.enqueue(ptr);
}

void Company::AddVIPList(Cargo* ptr)
{
	//add cargo to vip list uwing a priority equation
	double cost = ptr->getcost();
	VWaitingC.enqueue(ptr, cost / (ptr->getdeldis() + 0.3 * ptr->getprept().tohours()));

	//sets previous load time with current time if a new cargo is added to vip with higher priority while loading
	//this stops current cargo from being loaded an start loading higher priority
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
	//responsible for all actions in current time

	Maintenance();

	//read events when its time comes and excute its action
	Event* nxt;
	while (Events.peek(nxt) && nxt->GetTime() == timer)
	{
		Events.dequeue(nxt);
		nxt->excute(this);
		//deallocate event after excution
		delete nxt;
	}
	//assign ready and loading cargos to trucks
	Assignment();
	TruckControl();
}

void Company::Assignment()
{

	if (timer.CompInRangeH(5, 23))//checks current hour is in range of working hours
	{
		AssignmentVIP();
		AssignmentSpecial();
		AssignmentNormal();
		LoadingCargo(VIP);
		LoadingCargo(Normal);
		LoadingCargo(Special);
		autopromote();
	}
}


void Company::AssignmentVIP()
{
	Truck* T = nullptr;
	int AvailableCargos = VWaitingC.GetSize(); //number of available cargos
	if (loadflag[VIP] == 0) //checking whether there are current assignment for vip cargo
	{
		//if there are no current loading for vip cargos
		if (!ReadyT[VIP].isempty() && !LoadingV) //if there is available trucks and no current loading vipv or normal cargos through vip trucks
		{
			ReadyT[VIP].peek(T);
			if (AvailableCargos >= T->getcap())
			{
				ReadyT[VIP].dequeue(T);
				LoadingV = T;
				LoadingV->SetStartLoading(timer, VIP); //loading begins
				loadflag[VIP] = 1;
			}

		}
		else if (!ReadyT[Normal].isempty() && !LoadingN) //if there is available trucks and no current loading vip or normal cargos through normal trucks
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
		else if (!ReadyT[Special].isempty() && !LoadingS) //if there is available trucks and no current loading vip or special cargos through special trucks
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
	//the true(1) parameter is send for AssignmentSpecial to handle assigning a single cargo for maximum waiting rule
	Truck* T;
	int AvailableCargos = SWaitingC.GetSize();

	if (ReadyT[Special].peek(T) && loadflag[Special] == 0) //checks availability of special trucks and no current loading for special cargos 
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
void Company::AssignmentNormal(bool maxw)
{
	//the true(1) parameter is send for AssignmentNormal to handle assigning a single cargo for maximum waiting rule
	Truck* T = nullptr;
	int AvailableCargos = NWaitingC.GetSize();
	if (loadflag[Normal] == 0) //checks no current loading for normal cargos
	{
		if (!ReadyT[Normal].isempty() && !LoadingN) //if there is available trucks and no current loading vip or normal cargos through normal trucks
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
		else if (!ReadyT[VIP].isempty() && !LoadingV) //if there is available trucks and no current loading vip or normal cargos through vip trucks
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
void Company::MaxWaitAssign(Itemtype ctype)
{
	if (ctype == Normal)
		AssignmentNormal(1); //the true(1) parameter is send for AssignmentNormal to handle assigning a single cargo for maximum waiting rule 
	if (ctype == Special)
		AssignmentSpecial(1); //the true(1) parameter is send for AssignmentSpecial to handle assigning a single cargo for maximum waiting rule
}
bool Company::MaxWaitCheck(Itemtype ctype)
{
	if (ctype == VIP) //no max wait for vip
		return 0;
	if (ctype == Normal)
	{
		Cargo* C = NWaitingC.getEntry1();
		if (!C) return 0;
		return MaxWaitExceed(C); //checking for front element max wait
	}
	if (ctype == Special)
	{
		Cargo* C;
		if (SWaitingC.peek(C))
			return MaxWaitExceed(C); // checking for front element max wait
		else
			return 0;
	}
}
bool Company::MaxWaitExceed(Cargo* C)
{
	return ((timer - C->getprept()).tohours() >= maxW);
}
void Company::LoadingCargo(Itemtype ctype)
{
	bool isMaxW = MaxWaitCheck(ctype); //checks whether there are applicaple cargo of type for max wait 
	if (loadflag[ctype] == 0) //if there is no current truck loading
	{
		if (isMaxW) //if there are max wait case and no truck is loading 
		{
			MaxWaitAssign(ctype); //go ahead and assign a truck for this cargo to start loading and moving
			return;
		}
		else
			return;
	}
	Truck*& Tcargo = MapTruckToCargo(ctype); //gets the current truck that is loading cargo 
	Cargo* C = PeekTopCargo(ctype); //gets the top cargo of a list

	bool isloaded = 0;
	if (C && (C->getloadt() <= (timer - Tcargo->GetPrevLoad()).tohours())) //case cargo finishes its loading time
	{
		C = DequeueTopCargo(ctype); //dequeues the top cargo from a list of type ctype
		Tcargo->loadC(C, timer); //now cargo is actually loaded on the truck
		Tcargo->SetPrevLoad(timer); //for end of laoding of next which depend on the previous loaded cargo
		isloaded = 1;
	}
	CheckEndLoading(Tcargo, isMaxW && isloaded); //checks whether a truck finished its loading or not
}
void Company::CheckEndLoading(Truck*& T, bool maxw)
{
	if (T->FullCapacity() || maxw) //whether capacity of truck is full or there is a special case of max waiting and truck have to be moved to moving list
	{
		T->EndLoading(timer); //ends the loading process of truck 
		Cargo* c = nullptr;
		T->peekTopC(c);
		In_TripT.enqueue(T, -(c->getCDT().tohours())); //enqueuing the truck with the cargo delivery time of the first cargo to arrive
		loadflag[T->GetCargoType()] = 0; //return the status of loading to false
		T = nullptr;
	}
	else
	{ //Handling Case of Promotion or Cancelling during loading
		if (T->GetCargoType() == Normal && NWaitingC.GetSize() == 0)
		{
			//in case of promotion or cancellation there are two scenarios
			//a truck to be moved from the normal list is the common between the two scenarios
			//secnario 1: Truck doesn't find sufficent cargos to continue loading thus start moving
			//scenario 2: Truck isn't laoded with any item and no waiting normal cargos thus return truck 
			//again to the ready truck list
			if (T->GetCargoSize() == 0)
			{//handling scenario2
				T->EndLoading(timer);
				ReadyT[T->GetType()].enqueue(T);
				loadflag[Normal] = 0;
				T = nullptr;
			}
			else
			{//handling scenario 1
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
	//Mapping proccess
	if (LoadingN && LoadingN->GetCargoType() == ctype)
		return LoadingN;
	if (LoadingS && LoadingS->GetCargoType() == ctype)
		return LoadingS;
	if (LoadingV && LoadingV->GetCargoType() == ctype)
		return LoadingV;
}

void Company::autopromote()
{
	//function to autopromote normal cargo to vip if time exceeded

	//stops autopromotion if cargo is loading 
	if (loadflag[Normal] == 1)
		return;
	Cargo* c;

	//gets first cargo from list
	c = NWaitingC.getEntry1();
	if (c)
	{
		//check the waiting time with autopromotion limit, then promote if exceeded
		while ((timer.tohours() - c->getprept().tohours()) >= AutoP * 24)
		{
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
			PUI->displaytext("Simulation starts...\n");
		}
		if (!IsRemainingEvents())
		{
			PUI->displaytext("Simulation ends, output file generated.\n");
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
	savefile();
}

void Company::IncrementHour()
{
	timer.hour_incr();
}
void Company::Maintenance()
{
	for (int i = 0; i < 3; i++) //looping through trucks and check whether 
	{							//Truck has finished its maintenance duration or not
		if (!MaintainedT[i].isempty())
		{
			Truck* ptr;
			bool itemfound = MaintainedT[i].peek(ptr);
			while (itemfound && !ptr->InMaintainence(timer))
			{

				MaintainedT[i].dequeue(ptr);
				ptr->EndMaitainence();
				addtoready(ptr);
				itemfound = MaintainedT[i].peek(ptr); //if there is more trucks
															//then continue checking for maintainence end
			}
		}
	}
}
void Company::cargodeliver(Truck*& t, bool& moretrucks, Cargo*& c) //deliver cargo then rearange the truck pos. in IN_Trip queue
{
	while (t->peekTopC(c) && c->getCDT() == timer) //(time to deliver cargo)
	{
		moretrucks = 1;
		t->dequeuetop(c);
		c->setdelivered(1);
		DeliveredC.enqueue(c);
		t->inc_tDC();

	}

	if (moretrucks == 1)	//rearange the position of the truck (either by CDT of top cargo OR return time of truck)
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

void Company::addtomaintain(Truck*& t)//adds the truck to the right maintnance queue
{
	//checks the type of truck and adds it to corresponding maintainence list
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

void Company::addtoready(Truck*& t)//adds the truck to the right Ready queue
{
	//checks the type of truck and adds it to corresponding list
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
void Company::returnTruck(Truck*& t, bool& moretrucks)//Checks if the truck finished the trip then adds it to Maint. or ready list
{
	if (t->getReturn_time() == timer) //truck finished the trip
	{
		moretrucks = 1;
		In_TripT.dequeue(t);
		t->IncementJ();
		if (t->getCurrj() % MaintainenceLimit == 0)	//Adds the truck to suitable list after finishing the trip
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
			cargodeliver(t, moretrucks, c); //deliver cargo then rearange the truck position in IN_Trip
		}
		else
		{
			returnTruck(t, moretrucks);	//Checks if the truck finished the trip then adds it to Maint. or ready list
		}
	}
}

Company::~Company()
{
	delete PUI;
}
