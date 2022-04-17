#include "UI.h"

UI::UI(Company* ptr)
{
	//this->mode = mode;
	this->ptr = ptr;
}

int UI::readnumber()
{
	int x;
	cout << "Enter number: ";
	cin >> x;
	cout << endl;
	return x;
}

void UI::displaytext(string c)
{
	cout << c << endl;
}

void UI::readmode()
{
	displaytext("Choose mode of opeartion");
	displaytext("For interactive mode enter 1");
	displaytext("For step-by-step mode enter 2");
	displaytext("For silent mode enter 3");
	mode = (readnumber() == 1) ? interactive : (readnumber() == 2) ? stepBstep : silent;
}

void UI::PrintCargoId(Queue<int>* n, Queue<int>* s, Queue<int>* v)
{
	int szn, szs, szv;
	szn = n->GetSize();
	szs = n->GetSize();
	szv = n->GetSize();
	cout << "[";
	PrintQueue(n);
	cout << "] ";
	cout << "(";
	PrintQueue(s);
	cout << ") ";
	cout << "{";
	PrintQueue(v);
	cout << "} ";
	cout << endl << "--------------------------------" << endl;
}

void UI::PrintQueue(Queue<int>* q)
{
	int sz = q->GetSize();
	for (int i = 0; i < sz; i++)
	{
		int x;
		q->dequeue(x);
		cout << x ;
		if (i != sz-1)
			cout << ",";
	}
}

void UI::PrintMode(Queue<int>* n, Queue<int>* s, Queue<int>* v, ListType L)
{
	cout << n->GetSize() + s->GetSize() + v->GetSize();
	if (L == PCargoWaiting)
	{
		cout << " Waiting Cargos: ";
		PrintCargoId(n, s, v);
	}
	if (L == PCargoDelivered)
	{
		cout << " Delivered Cargos: ";
		PrintCargoId(n, s, v);
	}
}

//void UI::Print()
//{
//	cout << "Current Time(Day:Hour):"<<ptr->GetTime().GetDay() << ":" << ptr->GetTime().GetHour() << endl;
//	Queue<int>* n = ptr->AccessCargoIds(PCargoWaiting,Normal);
//	Queue<int>* s = ptr->AccessCargoIds(PCargoWaiting, Special);
//	Queue<int>* v = ptr->AccessCargoIds(PCargoWaiting, VIP);
//	PrintMode(n, s, v, PCargoWaiting);
//	cout << endl;
//	delete n; delete s; delete v;
//     n = ptr->AccessCargoIds(PCargoDelivered, Normal);
//	 s = ptr->AccessCargoIds(PCargoDelivered, Special);
//	 v = ptr->AccessCargoIds(PCargoDelivered, VIP);
//	PrintMode(n, s, v, PCargoDelivered);
//	delete n; delete s; delete v;
//}

void UI::WaitOption()
{
	if (mode == interactive)
	{
		ptr->printwaiting();
		ptr->printdelivered();
		char x;
		cin.get();
	}
	if (mode == silent)
		return;
}

void UI::save(ofstream& s)
{
	
}

void UI::simulate()
{
	readmode();
	for (int i = 0; i < 720; i++)
	{
		WaitOption();
		ptr->Timer();
	}
}

