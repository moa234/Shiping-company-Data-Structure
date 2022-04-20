#pragma once
#include "DEFS.h"
#include <iostream>
class Truck
{
    int TCap; // Truck Capacity
    int MTime; // Maintenance Time
    int Mjourney; //Number of journies for maintenance
    int Currjourney; //The current counter for journies done by truck
    int speed; // Speed of truck
    int DI; //Delivery interval.
    int ID;
    Itemtype type;
public:
    Truck( int speed, int Tcap, int Mjourney, Itemtype type,int ID);
    Truck(); 
    int getcap() const;
    int getspeed() const;
    int getid() const;
    void setDI(int DeliveryT); //setter for delivery interval
    void IncementJ(); // increment number of journies
    friend std::ostream& operator <<(std::ostream& f, const Truck* C); 
};