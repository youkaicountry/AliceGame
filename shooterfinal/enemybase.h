#ifndef _ENEMY__
#define _ENEMY__

#include <vector>

class Waypoint;
class Enemy;

#include "barrage.h"
#include "bullet.h"
#include "gamespace.h"

class Enemy
{
   public: //writing accessors sucks and I just don't feel like doing it again
   Enemy();
   virtual ~Enemy();
   virtual bool isVisible();
   virtual bool isHittable();
   
   vector<Waypoint*> vwaypoints;
   vector<Barrage> vbarrages;
   double dir;
   double powerdropchance;
   double scoredropchance;
   double hp;
   double score;
   double x, y;
   double xvel, yvel;
   double xaccel, yaccel;
   double rcenterx, rcentery;
   double rotaccel, rotvel;
   double radaccel, radvel;
   double radius;
   bool active, dead, dissolve;
   int sprite;
   int currentwaypoint;
   int activatecycles;
   //double getX();
   //double getY();
   //double getSprite();
   virtual bool update(list<Bullet>* bv, Player* p, GameSpace *gs); //returns true if enemy should be deleted.
};

class Waypoint
{
    public:
    int cyclesleft;
    Waypoint();
    virtual ~Waypoint();
    
    virtual int enter(Enemy* e,list<Bullet>* bv, Player* p);
    virtual int die(Enemy* e,list<Bullet>* bv, Player* p);
    virtual int update(Enemy* e,list<Bullet>* bv, Player* p);
    //virtual void barrage(Enemy* e, Bullet* b);
    
};

#endif
