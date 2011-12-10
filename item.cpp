#include "item.h"
#include "player.h"

Item::Item()
{
    return;
}

Item::~Item()
{
    return;
}

double Item::getX()
{
    return x;
}

void Item::setX(double newx)
{
    x = newx;
    return;
}

double Item::getY()
{
    return y;
}

void Item::setY(double newy)
{
    y = newy;
    return;
}

double Item::getXVel()
{
    return xvel;
}

void Item::setXVel(double newxvel)
{
    xvel = newxvel;
    return;
}

double Item::getYVel()
{
    return yvel;
}

void Item::setYVel(double newyvel)
{
    yvel = newyvel;
    return;
}

double Item::getXAccel()
{
    return xaccel;
}

void Item::setXAccel(double newxaccel)
{
    xaccel = newxaccel;
    return;
}

double Item::getYAccel()
{
    return yaccel;
}

void Item::setYAccel(double newyaccel)
{
    yaccel = newyaccel;
    return;
}

double Item::getRadius()
{
   return radius;
}

void Item::setRadius(double newradius)
{
   radius = newradius;
   return;
}
   

int Item::getSprite()
{
    return sprite;
}

void Item::setSprite(int newsprite)
{
    sprite = newsprite;
}

void Item::onPickup(Player* pl)
{
    return;
}

void Item::update()
{
    xvel += xaccel;
    yvel += yaccel;
    if (yvel > 3) {yvel = 3;}
    x += xvel;
    y += yvel;
    return;
}


