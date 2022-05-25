#pragma once
#include "List.h"
class CargoList : public List<Cargo*>
{
	int getPos(int id)
	{
		Node<Cargo*>* currptr = headptr;
		if (currptr != nullptr)
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
	int GetSize()
	{
		return count;
	}
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
			count--;
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
	Cargo* getEntry1()
	{
		if (count >= 1)
		{
			return headptr->getitem();
		}
		return nullptr;
	}
	Cargo* remRet1()
	{
		if (count >= 1)
		{
			Node<Cargo*>* currptr = nullptr;
			currptr = headptr;
			headptr = headptr->getnext();
			count--;
			return currptr->getitem();
		}
		return nullptr;
	}
};

