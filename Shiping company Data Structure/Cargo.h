#pragma once
class Cargo
{
	struct time
	{
		int Day;
		int Hour;
		//add day when hour > 24
	};
protected:
	int loadt;	 //load time in hours  
	int unloadt; //unload time in hours
	time prept;	 //preparation time in (day:hour)
	int deldis;	 //delivery distance in km
	int cost;	 //cost of delivering truck


public:
	void setprept(time pt);
	void setloadt(int lt);
	void setunloadt(int ult);
	void setdeldis(int ds);
	void setcost(int cost);
	time getprept();
	int getload();
	int getunload();
	int getdeldis();
	int getcost();

	//virtual bool load() = 0;
	//virtual bool unload() = 0;
	//bool virtual assign() = 0;
};

