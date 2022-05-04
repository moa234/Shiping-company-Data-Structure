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

int Time::tohours()
{
	return day * 24 + hour;
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
	return (day == t2.day && hour == t2.hour);
}

bool Time::CompInRangeH(int h1, int h2)
{
	int h = hour;
	return (h >= h1 && h <= h2);
}

Time Time::operator+(int t)
{
	int h, d;
	d = day + t;
	if (d > 24)
	{
		hour++;
		day -= 24;
	}
	h = hour;
	Time x(d, h);
	return x;
}

Time Time::operator+(Time t)
{
	int h, d;
	d = day + t.day;
	h = hour + t.hour;
	if (d > 24)
	{
		h++;
		day -= 24;
	}

	Time x(d, h);
	return x;
}

