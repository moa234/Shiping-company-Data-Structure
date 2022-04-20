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

	Cargo* remRet(int id)
	{
		int pos = this->getPos(id);
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
			return currptr->getitem();
		}
		return nullptr;
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
	Cargo* remRet1(int pos)
	{
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
			return currptr->getitem();
		}
		return nullptr;
	}
};

