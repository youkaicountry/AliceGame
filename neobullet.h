#ifndef _NEOBULLET__
#define _NEOBULLET__

class NeoBullet;
#include "gameobject.h"
#include "cwaypoint.h"
#include <list.h>
#include <vector.h>
#include "bullet.h"
#include "player.h"
#include "gamespace.h"

class NeoBullet : public GameObject
{
   public: //writing accessors sucks and I just don't feel like doing it again
   NeoBullet(GameSpace* ngs);
   virtual ~NeoBullet();
};


#endif
