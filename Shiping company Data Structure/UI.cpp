#include "UI.h"

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
	cout << "Choose mode of opeartion" << endl;
	cout << "For interactive mode enter 1" << endl;
	cout << "For interactive mode enter 2" << endl;
	cout << "For interactive mode enter 3" << endl;
	displaytext("Choose mode of opeartion");
	displaytext("For interactive mode enter 1");
	displaytext("For step-by-step mode enter 2");
	displaytext("For silent mode enter 3");
	mode = (readnumber() == 0)? interactive: (readnumber() == 1) ?stepBstep:silent ;
}
