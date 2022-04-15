#include <iostream>
#include "PriorityQueue.h"
#include "Queue.h"
#include "Truck.h"
#include "Company.h"
#include <fstream>
using namespace std;
int main()
{

	Queue<int*> pq;
	Company c;
	ifstream fin("test.txt") ;
	c.ReadFile(fin);
	//for (int i = 0; i < 6; i++)
	//{
	//	int x,w;
	//	cin >> x;
	//	int* p = new int(x);
	//	pq.enqueue(p);
	//}
	//for (int i = 0; i < 6; i++)
	//{
	//	int* p;
	//	pq.dequeue(p);
	//	delete p;
	//}
	//pq.print();
}