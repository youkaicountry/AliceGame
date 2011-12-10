#include "enemybase.h"
#include "bullet.h"
#include "twovector.h"
#include "gamespace.h"
#include "scoreitem.h"
#include "pointitem.h"
#include <math.h>

//all waypoint functions should return an int that tell which
//waypoint should be executed next, relative to the current in
//the waypoint vector contained in the enemy.
//in die, put code for when the enemy dies. to have the enemy
//actually die, set enemy.dead to true, and the enemy will die.
//in enter, put code for when the state is first initiated
//in update, put stuff that happens each update.

Enemy::Enemy()
{
    return;
}

Enemy::~Enemy()
{
    vector<Waypoint*>::iterator k;
    for(k=vwaypoints.begin(); k != vwaypoints.end(); k++)
    {
       delete (*k);
    } 
    return;
}

bool Enemy::isVisible()
{
   return active;
}

bool Enemy::isHittable()
{
   return active;
}

bool Enemy::update(list<Bullet>* bv, Player* p, GameSpace *gs)
{
    activatecycles--;
    if (activatecycles > 0) {return false;}
    active = true;
    double theta, tx, ty, txx;
    
    xvel += xaccel;
    yvel += yaccel;
    x += xvel;
    y += yvel;
    
    //rotational
    rotvel += rotaccel;
    TwoVector v(x-rcenterx, y-rcentery);
    if (rotvel != 0)
    {

       theta = rotvel / v.getLength();
       tx = x - rcenterx; ty = y - rcentery;
       txx = tx;
       tx = tx * cos(theta) - ty * sin(theta);
       ty = txx * sin(theta) + ty * cos(theta);
       x = tx + rcenterx; y = ty + rcentery;
    }
    
    //radial
    radvel += radaccel;
    if (radvel != 0)
    {
        TwoVector vc = v.normalize();
        vc = vc.scale(radvel);
        x += vc.getX(); y += vc.getY();
    }
    
    
    //do waypoint logic
    int a;
    if (hp <= 0)
    {
        a = vwaypoints[currentwaypoint]->die(this,bv, p);
    }
    else
    {
        a = vwaypoints[currentwaypoint]->update(this,bv, p);
    }
    if (a != 0)
    {
        currentwaypoint += a;
        vwaypoints[currentwaypoint]->enter(this,bv, p);
    }


   if (dead && !dissolve)
   {
      gs->thePlayer.setScore((int)(gs->thePlayer.getScore()+this->score));   //increase player score for the kill.
      if (gs->gsran.nextDouble(1.0) < this->scoredropchance)
         gs->lItems.push_back(new ScoreItem(this->x, this->y, gs->gsran.nextDouble(1)-.5, -2, 0.0, .033));
      if (gs->gsran.nextDouble(1.0) < this->powerdropchance)
         gs->lItems.push_back(new PowerItem(this->x, this->y, gs->gsran.nextDouble(1)-.5, -2.1, 0.0, .035));
      gs->fx_explosion(x, y, 16, 3.0, 11);
   }
   return dead;
}

Waypoint::Waypoint()
{
    return;
}

Waypoint::~Waypoint()
{
    return;
}

int Waypoint::enter(Enemy* e,list<Bullet>* bv, Player* p)
{
    return 0;
}

int Waypoint::die(Enemy* e,list<Bullet>* bv, Player* p)
{
    return 0;
}

int Waypoint::update(Enemy* e,list<Bullet>* bv, Player* p)
{
    return 0;
}

//void Waypoint::barrage(Enemy* e, Bullet* b)
//{
//    return;
//}
