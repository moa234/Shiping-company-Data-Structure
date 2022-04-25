#pragma once
class Time
{
	int day;
	int hour;
public:
	Time();
	Time(int d, int h);
	void day_incr();
	void hour_incr();
	int GetDay();
	int GetHour();
	int tohours();
	void SetDay(int num);
	void SetHour(int num);
	bool operator == (const Time& t2);
	bool CompInRangeH(int h1,int h2);
	
};

