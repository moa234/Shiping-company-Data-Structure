#pragma once
#include "Time.h"
#include "DEFS.h"
#include "Cargo.h"
#include "PriorityQueue.h"
#include <iostream>
class Truck
{
    int TCap;           // Truck Capacity
    Time MTime;          //time That Truck entered maintainence
    int CheckUpDuration;//check up duration for maintenance
    int Currjourney;    //The current counter for journies done by truck
    int speed;          // Speed of truck
    int DI;             //Delivery interval.
    int ID;             //unique id
    Itemtype type;      //type of truck
    PriorityQueue<Cargo*> MovingC;  //list of moving cargos inside the truck
    int TActive;        //truck active time
    int util;           // truck utilization
    int tDC;            //total cargos delivered
    int tl;
    int DDFC = 0;       // delivery distance of furthest cargo
    Time maxCDT;
    bool loaded;
    Time StartLoading; //time where the truck started loading
    Time maxCargoLT;    //max cargo load time
    Time Returntime; //

public:
    Truck(int speed, int Tcap, int CheckUpDuration, Itemtype type,int ID);
    //Truck(); 
    int getcap() const;
    Itemtype GetType();//get type of truck
    void updateDI();
    bool loadC(Cargo*& c);
    int getspeed() const;
    int getid() const;
    //Cargo* PeekTopCargo();
    //dequeue cargo
    void setDI(int DeliveryT); //setter for delivery interval
    void IncementJ(); // increment number of journies
    friend std::ostream& operator <<(std::ostream& f, Truck* C); 
    bool peekTopC(Cargo* c);
    void SetStartLoading(const Time& T);
    Time getStartLoading() const;// returns time when the loading started
    void EndLoading();
    Time getMaxCLT() const;//returns max cargo load time
    bool dequeuetop(Cargo*& c);//dequeue top cargo from truck
    int getCurrj()const;
    int getMj()const; //to be deleted
    void SetMTime(Time T);
    bool InMaintainence(const Time& T); //to check whether truck finished maintaince or not
    void EndMaitainence();
    void inc_tDC();
    void updateCDT(Time& currTime);
    //increment total cargos delivered
    int get_DDFC();
    void updateReturn_time();
    Time getReturn_time()const;
};