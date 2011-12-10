#include "star.h"

Star::Star(double sx, double sy, double sz)
{
    x = sx;
    y = sy;
    z = sz;
    return;
}

Star::~Star()
{
    return;
}

double Star::getX()
{
    return x;
}

void Star::setX(double newx)
{
    x = newx;
    return;
}

double Star::getY()
{
    return y;
}

void Star::setY(double newy)
{
    y = newy;
    return;
}

double Star::getZ()
{
    return z;
}

void Star::setZ(double newz)
{
    z = newz;
    return;
}
   
int Star::getSprite()
{
    return sprite;
}

void Star::setSprite(int newsprite)
{
    sprite = newsprite;
}

void Star::update(double relvel)
{
    double a = ((1 - (z/100)) * relvel) + .03;
    y += a;
    return;
}
