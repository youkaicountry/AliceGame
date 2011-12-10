#ifndef _ITEM__
#define _ITEM__

#include "player.h"

class Item
{
    public:
       Item();
       virtual ~Item();
       
       virtual void update();  //the physics simulation for the bullet
       virtual void onPickup(Player* pl);  //what happens if this is picked up
       
       virtual double getX();
       virtual void setX(double newx);
       
       virtual double getY();
       virtual void setY(double newy);
       
       virtual double getXVel();
       virtual void setXVel(double newxvel);
       
       virtual double getYVel();
       virtual void setYVel(double newyvel);
       
       virtual double getXAccel();
       virtual void setXAccel(double newxaccel);
       
       virtual double getYAccel();
       virtual void setYAccel(double newyaccel);
       
       virtual double getRadius();
       virtual void setRadius(double newradius);
       
       virtual int getSprite();
       virtual void setSprite(int newsprite);
       
    protected:
        double x, y;
        double xvel, yvel;
        double xaccel, yaccel;
        double radius;
        int sprite;
        
        
};

#endif
