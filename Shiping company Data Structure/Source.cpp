#include <iostream>
#include "PriorityQueue.h"
#include "Queue.h"
#include "Truck.h"
#include "Company.h"
#include <fstream>
using namespace std;
int main()
{

	//Queue<Truck*> pq[5];
	Company c;
	ifstream fin("test.txt") ;
	c.ReadFile(fin);
	/*for (int i = 0; i < 6; i++)
	{
		int x,w;
		cin >> x>>w;
		pq[0].enqueue(x, w);
	}
	pq[0].print();*/
}