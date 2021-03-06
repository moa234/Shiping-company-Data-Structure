#pragma once
template <typename T>
class PriorityQueueADT
{
public:
	virtual bool peek(T & item) const = 0;
	virtual bool dequeue(T& item) = 0;
	virtual bool enqueue(const T & item,double weight) = 0;
	virtual bool isempty() = 0;
	virtual int GetSize()=0;
};

