#pragma once
#include"Time.h"
#include"Company.h"
class Event
{
protected:
	Time time;
	int ID;
public:
	virtual void excute() = 0;
};

