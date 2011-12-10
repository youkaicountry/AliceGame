#ifndef _CWAYPOINT__
#define _CWAYPOINT__

class CWayPoint;
#include <vector.h>
#include "neoenemy.h"
#include "gameobject.h"
#include "pather.h"

class CWayPoint
{
   public:
   CWayPoint();
   ~CWayPoint();
   
   void setInitAccel(double x, double y);
   
   void setInitVel(double x, double y);
   
   void setInitRadVel(double v);
   
   void setInitRotVel(double v);
   
   void setCenter(double x, double y);
   
   void setCycleInfo(int cycles, int next, bool nlast);
   
   void setDeathInfo(bool ndeathfinal, int ndeathnextwp);
   
   void setHP(int nhp);
   
   void addSpeedPath(int num, double endx, double endy, double speed, int nextstate, Pather* pa);
   void addTimedPath(int num, double endx, double endy, int cycles, int nextstate, Pather* pa);
   
   void setRotation(double newrotation);
   
   int enter(GameObject* ne, GameSpace* gs);
   int die(GameObject* ne);
   int update(GameObject* ne);
   
   private:
   bool initaccelon;
   double initaccelx;
   double initaccely;
   
   bool initvelon;
   double initvelx;
   double initvely;
   
   bool initradvelon;
   double initradvel;
   
   bool initrotvelon;
   double initrotvel;
   
   double centerx;
   double centery;
   
   int cyclesleft;
   int cyclenextwp;
   bool last;
   
   double endx;
   double endy;
   
   vector<int> barrages;
   vector<int> frequency;
   
   bool hpchange;
   int hp;
   
   bool deathfinal;
   int deathnextwp;
   
   bool rotationchange;
   double rotation;
   double sinetheta;
   double cosinetheta;
   
   bool onpath;
   int pathnum;
   int pathnextstate;
   double npercycle;
   
};
   
#endif
