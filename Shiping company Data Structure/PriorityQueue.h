#pragma once
#include "PriorityQueueADT.h"
#include "Node.h"
template <typename T>
class PriorityQueue: public PriorityQueueADT<T>
{
	Node<T>* head;
	PriorityQueue();
};

