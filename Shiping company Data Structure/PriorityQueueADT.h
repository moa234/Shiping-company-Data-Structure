#pragma once
template <typename T>
class PriorityQueueADT
{
public:
	virtual T front() const = 0;
	virtual bool dequeue(T& item) = 0;
	virtual bool enqueue(const T & item) = 0;
	virtual bool isempty() = 0;
};

