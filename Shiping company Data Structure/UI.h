#pragma once
#include "DEFS.h"
#include <iostream>
#include <string>

using namespace std;

class UI
{
	Modetype mode;
public:
	int readnumber();
	void displaytext(string c);
	void readmode();
};

