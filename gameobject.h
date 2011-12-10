#ifndef _GAMEOBJECT__
#define _GAMEOBJECT__

class GameObject;
class CWayPoint;
#include <list.h>
#include <vector.h>
//#include "barrage.h"
#include "bullet.h"
#include "player.h"
#include "gamespace.h"
#include "pather.h"

class GameObject
{
   public: //writing accessors sucks and I just don't feel like doing it again
   GameObject();
   virtual ~GameObject();
   virtual void addWayPoint(CWayPoint* wp);
   virtual void copyFrom(GameObject* ne);

   virtual bool isVisible();
   virtual bool isHittable();

   vector<CWayPoint*> vwaypoints;
   //vector<Barrage*> vbarrages;
   double dir;
   double powerdropchance;
   double scoredropchance;
   double hp;
   double damage;
   double endx;
   double endy;
   
   GameSpace* gs;
   
   double rotation;
   double sinetheta;
   double cosinetheta;
   
   Pather* path;
   double npercycle;
   double pathlocation;
   
   double effvelx;
   double effvely;
   
   bool bullet;
   double score;
   double x, y;
   double oldx, oldy;
   double xvel, yvel;
   double xaccel, yaccel;
   double rcenterx, rcentery;
   double rotaccel, rotvel;
   double radaccel, radvel;
   double radius;
   double wcyclesleft;
   bool active, dead, dissolve, initial;
   int sprite;
   int currentwaypoint;
   int activatecycles;
   //double getX();
   //double getY();
   //double getSprite();
   virtual bool update(Player* p, GameSpace* gs); //returns true if enemy should be deleted.
};

#include "cwaypoint.h"

#endif
