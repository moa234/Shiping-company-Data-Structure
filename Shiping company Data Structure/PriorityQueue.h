#pragma once
#include "PriorityQueueADT.h"
#include "PqNode.h"
#include "Node.h"
template <typename T>
class PriorityQueue: public PriorityQueueADT<T>
{
	PqNode<T>* head;
public:
	PriorityQueue();
	virtual bool peek(T& item) const;
	virtual bool dequeue(T& item);
	virtual bool enqueue(const T& item,int weight);
	virtual bool isempty();
};

template<typename T>
PriorityQueue<T>::PriorityQueue()
{
	head = nullptr;
}

template<typename T>
bool PriorityQueue<T>::peek(T& item) const
{
	 if(head==nullptr)
		return false;
	 item = head->getitem();
	 return true;
}

 template<typename T>
 bool PriorityQueue<T>::dequeue(T& item)
 {
	 if(head==nullptr)
		return false;
	 item = head->data;
	 PqNode<T>* ptr = head;
	 head = head->getnext();
	 delete ptr;
	 return true;
 }

 template<typename T>
 bool PriorityQueue<T>::enqueue(const T& item, int weight)
 {
	 PqNode <T>* ptr = new PqNode<T>(item, weight);
	 ptr->setnext(nullptr);
	 if (!head)
	 {
		 head = ptr;
		 return true;
	 }
	 if (head->GetWeight() < weight)
	 {
		 ptr->setnext(head);
		 head = ptr;
		 return true;
	 }
	 PqNode<T>* location = head;
	 while (location->getnext() && location->getnext()->GetWeight() >= weight)
	 {
		 location = location->getnext();
	 }
	 ptr->setnext(location->getnext());
	 location->setnext(ptr);
 }
 template<typename T>
 bool PriorityQueue<T>::isempty()
 {
	 if(head==nullptr)
	 return false;
	 return true;
 }
