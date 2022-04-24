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
public:
    Truck( int speed, int Tcap, int Mjourney, Itemtype type,int ID);
    Truck(); 
    int getcap() const;
    void updateDI();
    bool loadC(Cargo*& c);
    int getspeed() const;
    int getid() const;
    void setDI(int DeliveryT); //setter for delivery interval
    void IncementJ(); // increment number of journies
    friend std::ostream& operator <<(std::ostream& f, Truck* C); 
};