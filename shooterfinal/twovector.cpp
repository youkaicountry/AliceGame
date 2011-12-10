#include "twovector.h"
#include <math.h>

TwoVector::TwoVector()
{
    x = 0;
    y = 0;
    return;
}

TwoVector::TwoVector(double sx, double sy)
{
    x = sx;
    y = sy;
    return;
}

TwoVector::~TwoVector()
{
    return;
}

double TwoVector::getLength()
{
    return sqrt(x*x+y*y);
}

TwoVector TwoVector::normalize()
{
    TwoVector v;
    double length = this->getLength();
    v.setX(this->x / length);
    v.setY(this->y / length);
    return v;
}

TwoVector TwoVector::scale(double scaler)
{
    TwoVector v;
    v.setX(this->x*scaler);
    v.setY(this->y*scaler);
    return v;
} 

double TwoVector::getX()
{
    return x;
}

void TwoVector::setX(double newx)
{
    x = newx;
    return;
}

double TwoVector::getY()
{
    return y;
}

void TwoVector::setY(double newy)
{
    y = newy;
    return;
}
