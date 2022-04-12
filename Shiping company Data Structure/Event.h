#pragma once
class Event
{
protected:
	int time;
public:
	virtual void excute() = 0;
};

