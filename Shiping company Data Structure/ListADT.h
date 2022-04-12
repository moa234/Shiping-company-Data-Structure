#pragma once
template <typename T>
class ListADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual int getLength() const = 0;
	virtual bool insert(int newPosition, const T& entry) = 0;
	virtual bool remove(int position) = 0;
	virtual void clear() = 0;
	virtual T getEntry(int position) = 0;
	virtual T repalce(int position, const T& entry) = 0;

};