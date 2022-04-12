#pragma once
#include "PriorityQueueADT.h"
#include "Node.h"
#include <iostream>
using namespace std;
template <typename T>
class PriorityQueue: public PriorityQueueADT<T>
{
	Node<T>* head;
public:
	PriorityQueue();
	virtual bool peek(T& item) const;
	virtual bool dequeue(T& item);
	virtual bool enqueue(const T& item,int weight);
	virtual bool isempty();
	void print();
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
	 item = head->getitem();
	 Node<T>* ptr = head;
	 head = head->getnext();
	 delete ptr;
	 return true;
 }

 template<typename T>
 bool PriorityQueue<T>::enqueue(const T& item, int weight)
 {
	 Node <T>* ptr = new Node<T>(item, weight);
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
	 Node<T>* location = head;
	 while (location->getnext() && location->getnext()->GetWeight() >= weight)
	 {
		 location = location->getnext();
	 }
	 ptr->setnext(location->getnext());
	 location->setnext(ptr);
	 return true;
 }
 template<typename T>
 bool PriorityQueue<T>::isempty()
 {
	 if(head==nullptr)
	 return false;
	 return true;
 }

 template<typename T>
 void PriorityQueue<T>::print()
 {
	 Node<T>* ptr = head;
	 while (ptr)
	 {
		 cout << ptr->getitem() << " ";
		 ptr = ptr->getnext();
	 }
	cout << endl;
 }
