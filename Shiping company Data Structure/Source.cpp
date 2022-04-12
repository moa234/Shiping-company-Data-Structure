#include <iostream>
#include "PriorityQueue.h"
#include "Queue.h"
using namespace std;
int main()
{
	PriorityQueue<int> pq;
	for (int i = 0; i < 6; i++)
	{
		int x,w;
		cin >> x>>w;
		pq.enqueue(x,w);
	}
}