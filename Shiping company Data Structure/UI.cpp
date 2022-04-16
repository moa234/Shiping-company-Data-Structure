#include "UI.h"

int UI::readnumber()
{
	int x;
	cout << "Enter number: ";
	cin >> x;
	cout << endl;
	return x;
}

void UI::readmode()
{
	cout << "Choose mode of opeartion" << endl;
	cout << "For interactive mode enter 1" << endl;
	cout << "For interactive mode enter 2" << endl;
	cout << "For interactive mode enter 3" << endl;
}
