#pragma once
#pragma once
#include "QueueADT.h"
#include "Node.h"
#include <iostream>
using namespace std;
template <typename T>
class Queue : public QueueADT<T>
{
	Node<T>* head;
	Node<T>* rear;
public:
	Queue();
	virtual bool peek(T& item) const;
	virtual bool dequeue(T& item);
	virtual bool enqueue(const T& item);
	virtual bool isempty();
	void print();
	virtual ~Queue();
};

template<typename T>
Queue<T>::Queue()
{
	head = nullptr;
	rear = nullptr;
}

template<typename T>
bool Queue<T>::peek(T& item) const
{
	if (head == nullptr)
		return false;
	item = head->getitem();
	return true;
}

template<typename T>
bool Queue<T>::dequeue(T& item)
{
	if (head == nullptr)
		return false;
	if (head == rear)
		rear = nullptr;
	item = head->getitem();
	Node<T>* ptr = head;
	head = head->getnext();
	delete ptr;
	return true;
}

template<typename T>
bool Queue<T>::enqueue(const T& item)
{
	Node <T>* ptr = new Node<T>(item);
	ptr->setnext(nullptr);
	if (!head)
	{
		head = ptr;
		rear = ptr;
		return true;
	}
	rear->setnext(ptr);
	rear = ptr;
	return true;
}
template<typename T>
bool Queue<T>::isempty()
{
	if (head == nullptr)
		return false;
	return true;
}

template<typename T>
void Queue<T>::print()
{
	Node<T>* ptr = head;
	while (ptr)
	{
		cout << ptr->getitem() << " ";
		ptr = ptr->getnext();
	}
	cout << endl;
}

template<typename T>
Queue<T>::~Queue()
{
	int x;
	while (dequeue(x))
	{
	}
}


