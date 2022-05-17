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

void Time::toTime(int t)
{
	day = t / 24;
	hour = t - (day * 24);
}

bool Time::operator==(const Time& t2) const
{
	return (day == t2.day && hour == t2.hour);
}

bool Time::CompInRangeH(int h1, int h2)
{
	int h = hour;
	return (h >= h1 && h <= h2);
}

Time Time::operator+(int t) const
{
	int h, d;
	d = day;
	h = hour + t;
	if (hour >= 24)
	{
		h = h % 24;
		d += h / 24;
	}
	Time x(d, h);
	return x;
}

bool Time::operator>(const Time& t) const
{
	if (day > t.day)
		return true;
	if (t.day > day)
		return false;
	if (hour > t.hour)
		return true;
	return false; //case hour of second paramenter is greater
}

Time Time::operator+(const Time& t) const
{
	int h, d;
	h = hour + t.hour;
	d = day + t.day;
	if (hour >= 24)
	{
		h = h % 24;
		d += h / 24;
	}
	Time x(d, h);
	return x;
}

