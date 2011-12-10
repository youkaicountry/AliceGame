#ifndef _POWERITEM__
#define _POWERITEM__

#include "player.h"
#include "item.h"

class PowerItem : public Item
{
    public:
        PowerItem(double sx, double sy, double sxvel, double syvel, double sxaccel, double syaccel); //position only one needed. other physics
                                       //values are always the same
        ~PowerItem();
        void onPickup(Player* pl);     //this is run on pickup
};

#endif
