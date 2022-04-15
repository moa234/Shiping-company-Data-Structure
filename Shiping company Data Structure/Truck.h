#pragma once
#include "DEFS.h"
class Truck
{
    int TCap; // Truck Capacity
    int MTime; // Maintenance Time
    int Mjourney; //Number of journies for maintenance
    int Currjourney; //The current counter for journies done by truck
    int speed; // Speed of truck
    int DI; //Delivery interval
    Itemtype type;
public:
    Truck(int Tcap, int speed, int Mjourney, Itemtype type);
    Truck(); 
    int getcap();
    int getspeed();
    void setDI(int DeliveryT); //setter for delivery interval
    void IncementJ(); // increment number of journies

};