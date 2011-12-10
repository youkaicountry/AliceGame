//#include "bullet.h"
#include "neoenemy.h"
#include "twovector.h"
#include "gamespace.h"
#include "bullet.h"
#include "player.h"
#include "scoreitem.h"
#include "pointitem.h"
#include "cwaypoint.h"

#include <stdio.h>
#include <math.h>
#include <list.h>
#include <vector.h>

//all waypoint functions should return an int that tell which
//waypoint should be executed next, relative to the current in
//the waypoint vector contained in the NeoEnemy.
//in die, put code for when the NeoEnemy dies. to have the NeoEnemy
//actually die, set NeoEnemy.dead to true, and the NeoEnemy will die.
//in enter, put code for when the state is first initiated
//in update, put stuff that happens each update.

NeoEnemy::NeoEnemy(GameSpace* ngs)
{
   dir = 0;
   powerdropchance = 0;
   scoredropchance = 0;
   hp = 1;
   score = 1;
   x = 30;
   y = 30;
   xvel = 0;
   yvel = 0;
   xaccel = 0;
   yaccel = 0;
   rcenterx = 0; 
   rcentery = 0;
   rotaccel = 0;
   rotvel = 0;
   radaccel = 0;
   radvel = 0;
   radius = 5;
   active = false;
   dead = false;
   dissolve = false;
   sprite = 1;
   currentwaypoint = 0;
   activatecycles = 20;
   initial = true;
   this->gs = ngs;
    return;
}

NeoEnemy::~NeoEnemy()
{
    //vector<CWayPoint*>::iterator k;
    //for(k=vwaypoints.begin(); k != vwaypoints.end(); k++)
    //{
    //   delete (*k);
    //}
    return;
}

/*void NeoEnemy::addWayPoint(CWayPoint* wp)
{
   vwaypoints.push_back(wp);
}

bool NeoEnemy::isVisible()
{
   return active;
}

bool NeoEnemy::isHittable()
{
   return active;
}

bool NeoEnemy::update(list<Bullet>* bv, Player* p, GameSpace* gs)
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



    //printf("hp: %lf\n", this->hp);
    //do waypoint logic
    int a;
    if (initial == true)
    {
         vwaypoints[currentwaypoint]->enter(this);
         initial = false;
    }
    //printf("hp: %d\n", this->hp);
    if (hp <= 0)
    {
        a = vwaypoints[currentwaypoint]->die(this);
    }
    else
    {
        a = vwaypoints[currentwaypoint]->update(this);
        //if(vwaypoints[currentwaypoint] == NULL) {system("pause");}
    }
    if (a != 0 && dead == false)
    {
        currentwaypoint += a;
        vwaypoints[currentwaypoint]->enter(this);
    }


   if (dead && !dissolve)
   {
      gs->thePlayer->setScore((int)(gs->thePlayer->getScore()+this->score));   //increase player score for the kill.
      if (gs->gsran.nextDouble(1.0) < this->scoredropchance)
         gs->lItems.push_back(new ScoreItem(this->x, this->y, gs->gsran.nextDouble(1)-.5, -2, 0.0, .033));
      if (gs->gsran.nextDouble(1.0) < this->powerdropchance)
         gs->lItems.push_back(new PowerItem(this->x, this->y, gs->gsran.nextDouble(1)-.5, -2.1, 0.0, .035));
      gs->fx_explosion(x, y, 16, 3.0, 11);
   }
   return dead;
}

void NeoEnemy::copyFrom(NeoEnemy* ne)
{
   dir = ne->dir;
   powerdropchance = ne->powerdropchance;
   scoredropchance = ne->scoredropchance;
   hp = ne->hp;
   score = ne->score;
   x = ne->x;
   y = ne->y;
   xvel = ne->xvel;
   yvel = ne->yvel;
   xaccel = ne->xaccel;
   yaccel = ne->yaccel;
   rcenterx = ne->rcenterx;
   rcentery = ne->rcentery;
   rotaccel = ne->rotaccel;
   wcyclesleft = ne->wcyclesleft;
   rotvel = ne->rotvel;
   radaccel = ne->radaccel;
   radvel = ne->radvel;
   radius = ne->radius;
   active = ne->active;
   dead = ne->dead;
   dissolve = ne->dissolve;
   sprite = ne->sprite;
   currentwaypoint = ne->currentwaypoint;
   activatecycles = ne->activatecycles;
   initial = ne->initial;
   for (int ij = 0;ij < ne->vwaypoints.size();ij++)
   {
      vwaypoints.push_back(ne->vwaypoints[ij]);
   }
   return;
}*/
