#include "Time.h"

Time::Time()
{
	day = hour = 0;
}

Time::Time(int d, int h)
{
	day = d;
	hour = h;
}

void Time::day_incr()
{
	day++;
}

void Time::hour_incr()
{
	if (hour + 1 == 24)
	{
		hour = 0;
		day++;
		return;
	}
	hour++;
}

int Time::GetDay()
{
	return day;
}

int Time::GetHour()
{
	return hour;
}

void Time::SetDay(int num)
{
	day = num;
}

void Time::SetHour(int num)
{
	hour = num;
}

bool Time::operator==(const Time& t2)
{
	return (day==t2.day && hour==t2.hour);
}
