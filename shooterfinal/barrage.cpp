#include "barrage.h"
#include <math.h>
#include "twovector.h"
#include "bullet.h"
#include <vector>
#include <list>
#include <iostream.h>
#include "player.h"

//#define PI = 3.14159
using namespace std;

Barrage::Barrage()
{
    return;
}

Barrage::~Barrage()
{
    return;
}

void Barrage::addBullet(Bullet b, int info)
{
    //cout << "here";
    this->bulletvector.push_back(b);
    this->bulletinfo.push_back(info);
    return;
}

void Barrage::addOutCircle(double circleradius, int n, double angleoffset,
                           double acceleration, double velocity, int sprite,
                           double bulletradius, int info)
{
    double ta, tb, tc, td, angleseperation, twopi;
    twopi = (2 * 3.14159); //let's set our 2pi
    angleseperation = twopi/n;
    
    //this for loop actually creates the circle
    for (double theta = angleoffset;theta < (twopi+angleoffset);theta+=angleseperation)
    {
       TwoVector v(circleradius*cos(theta),circleradius*sin(theta));
       TwoVector vvel = v.normalize(); vvel = vvel.scale(velocity);
       TwoVector vaccel = v.normalize();vaccel = vaccel.scale(acceleration);
       
       bulletvector.push_back(Bullet(v.getX(),v.getY(), vaccel.getX(), vaccel.getY(),
       vvel.getX(), vvel.getY(), bulletradius, 0 ,sprite));
       
       bulletinfo.push_back(info);
    }
    return;
}

void Barrage::addOutCircleRotate(double circleradius, int n, double angleoffset,
                       double acceleration, double velocity, Bullet b, int info)
{
    double ta, tb, tc, td, angleseperation, twopi;
    twopi = (2 * 3.14159); //let's set our 2pi
    angleseperation = twopi/n;
    
    //this for loop actually creates the circle
    for (double theta = angleoffset;theta < (twopi+angleoffset);theta+=angleseperation)
    {
       TwoVector v(circleradius*cos(theta),circleradius*sin(theta));
       TwoVector vvel = v.normalize(); vvel = vvel.scale(velocity);
       TwoVector vaccel = v.normalize();vaccel = vaccel.scale(acceleration);
       
       bulletvector.push_back(Bullet(v.getX()+b.getX(),v.getY()+b.getY(), vaccel.getX()+b.getXAccel(), vaccel.getY()+b.getYAccel(),
       vvel.getX()+b.getXVel(), vvel.getY()+b.getYVel(), b.getArcLengthRotation(), b.getRotationCenterX(), b.getRotationCenterY(), 
       b.getRotationalVelocity(), b.getRotationalAcceleration(), b.getRadialAcceleration(), b.getRadialVelocity(), b.getRadius(), b.getDamage(), b.getSprite()));
       
       bulletinfo.push_back(info);
    }
    return;
}

void Barrage::addCircle(double radius, double x, double y, double xvel, double yvel,
                        double xaccel, double yaccel, int sprite, int info)
{
    return;
}

void Barrage::addLine(double x1, double y1, double x2, double y2, int n, double xvel,
                      double yvel, double xaccel, double yaccel, int sprite, int info)
{
    return;
}
                      
void Barrage::getBarrage(list<Bullet>* bv, double x, double y, double xvel, double yvel, Player* p)
{
    //cout << out
    TwoVector v(0, 0);
    TwoVector vn(0, 0);
    TwoVector vmid(p->getX()- x, p->getY() - y); vmid = vmid.normalize();
    for(int i = 0;i < bulletvector.size();i++)
    {
        Bullet b = bulletvector[i];
        TwoVector vel(b.getXVel()+ xvel, b.getYVel() + yvel);
        double velocityscaler = vel.getLength();
        TwoVector acc(b.getXAccel(), b.getYAccel());
        double accelscaler = acc.getLength();
        //cout << bulletinfo[i];
        if (bulletinfo[i] == 0)
        {
           //b = bulletvector[i];
           //cout << b.getX()+x << " :: " << b.getY()+y;
           b.setX(b.getX()+x);b.setY(b.getY()+y);
           b.setXVel(b.getXVel() + xvel);b.setYVel(b.getYVel() + yvel);
           b.setRotationCenterX(b.getRotationCenterX()+x);
           b.setRotationCenterY(b.getRotationCenterY()+y);
           bv->push_back(b);
        }
        else if (bulletinfo[i] == 1)
        {
           TwoVector veach(p->getX() - (b.getX() + x), p->getY() - (b.getY() + y));
           veach = veach.normalize();
           TwoVector tvel = veach.scale(velocityscaler);
           TwoVector tacc = veach.scale(accelscaler);
           b.setX(b.getX()+x);b.setY(b.getY()+y);
           b.setXVel(tvel.getX());b.setYVel(tvel.getY());
           b.setXAccel(tacc.getX());b.setYAccel(tacc.getY());
           b.setRotationCenterX(b.getRotationCenterX()+x);
           b.setRotationCenterY(b.getRotationCenterY()+y);
           bv->push_back(b);
        }     
    }
    return;
}
