#include "neoenemy.h"
#include "gameobject.h"
#include "cwaypoint.h"
#include <vector.h>
#include <math.h>

CWayPoint::CWayPoint()
{
   initaccelon = false;
   initaccelx = 0;
   initaccely = 0;

   initvelon = false;
   initvelx = 0;
   initvely = 0;

   initradvelon = false;
   initradvel = 0;

   initrotvelon = false;
   initrotvel = 0;

   centerx = 0;
   centery = 0;

   cyclesleft = 0;
   cyclenextwp = 0;
   
   this->hp = 0;
   this->deathfinal = 0;
   this->deathnextwp = 0;
   this->hpchange = false;
   
   this->rotationchange = false;
   return;
}

CWayPoint::~CWayPoint()
{
   return;
}

void CWayPoint::setInitAccel(double x, double y)
{
   this->initaccelon = true;
   this->initaccelx = x;
   this->initaccely = y;
}
   

void CWayPoint::setInitVel(double x, double y)
{
   this->initvelon = true;
   this->initvelx = x;
   this->initvely = y;
   return;
}

void CWayPoint::setInitRadVel(double v)
{
   this->initradvelon = true;
   this->initradvel = v;
   return;
}

void CWayPoint::setInitRotVel(double v)
{
   this->initrotvelon = true;
   this->initrotvel = v;
   return;
}

void CWayPoint::setCenter(double x, double y)
{
   this->centerx = x;
   this->centery = y;
   return;
}

void CWayPoint::setCycleInfo(int cycles, int next, bool nlast)
{
   this->cyclesleft = cycles;
   this->cyclenextwp = next;
   this->last = nlast;
   return;
}

void CWayPoint::setDeathInfo(bool ndeathfinal, int ndeathnextwp)
{
   this->deathfinal = ndeathfinal;
   this->deathnextwp = ndeathnextwp;
   return;
}

void CWayPoint::setHP(int nhp)
{
   this->hp = nhp;
   this->hpchange = true;
}

int CWayPoint::enter(GameObject* ne, GameSpace* gs)
{
   printf("top\n");
   if (this->hpchange == true)
   {
      //printf("BAM\n");
      ne->hp = this->hp;
      //printf("ne->hp: %lf\n", ne->hp);
   }
   
   if(initvelon == true)
   {
      ne->xvel = this->initvelx;
      ne->yvel = this->initvely;
   }
   
   if (initaccelon == true)
   {
      ne->xaccel = this->initaccelx;
      ne->yaccel = this->initaccely;
   }
   
   ne->rcenterx = this->centerx;
   ne->rcentery = this->centerx;
   
   ne->rotaccel = 0;
   
   if (initrotvelon == true)
   {
      ne->rotvel = this->initrotvel;
   }
   
   ne->radaccel = 0;
   
   if (initradvelon == true)
   {
      ne->radvel = this->initradvel;
   }
   
   ne->wcyclesleft = cyclesleft;
   
   
   if (this->onpath == true)
   {
      //printf("1\n");
      //printf("pathnum: %d\n",this->pathnum);
      //printf("size: %d\n", gs->vPathers.size());
      ne->path = gs->vPathers[this->pathnum];
      //printf("2\n");
      ne->npercycle = this->npercycle;
      ne->endx = this->endx;
      ne->endy = this->endy;
      //printf("3\n");
      ne->pathlocation = 0;
   }
   else
   {
      ne->path = NULL;
   }
   
   if (this->rotationchange == true)
   {
      ne->rotation = this->rotation;
      ne->sinetheta = this->sinetheta;
      ne->cosinetheta = this->cosinetheta;
   }
   printf("bottom\n");
   return 0;
}

int CWayPoint::die(GameObject* ne)
{
   if (deathfinal == true)
   {
      ne->dead = true;
      //ne->dissolve = true;
      return 0;
   }
   
   return deathnextwp;
}

int CWayPoint::update(GameObject* ne)
{
   //shooting should go in here...
   ne->wcyclesleft--;
   if (ne->wcyclesleft <= 0)
   {
      if (last == true)
      {
         ne->dead = true;
         ne->dissolve = true;
      }
      return cyclenextwp;
   }
   if (ne->pathlocation > 1.0 && this->onpath == true)
   {
      
      printf("pathnext: %d\n", this->pathnextstate);
      return this->pathnextstate;
   }

   return 0;
}

void CWayPoint::addSpeedPath(int num, double endx, double endy, double speed, int nextstate, Pather* pa)
{
   this->onpath = true;
   this->pathnum = num;
   this->npercycle = speed / pa->getLength();
   this->pathnextstate = nextstate;
   printf("in add nextstate = %d\n", this->pathnextstate);
   this->endx = endx;
   this->endy = endy;
   return;
}

void CWayPoint::addTimedPath(int num, double endx, double endy, int cycles, int nextstate, Pather* pa)
{
   this->onpath = true;
   this->pathnum = num;
   this->npercycle = 1.0 / ((double)cycles);
   this->pathnextstate = nextstate;
   this->endx = endx;
   this->endy = endy;
   return;
}

void CWayPoint::setRotation(double newrotation)
{
   this->rotationchange = true;
   this->rotation = newrotation;
   double piover = (3.14159 / 180)*this->rotation;
   this->sinetheta = sin(piover);
   this->cosinetheta = cos(piover);
   return;
}
