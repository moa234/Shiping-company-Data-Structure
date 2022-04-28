#pragma once
class Time //This class is to help in dealing with Day and hour format
{
	int day;
	int hour;
public:
	Time(); 
	Time(int d, int h); 
	void day_incr(); //increment day 
	void hour_incr(); //increment hour
	int GetDay(); //getter for day
	int GetHour(); //getter for hour
	int tohours(); //convert day and hour to hours only
	void SetDay(int num);
	void SetHour(int num);
	bool operator == (const Time& t2); //overloading comparison operator == 
	bool CompInRangeH(int h1,int h2); //compares current hour whether it is in range of two other hours
	
};

