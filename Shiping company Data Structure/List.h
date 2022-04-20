#pragma once
#include "ListADT.h"
#include "Node.h"

template <class T>
class List : public ListADT<T>
{
protected:
	Node<T>* headptr = nullptr;
	int count = 0;
	Node<T>* getNode(int position) const
	{
		Node<T>* currptr = headptr;
		for (int i = 1; i < position; i++)
		{
			currptr = currptr->getnext();
		}
		return currptr;
	}

public:
	bool isEmpty() const
	{
		if (headptr == nullptr)
		{
			return true;
		}
		return false;
	}
	int getLength() const
	{
		return count;
	}
	bool insert(int newPosition, const T& entry)
	{
		bool abletoinsert = (newPosition >= 1) && (newPosition <= count + 1);
		if (abletoinsert)
		{
			Node<T>* newNode = new Node<T>(entry);
			if (newPosition == 1)
			{
				newNode->setnext(headptr);
				headptr = newNode;
			}
			else
			{
				Node<T>* prevNode = getNode(newPosition - 1);
				newNode->setnext(prevNode->getnext());
				prevNode->setnext(newNode);
			}
			count++;
		}
		return abletoinsert;
	}
	bool insertend(const T& entry)
	{
		return insert(count, entry);
	}
	bool remove(int position)
	{
		bool abletoremove = (position >= 1) && (position <= count);
		if (abletoremove)
		{
			Node<T>* currptr = nullptr;
			if (position == 1)
			{
				currptr = headptr;
				headptr = headptr->getnext();
			}
			else
			{
				Node<T>* prevNode = getNode(position - 1);
				currptr = prevNode->getnext();
				prevNode->setnext(currptr->getnext());
			}
			delete currptr;
			currptr = nullptr;
			count--;
		}
		return abletoremove;
	}
	void clear()
	{
		while (isEmpty())
		{
			remove(1);
		}
	}
	T getEntry(int position)
	{
		bool exist = (position >= 1) && (position <= count);
		if (exist)
		{
			Node<T>* currptr = getNode(position);
			return currptr->getitem();
		}
	}
	T repalce(int position, const T& entry)
	{
		T replaced = getEntry(position);
		remove(position);
		insert(position, entry);
		return replaced;
	}
	//void Print()
	//{
	//	Node<T>* ptr = headptr;
	//	while (ptr)
	//	{
	//		cout << ptr->getitem();
	//		ptr = ptr->getnext();
	//		if (ptr)
	//			cout << ",";
	//	}
	//}
	~List()
	{
		clear();
	}
};