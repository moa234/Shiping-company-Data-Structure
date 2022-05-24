#include "UI.h"

UI::UI()
{
	mode={};
}

int UI::readnumber()
{
	int x;
	cout << "Enter number: ";
	cin >> x;
	cout << endl;
	return x;
}

string UI::readfilename()
{
	string name;
	cout << "Enter file name: ";
	cin >> name;
	name += ".txt";
	cout << endl;
	return name;
}

void UI::displayTime(Time t)
{
	cout << "Current Time (Day:Hour):" << t.GetDay() << ":" << t.GetHour() << endl;
}

void UI::displayline()
{
	cout << endl<<"----------------------------------" << endl;
}

void UI::displaytext(string c)
{
	cout << c ;
}

void UI::displayNum(int n)
{
	cout << n;
}

void UI::readmode()
{
	displaytext("Choose mode of opeartion");
	cout << endl;
	displaytext("For interactive mode enter 1");
	cout << endl;
	displaytext("For step-by-step mode enter 2");
	cout << endl;
	displaytext("For silent mode enter 3");
	cout << endl;
	int num = readnumber();
	mode = ( num== 1) ? interactive : (num == 2) ? stepBstep : silent;
}

void UI::PrintBracketStart(Itemtype t)
{
	if (t == Normal)
		cout << "[";
	if (t == Special)
		cout << "(";
	if (t == VIP)
		cout << "{";

}

void UI::PrintBracketEnd(Itemtype t)
{
	if (t == Normal)
		cout << "]";
	if (t == Special)
		cout << ")";
	if (t == VIP)
		cout << "}";
}

void UI::PrintQC(Queue<Cargo*>& q, Itemtype t)
{
	PrintBracketStart(t);
	q.print();
	PrintBracketEnd(t);
}

void UI::PrintDQC(Queue<Cargo*>& q)
{
	q.print();

}

void UI::PrintLC(CargoList& q, Itemtype t)
{
	PrintBracketStart(t);
	q.Print();
	PrintBracketEnd(t);
}

void UI::PrintPQC(PriorityQueue<Cargo*>& q, Itemtype t)
{
	PrintBracketStart(t);
	q.print();
	PrintBracketEnd(t);
}


void UI::PrintEQT(Queue<Truck*>& q, Itemtype t)
{
	PrintBracketStart(t);
	q.print();
	PrintBracketEnd(t);
}

void UI::PrintPQT(PriorityQueue<Truck*>& q)
{
	q.print();
}

void UI::PrintT(Truck* T)
{
	if (T == nullptr)
		return;
	cout << T;
}

Modetype UI::getmode()
{
	return mode;
}




void UI::WaitOption()
{
	if (mode == interactive)
	{
		cin.get();
	}
	if (mode == stepBstep)
	{
		Sleep(1000);
	}
}


