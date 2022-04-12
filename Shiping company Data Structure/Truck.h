#pragma once
class Truck
{
protected:
    int TCap; // Truck Capacity
    int MTime; // Maintenance Time
    int Mjourney; //Number of journies for maintenance
    int Currjourney; //The current counter for journies done by truck
    int speed; // Speed of truck
    int DI; //Delivery interval
public:
    Truck(int tc);
    int getcap();
    int getspeed();
    void setDI(int DeliveryT); //setter for delivery interval
    
};