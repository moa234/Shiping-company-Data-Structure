#pragma once
#include "PriorityQueueADT.h"
#include "Node.h"
#include <iostream>
#define max 1000
using namespace std;
template <typename T>
class PriorityQueue: public PriorityQueueADT<T>
{
	Node <T>* nodes[max];
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
	virtual bool enqueue(const T& item,int weight);
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
	if (nodes[idx]->GetWeight() > nodes[p]->GetWeight())
	{
		Node<T>* tmp = nodes[idx];
		nodes[idx] = nodes[p];
		nodes[p] = tmp;
		reheapup(p);
	}
}

template<typename T> 
void PriorityQueue<T>::reheapdown(int idx)
{
	int maxpos = idx;
	int l = lch(idx);
	int r = rch(idx);
	if (l<count && nodes[l]->GetWeight() > nodes[idx]->GetWeight())
	{
		maxpos = l;
	}
	if (r<count && nodes[r]->GetWeight() > nodes[maxpos]->GetWeight())
	{
		maxpos = r;
	}
	if (maxpos != idx)
	{
		Node<T>* tmp = nodes[idx];
		nodes[idx] = nodes[maxpos];
		nodes[maxpos] = tmp;
		reheapdown(maxpos);
	}
}

template<typename T>
PriorityQueue<T>::PriorityQueue()
{
	for (int i = 0; i < max; i++)
		nodes[i] = nullptr;
	count=-1;
}

template<typename T>
bool PriorityQueue<T>::peek(T& item) const
{
	 if(count==-1)
		return false;
	 item = nodes[0]->getitem();
	 return true;
}

 template<typename T>
 bool PriorityQueue<T>::dequeue(T& item)
 {
	 if(count==-1)
		return false;
	 item = nodes[0]->getitem();
	 Node<T>* tmp = nodes[0];
	 nodes[0] = nodes[count];
	 nodes[count] = tmp;
	 delete tmp;
	 count--;
	 reheapdown(0);
	 return true;
 }

 template<typename T>
 bool PriorityQueue<T>::enqueue(const T& item, int weight)
 {
	 if (count == max - 1)
		 return false;
	 Node <T>* ptr = new Node<T>(item, weight);
	 nodes[++count] = ptr;
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
		 cout << nodes[i]->getitem() << " ";
	cout << endl;
 }

 template<typename T>
 PriorityQueue<T>::~PriorityQueue()
 {
	 T x;
	 while (dequeue(x))
	 {
	 }
 }
