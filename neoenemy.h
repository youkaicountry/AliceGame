#ifndef _NEOENEMY__
#define _NEOENEMY__

class NeoEnemy;
#include "cwaypoint.h"
#include <list.h>
#include <vector.h>
//#include "barrage.h"
#include "bullet.h"
#include "player.h"
#include "gamespace.h"
#include "gameobject.h"

class NeoEnemy : public GameObject
{
   public: //writing accessors sucks and I just don't feel like doing it again
   NeoEnemy(GameSpace* ngs);
   virtual ~NeoEnemy();
   //void addWayPoint(CWayPoint* wp);
   //void copyFrom(NeoEnemy* ne);
   
   //bool isVisible();
   //bool isHittable();

   //vector<CWayPoint*> vwaypoints;
   //vector<Barrage*> vbarrages;
   //double dir;
   //double powerdropchance;
   //double scoredropchance;
   //double hp;
   //double score;
   //double x, y;
   //double xvel, yvel;
   //double xaccel, yaccel;
   //double rcenterx, rcentery;
   //double rotaccel, rotvel;
   //double radaccel, radvel;
   //double radius;
   //double wcyclesleft;
   //bool active, dead, dissolve, initial;
   //int sprite;
   //int currentwaypoint;
   //int activatecycles;
   //double getX();
   //double getY();
   //double getSprite();
   //bool update(list<Bullet>* bv, Player* p, GameSpace* gs); //returns true if enemy should be deleted.
};


#endif
