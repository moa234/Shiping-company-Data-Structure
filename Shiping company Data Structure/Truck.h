#pragma once
#include "DEFS.h"
#include "Cargo.h"
#include "PriorityQueue.h"
#include <iostream>
class Truck
{
    int TCap;           // Truck Capacity
    int MTime;          // Maintenance Time
    int Mjourney;       //Number of journies for maintenance
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

    bool loaded;
    Time StartLoading; //time where the truck started loading
    Time maxCargoLT;    //max cargo load time

public:
    Truck( int speed, int Tcap, int Mjourney, Itemtype type,int ID);
    Truck(); 
    int getcap() const;
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
    Time getStartLoading() const;// returns time when the loading started
    Time getMaxCLT() const;//returns max cargo load time
    bool dequeuetop(Cargo*& c);//dequeue top cargo from truck
    int getCurrj()const;
    int getMj()const;

};