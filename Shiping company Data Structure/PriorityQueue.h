#pragma once
#include "PriorityQueueADT.h"
#include "PQNode.h"
#include <iostream>
#define MaxSz 15000
using namespace std;
template <typename T>
class PriorityQueue: public PriorityQueueADT<T>
{
	PQNode <T>* PQNodes[MaxSz];
	int count;
	int parent(int idx);
	int lch(int idx);
	int rch(int idx);
	void reheapup(int idx);
	void reheapdown(int idx);
		
public:
	PriorityQueue();
	virtual bool peek(T& item) const;
	virtual bool dequeue(T& item);
	virtual bool enqueue(const T& item,double weight);
	virtual bool isempty();
	virtual int GetSize();
	void print();
	~PriorityQueue();
};

template<typename T>
int PriorityQueue<T>::parent(int idx)
{
	return (idx-1)/2;
}

template<typename T>
int PriorityQueue<T>::lch(int idx)
{
	return 2*idx+1;
}

template<typename T>
inline int PriorityQueue<T>::rch(int idx)
{
	return 2*idx+2;
}

template<typename T>
void PriorityQueue<T>::reheapup(int idx)
{
	if (idx == 0)
		return;
	int p = parent(idx);
	if (PQNodes[idx]->GetWeight() > PQNodes[p]->GetWeight())
	{
		PQNode<T>* tmp = PQNodes[idx];
		PQNodes[idx] = PQNodes[p];
		PQNodes[p] = tmp;
		reheapup(p);
	}
}

template<typename T> 
void PriorityQueue<T>::reheapdown(int idx)
{
	int maxpos = idx;
	int l = lch(idx);
	int r = rch(idx);
	
	if (l<=count && PQNodes[l]->GetWeight() > PQNodes[idx]->GetWeight())
	{
		maxpos = l;
	}
	
	if (r<=count && PQNodes[r]->GetWeight() > PQNodes[maxpos]->GetWeight())
	{
		maxpos = r;
	}
		
	if (maxpos != idx)
	{
		PQNode<T>* tmp = PQNodes[idx];
		PQNodes[idx] = PQNodes[maxpos];
		PQNodes[maxpos] = tmp;
		reheapdown(maxpos);
	}
}

template<typename T>
PriorityQueue<T>::PriorityQueue()
{
	for (int i = 0; i < MaxSz; i++)
		PQNodes[i] = nullptr;
	count=-1;
}

template<typename T>
bool PriorityQueue<T>::peek(T& item) const
{
	 if(count==-1)
		return false;
	 item = PQNodes[0]->getitem();
	 return true;
}

 template<typename T>
 bool PriorityQueue<T>::dequeue(T& item)
 {
	 if(count==-1)
		return false;
	 item = PQNodes[0]->getitem();
	 PQNode<T>* tmp = PQNodes[0];
	 PQNodes[0] = PQNodes[count];
	 PQNodes[count] = tmp;
	 delete tmp;
	 reheapdown(0);
	 count--;
	 return true;
 }

 template<typename T>
 bool PriorityQueue<T>::enqueue(const T& item, double weight)
 {
	 if (count == MaxSz - 1)
		 return false;
	 PQNode <T>* ptr = new PQNode<T>(item, weight+(double)(MaxSz-count) / (100 * MaxSz));
	 PQNodes[++count] = ptr;
	 reheapup(count);
	 return true;
 }
 template<typename T>
 bool PriorityQueue<T>::isempty()
 {
	 if(count==-1)
	 return true;
	 return false;
 }

 template<typename T>
 int PriorityQueue<T>::GetSize()
 {
	 return count+1;
 }

 template<typename T>
 void PriorityQueue<T>::print()
 {
	 for (int i = 0; i <= count; i++)
	 {
		 cout << PQNodes[0]->getitem();
		 if (i != count)
			 cout << ",";
		 PQNodes[0]->SetWeight(PQNodes[0]->GetWeight()-1e6);
		 reheapdown(0);
	 }
	 for (int i = 0; i <= count; i++)
	 {
		 PQNodes[i]->SetWeight(PQNodes[i]->GetWeight()+1e6);
	 }
	 for (int i = 0; i <= count; i++)
	 {
		 reheapup(i);
	 }
 }
 template<typename T>
 PriorityQueue<T>::~PriorityQueue()
 {
	 T x;
	 while (dequeue(x))
	 {
	 }
 }
