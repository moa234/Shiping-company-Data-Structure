#pragma once
class Cargo
{
	struct time
	{
		int Day;
		int Hour;
		//add day when hour > 24
	};
	struct loading
	{
		int load;
		int unload;
	};
protected:
	loading l_u; //load and unload time in hours
	time prept; //preparation time in (day:hour)
	int deldis; //delivery distance in km
	int cost; //cost of delivering truck


public:
	bool virtual load() = 0;
	bool virtual unload() = 0;
	//bool virtual assign() = 0;
};

