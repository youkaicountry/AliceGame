#include "twovector.h"
#include <math.h>
#include "bullet.h"

Bullet::Bullet(double sx, double sy, double sxaccel, double syaccel, 
               double sxvel, double syvel, double sradius, double sdamage, int ssprite)
{
    x = sx;
    y = sy;
    xaccel = sxaccel;
    yaccel = syaccel;
    xvel = sxvel;
    yvel = syvel;
    radius = sradius;
    sprite = ssprite;
    arclengthrotation = true;
    rcenterx = 0;
    rcentery = 0;
    rvel = 0;
    raccel = 0;
    radialaccel = 0;
    radialvel = 0;
    damage = sdamage;
    return;
}

Bullet::Bullet(double sx, double sy, double sxaccel, double syaccel,
               double sxvel, double syvel, bool sarclengthrotation,
               double srcenterx, double srcentery, double srvel, double sraccel,
               double sradialaccel, double sradialvel, double sradius, double sdamage, int ssprite)
{
    x = sx;
    y = sy;
    xaccel = sxaccel;
    yaccel = syaccel;
    xvel = sxvel;
    yvel = syvel;
    radius = sradius;
    sprite = ssprite;
    arclengthrotation = sarclengthrotation;
    rcenterx = srcenterx;
    rcentery = srcentery;
    rvel = srvel;
    raccel = sraccel;
    radialaccel = sradialaccel;
    radialvel = sradialvel;
    damage = sdamage;
    return;
}

Bullet::~Bullet()
{
    return;
}

double Bullet::getX()
{
    return x;
}

void Bullet::setX(double newx)
{
    x = newx;
    return;
}

double Bullet::getY()
{
    return y;
}

void Bullet::setY(double newy)
{
    y = newy;
    return;
}

double Bullet::getXVel()
{
    return xvel;
}

void Bullet::setXVel(double newxvel)
{
    xvel = newxvel;
    return;
}

double Bullet::getYVel()
{
    return yvel;
}

void Bullet::setYVel(double newyvel)
{
    yvel = newyvel;
    return;
}

double Bullet::getXAccel()
{
    return xaccel;
}

void Bullet::setXAccel(double newxaccel)
{
    xaccel = newxaccel;
    return;
}

double Bullet::getYAccel()
{
    return yaccel;
}

void Bullet::setYAccel(double newyaccel)
{
    yaccel = newyaccel;
    return;
}

double Bullet::getRotationCenterX()
{
    return rcenterx;
}

void Bullet::setRotationCenterX(double newrcenterx)
{
    rcenterx = newrcenterx;
    return;
}

double Bullet::getRotationCenterY()
{
    return rcentery;
}

void Bullet::setRotationCenterY(double newrcentery)
{
    rcentery = newrcentery;
    return;
}

bool Bullet::getArcLengthRotation()
{
    return arclengthrotation;
}

void Bullet::setArcLengthRotation(bool newarclengthrotation)
{
    arclengthrotation = newarclengthrotation;
    return;
}

double Bullet::getRotationalAcceleration()
{
    return raccel;
}

void Bullet::setRotationalAcceleration(double newraccel)
{
    raccel = newraccel;
    return;
}

double Bullet::getRotationalVelocity()
{
    return rvel;
}

void Bullet::setRotationalVelocity(double newrvel)
{
    rvel = newrvel;
    return;
}

double Bullet::getRadialAcceleration()
{
    return radialaccel;
}

void Bullet::setRadialAcceleration(double newradaccel)
{
    radialaccel = newradaccel;
    return;
}

double Bullet::getRadialVelocity()
{
    return radialvel;
}

void Bullet::setRadialVelocity(double newradvel)
{
    radialvel = newradvel;
    return;
}

double Bullet::getRadius()
{
    return radius;
}

void Bullet::setRadius(double newradius)
{
    radius = newradius;
    return;
}

int Bullet::getSprite()
{
    return sprite;
}

void Bullet::setSprite(int newsprite)
{
    sprite = newsprite;
    return;
}

double Bullet::getDamage()
{
    return damage;
}

void Bullet::setDamage(double newdamage)
{
    damage = newdamage;
}

void Bullet::update()
{
    double theta, tx, ty, txx;
    
    xvel += xaccel;
    yvel += yaccel;
    oldx = x;oldy = y;
    x += xvel;
    y += yvel;
    
    
    //rotational
    rvel += raccel;
    TwoVector v(x-rcenterx, y-rcentery);
    if (rvel != 0)
    {
       if (arclengthrotation)
       {
           theta = rvel / v.getLength();
       }
       else
       {
           theta = rvel;
       }
       tx = x - rcenterx; ty = y - rcentery;
       txx = tx;
       tx = tx * cos(theta) - ty * sin(theta);
       ty = txx * sin(theta) + ty * cos(theta);
       x = tx + rcenterx; y = ty + rcentery;
    }
    
    //radial
    radialvel += radialaccel;
    if (radialvel != 0)
    {
        TwoVector vc = v.normalize();
        vc = vc.scale(radialvel);
        x += vc.getX(); y += vc.getY();
    }
    
    effvelx = x - oldx;
    effvely = y - oldy;
    
    return;
}
