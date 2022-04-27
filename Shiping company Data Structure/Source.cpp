#include <iostream>
#include "PriorityQueue.h"
#include "Queue.h"
#include "UI.h"
#include "Company.h"
#include <fstream>
using namespace std;

int main()
{
	Company c;
	c.LoadFile();
	c.simulate();
	return 0;
}