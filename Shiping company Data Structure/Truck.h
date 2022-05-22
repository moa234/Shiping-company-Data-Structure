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

    bool loaded;

    Time MTime;          //time That Truck entered maintainence
    Time maxCDT;
    Time StartLoading; //time where the truck started loading
    Time maxCargoLT;    //max cargo load time
    Time Returntime; //

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

    Itemtype GetCargoType();
    Itemtype GetType();//get type of truck

    Time getMaxCLT() const;//returns max cargo load time
    Time getReturn_time()const;
    Time getStartLoading() const;// returns time when the loading started

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

    bool dequeuetop(Cargo*& c);//dequeue top cargo from truck
    bool InMaintainence(const Time& T); //to check whether truck finished maintaince or not    void EndLoading(Time& currTime);
    bool loadC(Cargo*& c, Time& t);
    bool peekTopC(Cargo*& c);

    void EndMaitainence();

    friend std::ostream& operator <<(std::ostream& f, Truck* C);


    //Truck(); 
    //increment total cargos delivered
    //Cargo* PeekTopCargo();
    //dequeue cargo
};