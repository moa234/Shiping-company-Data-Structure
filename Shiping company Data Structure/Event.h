#pragma once
#include"Time.h"
#include "Cargo.h"
class Event
{
protected:
	int ID;
	Time time;
public:
	virtual void excute() = 0;
};

