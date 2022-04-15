#pragma once
#include"Time.h"
#include"Company.h"
class Event
{
protected:
	int ID;
	Time time;
public:
	virtual void excute(const Company*& MainPtr) = 0;
};

