#pragma once
#include "List.h"
class CargoList : public List<Cargo*>
{
	int getPos(int id)
	{
		Node<Cargo*>* currptr = headptr;
		if (currptr)
		{
			for (int i = 0; i < count; i++)
			{
				if (currptr->getitem()->getid() == id)
				{
					return i + 1;
				}
				else
				{
					currptr = currptr->getnext();
				}
			}
		}
		return -1;

	}
public:

	bool remove(int position)
	{
		int pos = this->getPos(position);
		bool abletoremove = (pos >= 1) && (pos <= count);
		if (abletoremove)
		{
			Node<Cargo*>* currptr = nullptr;
			if (pos == 1)
			{
				currptr = headptr;
				headptr = headptr->getnext();
			}
			else
			{
				Node<Cargo*>* prevNode = getNode(pos - 1);
				currptr = prevNode->getnext();
				prevNode->setnext(currptr->getnext());
			}
			delete currptr;
			currptr = nullptr;
			count--;
		}
		return abletoremove;
	}
	Cargo* getEntry(int id)
	{
		int position = this->getPos(id);
		bool exist = (position >= 1) && (position <= count);
		if (exist)
		{
			Node<Cargo*>* currptr = getNode(position);
			return currptr->getitem();
		}
		return nullptr;
	}
};

