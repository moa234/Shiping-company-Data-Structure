#pragma once
#include"Time.h"
class Event
{
protected:
	Time time;
public:
	virtual void excute() = 0;
};

