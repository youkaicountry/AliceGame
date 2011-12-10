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
#include "neobullet.h"

//all waypoint functions should return an int that tell which
//waypoint should be executed next, relative to the current in
//the waypoint vector contained in the NeoEnemy.
//in die, put code for when the NeoEnemy dies. to have the NeoEnemy
//actually die, set NeoEnemy.dead to true, and the NeoEnemy will die.
//in enter, put code for when the state is first initiated
//in update, put stuff that happens each update.

NeoBullet::NeoBullet(GameSpace* ngs)
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
   bullet = true;
   sprite = 1;
   currentwaypoint = 0;
   activatecycles = 0;
   initial = true;
   this->gs = ngs;
    return;
}

NeoBullet::~NeoBullet()
{
    //vector<CWayPoint*>::iterator k;
    //for(k=vwaypoints.begin(); k != vwaypoints.end(); k++)
    //{
    //   delete (*k);
    //}
    return;
}
