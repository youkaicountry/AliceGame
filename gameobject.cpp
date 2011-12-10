//#include "bullet.h"
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
#include "GameObject.h"
#include "twovector.h"
#include "neobullet.h"

//all waypoint functions should return an int that tell which
//waypoint should be executed next, relative to the current in
//the waypoint vector contained in the GameObject.
//in die, put code for when the GameObject dies. to have the GameObject
//actually die, set GameObject.dead to true, and the GameObject will die.
//in enter, put code for when the state is first initiated
//in update, put stuff that happens each update.

GameObject::GameObject()
{
   dir = 0;
   bullet = false;
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
   rotation = 0;
   sinetheta = 0;
   cosinetheta = 0;
   path = NULL;
    return;
}

GameObject::~GameObject()
{
    //vector<CWayPoint*>::iterator k;
    //for(k=vwaypoints.begin(); k != vwaypoints.end(); k++)
    //{
    //   delete (*k);
    //}
    return;
}

void GameObject::addWayPoint(CWayPoint* wp)
{
   vwaypoints.push_back(wp);
}

bool GameObject::isVisible()
{
   return active;
}

bool GameObject::isHittable()
{
   return active;
}

bool GameObject::update(Player* p, GameSpace* gs)
{
    activatecycles--;
    if (activatecycles > 0) {return false;}
    active = true;
    double theta, tx, ty, txx;

    xvel += xaccel;
    yvel += yaccel;
    x += xvel;
    y += yvel;
    
    effvelx = x - oldx;
    effvely = y - oldy;

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
    
    //path
    if (this->path != NULL)
    {
         
       //system("pause");
       TwoVector nextloc;
       TwoVector thisloc;
       this->path->getPoint(0.0, 0.0, this->endx, this->endy, pathlocation+npercycle, &nextloc);
       this->path->getPoint(0, 0, this->endx, this->endy, pathlocation, &thisloc);
       double aax = nextloc.getX() - thisloc.getX();
       double aay = nextloc.getY() - thisloc.getY();
       this->x += aax;
       this->y += aay;
       this->pathlocation += this->npercycle;
    }



    //printf("hp: %lf\n", this->hp);
    //do waypoint logic
    int a;
    if (!bullet) {
    if (initial == true)
    {
         vwaypoints[currentwaypoint]->enter(this, this->gs);
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
        vwaypoints[currentwaypoint]->enter(this,this->gs);
    }
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

void GameObject::copyFrom(GameObject* ne)
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
   damage = ne->damage;
   rotation = ne->rotation;
   for (int ij = 0;ij < ne->vwaypoints.size();ij++)
   {
      vwaypoints.push_back(ne->vwaypoints[ij]);
   }
   return;
}
