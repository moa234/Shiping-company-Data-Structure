#pragma once
#include "PriorityQueueADT.h"
#include "Node.h"
template <typename T>
class PriorityQueue: public PriorityQueueADT<T>
{
	Node<T>* head;
public:
	PriorityQueue();
	bool peek(T& item);
};

template<typename T>
PriorityQueue<T>::PriorityQueue()
{
	head = nullptr;
}

template<typename T>
 bool PriorityQueue<T>::peek(T& item)
{
	 if(head==nullptr)
		return false;
	 item = head->getitem();
}
