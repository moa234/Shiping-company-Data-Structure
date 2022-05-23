#pragma once
#include "Time.h"
#include "DEFS.h"
#include "Cargo.h"
#include "PriorityQueue.h"
#include <iostream>
class Truck
{
    int CheckUpDuration;//check up duration for maintenance
    int Currjourney;    //The current counter for journies done by truck
    int DI;             //Delivery interval.
    int DDFC = 0;       // delivery distance of furthest cargo
    int ID;             //unique id
    int speed;          // Speed of truck
    int TActive;        //truck active time
    int TCap;           // Truck Capacity
    int tDC;            //total cargos delivered
    int tl;
    int util;           // truck utilization

    Itemtype Ctype;     //type of cargo truck is carrying
    Itemtype type;      //type of truck

    bool loading;

    Time MTime;          //time That Truck entered maintainence
    Time maxCDT;
    Time StartLoading; //time where the truck started loading
    Time maxCargoLT;    //max cargo load time
    Time Returntime; //
    Time PreviousLoadC; //loadtime that previous cargo finishes at
    PriorityQueue<Cargo*> MovingC;  //list of moving cargos inside the truck

public:
    Truck(int speed, int Tcap, int CheckUpDuration, Itemtype type,int ID);
    
    //Getters
    int getcap() const;
    int getCurrj()const;
    int get_DDFC();
    int getid() const;
    int getMj()const; //to be deleted
    int getspeed() const;

    Itemtype GetCargoType(); //get type of cargo
    Itemtype GetType();//get type of truck

    Time getMaxCLT() const;//returns max cargo load time
    Time getReturn_time()const;
    Time getStartLoading() const;// returns time when the loading started
    void SetPrevLoad(Time T);
    Time GetPrevLoad();

    //Setters
    void SetCargoType(Itemtype type);
    void setDI(int DeliveryT); //setter for delivery interval
    void SetMTime(Time T);
    void SetStartLoading(const Time& T, Itemtype ctype);

    //Updaters

    void inc_tDC();
    void IncementJ(); // increment number of journies
    void updateCDT(Time& currTime);
    void updateDI();
    void updateReturn_time();
    int GetCargoSize();
    bool dequeuetop(Cargo*& c);//dequeue top cargo from truck
    bool InMaintainence(const Time& T); //to check whether truck finished maintaince or not    void EndLoading(Time& currTime);
    bool loadC(Cargo*& c, Time& t);
    bool peekTopC(Cargo*& c);
    bool FullCapacity();
    void EndMaitainence();
    void EndLoading(Time& currTime);

    friend std::ostream& operator <<(std::ostream& f, Truck* C);


};